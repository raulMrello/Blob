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
#define _EXPR_	(true)


namespace JSON {


//---------------------------------------------------------------------------------
//- Param Keys --------------------------------------------------------------------
//---------------------------------------------------------------------------------

/** JSON keys common */
const char* p_code	 		= "code";
const char* p_cfg 			= "cfg";
const char* p_data	 		= "data";
const char* p_descr	 		= "descr";
const char* p_error	 		= "error";
const char* p_evtFlags 		= "evtFlags";
const char* p_flags			= "flags";
const char* p_header			= "header";
const char* p_idTrans 		= "idTrans";
const char* p_keys 			= "keys";
const char* p_stat 			= "stat";
const char* p_timestamp		= "timestamp";
const char* p_updFlags 		= "updFlags";

/** JSON keys AstCalendar */
const char* p_astcal 		= "astcal";
const char* p_astCfg 		= "astCfg";
const char* p_astData 		= "astData";
const char* p_latitude 		= "latitude";
const char* p_longitude 		= "longitude";
const char* p_now	 		= "now";
const char* p_period 		= "period";
const char* p_reductionStart = "reductionStart";
const char* p_reductionStop	= "reductionStop";
const char* p_seasonCfg 		= "seasonCfg";
const char* p_wdowDawnStart 	= "wdowDawnStart";
const char* p_wdowDawnStop 	= "wdowDawnStop";
const char* p_wdowDuskStart 	= "wdowDuskStart";
const char* p_wdowDuskStop 	= "wdowDuskStop";

/** JSON keys AMManager */
const char* p_active			= "active";
const char* p_aPow			= "aPow";
const char* p_energy 		= "energy";
const char* p_calibData		= "calibData";
const char* p_current		= "current";
const char* p_energyValues	= "energyValues";
const char* p_freq			= "freq";
const char* p_max			= "max";
const char* p_measPeriod		= "measPeriod";
const char* p_measRegs		= "measRegs";
const char* p_measureValues	= "measureValues";
const char* p_meterRegs		= "meterRegs";
const char* p_min			= "min";
const char* p_minmaxData		= "minmaxData";
const char* p_msPow			= "msPow";
const char* p_outValue		= "outValue";
const char* p_pfactor		= "pfactor";
const char* p_phase			= "phase";
const char* p_reactive		= "reactive";
const char* p_rPow			= "rPow";
const char* p_thres			= "thres";
const char* p_voltage 		= "voltage";

/** JSON keys LightManager */
const char* p_actions		= "actions";
const char* p_alsData		= "alsData";
const char* p_astCorr 		= "astCorr";
//const char* p_astData 		= "astData";
const char* p_curve	 		= "curve";
const char* p_date 	 		= "date";
const char* p_id  			= "id";
const char* p_latitude 		= "latitude";
const char* p_light			= "light";
const char* p_longitude 		= "longitude";
const char* p_lux			= "lux";
const char* p_luxLevel		= "luxLevel";
const char* p_max			= "max";
const char* p_min			= "min";
const char* p_mode			= "mode";
const char* p_now			= "now";
const char* p_numActions		= "numActions";
const char* p_outData		= "outData";
const char* p_outValue		= "outValue";
const char* p_period			= "period";
const char* p_reductionStart = "reductionStart";
const char* p_reductionStop	= "reductionStop";
const char* p_samples		= "samples";
const char* p_thres			= "thres";
const char* p_time	 		= "time";
const char* p_wdowDawnStart 	= "wdowDawnStart";
const char* p_wdowDawnStop 	= "wdowDawnStop";
const char* p_wdowDuskStart 	= "wdowDuskStart";
const char* p_wdowDuskStop 	= "wdowDuskStop";

/** JSON keys SysManager */
const char* p_astcal 		= "astcal";
const char* p_channel 		= "channel";
const char* p_code	 		= "code";
const char* p_descr	 		= "descr";
const char* p_energy	 		= "energy";
const char* p_error	 		= "error";
const char* p_fwv		 	= "fwv";
const char* p_groupMask 		= "groupMask";
const char* p_header			= "header";
const char* p_hwv		 	= "hwv";
const char* p_idTrans 		= "idTrans";
const char* p_keys 			= "keys";
const char* p_light 			= "light";
const char* p_mac		 	= "mac";
const char* p_meshId		 	= "meshId";
const char* p_meshPasswd	 	= "meshPasswd";
const char* p_netCfg		 	= "netCfg";
const char* p_staEssid	 	= "staEssid";
const char* p_staPasswd	 	= "staPasswd";
const char* p_sys		 	= "sys";
const char* p_timestamp		= "timestamp";
const char* p_updFlags 		= "updFlags";



//------------------------------------------------------------------------------------
//-- PUBLIC METHODS IMPLEMENTATION ---------------------------------------------------
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
bool getGetRequestFromJson(Blob::GetRequest_t &req, cJSON* json){
	cJSON* cfg = NULL;
	cJSON* stat = NULL;

	if(json == NULL){
		return false;
	}
	cJSON *idtrans = NULL;
	if((idtrans = cJSON_GetObjectItem(json, keys[p_IDTRANS])) == NULL){
		return false;
	}
	req.idTrans = idtrans->valueint;
	req._error.code = Blob::ErrOK;
	strcpy(req._error.descr, Blob::errList[req._error.code]);
	return true;
}


//------------------------------------------------------------------------------------
bool getGetRequestFromJson(Blob::GetRequest_t &req, char* json){
	cJSON *json_obj = cJSON_Parse(json);
	if(json_obj == NULL)
		return false;
	bool result = getGetRequestFromJson(req, json);
	cJSON_Delete(json_obj);
	return result;
}


//------------------------------------------------------------------------------------
cJSON* getJsonFromGetRequest(const Blob::GetRequest_t& req){
	cJSON* root = NULL;
	cJSON* error = NULL;
	cJSON* item = NULL;
	if((root=cJSON_CreateObject()) == NULL){
		return NULL;
	}

	cJSON_AddNumberToObject(root, keys[p_IDTRANS], req.idTrans);
	if((error=cJSON_CreateObject()) == NULL){
		goto __parseGetRequest_Err;
	}
	cJSON_AddNumberToObject(error, keys[p_CODE], req._error.code);
	if((item=cJSON_CreateString(req._error.descr)) == NULL){
		cJSON_Delete(error);
		goto __parseGetRequest_Err;
	}
	cJSON_AddItemToObject(error, keys[p_DESCR], item);
	cJSON_AddItemToObject(root, keys[p_ERROR], error);
	return root;

__parseGetRequest_Err:
	cJSON_Delete(root);
	return NULL;
}




}	/** End of namespace JSON */

