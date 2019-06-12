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
#include "ServerSocketBlob.h"

/** Definiciones de los Modelos de datos */
#include "common_objects.h"
#include "metering_objects.h"
#include "calendar_objects.h"

#include <type_traits>



class JsonParser {
public:
	/** JSON param Keys */
	static const char*	p_actions;
	static const char*	p_active;
	static const char*	p_alsData;
	static const char*	p_analyzers;
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
	static const char*	p_clock;
	static const char*	p_code;
	static const char*	p_coords;
	static const char*	p_current;
	static const char*	p_curve;
	static const char*	p_data;
	static const char*	p_date;
	static const char*	p_dawn;
	static const char*	p_delay;
	static const char*	p_descr;
	static const char*	p_devCount;
	static const char*	p_devList;
	static const char*	p_dusk;
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
	static const char*	p_geoloc;
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
	static const char*	p_loadPercent;
	static const char*	p_localtime;
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
	static const char * p_mqttUser;
	static const char * p_mqttPass;
	static const char*	p_mqttData;
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
	static const char*	p_timezone;
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


	static inline bool isTokenInTopic(const char* topic, const char* token){
    	return ((strstr(topic, token) != NULL)? true : false);
    }

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
	static cJSON* getJsonFromSetRequest(const Blob::SetRequest_t<T> &req, const char* name = p_data, ObjDataSelection type = ObjSelectAll){
		cJSON *root = cJSON_CreateObject();

		if(!root){
			return NULL;
		}

		// key: idTrans
		cJSON_AddNumberToObject(root, p_idTrans, req.idTrans);
		cJSON_AddNumberToObject(root, p_keys, req.keys);

		// key: object
		cJSON* obj = getJsonFromObj(req.data, type);
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
	static cJSON* getJsonFromResponse(const Blob::Response_t<T> &resp, ObjDataSelection type = ObjSelectAll){
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
		cJSON* obj = getJsonFromObj(resp.data, type);
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
	static cJSON* getJsonFromNotification(const Blob::NotificationData_t<T> &notif, ObjDataSelection type = ObjSelectAll){
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
		cJSON* obj = getJsonFromObj(notif.data, type);
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
	static cJSON* getJsonFromObj(const T& obj, ObjDataSelection type = ObjSelectAll){
		if (std::is_same<T, Blob::GetRequest_t>::value){
			return getJsonFromGetRequest((const Blob::GetRequest_t&)obj);
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
		if (std::is_same<T, Blob::SysRestartData_t>::value){
			return JSON::getJsonFromSysRestart((const Blob::SysRestartData_t&)obj);
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
		//----- Socket delegation
		if (std::is_same<T, Blob::ServerSocketCfgData_t>::value){
			return JSON::getJsonFromServerSocketCfg((const Blob::ServerSocketCfgData_t&)obj);
		}
		if (std::is_same<T, Blob::SocketEvtFlags>::value){
			return JSON::getJsonFromSocketEvent((const Blob::SocketEvtFlags&)obj);
		}
		//----- Objetos metering
		cJSON* result = NULL;
		if((result = JSON::getJsonFromMetering((const T&)obj, type)) != NULL){
			return result;
		}
		//----- Objetos calendar
		if((result = JSON::getJsonFromCalendar((const T&)obj, type)) != NULL){
			return result;
		}
		//----- Objetos light
		if((result = JSON::getJsonFromLight((const T&)obj, type)) != NULL){
			return result;
		}

		//----- Objetos externos de prop�sito general
		if (std::is_same<T, common_range_minmaxthres_double>::value){
			return JSON::getJsonFromRangeMinMaxThresDouble((const common_range_minmaxthres_double&)obj);
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
		// decodifica objeto de solicitud de reset
		if (std::is_same<T, Blob::SysRestartData_t>::value){
			result = JSON::getSysRestartFromJson((Blob::SysRestartData_t&)obj, json_obj);
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
		//decodifica objeto serverSocket
		if (std::is_same<T, Blob::ServerSocketCfgData_t>::value){
			result = JSON::getServerSocketCfgFromJson((Blob::ServerSocketCfgData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		// decodifica objeto
		if (std::is_same<T, Blob::SocketEvtFlags>::value){
			result = JSON::getSocketEventFromJson((Blob::SocketEvtFlags&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		//---- Decodifica Objetos metering
		if((result = JSON::getMeteringObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		//---- Decodifica Objetos calendar
		if((result = JSON::getCalendarObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		//---- Decodifica Objetos light
		if((result = JSON::getLightObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}

		//---- Decodifica Objetos comunes de prop�sito general
		if (std::is_same<T, common_range_minmaxthres_double>::value){
			result = JSON::getRangeMinMaxThresDoubleFromJson((common_range_minmaxthres_double&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}

	_getObjFromJson_Exit:
		if(std::is_same<U,char>::value){
			cJSON_Delete(json_obj);
		}
		return result;
	}


	template <typename U>
	static void* getObjFromDataTopic(char* topic, U* json, uint16_t *size){
		void* obj = NULL;

		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = NULL;
		if(std::is_same<U,cJSON>::value){
			json_obj = (cJSON*)json;
		}
		if(std::is_same<U,char>::value){
			json_obj = cJSON_Parse((char*)json);
		}

		if(json_obj != NULL)
		{
			if(isTokenInTopic(topic, "get/"))
			{
				if(isTokenInTopic(topic, "/cfg/") || isTokenInTopic(topic, "/value/")){
					obj = (Blob::GetRequest_t*)Heap::memAlloc(sizeof(Blob::GetRequest_t));
					MBED_ASSERT(obj);
					if(getGetRequestFromJson(*(Blob::GetRequest_t*) (obj), json_obj)){
						*size = sizeof(Blob::GetRequest_t);				
					}
					else{
						*size = 0;
						obj = NULL;
					}
				}
			}
			else if(isTokenInTopic(topic, "set/")){
				if(isTokenInTopic(topic, "/energy")){
					obj = (Blob::SetRequest_t<metering_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<metering_manager>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<metering_manager>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<metering_manager>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
				}
				else if(isTokenInTopic(topic, "/astcal")){
					obj = (Blob::SetRequest_t<calendar_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<calendar_manager>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<calendar_manager>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<calendar_manager>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
				}
				else if(isTokenInTopic(topic, "/sys")){
					if(isTokenInTopic(topic, "/restart")){
						obj = (Blob::SetRequest_t<Blob::SysRestartData_t>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<Blob::SysRestartData_t>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<Blob::SysRestartData_t>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<Blob::SysRestartData_t>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else{
						obj = (Blob::SetRequest_t<Blob::SysBootData_t>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<Blob::SysBootData_t>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<Blob::SysBootData_t>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<Blob::SysBootData_t>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
				}
				else if(isTokenInTopic(topic, "/light")){
					if(isTokenInTopic(topic, "/cfg/")){
						obj = (Blob::SetRequest_t<Blob::LightCfgData_t>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<Blob::LightCfgData_t>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<Blob::LightCfgData_t>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<Blob::LightCfgData_t>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else if(isTokenInTopic(topic, "/value/")){
						obj = (Blob::SetRequest_t<Blob::LightStatData_t>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<Blob::LightStatData_t>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<Blob::LightStatData_t>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<Blob::LightStatData_t>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else {
						DEBUG_TRACE_E(true, "[JsonParser]....", "Objeto set/light no identificado");
					}
				}
				else if(isTokenInTopic(topic, "/fwupd")){
					if(isTokenInTopic(topic, "/start")){
						obj = (Blob::SetRequest_t<Blob::FwUpdJob_t>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<Blob::FwUpdJob_t>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<Blob::FwUpdJob_t>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<Blob::FwUpdJob_t>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else if(isTokenInTopic(topic, "/cfg/")){
						obj = (Blob::SetRequest_t<Blob::FwUpdCfgData_t>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<Blob::FwUpdCfgData_t>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<Blob::FwUpdCfgData_t>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<Blob::FwUpdCfgData_t>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getObjectFromDataTopic: topic no controlado");
			}
		}

		if(std::is_same<U,char>::value){
			cJSON_Delete(json_obj);
		}
		return obj;
	}



	static cJSON* getDataFromObjTopic(char* topic, void* data, uint16_t size){
		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = NULL;
		
		if(isTokenInTopic(topic, "/energy")){
			if(size == sizeof(Blob::Response_t<metering_manager>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<metering_manager>*)data);
			}
			else if(size == sizeof(Blob::NotificationData_t<metering_manager>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<metering_manager>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: estructura no controlada");
			}
		}

		else if(isTokenInTopic(topic, "/astcal")){
			if(size == sizeof(Blob::Response_t<calendar_manager>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<calendar_manager>*)data);
			}
			else if(size == sizeof(Blob::NotificationData_t<calendar_manager>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<calendar_manager>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: estructura no controlada");
			}
		}

		else if(isTokenInTopic(topic, "/sys")){
			if(isTokenInTopic(topic, "/restart") && size == sizeof(Blob::Response_t<Blob::SysRestartData_t>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<Blob::SysRestartData_t>*)data);
			}
			else if(size == sizeof(Blob::Response_t<Blob::SysBootData_t>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<Blob::SysBootData_t>*)data);
			}
			else if(size == sizeof(Blob::NotificationData_t<Blob::SysBootData_t>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<Blob::SysBootData_t>*)data);
			}
			else if(size == sizeof(Blob::Response_t<Blob::SysCfgData_t>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<Blob::SysCfgData_t>*)data);
			}
			else if(size == sizeof(Blob::NotificationData_t<Blob::SysCfgData_t>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<Blob::SysCfgData_t>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: estructura no controlada");
			}
		}

		else if(isTokenInTopic(topic, "/light")){
			if(size == sizeof(Blob::Response_t<Blob::LightCfgData_t>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<Blob::LightCfgData_t>*)data);
			}
			else if(size == sizeof(Blob::Response_t<Blob::LightStatData_t>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<Blob::LightStatData_t>*)data);
			}
			else if(size == sizeof(Blob::NotificationData_t<Blob::LightStatData_t>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<Blob::LightStatData_t>*)data);
			}
			else if(size == sizeof(Blob::NotificationData_t<Blob::LightBootData_t>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<Blob::LightBootData_t>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: estructura no controlada");
			}
		}

		else if(isTokenInTopic(topic, "/fwupd")){
			if(size == sizeof(Blob::Response_t<Blob::FwUpdCfgData_t>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<Blob::FwUpdCfgData_t>*)data);
			}
			else if(size == sizeof(Blob::Response_t<Blob::FwUpdStatData_t>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<Blob::FwUpdStatData_t>*)data);
			}
			else if(size == sizeof(Blob::NotificationData_t<Blob::FwUpdStatData_t>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<Blob::FwUpdStatData_t>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: estructura no controlada");
			}
		}

		else{
			DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: topic no controlado");
		}
		
		return json_obj;
	}


	static void printBinaryObject(char* topic, void* data, uint16_t size){
		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = getDataFromObjTopic(topic, data, size);

		if(json_obj != NULL){
			DEBUG_TRACE_I(true, "[JsonParser]....", "Topic: %s, Msg: %s", topic, cJSON_PrintUnformatted(json_obj));
		}
		cJSON_Delete(json_obj);
	}

};	// end class Parser





#endif
