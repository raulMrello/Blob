/*
 * JsonParserBlob.h
 *
 *  Created on: Abr 2018
 *      Author: raulMrello
 *
 *	JsonParserBlob es el modulo encargado de traducir las estructuras de datos utilizadas en MQLib a mensajes JSON entendidos
 *	por el enlace MQTT y viceversa.
 */
 
#ifndef JSONPARSERBLOB_H
#define JSONPARSERBLOB_H

#include "mbed.h"
#include "Blob.h"
#include "cJSON.h"

/** Cabeceras de los m�dulos integrados en el namespace JSON */
#include "AstCalendarBlob.h"
#include "AMManagerBlob.h"
#include "LightManagerBlob.h"
#include "SysManagerBlob.h"
#include "FwUpdaterBlob.h"
#include "MQTTClientBlob.h"
#include "HMIManagerBlob.h"
#include "BlufiManagerBlob.h"

/** Definiciones de los Modelos de datos */
#include "common_objects.h"
#include "ppl_energy_objects.h"


#include <type_traits>



class JsonParser {
public:
	/** JSON param Keys */
	static const char*	p_actions;
	static const char*	p_active;
	static const char*	p_alsData;
	static const char*	p_aPow;
	static const char*	p_ast;
	static const char*	p_astcal;
	static const char*	p_astCorr;
	static const char*	p_blinkOn;
	static const char*	p_blinkOff;
	static const char*	p_bootCondition;
	static const char*	p_bootVers;
	static const char*	p_calibData;
	static const char*	p_cfg;
	static const char*	p_channel;
	static const char*	p_code;
	static const char*	p_current;
	static const char*	p_curve;
	static const char*	p_data;
	static const char*	p_date;
	static const char*	p_descr;
	static const char*	p_devCount;
	static const char*	p_devList;
	static const char*	p_enabled;
	static const char*	p_energy;
	static const char*	p_energyValues;
	static const char*	p_error;
	static const char*	p_evtFlags;
	static const char*	p_flags;
	static const char*	p_freq;
	static const char*	p_fwSize;
	static const char*	p_fwUrl;
	static const char*	p_fwv;
	static const char*	p_groupMask;
	static const char*	p_header;
	static const char*	p_hwv;
	static const char*	p_id;
	static const char*	p_idTrans;
	static const char*	p_isRoot;
	static const char*	p_job;
	static const char*	p_jobId;
	static const char*	p_keepAlive;
	static const char*	p_keys;
	static const char*	p_latitude;
	static const char*	p_light;
	static const char*	p_longitude;
	static const char*	p_lux;
	static const char*	p_luxLevel;
	static const char*	p_mac;
	static const char*	p_max;
	static const char*	p_measPeriod;
	static const char*	p_measRegs;
	static const char*	p_measureValues;
	static const char*	p_meshId;
	static const char*	p_meshPasswd;
	static const char*	p_meterRegs;
	static const char*	p_min;
	static const char*	p_minmaxData;
	static const char*	p_mode;
	static const char * p_mqttPort;
	static const char * p_mqttUrl;
	static const char*	p_msPow;
	static const char*	p_netCfg;
	static const char*	p_netReady;
	static const char*	p_now;
	static const char*	p_numActions;
	static const char*	p_outData;
	static const char*	p_outValue;
	static const char*	p_passwd;
	static const char*	p_period;
	static const char*	p_periods;
	static const char*	p_pfactor;
	static const char*	p_phase;
	static const char*	p_qos;
	static const char*	p_reactive;
	static const char*	p_reductionStart;
	static const char*	p_reductionStop;
	static const char*	p_rPow;
	static const char*	p_samples;
	static const char*	p_serial;
	static const char*	p_seasonCfg;
	static const char*	p_since;
	static const char*	p_staEssid;
	static const char*	p_staPasswd;
	static const char*	p_stat;
	static const char*	p_thdA;
	static const char*	p_thdV;
	static const char*	p_thres;
	static const char*	p_time;
	static const char*	p_timestamp;
	static const char*	p_uid;
	static const char*	p_until;
	static const char*	p_updFlags;
	static const char*	p_username;
	static const char*	p_verbosity;
	static const char*	p_version;
	static const char*	p_voltage;
	static const char*	p_wdowDawnStart;
	static const char*	p_wdowDawnStop;
	static const char*	p_wdowDuskStart;
	static const char*	p_wdowDuskStop;


	/** Parsea un objeto Blob::GetRequest_t en un mensaje JSON
	 *  @param req Solicitud a convertir a json
	 * 	@return Objeto JSON generado
	 */
	static cJSON* getJsonFromGetRequest(const Blob::GetRequest_t &req){
		cJSON* root = NULL;
		cJSON* error = NULL;
		cJSON* item = NULL;
		if((root=cJSON_CreateObject()) == NULL){
			return NULL;
		}

		cJSON_AddNumberToObject(root, p_idTrans, req.idTrans);
		if((error=cJSON_CreateObject()) == NULL){
			goto __parseGetRequest_Err;
		}
		cJSON_AddNumberToObject(error, p_code, req._error.code);
		if((item=cJSON_CreateString(req._error.descr)) == NULL){
			cJSON_Delete(error);
			goto __parseGetRequest_Err;
		}
		cJSON_AddItemToObject(error, p_descr, item);
		cJSON_AddItemToObject(root, p_error, error);
		return root;

	__parseGetRequest_Err:
		cJSON_Delete(root);
		return NULL;
	}


	/** Parsea un objeto Blob::SetRequest_t<T> en un mensaje JSON
	 *  @param req Solicitud a convertir a json
	 * 	@param name Nombre del objeto json a insertar en el SetRequest
	 * 	@return Objeto JSON generado
	 */
	template <typename T>
	static cJSON* getJsonFromSetRequest(const Blob::SetRequest_t<T> &req, const char* name = p_data){
		cJSON *root = cJSON_CreateObject();

		if(!root){
			return NULL;
		}

		// key: idTrans
		cJSON_AddNumberToObject(root, p_idTrans, req.idTrans);
		cJSON_AddNumberToObject(root, p_keys, req.keys);

		// key: object
		cJSON* obj = getJsonFromObj(req.data);
		if(!obj){
			cJSON_Delete(root);
			return NULL;
		}
		cJSON_AddItemToObject(root, name, obj);
		return root;
	}


	/** Parsea un objeto Blob::Response_t<T> en un mensaje JSON
	 *  @param resp Respuresta a convertir a json
	 * 	@return Objeto JSON generado
	 */
	template <typename T>
	static cJSON* getJsonFromResponse(const Blob::Response_t<T> &resp){
		// keys: root, idtrans, header, error
		cJSON *header = NULL;
		cJSON *error = NULL;
		cJSON *value = NULL;
		cJSON *root = cJSON_CreateObject();

		if(!root){
			DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromResponse: creando root");
			return NULL;
		}

		// key: idTrans s�lo se env�a si est� en uso
		if(resp.idTrans != Blob::UnusedIdTrans){
			cJSON_AddNumberToObject(root, p_idTrans, resp.idTrans);
		}

		// key: header
		if((header=cJSON_CreateObject()) == NULL){
			cJSON_Delete(root);
			DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromResponse: creando header");
			return NULL;
		}
		cJSON_AddNumberToObject(header, p_timestamp, resp.header.timestamp);
		cJSON_AddItemToObject(root, p_header, header);

		// key: error s�lo se env�a si el error es distinto de Blob::ErrOK
		if(resp.error.code != Blob::ErrOK){
			if((error=cJSON_CreateObject()) == NULL){
				cJSON_Delete(root);
				DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromResponse: creando error");
				return NULL;
			}
			cJSON_AddNumberToObject(error, p_code, resp.error.code);
			if((value=cJSON_CreateString(resp.error.descr)) == NULL){
				cJSON_Delete(error);
				cJSON_Delete(root);
				DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromResponse: creando error.descr");
				return NULL;
			}
			cJSON_AddItemToObject(error, p_descr, value);
			// a�ade objeto
			cJSON_AddItemToObject(root, p_error, error);
		}

		// key: object
		cJSON* obj = getJsonFromObj(resp.data);
		if(!obj){
			cJSON_Delete(root);
			DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromResponse: data=NULL");
			return NULL;
		}
		cJSON_AddItemToObject(root, p_data, obj);
		return root;
	}


	/** Parsea un objeto Blob::NotificationData_t<T> en un mensaje JSON
	 *  @param resp Respuresta a convertir a json
	 * 	@return Objeto JSON generado
	 */
	template <typename T>
	static cJSON* getJsonFromNotification(const Blob::NotificationData_t<T> &notif){
		// keys: root, idtrans, header, error
		cJSON *header = NULL;
		cJSON *root = cJSON_CreateObject();

		if(!root){
			DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromNotification: creando root");
			return NULL;
		}

		// key: header
		if((header=cJSON_CreateObject()) == NULL){
			DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromNotification: creando header");
			cJSON_Delete(root);
			return NULL;
		}
		cJSON_AddNumberToObject(header, p_timestamp, notif.header.timestamp);
		cJSON_AddItemToObject(root, p_header, header);

		// key: object
		cJSON* obj = getJsonFromObj(notif.data);
		if(!obj){
			DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromNotification: creando data");
			cJSON_Delete(root);
			return NULL;
		}
		cJSON_AddItemToObject(root, p_data, obj);
		return root;
	}


	/**
	 * Codifica la configuraci�n actual en un objeto JSON. Dependiendo del tipo de dato, delega
	 * al m�dulo correspondiente.
	 * @param cfg Configuraci�n
	 * @return Objeto JSON o NULL en caso de error
	 */
	template <typename T>
	static cJSON* getJsonFromObj(const T& obj){
		if (std::is_same<T, Blob::GetRequest_t>::value){
			return getJsonFromGetRequest((const Blob::GetRequest_t&)obj);
		}
		//----- AstCal delegation
		if (std::is_same<T, Blob::AstCalCfgData_t>::value){
			return JSON::getJsonFromAstCalCfg((const Blob::AstCalCfgData_t&)obj);
		}
		if (std::is_same<T, Blob::AstCalStatData_t>::value){
			return JSON::getJsonFromAstCalStat((const Blob::AstCalStatData_t&)obj);
		}
		if (std::is_same<T, Blob::AstCalBootData_t>::value){
			return JSON::getJsonFromAstCalBoot((const Blob::AstCalBootData_t&)obj);
		}
		//----- AMManager delegation
		if (std::is_same<T, Blob::AMCfgData_t>::value){
			return JSON::getJsonFromAMCfg((const Blob::AMCfgData_t&)obj);
		}
		if (std::is_same<T, Blob::AMStatData_t>::value){
			return JSON::getJsonFromAMStat((const Blob::AMStatData_t&)obj);
		}
		if (std::is_same<T, Blob::AMBootData_t>::value){
			return JSON::getJsonFromAMBoot((const Blob::AMBootData_t&)obj);
		}
		if (std::is_same<T, Blob::AMLoadData_t>::value){
			return JSON::getJsonFromAMLoad((const Blob::AMLoadData_t&)obj);
		}
		//----- LightManager delegation
		if (std::is_same<T, Blob::LightCfgData_t>::value){
			return JSON::getJsonFromLightCfg((const Blob::LightCfgData_t&)obj);
		}
		if (std::is_same<T, Blob::LightStatData_t>::value){
			return JSON::getJsonFromLightStat((const Blob::LightStatData_t&)obj);
		}
		if (std::is_same<T, Blob::LightBootData_t>::value){
			return JSON::getJsonFromLightBoot((const Blob::LightBootData_t&)obj);
		}
		if (std::is_same<T, Blob::LightLuxLevel>::value){
			return JSON::getJsonFromLightLux((const Blob::LightLuxLevel&)obj);
		}
		if (std::is_same<T, Blob::LightTimeData_t>::value){
			return JSON::getJsonFromLightTime((const Blob::LightTimeData_t&)obj);
		}
		//----- FwUpdater delegation
		if (std::is_same<T, Blob::FwUpdCfgData_t>::value){
			return JSON::getJsonFromFwUpdCfg((const Blob::FwUpdCfgData_t&)obj);
		}
		if (std::is_same<T, Blob::FwUpdStatData_t>::value){
			return JSON::getJsonFromFwUpdStat((const Blob::FwUpdStatData_t&)obj);
		}
		if (std::is_same<T, Blob::FwUpdBootData_t>::value){
			return JSON::getJsonFromFwUpdBoot((const Blob::FwUpdBootData_t&)obj);
		}
		if (std::is_same<T, Blob::FwUpdJob_t>::value){
			return JSON::getJsonFromFwUpdJob((const Blob::FwUpdJob_t&)obj);
		}
		//----- SysManager delegation
		if (std::is_same<T, Blob::SysCfgData_t>::value){
			return JSON::getJsonFromSysCfg((const Blob::SysCfgData_t&)obj);
		}
		if (std::is_same<T, Blob::SysStatData_t>::value){
			return JSON::getJsonFromSysStat((const Blob::SysStatData_t&)obj);
		}
		if (std::is_same<T, Blob::SysBootData_t>::value){
			return JSON::getJsonFromSysBoot((const Blob::SysBootData_t&)obj);
		}
		if (std::is_same<T, Blob::SysNullData_t>::value){
			return JSON::getJsonFromSysNull((const Blob::SysNullData_t&)obj);
		}
		//----- MQTTClient delegation
		if (std::is_same<T, Blob::MqttStatusFlags>::value){
			return JSON::getJsonFromMQTTCliStat((const Blob::MqttStatusFlags&)obj);
		}
		if (std::is_same<T, Blob::MQTTCfgData_t>::value){
			return JSON::getJsonFromMQTTCliCfg((const Blob::MQTTCfgData_t&)obj);
		}
		//----- HMIManager delegation
		if (std::is_same<T, Blob::HmiLedData_t>::value){
			return JSON::getJsonFromHMILed((const Blob::HmiLedData_t&)obj);
		}
		if (std::is_same<T, Blob::HmiEvtFlags>::value){
			return JSON::getJsonFromHMIEvent((const Blob::HmiEvtFlags&)obj);
		}
		//----- BlufiManager delegation
		if (std::is_same<T, Blob::BlufiCfgData_t>::value){
			return JSON::getJsonFromBlufiManStat((const Blob::BlufiCfgData_t&)obj);
		}
		//----- Objetos ppl:energy
		if (std::is_same<T, ppl_energy>::value){
			return JSON::getJsonFromPplEnergy((const ppl_energy&)obj);
		}
		if (std::is_same<T, ppl_energy_cfg>::value){
			return JSON::getJsonFromPplEnergyCfg((const ppl_energy_cfg&)obj);
		}
		if (std::is_same<T, ppl_energy_stat>::value){
			return JSON::getJsonFromPplEnergyStat((const ppl_energy_stat&)obj);
		}
		if (std::is_same<T, ppl_energy_analyzer>::value){
			return JSON::getJsonFromPplEnergyAnalyzer((const ppl_energy_analyzer&)obj);
		}
		if (std::is_same<T, ppl_energy_analyzer_cfg>::value){
			return JSON::getJsonFromPplEnergyAnalyzerCfg((const ppl_energy_analyzer_cfg&)obj);
		}
		if (std::is_same<T, ppl_energy_analyzer_cfg_minmax>::value){
			return JSON::getJsonFromPplEnergyAnalyzerCfgMinMax((const ppl_energy_analyzer_cfg_minmax&)obj);
		}
		if (std::is_same<T, ppl_energy_analyzer_cfg_calib>::value){
			return JSON::getJsonFromPplEnergyAnalyzerCfgCalib((const ppl_energy_analyzer_cfg_calib&)obj);
		}
		if (std::is_same<T, ppl_energy_analyzer_stat>::value){
			return JSON::getJsonFromPplEnergyAnalyzerStat((const ppl_energy_analyzer_stat&)obj);
		}
		if (std::is_same<T, ppl_energy_analyzer_stat_totals>::value){
			return JSON::getJsonFromPplEnergyAnalyzerStatTotals((const ppl_energy_analyzer_stat_totals&)obj);
		}
		if (std::is_same<T, ppl_energy_analyzer_stat_measure>::value){
			return JSON::getJsonFromPplEnergyAnalyzerStatMeasure((const ppl_energy_analyzer_stat_measure&)obj);
		}
		//----- Objetos externos de prop�sito general
		if (std::is_same<T, range_minmaxthres_double>::value){
			return JSON::getJsonFromRangeMinMaxThresDouble((const range_minmaxthres_double&)obj);
		}

		DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromObj: Objeto no manejado, result NULL");
		return NULL;
	}


	/** Decodifica el mensaje JSON en un objeto Blob::GetRequest_t
	 * @param req Recibe el objeto decodificado
	 * @param json Objeto JSON a decodificar
	 * @return keys Par�metros decodificados o 0 en caso de error
	 */
	template <typename U>
	static bool getGetRequestFromJson(Blob::GetRequest_t &req, U* json){
		cJSON* cfg = NULL;
		cJSON* stat = NULL;
		bool result = false;

		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = NULL;
		if(std::is_same<U,cJSON>::value){
			json_obj = (cJSON*)json;
		}
		if(std::is_same<U,char>::value){
			json_obj = cJSON_Parse((char*)json);
		}

		if(json_obj == NULL){
			req._error.code = Blob::ErrJsonMalformed;
			strcpy(req._error.descr, Blob::errList[req._error.code]);
			return false;
		}

		cJSON *idtrans = NULL;
		if((idtrans = cJSON_GetObjectItem(json_obj, p_idTrans)) == NULL){
			req._error.code = Blob::ErrIdTransInvalid;
			strcpy(req._error.descr, Blob::errList[req._error.code]);
			goto _getGetRequestFromJson_Exit;
		}
		req.idTrans = idtrans->valueint;
		req._error.code = Blob::ErrOK;
		strcpy(req._error.descr, Blob::errList[req._error.code]);
		result = true;

	_getGetRequestFromJson_Exit:
		if(std::is_same<U,char>::value){
			cJSON_Delete(json_obj);
		}
		return result;
	}



	/** Decodifica el mensaje JSON en un objeto Blob::NotificationData_t<T>
	 *  @param req Recibe el objeto decodificado
	 * @param json Objeto JSON a decodificar (cJSON* o char*)
	 * @return keys Par�metros decodificados o 0 en caso de error
	 */
	template <typename T, typename U>
	static bool getNotificationFromJson(Blob::NotificationData_t<T> &notif, U* json){
		cJSON *obj = NULL;
		cJSON *value = NULL;
		cJSON *root = NULL;
		bool result = false;
		
		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = NULL;
		if(std::is_same<U,cJSON>::value){
			json_obj = (cJSON*)json;
		}
		if(std::is_same<U,char>::value){
			json_obj = cJSON_Parse((char*)json);
		}

		if(json_obj == NULL){
			DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromJson: json_obj is NULL");
			return false;
		}

		// key: header
		if((obj = cJSON_GetObjectItem(json_obj, p_header)) == NULL){
			DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromJson: header is NULL");
			goto _getNotificationFromJson_Exit;
		}

		// key: timestamp
		if((value = cJSON_GetObjectItem(obj, p_timestamp)) == NULL){
			DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromJson: timestamp is NULL");
			goto _getNotificationFromJson_Exit;
		}
		notif.header.timestamp = (time_t)obj->valuedouble;

		// key:obj
		if((obj = cJSON_GetObjectItem(json_obj, p_data)) == NULL){
			DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromJson: data is NULL");
			goto _getNotificationFromJson_Exit;
		}

		result = (getObjFromJson(notif.data, obj))? true : false;

	_getNotificationFromJson_Exit:
		if(std::is_same<U,char>::value){
			cJSON_Delete(json_obj);
		}

		return result;
	}


	/** Decodifica el mensaje JSON en un objeto Blob::SetRequest_t<T>
	 *  @param req Recibe el objeto decodificado
	 * @param json Objeto JSON a decodificar (cJSON* o char*)
	 * @return keys Par�metros decodificados o 0 en caso de error
	 */
	template <typename T, typename U>
	static bool getSetRequestFromJson(Blob::SetRequest_t<T> &req, U* json){
		cJSON *obj = NULL;
		req.keys = 0;
		req._error.code = Blob::ErrOK;
		strcpy(req._error.descr, Blob::errList[req._error.code]);

		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = NULL;
		if(std::is_same<U,cJSON>::value){
			json_obj = (cJSON*)json;
		}
		if(std::is_same<U,char>::value){
			json_obj = cJSON_Parse((char*)json);
		}

		if(json_obj == NULL){
			req._error.code = Blob::ErrJsonMalformed;
			strcpy(req._error.descr, Blob::errList[req._error.code]);
			return false;
		}

		// key: idTrans
		if((obj = cJSON_GetObjectItem(json_obj, p_idTrans)) == NULL){
			req._error.code = Blob::ErrIdTransInvalid;
			strcpy(req._error.descr, Blob::errList[req._error.code]);
			goto _getSetRequestFromJson_Exit;
		}
		req.idTrans = obj->valueint;

		// key:obj
		if((obj = cJSON_GetObjectItem(json_obj, p_data)) == NULL){
			req._error.code = Blob::ErrEmptyContent;
			strcpy(req._error.descr, Blob::errList[req._error.code]);
			goto _getSetRequestFromJson_Exit;
		}
		req.keys = getObjFromJson(req.data, obj);

	_getSetRequestFromJson_Exit:
		if(std::is_same<U,char>::value){
			cJSON_Delete(json_obj);
		}
		return (req.keys)? true : false;
	}



	/** Decodifica el mensaje JSON en un objeto Blob::SetRequest_t<T>
	 *  @param req Recibe el objeto decodificado
	 * @param json Objeto JSON a decodificar
	 * @return keys Par�metros decodificados o 0 en caso de error
	 */
	template <typename T, typename U>
	static bool getResponseFromJson(Blob::Response_t<T> &resp, U* json){
		cJSON *obj = NULL;
		cJSON *value = NULL;
		bool result = false;
		resp.error.code = Blob::ErrOK;
		strcpy(resp.error.descr, Blob::errList[resp.error.code]);

		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = NULL;
		if(std::is_same<U,cJSON>::value){
			json_obj = (cJSON*)json;
		}
		if(std::is_same<U,char>::value){
			json_obj = cJSON_Parse((char*)json);
		}

		if(json_obj == NULL){
			resp.error.code = Blob::ErrJsonMalformed;
			strcpy(resp.error.descr, Blob::errList[resp.error.code]);
			return false;
		}

		// key: idTrans [opcional]
		if((obj = cJSON_GetObjectItem(json_obj, p_idTrans)) != NULL){
			resp.idTrans = obj->valueint;
		}

		// key: header
		if((obj = cJSON_GetObjectItem(json_obj, p_header)) == NULL){
			resp.error.code = Blob::ErrEmptyContent;
			strcpy(resp.error.descr, Blob::errList[resp.error.code]);
			goto _getResponseFromJson_Exit;
		}
		// key: timestamp
		if((value = cJSON_GetObjectItem(obj, p_timestamp)) == NULL){
			resp.error.code = Blob::ErrEmptyContent;
			strcpy(resp.error.descr, Blob::errList[resp.error.code]);
			goto _getResponseFromJson_Exit;
		}
		resp.header.timestamp = (time_t)obj->valuedouble;

		// key: error
		if((obj = cJSON_GetObjectItem(json_obj, p_error)) != NULL){
			// key: code
			if((value = cJSON_GetObjectItem(obj, p_code)) == NULL){
				resp.error.code = Blob::ErrEmptyContent;
				strcpy(resp.error.descr, Blob::errList[resp.error.code]);
				goto _getResponseFromJson_Exit;
			}
			resp.error.code = obj->valueint;
			// key: descr
			if((value = cJSON_GetObjectItem(obj, p_descr)) == NULL){
				resp.error.code = Blob::ErrEmptyContent;
				strcpy(resp.error.descr, Blob::errList[resp.error.code]);
				goto _getResponseFromJson_Exit;
			}
			strncpy(resp.error.descr, obj->valuestring, Blob::DefaultErrDescrLen);
		}

		// key:obj
		if((obj = cJSON_GetObjectItem(json_obj, p_data)) == NULL){
			resp.error.code = Blob::ErrEmptyContent;
			strcpy(resp.error.descr, Blob::errList[resp.error.code]);
			goto _getResponseFromJson_Exit;
		}

		result = (getObjFromJson(resp.data, obj))? true : false;

	_getResponseFromJson_Exit:
		if(std::is_same<U,char>::value){
			cJSON_Delete(json_obj);
		}
		return result;
	}


	/**
	 * Decodifica el mensaje JSON en un objeto
	 * @param obj Recibe el objeto decodificado
	 * @param json Objeto JSON a decodificar
	 * @return keys Par�metros decodificados o 0 en caso de error
	 */
	template <typename T, typename U>
	static uint32_t getObjFromJson(T &obj, U* json){
		uint32_t result = 0;

		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = NULL;
		if(std::is_same<U,cJSON>::value){
			json_obj = (cJSON*)json;
		}
		if(std::is_same<U,char>::value){
			json_obj = cJSON_Parse((char*)json);
		}

		if(json_obj == NULL){
			return false;
		}
		// decodifica objeto de configuraci�n
		if (std::is_same<T, Blob::GetRequest_t>::value){
			result = (uint32_t)getGetRequestFromJson((Blob::GetRequest_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//----
		// decodifica objeto de configuraci�n
		if (std::is_same<T, Blob::AstCalCfgData_t>::value){
			result = JSON::getAstCalCfgFromJson((Blob::AstCalCfgData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de estado
		if (std::is_same<T, Blob::AstCalStatData_t>::value){
			result = JSON::getAstCalStatFromJson((Blob::AstCalStatData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de arranque
		if (std::is_same<T, Blob::AstCalBootData_t>::value){
			result = JSON::getAstCalBootFromJson((Blob::AstCalBootData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//----
		// decodifica objeto de configuraci�n
		if (std::is_same<T, Blob::AMCfgData_t>::value){
			result = JSON::getAMCfgFromJson((Blob::AMCfgData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de estado
		if (std::is_same<T, Blob::AMStatData_t>::value){
			result = JSON::getAMStatFromJson((Blob::AMStatData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de arranque
		if (std::is_same<T, Blob::AMBootData_t>::value){
			result = JSON::getAMBootFromJson((Blob::AMBootData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de % de activaci�n
		if (std::is_same<T, Blob::AMLoadData_t>::value){
			result = JSON::getAMLoadFromJson((Blob::AMLoadData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//----
		// decodifica objeto de configuraci�n
		if (std::is_same<T, Blob::LightCfgData_t>::value){
			result = JSON::getLightCfgFromJson((Blob::LightCfgData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de estado
		if (std::is_same<T, Blob::LightStatData_t>::value){
			result = JSON::getLightStatFromJson((Blob::LightStatData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de arranque
		if (std::is_same<T, Blob::LightBootData_t>::value){
			result = JSON::getLightBootFromJson((Blob::LightBootData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de configuraci�n ALS
		if (std::is_same<T, Blob::LightLuxLevel>::value){
			result = JSON::getLightLuxFromJson((Blob::LightLuxLevel&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de evento temporal
		if (std::is_same<T, Blob::LightTimeData_t>::value){
			result = JSON::getLightTimeFromJson((Blob::LightTimeData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//----
		// decodifica objeto de configuraci�n
		if (std::is_same<T, Blob::FwUpdCfgData_t>::value){
			result = JSON::getFwUpdCfgFromJson((Blob::FwUpdCfgData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de estado
		if (std::is_same<T, Blob::FwUpdStatData_t>::value){
			result = JSON::getFwUpdStatFromJson((Blob::FwUpdStatData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de arranque
		if (std::is_same<T, Blob::FwUpdBootData_t>::value){
			result = JSON::getFwUpdBootFromJson((Blob::FwUpdBootData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de configuraci�n ALS
		if (std::is_same<T, Blob::FwUpdJob_t>::value){
			result = JSON::getFwUpdJobFromJson((Blob::FwUpdJob_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//----
		// decodifica objeto de configuraci�n
		if (std::is_same<T, Blob::SysCfgData_t>::value){
			result = JSON::getSysCfgFromJson((Blob::SysCfgData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de estado
		if (std::is_same<T, Blob::SysStatData_t>::value){
			result = JSON::getSysStatFromJson((Blob::SysStatData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de arranque
		if (std::is_same<T, Blob::SysBootData_t>::value){
			result = JSON::getSysBootFromJson((Blob::SysBootData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto de solicitud de arranque
		if (std::is_same<T, Blob::SysNullData_t>::value){
			result = JSON::getSysNullFromJson((Blob::SysNullData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//----
		// decodifica objeto de estado
		if (std::is_same<T, Blob::MqttStatusFlags>::value){
			result = JSON::getMQTTCliStatFromJson((Blob::MqttStatusFlags&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, Blob::MQTTCfgData_t>::value){
			result = JSON::getMQTTCliCfgFromJson((Blob::MQTTCfgData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//----
		// decodifica objeto
		if (std::is_same<T, Blob::HmiLedData_t>::value){
			result = JSON::getHMILedFromJson((Blob::HmiLedData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto
		if (std::is_same<T, Blob::HmiEvtFlags>::value){
			result = JSON::getHMIEventFromJson((Blob::HmiEvtFlags&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//decodifica objeto blufiMan
		if (std::is_same<T, Blob::BlufiCfgData_t>::value){
			result = JSON::getBlufiManStatFromJson((Blob::BlufiCfgData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//---- Decodifica Objetos ppl:energy
		if (std::is_same<T, ppl_energy>::value){
			result = JSON::getPplEnergyFromJson((ppl_energy&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, ppl_energy_cfg>::value){
			result = JSON::getPplEnergyCfgFromJson((ppl_energy_cfg&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, ppl_energy_stat>::value){
			result = JSON::getPplEnergyStatFromJson((ppl_energy_stat&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, ppl_energy_analyzer>::value){
			result = JSON::getPplEnergyAnalyzerFromJson((ppl_energy_analyzer&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, ppl_energy_analyzer_cfg>::value){
			result = JSON::getPplEnergyAnalyzerCfgFromJson((ppl_energy_analyzer_cfg&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, ppl_energy_analyzer_cfg_minmax>::value){
			result = JSON::getPplEnergyAnalyzerCfgMinMaxFromJson((ppl_energy_analyzer_cfg_minmax&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, ppl_energy_analyzer_cfg_calib>::value){
			result = JSON::getPplEnergyAnalyzerCfgCalibFromJson((ppl_energy_analyzer_cfg_calib&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, ppl_energy_analyzer_stat>::value){
			result = JSON::getPplEnergyAnalyzerStatFromJson((ppl_energy_analyzer_stat&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, ppl_energy_analyzer_stat_totals>::value){
			result = JSON::getPplEnergyAnalyzerStatTotalsFromJson((ppl_energy_analyzer_stat_totals&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		if (std::is_same<T, ppl_energy_analyzer_stat_measure>::value){
			result = JSON::getPplEnergyAnalyzerStatMeasureFromJson((ppl_energy_analyzer_stat_measure&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//---- Decodifica Objetos comunes de prop�sito general
		if (std::is_same<T, range_minmaxthres_double>::value){
			result = JSON::getRangeMinMaxThresDoubleFromJson((range_minmaxthres_double&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}

	_getObjFromJson_Exit:
		if(std::is_same<U,char>::value){
			cJSON_Delete(json_obj);
		}
		return result;
	}

};	// end class Parser





#endif
