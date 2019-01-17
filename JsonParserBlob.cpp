/*
 * JsonParserBlob.cpp
 *
 *  Created on: Abr 2018
 *      Author: raulMrello
 *
 *	JsonParserBlob es el módulo encargado de traducir las estructuras de datos utilizadas en MQLib a mensajes JSON entendidos
 *	por el enlace MQTT y viceversa.
 */
 
#include "JsonParserBlob.h"
  


//------------------------------------------------------------------------------------
//--- PRIVATE TYPES ------------------------------------------------------------------
//------------------------------------------------------------------------------------

/** Macro para imprimir trazas de depuraci�n, siempre que se haya configurado un objeto
 *	Logger v�lido (ej: _debug)
 */
static const char* _MODULE_ = "[JSON]..........";
#define _EXPR_	(debug && !IS_ISR())


namespace Blob {


//---------------------------------------------------------------------------------
//- Param Keys --------------------------------------------------------------------
//---------------------------------------------------------------------------------

enum ParamKeys{
	p_IDTRANS,
	p_HEADER,
	p_TIMESTAMP,
	p_ERROR,
	p_CODE,
	p_DESCR,
	p_ASTCAL,
	p_UPDFLAGS,
	p_EVTFLAGS,
	p_ASTCFG,
	p_LATITUDE,
	p_LONGITUDE,
	p_WDOWDAWNSTART,
	p_WDOWDAWNSTOP,
	p_WDOWDUSKSTART,
	p_WDOWDUSKSTOP,
	p_SEASONCFG,
	p_ENERGY,
	p_MEASPERIOD,
	p_MINMAXDATA,
	p_MIN,
	p_MAX,
	p_THRES,
	p_VOLTAGE,
	p_CURRENT,
	p_PHASE,
	p_PFACTOR,
	p_APOW,
	p_RPOW,
	p_MSPOW,
	p_FREQ,
	p_CALIBDATA,
	p_METERREGS,
	p_MEASREGS,
	p_FLAGS,
	p_ENERGYVALUES,
	p_ACTIVE,
	p_REACTIVE,
	p_MEASUREVALUES,
	p_LIGHT,
	p_ALSDATA,
	p_LUX,
	p_OUTDATA,
	p_MODE,
	p_CURVE,
	p_SAMPLES,
	p_DATA,
	p_NUMACTIONS,
	p_ACTIONS,
	p_ID,
	p_DATE,
	p_TIME,
	p_ASTCORR,
	p_LUXLEVEL,
	p_OUTVALUE,
	p_CFG,
	p_STAT,
	MaxNumParamKeys
};

//------------------------------------------------------------------------------------
static const char *keys[] = {
	"idTrans",
	"header",
	"timestamp",
	"error",
	"code",
	"descr",
	"astcal",
	"updFlags",
	"evtFlags",
	"astCfg",
	"latitude",
	"longitude",
	"wdowDawnStart",
	"wdowDawnStop",
	"wdowDuskStart",
	"wdowDuskStop",
	"seasonCfg",
	"energy",
	"measPeriod",
	"minmaxData",
	"min",
	"max",
	"thres",
	"voltage",
	"current",
	"phase",
	"pfactor",
	"aPow",
	"rPow",
	"msPow",
	"freq",
	"calibData",
	"meterRegs",
	"measRegs",
	"flags",
	"energyValues",
	"active",
	"reactive",
	"measureValues",
	"light",
	"alsData",
	"lux",
	"outData",
	"mode",
	"curve",
	"samples",
	"data",
	"numActions",
	"actions",
	"id",
	"date",
	"time",
	"astCorr",
	"luxLevel",
	"outValue",
	"cfg",
	"stat"
};



//---------------------------------------------------------------------------------
//- Funciones privadas ------------------------------------------------------------
//---------------------------------------------------------------------------------


static bool checkStart(char* sample, const char* mask){
	return ((strncmp(sample, mask, strlen(mask)) == 0)? true : false);
}


/** Declaraci�n de funciones espec�ficas de parseo y decodificaci�n */
static char* parseAstCalCfg(Blob::Response_t<Blob::AstCalCfgData_t>* obj, bool debug);
static char* parseEnergyCfg(Blob::Response_t<Blob::AMCfgData_t>* obj, bool debug);
static char* parseEnergyValue(Blob::Response_t<Blob::AMStatData_t>* obj, bool debug);
static char* parseLightCfg(Blob::Response_t<Blob::LightCfgData_t>* obj, bool debug);
static char* parseLightValue(Blob::Response_t<Blob::LightStatData_t>* obj, bool debug);
static char* parseBootSys(Blob::Response_t<Blob::SysBootData_t>* obj, bool debug);

static void* decodeGetRequest(char* json_data, int* data_len, bool debug);
static void* decodeAstCalSetRequest(char* topic, char* json_data, int* data_len, bool debug);
static void* decodeEnergySetRequest(char* topic, char* json_data, int* data_len, bool debug);
static void* decodeLightCfgSetRequest(char* topic, char* json_data, int* data_len, bool debug);
static void* decodeLightValueSetRequest(char* topic, char* json_data, int* data_len, bool debug);

//------------------------------------------------------------------------------------
//-- PUBLIC METHODS IMPLEMENTATION ---------------------------------------------------
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void* DecodeJson(char* topic, char* json_data, int* data_len, bool debug){
	if(checkStart(topic, "set/cfg/astcal")){
		return decodeAstCalSetRequest(topic, json_data, data_len, debug);
	}


	if(checkStart(topic, "set/cfg/energy")){
		return decodeEnergySetRequest(topic, json_data, data_len, debug);
	}


	if(checkStart(topic, "set/cfg/light")){
		return decodeLightCfgSetRequest(topic, json_data, data_len, debug);
	}


	if(checkStart(topic, "set/value/light")){
		return decodeLightValueSetRequest(topic, json_data, data_len, debug);
	}

	if(checkStart(topic, "get/cfg/energy") || checkStart(topic, "get/value/energy") || checkStart(topic, "get/cfg/light") ||
	   checkStart(topic, "get/value/light") || checkStart(topic, "get/cfg/astcal")){
		return decodeGetRequest(json_data, data_len, debug);
	}
	DEBUG_TRACE_E(_EXPR_, _MODULE_, "ERR_DECODE Topic=%s no coincide con ninguna opción", topic);
	return NULL;
}


//------------------------------------------------------------------------------------
char* ParseJson(char* topic, void* data, int data_len, bool debug){
	char* result = NULL;
	Blob::ErrorData_t err;
	err.code = Blob::ErrOK;
	strcpy(err.descr, Blob::errList[err.code]);

	if(checkStart(topic, "stat/cfg/astcal")){
		if(data_len == sizeof(Blob::Response_t<Blob::AstCalCfgData_t>)){
			Blob::Response_t<Blob::AstCalCfgData_t>* obj = (Blob::Response_t<Blob::AstCalCfgData_t>*)data;
			return parseAstCalCfg(obj, debug);
		}
		if(data_len == sizeof(Blob::AstCalCfgData_t)){ //uint32_t idt, const Blob::ErrorData_t& err, const T& dat
			Blob::Response_t<Blob::AstCalCfgData_t>* obj = new Blob::Response_t<Blob::AstCalCfgData_t>(Blob::UnusedIdTrans, err, *(Blob::AstCalCfgData_t*)data);
			MBED_ASSERT(obj);
			obj->header.timestamp = time(NULL);
			result = parseAstCalCfg(obj, debug);
			delete(obj);
			return result;
		}
		return NULL;
	}

	if(checkStart(topic, "stat/cfg/energy")){
		if(data_len == sizeof(Blob::Response_t<Blob::AMCfgData_t>)){
			Blob::Response_t<Blob::AMCfgData_t>* obj = (Blob::Response_t<Blob::AMCfgData_t>*)data;
			return parseEnergyCfg(obj, debug);
		}
		if(data_len == sizeof(Blob::AMCfgData_t)){
			Blob::Response_t<Blob::AMCfgData_t>* obj = new Blob::Response_t<Blob::AMCfgData_t>(Blob::UnusedIdTrans, err, *(Blob::AMCfgData_t*)data);
			MBED_ASSERT(obj);
			obj->header.timestamp = time(NULL);
			result = parseEnergyCfg(obj, debug);
			delete(obj);
			return result;
		}
		return NULL;
	}

	if(checkStart(topic, "stat/value/energy")){
		if(data_len == sizeof(Blob::Response_t<Blob::AMStatData_t>)){
			Blob::Response_t<Blob::AMStatData_t>* obj = (Blob::Response_t<Blob::AMStatData_t>*)data;
			return parseEnergyValue(obj, debug);
		}
		if(data_len == sizeof(Blob::AMStatData_t)){
			Blob::Response_t<Blob::AMStatData_t>* obj = new Blob::Response_t<Blob::AMStatData_t>(Blob::UnusedIdTrans, err, *(Blob::AMStatData_t*)data);
			MBED_ASSERT(obj);
			obj->header.timestamp = time(NULL);
			result = parseEnergyValue(obj, debug);
			delete(obj);
			return result;
		}
		return NULL;
	}

	if(checkStart(topic, "stat/cfg/light")){
		if(data_len == sizeof(Blob::Response_t<Blob::LightCfgData_t>)){
			Blob::Response_t<Blob::LightCfgData_t>* obj = (Blob::Response_t<Blob::LightCfgData_t>*)data;
			return parseLightCfg(obj, debug);
		}
		if(data_len == sizeof(Blob::LightCfgData_t)){
			Blob::Response_t<Blob::LightCfgData_t>* obj = new Blob::Response_t<Blob::LightCfgData_t>(Blob::UnusedIdTrans, err, *(Blob::LightCfgData_t*)data);
			MBED_ASSERT(obj);
			obj->header.timestamp = time(NULL);
			result = parseLightCfg(obj, debug);
			delete(obj);
			return result;
		}
		return NULL;
	}

	if(checkStart(topic, "stat/value/light")){
		if(data_len == sizeof(Blob::Response_t<Blob::LightStatData_t>)){
			Blob::Response_t<Blob::LightStatData_t>* obj = (Blob::Response_t<Blob::LightStatData_t>*)data;
			return parseLightValue(obj, debug);
		}
		if(data_len == sizeof(Blob::LightStatData_t)){
			Blob::Response_t<Blob::LightStatData_t>* obj = new Blob::Response_t<Blob::LightStatData_t>(Blob::UnusedIdTrans, err, *(Blob::LightStatData_t*)data);
			MBED_ASSERT(obj);
			obj->header.timestamp = time(NULL);
			result = parseLightValue(obj, debug);
			delete(obj);
			return result;
		}
		return NULL;
	}

	if(checkStart(topic, "stat/boot/sys")){
		if(data_len != sizeof(Blob::SysBootData_t))
			return NULL;
		Blob::Response_t<Blob::SysBootData_t>* obj = new Blob::Response_t<Blob::SysBootData_t>(Blob::UnusedIdTrans, err, *(Blob::SysBootData_t*)data);
		MBED_ASSERT(obj);
		obj->header.timestamp = time(NULL);
		result = parseBootSys(obj, debug);
		delete(obj);
		return result;
	}

	return NULL;
}



//------------------------------------------------------------------------------------
//-- STATIC METHODS IMPLEMENTATION ---------------------------------------------------
//------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------
static bool encodeAstCalCfg(cJSON* astcal, const Blob::AstCalCfgData_t& data){
	cJSON* value = NULL;
	// key: astcal.updFlags
	cJSON_AddNumberToObject(astcal, keys[p_UPDFLAGS], data.updFlagMask);
	// key: astcal.evtFlags
	cJSON_AddNumberToObject(astcal, keys[p_EVTFLAGS], data.evtFlagMask);
	// key: astCfg
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_LATITUDE], data.astCfg.latitude);
	cJSON_AddNumberToObject(value, keys[p_LONGITUDE], data.astCfg.longitude);
	cJSON_AddNumberToObject(value, keys[p_WDOWDAWNSTART], data.astCfg.wdowDawnStart);
	cJSON_AddNumberToObject(value, keys[p_WDOWDAWNSTOP], data.astCfg.wdowDawnStop);
	cJSON_AddNumberToObject(value, keys[p_WDOWDUSKSTART], data.astCfg.wdowDuskStart);
	cJSON_AddNumberToObject(value, keys[p_WDOWDUSKSTOP], data.astCfg.wdowDuskStop);
	cJSON_AddItemToObject(astcal, keys[p_ASTCFG], value);
	// key: seasonCfg
	if((value=cJSON_CreateString(data.seasonCfg.envText)) == NULL){
		return false;
	}
	cJSON_AddItemToObject(astcal, keys[p_SEASONCFG], value);
	return true;
}


//------------------------------------------------------------------------------------
static char* parseAstCalCfg(Blob::Response_t<Blob::AstCalCfgData_t>* obj, bool debug){
	char* result = NULL;
	// keys: root, idtrans, header, error, astcal
	cJSON *header = NULL;
	cJSON *error = NULL;
	cJSON *astcal = NULL;
	cJSON *value = NULL;
	cJSON *root = cJSON_CreateObject();

	if(!root){
		return result;
	}

	// key: idTrans sólo se envía si está en uso
	if(obj->idTrans != Blob::UnusedIdTrans){
		cJSON_AddNumberToObject(root, keys[p_IDTRANS], obj->idTrans);
	}

	// key: header
	if((header=cJSON_CreateObject()) == NULL){
		goto _parseAstCalCfg_Exit;
	}
	cJSON_AddNumberToObject(header, keys[p_TIMESTAMP], obj->header.timestamp);
	cJSON_AddItemToObject(root, keys[p_HEADER], header);

	// key: error sólo se envía si el error es distinto de Blob::ErrOK
	if(obj->error.code != Blob::ErrOK){
		if((error=cJSON_CreateObject()) == NULL){
			goto _parseAstCalCfg_Exit;
		}
		cJSON_AddNumberToObject(error, keys[p_CODE], obj->error.code);
		if((value=cJSON_CreateString(obj->error.descr)) == NULL){
			goto _parseAstCalCfg_Exit;
		}
		cJSON_AddItemToObject(error, keys[p_DESCR], value);
		// añade objeto
		cJSON_AddItemToObject(root, keys[p_ERROR], error);
	}

	// key: astcal sólo se envía si el error es Blob::ErrOK
	if(obj->error.code == Blob::ErrOK){
		if((astcal=cJSON_CreateObject()) == NULL){
			goto _parseAstCalCfg_Exit;
		}
		if(!encodeAstCalCfg(astcal, obj->data)){
			goto _parseAstCalCfg_Exit;
		}
		// añade objeto
		cJSON_AddItemToObject(root, keys[p_ASTCAL], astcal);
	}

	result = cJSON_Print(root);

_parseAstCalCfg_Exit:
	if(root)
		cJSON_Delete(root);
	return result;
}


//------------------------------------------------------------------------------------
static bool encodeEnergyCfg(cJSON* energy, const Blob::AMCfgData_t& data){
	cJSON *minmaxData = NULL;
	cJSON *calibData = NULL;
	cJSON *regs = NULL;
	cJSON *value = NULL;
	// key: energy.updFlags
	cJSON_AddNumberToObject(energy, keys[p_UPDFLAGS], data.updFlagMask);

	// key: energy.evtFlags
	cJSON_AddNumberToObject(energy, keys[p_EVTFLAGS], data.evtFlagMask);

	// key: energy.measPeriod
	cJSON_AddNumberToObject(energy, keys[p_MEASPERIOD], data.measPeriod);

	// key: minmaxData
	if((minmaxData=cJSON_CreateObject()) == NULL){
		return false;
	}

	// key: minmaxData.voltage
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_MIN], data.minmaxData.voltage.min);
	cJSON_AddNumberToObject(value, keys[p_MAX], data.minmaxData.voltage.max);
	cJSON_AddNumberToObject(value, keys[p_THRES], data.minmaxData.voltage.thres);
	cJSON_AddItemToObject(minmaxData, keys[p_VOLTAGE], value);

	// key: minmaxData.current
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_MIN], data.minmaxData.current.min);
	cJSON_AddNumberToObject(value, keys[p_MAX], data.minmaxData.current.max);
	cJSON_AddNumberToObject(value, keys[p_THRES], data.minmaxData.current.thres);
	cJSON_AddItemToObject(minmaxData, keys[p_CURRENT], value);

	// key: minmaxData.phase
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_MIN], data.minmaxData.phase.min);
	cJSON_AddNumberToObject(value, keys[p_MAX], data.minmaxData.phase.max);
	cJSON_AddNumberToObject(value, keys[p_THRES], data.minmaxData.phase.thres);
	cJSON_AddItemToObject(minmaxData, keys[p_PHASE], value);

	// key: minmaxData.pfactor
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_MIN], data.minmaxData.pfactor.min);
	cJSON_AddNumberToObject(value, keys[p_MAX], data.minmaxData.pfactor.max);
	cJSON_AddNumberToObject(value, keys[p_THRES], data.minmaxData.pfactor.thres);
	cJSON_AddItemToObject(minmaxData, keys[p_PFACTOR], value);

	// key: minmaxData.aPow
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_MIN], data.minmaxData.aPow.min);
	cJSON_AddNumberToObject(value, keys[p_MAX], data.minmaxData.aPow.max);
	cJSON_AddNumberToObject(value, keys[p_THRES], data.minmaxData.aPow.thres);
	cJSON_AddItemToObject(minmaxData, keys[p_APOW], value);

	// key: minmaxData.rPow
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_MIN], data.minmaxData.rPow.min);
	cJSON_AddNumberToObject(value, keys[p_MAX], data.minmaxData.rPow.max);
	cJSON_AddNumberToObject(value, keys[p_THRES], data.minmaxData.rPow.thres);
	cJSON_AddItemToObject(minmaxData, keys[p_RPOW], value);

	// key: minmaxData.msPow
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_MIN], data.minmaxData.msPow.min);
	cJSON_AddNumberToObject(value, keys[p_MAX], data.minmaxData.msPow.max);
	cJSON_AddNumberToObject(value, keys[p_THRES], data.minmaxData.msPow.thres);
	cJSON_AddItemToObject(minmaxData, keys[p_MSPOW], value);

	// key: minmaxData.freq
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_MIN], data.minmaxData.freq.min);
	cJSON_AddNumberToObject(value, keys[p_MAX], data.minmaxData.freq.max);
	cJSON_AddNumberToObject(value, keys[p_THRES], data.minmaxData.freq.thres);
	cJSON_AddItemToObject(minmaxData, keys[p_FREQ], value);

	cJSON_AddItemToObject(energy, keys[p_MINMAXDATA], minmaxData);

	// key: calibData
	if((calibData=cJSON_CreateObject()) == NULL){
		return false;
	}

	// key: calibData.meterRegs
	if((regs=cJSON_CreateArray()) == NULL){
		return false;
	}
	for(int i=0; i < Blob::AMCalibRegCount; i++){
		if((value = cJSON_CreateNumber(data.calibData.meterRegs[i])) == NULL){
			return false;
		}
		cJSON_AddItemToArray(regs, value);
	}
	cJSON_AddItemToObject(calibData, keys[p_METERREGS], regs);

	// key: calibData.measRegs
	if((regs=cJSON_CreateArray()) == NULL){
		return false;
	}
	for(int i=0; i < Blob::AMCalibRegCount; i++){
		if((value = cJSON_CreateNumber(data.calibData.measRegs[i])) == NULL){
			return false;
		}
		cJSON_AddItemToArray(regs, value);
	}
	cJSON_AddItemToObject(calibData, keys[p_MEASREGS], regs);
	cJSON_AddItemToObject(energy, keys[p_CALIBDATA], calibData);
	return true;
}


//------------------------------------------------------------------------------------
static char* parseEnergyCfg(Blob::Response_t<Blob::AMCfgData_t>* obj, bool debug){
	char* result = NULL;
	// keys: root, idtrans, header, error, astcal
	cJSON *header = NULL;
	cJSON *error = NULL;
	cJSON *energy = NULL;
	cJSON *value = NULL;
	cJSON *root = cJSON_CreateObject();

	if(!root){
		return result;
	}

	// key: idTrans sólo se envía si está en uso
	if(obj->idTrans != Blob::UnusedIdTrans){
		cJSON_AddNumberToObject(root, keys[p_IDTRANS], obj->idTrans);
	}

	// key: header
	if((header=cJSON_CreateObject()) == NULL){
		goto _parseEnergyCfg_Exit;
	}
	cJSON_AddNumberToObject(header, keys[p_TIMESTAMP], obj->header.timestamp);
	cJSON_AddItemToObject(root, keys[p_HEADER], header);

	// key: error sólo se envía si el error es distinto de Blob::ErrOK
	if(obj->error.code != Blob::ErrOK){
		if((error=cJSON_CreateObject()) == NULL){
			goto _parseEnergyCfg_Exit;
		}
		cJSON_AddNumberToObject(error, keys[p_CODE], obj->error.code);
		if((value=cJSON_CreateString(obj->error.descr)) == NULL){
			goto _parseEnergyCfg_Exit;
		}
		cJSON_AddItemToObject(error, keys[p_DESCR], value);
		// añade objeto
		cJSON_AddItemToObject(root, keys[p_ERROR], error);
	}

	// key: energy sólo se envía si el error es Blob::ErrOK
	if(obj->error.code == Blob::ErrOK){
		if((energy=cJSON_CreateObject()) == NULL){
			goto _parseEnergyCfg_Exit;
		}
		if(!encodeEnergyCfg(energy, obj->data)){
			goto _parseEnergyCfg_Exit;
		}
		// añade objeto
		cJSON_AddItemToObject(root, keys[p_ENERGY], energy);
	}

	result = cJSON_Print(root);

_parseEnergyCfg_Exit:
	if(root)
		cJSON_Delete(root);
	return result;
}


//------------------------------------------------------------------------------------
static bool encodeEnergyStat(cJSON* energy, const Blob::AMStatData_t& data){
	cJSON *value = NULL;
	// key: flags
	cJSON_AddNumberToObject(energy, keys[p_FLAGS], data.flags);

	// key: energyValues
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_ACTIVE], data.energyValues.active);
	cJSON_AddNumberToObject(value, keys[p_REACTIVE], data.energyValues.reactive);
	cJSON_AddItemToObject(energy, keys[p_ENERGYVALUES], value);

	// key: measureValues
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_VOLTAGE], data.measureValues.voltage);
	cJSON_AddNumberToObject(value, keys[p_CURRENT], data.measureValues.current);
	cJSON_AddNumberToObject(value, keys[p_PHASE], data.measureValues.phase);
	cJSON_AddNumberToObject(value, keys[p_PFACTOR], data.measureValues.pfactor);
	cJSON_AddNumberToObject(value, keys[p_APOW], data.measureValues.aPow);
	cJSON_AddNumberToObject(value, keys[p_RPOW], data.measureValues.rPow);
	cJSON_AddNumberToObject(value, keys[p_MSPOW], data.measureValues.msPow);
	cJSON_AddNumberToObject(value, keys[p_FREQ], data.measureValues.freq);
	cJSON_AddItemToObject(energy, keys[p_MEASUREVALUES], value);
	return true;
}


//------------------------------------------------------------------------------------
static char* parseEnergyValue(Blob::Response_t<Blob::AMStatData_t>* obj, bool debug){
	char* result = NULL;
	// keys: root, idtrans, header, error, astcal
	cJSON *header = NULL;
	cJSON *error = NULL;
	cJSON *energy = NULL;
	cJSON *value = NULL;
	cJSON *root = cJSON_CreateObject();

	if(!root){
		return result;
	}

	// key: idTrans sólo se envía si está en uso
	if(obj->idTrans != Blob::UnusedIdTrans){
		cJSON_AddNumberToObject(root, keys[p_IDTRANS], obj->idTrans);
	}

	// key: header
	if((header=cJSON_CreateObject()) == NULL){
		goto _parseEnergyValue_Exit;
	}
	cJSON_AddNumberToObject(header, keys[p_TIMESTAMP], obj->header.timestamp);
	cJSON_AddItemToObject(root, keys[p_HEADER], header);

	// key: error sólo se envía si el error es distinto de Blob::ErrOK
	if(obj->error.code != Blob::ErrOK){
		if((error=cJSON_CreateObject()) == NULL){
			goto _parseEnergyValue_Exit;
		}
		cJSON_AddNumberToObject(error, keys[p_CODE], obj->error.code);
		if((value=cJSON_CreateString(obj->error.descr)) == NULL){
			goto _parseEnergyValue_Exit;
		}
		cJSON_AddItemToObject(error, keys[p_DESCR], value);
		// añade objeto
		cJSON_AddItemToObject(root, keys[p_ERROR], error);
	}

	// key: energy sólo se envía si el error es Blob::ErrOK
	if(obj->error.code == Blob::ErrOK){
		if((energy=cJSON_CreateObject()) == NULL){
			goto _parseEnergyValue_Exit;
		}
		if(!encodeEnergyStat(energy, obj->data)){
			goto _parseEnergyValue_Exit;
		}

		// añade objeto
		cJSON_AddItemToObject(root, keys[p_ENERGY], energy);
	}

	result = cJSON_Print(root);

_parseEnergyValue_Exit:
	if(root)
		cJSON_Delete(root);
	return result;
}


//------------------------------------------------------------------------------------
static bool encodeLightCfg(cJSON* light, const Blob::LightCfgData_t& data){
	cJSON *alsData = NULL;
	cJSON *outData = NULL;
	cJSON *curve = NULL;
	cJSON *array = NULL;
	cJSON *value = NULL;
	cJSON *luxLevel = NULL;

	// key: light.updFlags
	cJSON_AddNumberToObject(light, keys[p_UPDFLAGS], data.updFlagMask);

	// key: light.evtFlags
	cJSON_AddNumberToObject(light, keys[p_EVTFLAGS], data.evtFlagMask);

	// key: alsData
	if((alsData=cJSON_CreateObject()) == NULL){
		return false;
	}

	// key: alsData.lux
	if((value=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(value, keys[p_MIN], data.alsData.lux.min);
	cJSON_AddNumberToObject(value, keys[p_MAX], data.alsData.lux.max);
	cJSON_AddNumberToObject(value, keys[p_THRES], data.alsData.lux.thres);
	cJSON_AddItemToObject(alsData, keys[p_LUX], value);
	cJSON_AddItemToObject(light, keys[p_ALSDATA], alsData);

	// key: outData
	if((outData=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(outData, keys[p_MODE], data.outData.mode);
	cJSON_AddNumberToObject(outData, keys[p_NUMACTIONS], data.outData.numActions);

	// key: outData.curve
	if((curve=cJSON_CreateObject()) == NULL){
		return false;
	}
	cJSON_AddNumberToObject(curve, keys[p_SAMPLES], data.outData.curve.samples);

	// key: outData.curve.data
	if((array=cJSON_CreateArray()) == NULL){
		return false;
	}
	for(int i=0; i < Blob::LightCurveSampleCount; i++){
		if((value = cJSON_CreateNumber(data.outData.curve.data[i])) == NULL){
			return false;
		}
		cJSON_AddItemToArray(array, value);
	}
	cJSON_AddItemToObject(curve, keys[p_DATA], array);
	cJSON_AddItemToObject(outData, keys[p_CURVE], curve);

	// key: outData.actions
	if((array=cJSON_CreateArray()) == NULL){
		return false;
	}
	for(int i=0; i < data.outData.numActions; i++){
		if((value = cJSON_CreateObject()) == NULL){
			return false;
		}
		cJSON_AddNumberToObject(value, keys[p_ID], data.outData.actions[i].id);
		cJSON_AddNumberToObject(value, keys[p_FLAGS], data.outData.actions[i].flags);
		cJSON_AddNumberToObject(value, keys[p_DATE], data.outData.actions[i].date);
		cJSON_AddNumberToObject(value, keys[p_TIME], data.outData.actions[i].time);
		cJSON_AddNumberToObject(value, keys[p_ASTCORR], data.outData.actions[i].astCorr);
		cJSON_AddNumberToObject(value, keys[p_OUTVALUE], data.outData.actions[i].outValue);
		if((luxLevel=cJSON_CreateObject()) == NULL){
			return false;
		}
		cJSON_AddNumberToObject(luxLevel, keys[p_MIN], data.outData.actions[i].luxLevel.min);
		cJSON_AddNumberToObject(luxLevel, keys[p_MAX], data.outData.actions[i].luxLevel.max);
		cJSON_AddNumberToObject(luxLevel, keys[p_THRES], data.outData.actions[i].luxLevel.thres);
		cJSON_AddItemToObject(value, keys[p_LUXLEVEL], luxLevel);
		cJSON_AddItemToArray(array, value);
	}
	cJSON_AddItemToObject(outData, keys[p_ACTIONS], array);
	cJSON_AddItemToObject(light, keys[p_OUTDATA], outData);
	return true;
}


//------------------------------------------------------------------------------------
static char* parseLightCfg(Blob::Response_t<Blob::LightCfgData_t>* obj, bool debug){
	char* result = NULL;
	// keys: root, idtrans, header, error, astcal
	cJSON *header = NULL;
	cJSON *error = NULL;
	cJSON *light = NULL;
	cJSON *value = NULL;
	cJSON *root = cJSON_CreateObject();

	if(!root){
		return result;
	}

	// key: idTrans sólo se envía si está en uso
	if(obj->idTrans != Blob::UnusedIdTrans){
		cJSON_AddNumberToObject(root, keys[p_IDTRANS], obj->idTrans);
	}

	// key: header
	if((header=cJSON_CreateObject()) == NULL){
		goto _parseLightCfg_Exit;
	}
	cJSON_AddNumberToObject(header, keys[p_TIMESTAMP], obj->header.timestamp);
	cJSON_AddItemToObject(root, keys[p_HEADER], header);

	// key: error sólo se envía si el error es distinto de Blob::ErrOK
	if(obj->error.code != Blob::ErrOK){
		if((error=cJSON_CreateObject()) == NULL){
			goto _parseLightCfg_Exit;
		}
		cJSON_AddNumberToObject(error, keys[p_CODE], obj->error.code);
		if((value=cJSON_CreateString(obj->error.descr)) == NULL){
			goto _parseLightCfg_Exit;
		}
		cJSON_AddItemToObject(error, keys[p_DESCR], value);
		// añade objeto
		cJSON_AddItemToObject(root, keys[p_ERROR], error);
	}

	// key: light sólo se envía si el error es Blob::ErrOK
	if(obj->error.code == Blob::ErrOK){
		if((light=cJSON_CreateObject()) == NULL){
			goto _parseLightCfg_Exit;
		}
		if(!encodeLightCfg(light, obj->data)){
			goto _parseLightCfg_Exit;
		}

		cJSON_AddItemToObject(root, keys[p_LIGHT], light);
	}

	result = cJSON_Print(root);

_parseLightCfg_Exit:
	if(root)
		cJSON_Delete(root);
	return result;
}


//------------------------------------------------------------------------------------
static bool encodeLightStat(cJSON* light, const Blob::LightStatData_t& data){

	// key: light.updFlags
	cJSON_AddNumberToObject(light, keys[p_FLAGS], data.flags);

	// key: light.evtFlags
	cJSON_AddNumberToObject(light, keys[p_OUTVALUE], data.outValue);
	return true;
}

//------------------------------------------------------------------------------------
static char* parseLightValue(Blob::Response_t<Blob::LightStatData_t>* obj, bool debug){
	char* result = NULL;
	// keys: root, idtrans, header, error, astcal
	cJSON *header = NULL;
	cJSON *error = NULL;
	cJSON *light = NULL;
	cJSON *value = NULL;
	cJSON *root = cJSON_CreateObject();

	if(!root){
		return result;
	}

	// key: idTrans sólo se envía si está en uso
	if(obj->idTrans != Blob::UnusedIdTrans){
		cJSON_AddNumberToObject(root, keys[p_IDTRANS], obj->idTrans);
	}

	// key: header
	if((header=cJSON_CreateObject()) == NULL){
		goto _parseLightValue_Exit;
	}
	cJSON_AddNumberToObject(header, keys[p_TIMESTAMP], obj->header.timestamp);
	cJSON_AddItemToObject(root, keys[p_HEADER], header);

	// key: error sólo se envía si el error es distinto de Blob::ErrOK
	if(obj->error.code != Blob::ErrOK){
		if((error=cJSON_CreateObject()) == NULL){
			goto _parseLightValue_Exit;
		}
		cJSON_AddNumberToObject(error, keys[p_CODE], obj->error.code);
		if((value=cJSON_CreateString(obj->error.descr)) == NULL){
			goto _parseLightValue_Exit;
		}
		cJSON_AddItemToObject(error, keys[p_DESCR], value);
		// añade objeto
		cJSON_AddItemToObject(root, keys[p_ERROR], error);
	}

	// key: energy sólo se envía si el error es Blob::ErrOK
	if(obj->error.code == Blob::ErrOK){
		if((light=cJSON_CreateObject()) == NULL){
			goto _parseLightValue_Exit;
		}

		if(!encodeLightStat(light, obj->data)){
			goto _parseLightValue_Exit;
		}
		cJSON_AddItemToObject(root, keys[p_LIGHT], light);
	}

	result = cJSON_Print(root);

_parseLightValue_Exit:
	if(root)
		cJSON_Delete(root);
	return result;

}


//------------------------------------------------------------------------------------
static char* parseBootSys(Blob::Response_t<Blob::SysBootData_t>* obj, bool debug){
	char* result = NULL;
	// keys: root, idtrans, header, error, astcal
	cJSON *header = NULL;
	cJSON *light = NULL;
	cJSON *energy = NULL;
	cJSON *astcal = NULL;
	cJSON *value = NULL;
	cJSON *root = cJSON_CreateObject();

	if(!root){
		return result;
	}

	// key: header
	if((header=cJSON_CreateObject()) == NULL){
		goto _parseBootSys_Exit;
	}
	cJSON_AddNumberToObject(header, keys[p_TIMESTAMP], obj->header.timestamp);
	cJSON_AddItemToObject(root, keys[p_HEADER], header);

	// key: light
	if((light=cJSON_CreateObject()) == NULL){
		goto _parseBootSys_Exit;
	}

	if((value=cJSON_CreateObject()) == NULL){
		goto _parseBootSys_Exit;
	}
	if(!encodeLightCfg(value, obj->data.lightBoot.cfg)){
		goto _parseBootSys_Exit;
	}
	cJSON_AddItemToObject(light, keys[p_CFG], value);

	if((value=cJSON_CreateObject()) == NULL){
		goto _parseBootSys_Exit;
	}
	if(!encodeLightStat(value, obj->data.lightBoot.stat)){
		goto _parseBootSys_Exit;
	}
	cJSON_AddItemToObject(light, keys[p_STAT], value);
	cJSON_AddItemToObject(root, keys[p_LIGHT], light);

	// key: energy
	if((energy=cJSON_CreateObject()) == NULL){
		goto _parseBootSys_Exit;
	}

	if((value=cJSON_CreateObject()) == NULL){
		goto _parseBootSys_Exit;
	}
	if(!encodeEnergyCfg(value, obj->data.amBoot.cfg)){
		goto _parseBootSys_Exit;
	}
	cJSON_AddItemToObject(energy, keys[p_CFG], value);

	if((value=cJSON_CreateObject()) == NULL){
		goto _parseBootSys_Exit;
	}
	if(!encodeEnergyStat(value, obj->data.amBoot.stat)){
		goto _parseBootSys_Exit;
	}
	cJSON_AddItemToObject(energy, keys[p_STAT], value);
	cJSON_AddItemToObject(root, keys[p_ENERGY], energy);

	// key: astcal
	if((astcal=cJSON_CreateObject()) == NULL){
		goto _parseBootSys_Exit;
	}

	if((value=cJSON_CreateObject()) == NULL){
		goto _parseBootSys_Exit;
	}
	if(!encodeAstCalCfg(value, obj->data.astBoot.cfg)){
		goto _parseBootSys_Exit;
	}
	cJSON_AddItemToObject(astcal, keys[p_CFG], value);
	cJSON_AddItemToObject(root, keys[p_ASTCAL], astcal);

	result = cJSON_Print(root);

_parseBootSys_Exit:
	if(root)
		cJSON_Delete(root);
	return result;
}


//------------------------------------------------------------------------------------
static void* decodeAstCalSetRequest(char* topic, char* json_data, int* data_len, bool debug){
	cJSON *obj = NULL;
	cJSON *astcal = NULL;
	cJSON *astcfg = NULL;
	cJSON *root = NULL;
	DEBUG_TRACE_D(_EXPR_, _MODULE_, "Procesando topic [%s]", topic);
	SetRequest_t<AstCalCfgData_t>* data = (SetRequest_t<AstCalCfgData_t>*)Heap::memAlloc(sizeof(SetRequest_t<AstCalCfgData_t>));
	MBED_ASSERT(data);
	*data_len = sizeof(SetRequest_t<AstCalCfgData_t>);
	data->data.keys = Blob::AstCalKeyNone;
	data->_error.code = Blob::ErrOK;

	if((root = cJSON_Parse(json_data)) == NULL){
		data->_error.code = ErrJsonMalformed;
		data->idTrans = Blob::UnusedIdTrans;
		goto __decode_null_exitAstCalCfg;
	}

	// key: idTrans
	if((obj = cJSON_GetObjectItem(root, keys[p_IDTRANS])) == NULL){
		data->_error.code = ErrIdTransInvalid;
		data->idTrans = Blob::UnusedIdTrans;
		goto __decode_null_exitAstCalCfg;
	}
	data->idTrans = obj->valueint;

	// key:astcal
	if((astcal = cJSON_GetObjectItem(root, keys[p_ASTCAL])) == NULL){
		data->_error.code = ErrAstCalMissing;
		goto __decode_null_exitAstCalCfg;
	}

	if((obj = cJSON_GetObjectItem(astcal,keys[p_UPDFLAGS])) != NULL){
		data->data.updFlagMask = (Blob::AstCalUpdFlags)obj->valueint;
		data->data.keys |= Blob::AstCalKeyCfgUpd;
	}
	if((obj = cJSON_GetObjectItem(astcal,keys[p_EVTFLAGS])) != NULL){
		data->data.evtFlagMask = (Blob::AstCalEvtFlags)obj->valueint;
		data->data.keys |= Blob::AstCalKeyCfgEvt;
	}
	if((obj = cJSON_GetObjectItem(astcal, keys[p_SEASONCFG])) != NULL){
		char* seas_cfg = obj->valuestring;
		if(!seas_cfg || strlen(seas_cfg) >= Blob::LengthOfSeasonEnvText){
			data->_error.code = ErrSeasonCfgFormat;
			goto __decode_null_exitAstCalCfg;
		}
		strcpy(data->data.seasonCfg.envText, seas_cfg);
		data->data.keys |= Blob::AstCalKeyCfgSeason;
	}

	if((astcfg = cJSON_GetObjectItem(astcal, keys[p_ASTCFG])) != NULL){
		if((obj = cJSON_GetObjectItem(astcfg, keys[p_LATITUDE])) != NULL){
			data->data.astCfg.latitude = obj->valueint;
			data->data.keys |= Blob::AstCalKeyCfgLat;
		}
		if((obj = cJSON_GetObjectItem(astcfg,keys[p_LONGITUDE])) != NULL){
			data->data.astCfg.longitude = obj->valueint;
			data->data.keys |= Blob::AstCalKeyCfgLon;
		}
		if((obj = cJSON_GetObjectItem(astcfg,keys[p_WDOWDAWNSTART])) != NULL){
			data->data.astCfg.wdowDawnStart = obj->valueint;
			data->data.keys |= Blob::AstCalKeyCfgWdaSta;
		}
		if((obj = cJSON_GetObjectItem(astcfg,keys[p_WDOWDAWNSTOP])) != NULL){
			data->data.astCfg.wdowDawnStop = obj->valueint;
			data->data.keys |= Blob::AstCalKeyCfgWdaStp;
		}
		if((obj = cJSON_GetObjectItem(astcfg,keys[p_WDOWDUSKSTART])) != NULL){
			data->data.astCfg.wdowDuskStart = obj->valueint;
			data->data.keys |= Blob::AstCalKeyCfgWduSta;
		}
		if((obj = cJSON_GetObjectItem(astcfg,keys[p_WDOWDUSKSTOP])) != NULL){
			data->data.astCfg.wdowDuskStop = obj->valueint;
			data->data.keys |= Blob::AstCalKeyCfgWduStp;
		}
	}

__decode_null_exitAstCalCfg:
	strcpy(data->_error.descr, errList[data->_error.code]);
	DEBUG_TRACE_I(_EXPR_, _MODULE_, "Parseado topic [%s] con resultado %s", topic, data->_error.descr);
	if(root){
		cJSON_Delete(root);
	}
	return data;
}


//------------------------------------------------------------------------------------
static void* decodeGetRequest(char* json_data, int* data_len, bool debug){
	cJSON *root = NULL;
	DEBUG_TRACE_D(_EXPR_, _MODULE_, "Procesando GetRequest");
	Blob::GetRequest_t* data = (Blob::GetRequest_t*)Heap::memAlloc(sizeof(Blob::GetRequest_t));
	MBED_ASSERT(data);
	data->idTrans = 0;
	data->_error.code = ErrJsonMalformed;
	*data_len = sizeof(Blob::GetRequest_t);

	// json_data = {"idTrans": xxx}
	if((root = cJSON_Parse(json_data)) != NULL){
		cJSON *idtrans = NULL;
		if((idtrans = cJSON_GetObjectItem(root, keys[p_IDTRANS])) != NULL){
			data->idTrans = idtrans->valueint;
			data->_error.code = Blob::ErrOK;
			goto _decodeGetRequest_Exit;
		}
		data->_error.code = ErrIdTransInvalid;
	}
_decodeGetRequest_Exit:
	strcpy(data->_error.descr, errList[data->_error.code]);
	if(root){
		cJSON_Delete(root);
	}
	return data;
}

//------------------------------------------------------------------------------------
static void* decodeEnergySetRequest(char* topic, char* json_data, int* data_len, bool debug){
	cJSON *obj = NULL;
	cJSON *value = NULL;
	cJSON *array = NULL;
	cJSON *energy = NULL;
	cJSON *minmaxData = NULL;
	cJSON *calibData = NULL;
	cJSON *root = NULL;
	DEBUG_TRACE_D(_EXPR_, _MODULE_, "Procesando topic [%s]", topic);
	SetRequest_t<AMCfgData_t>* data = (SetRequest_t<AMCfgData_t>*)Heap::memAlloc(sizeof(SetRequest_t<AMCfgData_t>));
	MBED_ASSERT(data);
	*data_len = sizeof(SetRequest_t<AMCfgData_t>);
	data->data.keys = Blob::AMKeyNone;
	data->_error.code = Blob::ErrOK;

	if((root = cJSON_Parse(json_data)) == NULL){
		data->_error.code = ErrJsonMalformed;
		data->idTrans = Blob::UnusedIdTrans;
		goto __decode_null_exitAMCfg;
	}

	// key: idTrans
	if((obj = cJSON_GetObjectItem(root, keys[p_IDTRANS])) == NULL){
		data->_error.code = ErrIdTransInvalid;
		data->idTrans = Blob::UnusedIdTrans;
		goto __decode_null_exitAMCfg;
	}
	data->idTrans = obj->valueint;

	//key: energy
	if((energy = cJSON_GetObjectItem(root, keys[p_ENERGY])) == NULL){
		data->_error.code = ErrEnergyMissing;
		goto __decode_null_exitAMCfg;
	}

	if((obj = cJSON_GetObjectItem(energy, keys[p_UPDFLAGS])) != NULL){
		data->data.updFlagMask = (Blob::AMUpdFlags)obj->valueint;
		data->data.keys |= Blob::AMKeyCfgUpd;
	}
	if((obj = cJSON_GetObjectItem(energy, keys[p_EVTFLAGS])) != NULL){
		data->data.evtFlagMask = (Blob::AMEvtFlags)obj->valueint;
		data->data.keys |= Blob::AMKeyCfgEvt;
	}
	if((obj = cJSON_GetObjectItem(energy, keys[p_MEASPERIOD])) != NULL){
		data->data.measPeriod = (uint32_t)obj->valueint;
		data->data.keys |= Blob::AMKeyCfgMeas;
	}

	//key: minmaxData
	if((minmaxData = cJSON_GetObjectItem(energy, keys[p_MINMAXDATA])) != NULL){
		//key: minmaxData.voltage
		if((value = cJSON_GetObjectItem(minmaxData, keys[p_VOLTAGE])) != NULL){
			if((obj = cJSON_GetObjectItem(value, keys[p_MIN])) != NULL){
				data->data.minmaxData.voltage.min = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_MAX])) != NULL){
				data->data.minmaxData.voltage.max = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value,keys[p_THRES])) != NULL){
				data->data.minmaxData.voltage.thres = obj->valuedouble;
			}
			data->data.keys |= Blob::AMKeyCfgMnxVolt;
		}

		//key: minmaxData.current
		if((value = cJSON_GetObjectItem(minmaxData, keys[p_CURRENT])) != NULL){
			if((obj = cJSON_GetObjectItem(value,keys[p_MIN])) != NULL){
				data->data.minmaxData.current.min = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_MAX])) != NULL){
				data->data.minmaxData.current.max = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_THRES])) != NULL){
				data->data.minmaxData.current.thres = obj->valuedouble;
			}
			data->data.keys |= Blob::AMKeyCfgMnxCurr;
		}

		//key: minmaxData.phase
		if((value = cJSON_GetObjectItem(minmaxData, keys[p_PHASE])) != NULL){
			if((obj = cJSON_GetObjectItem(value, keys[p_MIN])) != NULL){
				data->data.minmaxData.phase.min = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_MAX])) != NULL){
				data->data.minmaxData.phase.max = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_THRES])) != NULL){
				data->data.minmaxData.phase.thres = obj->valuedouble;
			}
			data->data.keys |= Blob::AMKeyCfgMnxPhase;
		}

		//key: minmaxData.pfactor
		if((value = cJSON_GetObjectItem(minmaxData, keys[p_PFACTOR])) != NULL){
			if((obj = cJSON_GetObjectItem(value, keys[p_MIN])) != NULL){
				data->data.minmaxData.pfactor.min = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_MAX])) != NULL){
				data->data.minmaxData.pfactor.max = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_THRES])) != NULL){
				data->data.minmaxData.pfactor.thres = obj->valuedouble;
			}
			data->data.keys |= Blob::AMKeyCfgMnxPfact;
		}

		//key: minmaxData.aPow
		if((value = cJSON_GetObjectItem(minmaxData, keys[p_APOW])) != NULL){
			if((obj = cJSON_GetObjectItem(value, keys[p_MIN])) != NULL){
				data->data.minmaxData.aPow.min = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_MAX])) != NULL){
				data->data.minmaxData.aPow.max = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_THRES])) != NULL){
				data->data.minmaxData.aPow.thres = obj->valuedouble;
			}
			data->data.keys |= Blob::AMKeyCfgMnxApow;
		}

		//key: minmaxData.rPow
		if((value = cJSON_GetObjectItem(minmaxData, keys[p_RPOW])) != NULL){
			if((obj = cJSON_GetObjectItem(value, keys[p_MIN])) != NULL){
				data->data.minmaxData.rPow.min = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_MAX])) != NULL){
				data->data.minmaxData.rPow.max = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_THRES])) != NULL){
				data->data.minmaxData.rPow.thres = obj->valuedouble;
			}
			data->data.keys |= Blob::AMKeyCfgMnxRpow;
		}

		//key: minmaxData.msPow
		if((value = cJSON_GetObjectItem(minmaxData, keys[p_MSPOW])) != NULL){
			if((obj = cJSON_GetObjectItem(value, keys[p_MIN])) != NULL){
				data->data.minmaxData.msPow.min = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_MAX])) != NULL){
				data->data.minmaxData.msPow.max = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_THRES])) != NULL){
				data->data.minmaxData.msPow.thres = obj->valuedouble;
			}
			data->data.keys |= Blob::AMKeyCfgMnxMpow;
		}

		//key: minmaxData.freq
		if((value = cJSON_GetObjectItem(minmaxData, keys[p_FREQ])) != NULL){
			if((obj = cJSON_GetObjectItem(value, keys[p_MIN])) != NULL){
				data->data.minmaxData.freq.min = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_MAX])) != NULL){
				data->data.minmaxData.freq.max = obj->valuedouble;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_THRES])) != NULL){
				data->data.minmaxData.freq.thres = obj->valuedouble;
			}
			data->data.keys |= Blob::AMKeyCfgMnxFreq;
		}

	}

	if((calibData = cJSON_GetObjectItem(energy, keys[p_CALIBDATA])) != NULL){
		if((array = cJSON_GetObjectItem(calibData, keys[p_METERREGS])) != NULL){
			for(int i=0;i<cJSON_GetArraySize(array);i++){
				value = cJSON_GetArrayItem(array, i);
				data->data.calibData.meterRegs[i] = value->valueint;
			}
			data->data.keys |= Blob::AMKeyCfgCalMetr;
		}
		if((array = cJSON_GetObjectItem(calibData, keys[p_MEASREGS])) != NULL){
			for(int i=0;i<cJSON_GetArraySize(array);i++){
				value = cJSON_GetArrayItem(array, i);
				data->data.calibData.measRegs[i] = value->valueint;
			}
			data->data.keys |= Blob::AMKeyCfgCalMea;
		}
	}

__decode_null_exitAMCfg:
	strcpy(data->_error.descr, errList[data->_error.code]);
	DEBUG_TRACE_I(_EXPR_, _MODULE_, "Parseado topic [%s] con resultado %s", topic, data->_error.descr);
	if(root){
		cJSON_Delete(root);
	}
	return data;
}


//------------------------------------------------------------------------------------
static void* decodeLightCfgSetRequest(char* topic, char* json_data, int* data_len, bool debug){
	cJSON *obj = NULL;
	cJSON *root = NULL;
	cJSON *light = NULL;
	cJSON *alsData = NULL;
	cJSON *outData = NULL;
	cJSON *array = NULL;
	cJSON *value = NULL;
	cJSON *luxLevel = NULL;
	cJSON *item = NULL;

	DEBUG_TRACE_D(_EXPR_, _MODULE_, "Procesando topic [%s]", topic);
	SetRequest_t<LightCfgData_t>* data = (SetRequest_t<LightCfgData_t>*)Heap::memAlloc(sizeof(SetRequest_t<LightCfgData_t>));
	MBED_ASSERT(data);
	*data_len = sizeof(SetRequest_t<LightCfgData_t>);
	data->data.keys = Blob::LightKeyNone;
	data->_error.code = Blob::ErrOK;

	if((root = cJSON_Parse(json_data)) == NULL){
		data->_error.code = ErrJsonMalformed;
		data->idTrans = Blob::UnusedIdTrans;
		goto __decode_null_exitLightCfg;
	}

	// key: idTrans
	if((obj = cJSON_GetObjectItem(root, keys[p_IDTRANS])) == NULL){
		data->_error.code = ErrIdTransInvalid;
		data->idTrans = Blob::UnusedIdTrans;
		goto __decode_null_exitLightCfg;
	}
	data->idTrans = obj->valueint;

	//key: light
	if((light = cJSON_GetObjectItem(root, keys[p_LIGHT])) == NULL){
		data->_error.code = ErrLightMissing;
		goto __decode_null_exitLightCfg;
	}

	if((obj = cJSON_GetObjectItem(light, keys[p_UPDFLAGS])) != NULL){
		data->data.updFlagMask = (Blob::LightUpdFlags)obj->valueint;
		data->data.keys |= Blob::LightKeyCfgUpd;
	}
	if((obj = cJSON_GetObjectItem(light, keys[p_EVTFLAGS])) != NULL){
		data->data.evtFlagMask = (Blob::LightEvtFlags)obj->valueint;
		data->data.keys |= Blob::LightKeyCfgEvt;
	}

	//key: alsData
	if((alsData = cJSON_GetObjectItem(light, keys[p_ALSDATA])) != NULL){
		cJSON *lux = NULL;
		if((lux = cJSON_GetObjectItem(alsData, keys[p_LUX])) != NULL){
			if((obj = cJSON_GetObjectItem(lux, keys[p_MIN])) != NULL){
				data->data.alsData.lux.min = obj->valueint;
			}
			if((obj = cJSON_GetObjectItem(lux, keys[p_MAX])) != NULL){
				data->data.alsData.lux.max = obj->valueint;
			}
			if((obj = cJSON_GetObjectItem(lux, keys[p_THRES])) != NULL){
				data->data.alsData.lux.thres = obj->valueint;
			}
			data->data.keys |= Blob::LightKeyCfgAls;
		}
	}

	if((outData = cJSON_GetObjectItem(light, keys[p_OUTDATA])) != NULL){
		if((obj = cJSON_GetObjectItem(outData, keys[p_MODE])) != NULL){
			data->data.outData.mode = (Blob::LightOutModeFlags)obj->valueint;
			data->data.keys |= Blob::LightKeyCfgOutm;
		}
		if((obj = cJSON_GetObjectItem(outData, keys[p_NUMACTIONS])) != NULL){
			data->data.outData.numActions = obj->valueint;
		}

		if((value = cJSON_GetObjectItem(outData, keys[p_CURVE])) != NULL){
			if((obj = cJSON_GetObjectItem(value, keys[p_SAMPLES])) != NULL){
				data->data.outData.curve.samples = obj->valueint;
			}
			if((obj = cJSON_GetObjectItem(value, keys[p_DATA])) != NULL){
				for(int i=0;i<cJSON_GetArraySize(obj);i++){
					item = cJSON_GetArrayItem(obj, i);
					data->data.outData.curve.data[i] = item->valueint;
				}
			}
			data->data.keys |= Blob::LightKeyCfgCurve;
		}

		if((array = cJSON_GetObjectItem(outData, keys[p_ACTIONS])) != NULL){
			for(int i=0;i<cJSON_GetArraySize(array);i++){
				value = cJSON_GetArrayItem(array, i);
				if((obj = cJSON_GetObjectItem(value, keys[p_ID])) != NULL){
					data->data.outData.actions[i].id = obj->valueint;
				}
				if((obj = cJSON_GetObjectItem(value, keys[p_FLAGS])) != NULL){
					data->data.outData.actions[i].flags = (Blob::LightActionFlags)obj->valueint;
				}
				if((obj = cJSON_GetObjectItem(value, keys[p_DATE])) != NULL){
					data->data.outData.actions[i].date = obj->valueint;
				}
				if((obj = cJSON_GetObjectItem(value, keys[p_TIME])) != NULL){
					data->data.outData.actions[i].time = obj->valueint;
				}
				if((obj = cJSON_GetObjectItem(value, keys[p_ASTCORR])) != NULL){
					data->data.outData.actions[i].astCorr = obj->valueint;
				}
				if((obj = cJSON_GetObjectItem(value, keys[p_OUTVALUE])) != NULL){
					data->data.outData.actions[i].outValue = obj->valueint;
				}

				if((luxLevel = cJSON_GetObjectItem(value, keys[p_LUXLEVEL])) != NULL){
					if((obj = cJSON_GetObjectItem(luxLevel, keys[p_MIN])) != NULL){
						data->data.outData.actions[i].luxLevel.min = obj->valueint;
					}
					if((obj = cJSON_GetObjectItem(luxLevel, keys[p_MAX])) != NULL){
						data->data.outData.actions[i].luxLevel.max = obj->valueint;
					}
					if((obj = cJSON_GetObjectItem(luxLevel, keys[p_THRES])) != NULL){
						data->data.outData.actions[i].luxLevel.thres = obj->valueint;
					}
				}
			}
			data->data.keys |= Blob::LightKeyCfgActs;
		}
	}

__decode_null_exitLightCfg:
	strcpy(data->_error.descr, errList[data->_error.code]);
	DEBUG_TRACE_I(_EXPR_, _MODULE_, "Parseado topic [%s] con resultado %s", topic, data->_error.descr);
	if(root){
		cJSON_Delete(root);
	}
	return data;
}


//------------------------------------------------------------------------------------
static void* decodeLightValueSetRequest(char* topic, char* json_data, int* data_len, bool debug){
	cJSON *obj = NULL;
	cJSON *root = NULL;
	cJSON *light = NULL;
	DEBUG_TRACE_D(_EXPR_, _MODULE_, "Procesando topic [%s]", topic);
	SetRequest_t<LightStatData_t>* data = (SetRequest_t<LightStatData_t>*)Heap::memAlloc(sizeof(SetRequest_t<LightStatData_t>));
	MBED_ASSERT(data);
	*data_len = sizeof(SetRequest_t<LightStatData_t>);
	data->_error.code = Blob::ErrOK;

	if((root = cJSON_Parse(json_data)) == NULL){
		data->_error.code = ErrJsonMalformed;
		data->idTrans = Blob::UnusedIdTrans;
		goto __decode_null_exitLightValue;
	}

	// key: idTrans
	if((obj = cJSON_GetObjectItem(root, keys[p_IDTRANS])) == NULL){
		data->_error.code = ErrIdTransInvalid;
		data->idTrans = Blob::UnusedIdTrans;
		goto __decode_null_exitLightValue;
	}
	data->idTrans = obj->valueint;

	//key: light
	if((light = cJSON_GetObjectItem(root, keys[p_LIGHT])) == NULL){
		data->_error.code = ErrLightMissing;
		goto __decode_null_exitLightValue;
	}

	if((obj = cJSON_GetObjectItem(light, keys[p_OUTVALUE])) == NULL){
		data->_error.code = ErrOutValueMissing;
		goto __decode_null_exitLightValue;
	}
	data->data.outValue = obj->valueint;

__decode_null_exitLightValue:
	strcpy(data->_error.descr, errList[data->_error.code]);
	DEBUG_TRACE_I(_EXPR_, _MODULE_, "Parseado topic [%s] con resultado %s", topic, data->_error.descr);
	if(root){
		cJSON_Delete(root);
	}
	return data;
}

}	/** End of namespace Blob */

