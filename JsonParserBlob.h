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

/**
 * Este archivo de cabecera es externo al proyecto y debe definir las diferentes claves que habilitan o deshabilitan
 * porciones de c�digo. Puesto que este m�dulo integra objetos de diferentes proyectos (AstCalendar, AMManager,
 * LightManager, etc...) es necesario habilitar �nicamente aquellos componentes que se quiera utilizar, de forma que
 * la compilaci�n pueda llevarse a cabo en diferentes plataformas o proyectos.
 *
 * Las claves que debe definir este archivo son:
 *
 * JsonParser_AstCalendar_Enabled
 * JsonParser_AMManager_Enabled
 * JsonParser_SysManager_Enabled
 * JsonParser_LightManager_Enabled
 * JsonParser_FwUpdater_Enabled
 * JsonParser_MQTTClient_Enabled
 * JsonParser_HMIManager_Enabled
 * JsonParser_BlufiManager_Enabled
 * JsonParser_ServerSocket_Enabled
 *
 */
#include "JsonParserBlob_UserConfig.h"

/** Definiciones de los Modelos de datos */
#include "common_objects.h"

/** Cabeceras de los m�dulos integrados en el namespace JSON */
#if defined(JsonParser_AstCalendar_Enabled)
#include "AstCalendarBlob.h"
#endif
#if defined(JsonParser_AMManager_Enabled)
#include "AMManagerBlob.h"
#include "metering_objects.h"
#endif
#if defined(JsonParser_LightManager_Enabled)
#include "LightManagerBlob.h"
#endif
#if defined(JsonParser_FwUpdater_Enabled)
#include "FwUpdaterBlob.h"
#endif
#if defined(JsonParser_MQTTClient_Enabled)
#include "MQTTClientBlob.h"
#endif
#if defined(JsonParser_HMIManager_Enabled)
#include "HMIManagerBlob.h"
#include "hmi_objects.h"
#endif
#if defined(JsonParser_BlufiManager_Enabled)
#include "BlufiManagerBlob.h"
#endif
#if defined(JsonParser_ServerSocket_Enabled)
#include "ServerSocketBlob.h"
#endif
#if defined(JsonParser_ShuckoManager_Enabled)
#include "ShuckoManagerBlob.h"
#include "shucko_objects.h"
#endif
#if defined(JsonParser_MennekesManager_Enabled)
#include "MennekesManagerBlob.h"
#include "mennekes_objects.h"
#endif
#if defined(JsonParser_EVStateMachine_Enabled)
#include "EVStateMachineBlob.h"
#include "evsm_objects.h"
#endif
#if defined(JsonParser_RequestsManager_Enabled)
#include "requests_manager_objects.h"
#endif
#if defined(JsonParser_Stm32Updater_Enabled)
#include "Stm32UpdaterBlob.h"
#include "stm32updater_objects.h"
#endif


#if defined(JsonParser_AstCalendar_Enabled)
#include "calendar_objects.h"
#endif

#if defined(JsonParser_SchedulerManager_Enabled)
#include "scheduler_manager_objects.h"
#endif

#if defined(JsonParser_SysManager_Enabled)
#include "sys_manager_objects.h"
#endif

#if defined(JsonParser_ModulatorManager_Enabled)
#include "ModulatorManagerBlob.h"
#include "modulator_objects.h"
#endif

#if defined(JsonParser_OCPPManager_Enabled)
#include "ocpp_manager_objects.h"
#endif

#if defined(JsonParser_ModbusMap_Enabled)
#include "modbus_objects.h"
#endif

#if defined(JsonParser_SolarManager_Enabled)
#include "SolarManagerBlob.h"
#include "solar_objects.h"
#endif

#if defined(JsonParser_WSClient_Enabled)
#include "wsclient_objects.h"
#endif

#if defined(JsonParser_EmbWeb_Enabled)
#include "embweb_objects.h"
#endif

#include <type_traits>

#define JSONPARSER_ENABLE_PrintBinaryObject		false

class JsonParser {
public:
	/** JSON param Keys */
	static const char*	p_actions;
	static const char*	p_active;
	static const char*	p_alsData;
	static const char*	p_ampacity;
	static const char*	p_analyzer;
	static const char*	p_analyzers;
	static const char*	p_aPow;
	static const char*	p_assignment;
	static const char*	p_ast;
	static const char*	p_astcal;
	static const char*	p_astCorr;
	static const char*	p_barMode;
	static const char*	p_blinkOn;
	static const char*	p_blinkOff;
	static const char*	p_bootCondition;
	static const char*	p_bootVers;
	static const char*	p_calibData;
	static const char*	p_cardFile;
	static const char*	p_cfg;
	static const char*	p_channel;
	static const char*	p_chargeProcess;
	static const char*	p_childSync;
	static const char*	p_clock;
	static const char*	p_code;
	static const char*  p_connCfg;
	static const char*	p_connector;
	static const char*	p_connectorId;
	static const char*	p_connectorName;
	static const char*	p_connectorType;
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
	static const char*	p_eocMode;
	static const char*	p_error;
	static const char*  p_eth;
	static const char*  p_ethDhcpen;
	static const char*  p_ethipstatic;
	static const char*  p_ethmask;
	static const char*  p_ethgw;
	static const char*  p_ethdns;
	static const char*	p_evtFlags;
	static const char*  p_extraInfo;
	static const char*	p_flags;
	static const char*	p_freq;
	static const char*	p_fwSize;
	static const char*	p_fwUrl;
	static const char*	p_fwv;
	static const char*  p_fwvPot;
	static const char*  p_fwvCortex;
	static const char*	p_geoloc;
	static const char*	p_groupMask;
	static const char*	p_guiMode;
	static const char*	p_header;
	static const char*	p_holdCount;
	static const char*	p_hwv;
	static const char*	p_hwvPot;
	static const char*	p_iconMode;
	static const char*	p_id;
	static const char*  p_idTag;
	static const char*	p_idTrans;
	static const char*	p_ip;
	static const char*	p_inDomo;
	static const char*	p_isRoot;
	static const char*	p_job;
	static const char*	p_jobId;
	static const char*	p_keepAlive;
	static const char*	p_keys;
	static const char*	p_last;
	static const char*	p_latitude;
	static const char*	p_leakage;
	static const char*	p_light;
	static const char*	p_limited;
	static const char*	p_loadPercent;
	static const char*	p_localtime;
	static const char*	p_longitude;
	static const char*	p_lux;
	static const char*	p_luxLevel;
	static const char*	p_mac;
	static const char*	p_max;
	static const char*	p_maxAmpacity;
	static const char*	p_measPeriod;
	static const char*	p_measRegs;
	static const char*	p_measureValues;
	static const char*	p_meshId;
	static const char*	p_meshPasswd;
	static const char*	p_meterRegs;
	static const char*	p_min;
	static const char*	p_minCurrent;
	static const char*	p_minmaxData;
	static const char*	p_minPower;
	static const char*	p_minPwm;
	static const char*	p_mode;
	static const char*	p_modules;
	static const char * p_mqttPort;
	static const char * p_mqttUrl;
	static const char * p_mqttUser;
	static const char * p_mqttPass;
	static const char*	p_mqttData;
	static const char*  p_mqttClientId;
	static const char*	p_msPow;
	static const char*	p_netCfg;
	static const char*	p_netReady;
	static const char*	p_notifCycle;
	static const char*	p_now;
	static const char*	p_numActions;
	static const char*  p_nvsId;
	static const char*	p_outData;
	static const char*	p_outValue;
	static const char*	p_pass;
	static const char*	p_passwd;
	static const char*	p_period;
	static const char*	p_periods;
	static const char*	p_pfactor;
	static const char*	p_plugPresent;
	static const char*	p_plugLimit;
	static const char*	p_phase;
	static const char*	p_pwm;
	static const char*	p_qos;
	static const char*	p_reactive;
	static const char*	p_reductionStart;
	static const char*	p_reductionStop;
	static const char*	p_request;
	static const char*	p_requestStart;
	static const char*	p_requestStop;
	static const char*	p_relOverload;
	static const char*	p_rfid;
	static const char*	p_rfidCfg;
	static const char*	p_rPow;
	static const char*  p_rst_reason;
	static const char*	p_samples;
	static const char*	p_serial;
	static const char*	p_selectorPosition;
	static const char * p_shucko;
	static const char*	p_seasonCfg;
	static const char*	p_since;
	static const char*  p_solarPriority;
	static const char*	p_ssid;
	static const char*	p_staEssid;
	static const char*	p_staPasswd;
	static const char*	p_lastStaEssid;
	static const char*	p_lastStaPasswd;
	static const char*	p_start;
	static const char*	p_status;
	static const char*	p_stat;
	static const char*	p_thdA;
	static const char*	p_thdV;
	static const char*	p_thres;
	static const char*	p_time;
	static const char*	p_timeout;
	static const char*	p_timestamp;
	static const char*	p_heapFree;
	static const char*	p_timezone;
	static const char*	p_topic;
	static const char*	p_type;
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
	static const char*  p_wifi_sta;
	static const char*  p_wifiDhcpen;
	static const char*  p_wifidns;
	static const char* 	p_wifigw;
	static const char* 	p_wifiipstatic;
	static const char* 	p_wifimask;
	static const char*	p_port;
	static const char*	p_state;
	static const char*	p_idCharge;
	static const char*	p_updProgress;
	static const char*  p_url;
	static const char*	p_user;
	static const char*	p_dataAnalyzer;
	static const char*	p_source;
	static const char*	p_priority;
	static const char*	p_action;
	static const char*	p_group;
	static const char*	p_elements;
	static const char*	p_name;
	static const char*	p_tasks;
	static const char*	p_initTime;
	static const char*	p_endTime;
	static const char*	p_day;
	static const char*	p_month;
	static const char*	p_weekday;
	static const char*	p_timeList;
	static const char*	p_hour;
	static const char*	p_duration;
	static const char*	p_defaultState;
	static const char*	p_modeUser;
	static const char*	p_modeElements;
	static const char*	p_modeActivation;
	static const char*	p_sources;
	static const char*	p_childs;
	static const char*	p_event;
	static const char*	p_permis;
	static const char*	p_iconError;
	static const char*	p_iconConn;
	static const char*	p_iconPlug;
	static const char*	p_iconModul;
	static const char*	p_iconSched;
	static const char*  p_iconSched2;
	static const char*	p_limitPower;
	static const char*	p_maxPower;
	static const char*	p_totalPower;
	static const char*	p_homePower;
	static const char*	p_evsePower;
	static const char*	p_evseLimitPower;
	static const char*	p_evseTotalPower;
	static const char*	p_ownLimitPower;
	static const char*	p_selectorPower;
	static const char* 	p_model;
	static const char*	p_localOperations;
	static const char*	p_remoteOperations;
	static const char * p_count;
	static const char * p_body;
	static const char * p_inverse;
	static const char * p_erased;
	static const char * p_remaining;
	static const char * p_restore;
	static const char * p_totalCurrent;
	static const char*	p_serverUrl;
	static const char*	p_pingInterval;
	static const char*	p_bootInterval;
	static const char*	p_connectionTimeOut;
	static const char*	p_splCfg;
	static const char*	p_network;
	static const char*	p_mac_wifi;
	static const char*	p_mac_eth;
	static const char*	p_spl;
	static const char*	p_conn;
	static const char*	p_listAPs;
	static const char*	p_midAnalyzers;
	static const char*	p_timezoneCode;
	static const char*	p_wsConnected;
	static const char*	p_wifiConnected;
	static const char*	p_ethConnected;
	static const char*	p_phases;
	static const char*	p_idTask;
	static const char*	p_idTaskPower;
	static const char*	p_validFrom;
	static const char*	p_validTo;
	static const char*	p_chargeRelated;
	static const char*	p_initLocaltime;
	static const char*	p_endLocaltime;
	static const char* 	p_priorityPower;
	static const char* 	p_shelly;
	static const char*	p_spentMoney;
	static const char*	p_chargeSpentMoney;

	static void setLoggingLevel(esp_log_level_t level){
		esp_log_level_set("[JsonParser]....", level);
	}

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
		cJSON_AddNumberToObject(header, p_heapFree, resp.header.heapFree);
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
		if constexpr (std::is_same<T,int>::value){
			cJSON_AddNumberToObject(root, p_data, (int)resp.data);
			return root;
		}

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
		cJSON_AddNumberToObject(header, p_heapFree, notif.header.heapFree);
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
		cJSON* result = NULL;
		if (std::is_same<T, Blob::GetRequest_t>::value){
			return getJsonFromGetRequest((const Blob::GetRequest_t&)obj);
		}
		//----- Objetos hmi
		#if defined(JsonParser_HMIManager_Enabled)
		if((result = JSON::getJsonFromHMIObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- BlufiManager delegation
		#if defined(JsonParser_BlufiManager_Enabled)
		if (std::is_same<T, Blob::BlufiCfgData_t>::value){
			return JSON::getJsonFromBlufiManStat((const Blob::BlufiCfgData_t&)obj);
		}
		#endif
		//----- Objetos metering
		#if defined(JsonParser_AMManager_Enabled)
		if((result = JSON::getJsonFromMetering((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- Objetos shucko
		#if defined(JsonParser_ShuckoManager_Enabled)
		if((result = JSON::getJsonFromShucko((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- Objetos mennekes
		#if defined(JsonParser_MennekesManager_Enabled)
		if((result = JSON::getJsonFromMennekes((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- Objetos calendar
		#if defined(JsonParser_AstCalendar_Enabled)
		if((result = JSON::getJsonFromCalendar((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- Objetos light
		#if defined(JsonParser_LightManager_Enabled)
		if((result = JSON::getJsonFromLight((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- Objetos FwUpdater
		#if defined(JsonParser_FwUpdater_Enabled)
		if((result = JSON::getJsonFromFwUpd((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- Objetos mqtt
		#if defined(JsonParser_MQTTClient_Enabled)
		if((result = JSON::getJsonFromMQTTCli((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- Objetos srvsock
		#if defined(JsonParser_ServerSocket_Enabled)
		if((result = JSON::getJsonFromServerSocket((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- Objetos externos de prop�sito general
		if (std::is_same<T, common_range_minmaxthres_double>::value){
			return JSON::getJsonFromRangeMinMaxThresDouble((const common_range_minmaxthres_double&)obj);
		}
		//----- Objetos state
		#if defined(JsonParser_EVStateMachine_Enabled)
		if((result = JSON::getJsonFromEVStateMachine((const T&)obj, type)) != NULL){
			return result;
		}
		#endif
		//----- Objetos requests
		#if defined(JsonParser_RequestsManager_Enabled)
		if((result = JSON::getJsonFromRequestsManagerObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif

		//----- Objetos scheduler
		#if defined(JsonParser_SchedulerManager_Enabled)
		if((result = JSON::getJsonFromSchedulerManagerObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif

		//----- Objetos SysManager
		#if defined(JsonParser_SysManager_Enabled)
		if((result = JSON::getJsonFromSysManagerObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif

		//----- Objetos ModulatorManager
		#if defined(JsonParser_ModulatorManager_Enabled)
		if((result = JSON::getJsonFromModulatorManagerObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif

		//----- Objetos OCPPManager
		#if defined(JsonParser_OCPPManager_Enabled)
		if((result = JSON::getJsonFromOCPPManagerObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif

		//----- Objetos ModbusMap
		#if defined(JsonParser_ModbusMap_Enabled)
		if((result = JSON::getJsonFromModbusMapObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif

		//----- Objetos WSClient
		#if defined(JsonParser_WSClient_Enabled)
		if((result = JSON::getJsonFromWSClientObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif

		//----- Objetos SolarManager
		#if defined(JsonParser_SolarManager_Enabled)
		if((result = JSON::getJsonFromSolarManagerObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif

		//----- Objetos EmbWeb
		#if defined(JsonParser_EmbWeb_Enabled)
		if((result = JSON::getJsonFromEmbeddedWebObj((const T&)obj, type)) != NULL){
			return result;
		}
		#endif

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

		// key: heapFree
		if((value = cJSON_GetObjectItem(obj, p_heapFree)) == NULL){
			DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromJson: heapFree is NULL");
			goto _getNotificationFromJson_Exit;
		}
		notif.header.heapFree = obj->valueint;

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
		// key: heapFree
		if((value = cJSON_GetObjectItem(obj, p_heapFree)) == NULL){
			resp.error.code = Blob::ErrEmptyContent;
			strcpy(resp.error.descr, Blob::errList[resp.error.code]);
			goto _getResponseFromJson_Exit;
		}
		resp.header.heapFree = obj->valueint;

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

		if constexpr (std::is_same<T,int>::value){
			obj = json->valueint;
			return (1 << 0);
		}

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
		#if defined(JsonParser_HMIManager_Enabled)
		if((result = JSON::getHMIObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		#if defined(JsonParser_BlufiManager_Enabled)
		//decodifica objeto blufiMan
		if (std::is_same<T, Blob::BlufiCfgData_t>::value){
			result = JSON::getBlufiManStatFromJson((Blob::BlufiCfgData_t&)obj, json_obj);
			goto _getObjFromJson_Exit;
		}
		#endif
		#if defined(JsonParser_AMManager_Enabled)
		//---- Decodifica Objetos metering
		if((result = JSON::getMeteringObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		#if defined(JsonParser_ShuckoManager_Enabled)
		//---- Decodifica Objetos shucko
		if((result = JSON::getShuckoObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		#if defined(JsonParser_MennekesManager_Enabled)
		//---- Decodifica Objetos mennekes
		if((result = JSON::getMennekesObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos calendar
		#if defined(JsonParser_AstCalendar_Enabled)
		if((result = JSON::getCalendarObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos light
		#if defined(JsonParser_LightManager_Enabled)
		if((result = JSON::getLightObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos fwupd
		#if defined(JsonParser_FwUpdater_Enabled)
		if((result = JSON::getFwUpdObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos mqtt
		#if defined(JsonParser_MQTTClient_Enabled)
		if((result = JSON::getMQTTCliObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos srvsock
		#if defined(JsonParser_ServerSocket_Enabled)
		if((result = JSON::getServerSocketObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos schedman
		#if defined(JsonParser_SchedulerManager_Enabled)
		if((result = JSON::getSchedulerManagerObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos schedman
		#if defined(JsonParser_RequestsManager_Enabled)
		if((result = JSON::getRequestsManagerObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos modulator
		#if defined(JsonParser_ModulatorManager_Enabled)
		if((result = JSON::getModulatorManagerObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos modulator
		#if defined(JsonParser_SysManager_Enabled)
		if((result = JSON::getSysManagerObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos ocpp
		#if defined(JsonParser_OCPPManager_Enabled)
		if((result = JSON::getOCPPManagerObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos evsm
		#if defined(JsonParser_EVStateMachine_Enabled)
		if((result = JSON::getEVStateMachineObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos ModbusMap
		#if defined(JsonParser_ModbusMap_Enabled)
		if((result = JSON::getModbusMapObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos WSClient
		#if defined(JsonParser_WSClient_Enabled)
		if((result = JSON::getWSClientObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos Solar
		#if defined(JsonParser_SolarManager_Enabled)
		if((result = JSON::getSolarManagerObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif
		//---- Decodifica Objetos Embweb
		#if defined(JsonParser_EmbWeb_Enabled)
		if((result = JSON::getEmbeddedWebObjFromJson(obj, json_obj)) != 0){
			goto _getObjFromJson_Exit;
		}
		#endif

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
				if(isTokenInTopic(topic, "/cfg/") || isTokenInTopic(topic, "/value/") || isTokenInTopic(topic, "/modules/")  || isTokenInTopic(topic, "/boot/") || isTokenInTopic(topic, "/list_aps/") || isTokenInTopic(topic, "/analyzers/") || isTokenInTopic(topic, "/connector/") || isTokenInTopic(topic, "/tagsfile/") || isTokenInTopic(topic, "/boost/")){
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
				goto _gofdt_exit;
			}
			else if(isTokenInTopic(topic, "set/")){
				#if defined(JsonParser_SysManager_Enabled)
				if(isTokenInTopic(topic, "/fwupdate")){
					obj = (Blob::SetRequest_t<sys_fwUpdate_data>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<sys_fwUpdate_data>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<sys_fwUpdate_data>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<sys_fwUpdate_data>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				else if(isTokenInTopic(topic, "/simulator")){
					obj = (Blob::SetRequest_t<sys_simulator>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<sys_simulator>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<sys_simulator>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<sys_simulator>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				else if(isTokenInTopic(topic, "/reset")){
					obj = (Blob::SetRequest_t<sys_reset_data>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<sys_reset_data>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<sys_reset_data>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<sys_reset_data>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				else if(isTokenInTopic(topic, "/rfid")){
					obj = (Blob::SetRequest_t<rfid_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<rfid_manager>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<rfid_manager>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<rfid_manager>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				else if(isTokenInTopic(topic, "/sys")){
					if(isTokenInTopic(topic, "/boost")){
						obj = (Blob::SetRequest_t<int>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<int>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<int>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<int>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else if(isTokenInTopic(topic, "/stop_boost")){
						obj = (Blob::GetRequest_t*)Heap::memAlloc(sizeof(Blob::GetRequest_t));
						MBED_ASSERT(obj);
						if(getGetRequestFromJson(*(Blob::GetRequest_t*) (obj), json_obj)){
							*size = sizeof(Blob::GetRequest_t);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else{
						obj = (Blob::SetRequest_t<sys_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<sys_manager>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<sys_manager>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<sys_manager>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_AMManager_Enabled)
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
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_RequestsManager_Enabled)
				if(isTokenInTopic(topic, "/request")){
					obj = (Blob::NotificationData_t<requests_element_stat>*)Heap::memAlloc(sizeof(Blob::NotificationData_t<requests_element_stat>));
					MBED_ASSERT(obj);
					if(getNotificationFromJson(*(Blob::NotificationData_t<requests_element_stat>*) (obj), json_obj)){
						*size = sizeof(Blob::NotificationData_t<requests_element_stat>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				else if(isTokenInTopic(topic, "/del_tagsfile")){
					obj = (Blob::SetRequest_t<request_update_tag_file>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<request_update_tag_file>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<request_update_tag_file>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<request_update_tag_file>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				else if(isTokenInTopic(topic, "/tagsfile")){
					obj = (Blob::SetRequest_t<request_update_tag_file>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<request_update_tag_file>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<request_update_tag_file>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<request_update_tag_file>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				else if(isTokenInTopic(topic, "/reqman")){
					obj = (Blob::SetRequest_t<requests_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<requests_manager>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<requests_manager>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<requests_manager>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				#endif

				#if defined(JsonParser_AstCalendar_Enabled)
				if(isTokenInTopic(topic, "/astcal")){
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
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_LightManager_Enabled)
				if(isTokenInTopic(topic, "/light")){
					if(isTokenInTopic(topic, "/cfg/")){
						obj = (Blob::SetRequest_t<light_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<light_manager>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<light_manager>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<light_manager>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else if(isTokenInTopic(topic, "/value/")){
						obj = (Blob::SetRequest_t<light_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<light_manager>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<light_manager>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<light_manager>);
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
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_FwUpdater_Enabled)
				if(isTokenInTopic(topic, "/fwupd")){
					if(isTokenInTopic(topic, "/start")){
						obj = (Blob::SetRequest_t<fwupd_manager_job>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<fwupd_manager_job>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<fwupd_manager_job>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<fwupd_manager_job>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else if(isTokenInTopic(topic, "/cfg/")){
						obj = (Blob::SetRequest_t<fwupd_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<fwupd_manager>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<fwupd_manager>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<fwupd_manager>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_MQTTClient_Enabled)
				if(isTokenInTopic(topic, "/mqtt")){
					if(isTokenInTopic(topic, "/cfg/")){
						obj = (Blob::SetRequest_t<mqtt_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<mqtt_manager>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<mqtt_manager>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<mqtt_manager>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					goto _gofdt_exit;
				}
				#endif

				#if defined(JsonParser_SchedulerManager_Enabled)
				if(isTokenInTopic(topic, "/schedman/")){
					DEBUG_TRACE_D(true, "[JsonParser]....", "Schedman element cfg");
					obj = (Blob::SetRequest_t<scheduler_element>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<scheduler_element>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<scheduler_element>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<scheduler_element>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				else if(isTokenInTopic(topic, "/schedman")){
					if(isTokenInTopic(topic, "/filter_task")){
						obj = (Blob::SetRequest_t<scheduler_filter_task>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<scheduler_filter_task>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<scheduler_filter_task>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<scheduler_filter_task>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}else{
						obj = (Blob::SetRequest_t<scheduler_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<scheduler_manager>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<scheduler_manager>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<scheduler_manager>);
						}
						else{
							obj = (Blob::SetRequest_t<scheduler_element>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<scheduler_element>));
							MBED_ASSERT(obj);
							if(getSetRequestFromJson(*(Blob::SetRequest_t<scheduler_element>*) (obj), json_obj)){
								*size = sizeof(Blob::SetRequest_t<scheduler_element>);
							}
							else{
								*size = 0;
								Heap::memFree(obj);
								obj = NULL;
							}
						}
					}
					goto _gofdt_exit;
				}
				#endif

				#if defined(JsonParser_MennekesManager_Enabled)
				if((isTokenInTopic(topic, "/value") || isTokenInTopic(topic, "/cfg")) && isTokenInTopic(topic, "/mennekes")){
					obj = (Blob::SetRequest_t<mennekes_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<mennekes_manager>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<mennekes_manager>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<mennekes_manager>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_ShuckoManager_Enabled)
				if((isTokenInTopic(topic, "/cfg") || isTokenInTopic(topic, "/value")) && isTokenInTopic(topic, "/schuko")){
					obj = (Blob::SetRequest_t<shucko_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<shucko_manager>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<shucko_manager>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<shucko_manager>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_ModulatorManager_Enabled)
				if(isTokenInTopic(topic, "/modulator")){
					if(isTokenInTopic(topic, "/cfg/") || isTokenInTopic(topic, "/value/")){
						obj = (Blob::SetRequest_t<modulator_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<modulator_manager>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<modulator_manager>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<modulator_manager>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else if(isTokenInTopic(topic, "/rt/")){
						obj = (Blob::SetRequest_t<ModulatorRt>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<ModulatorRt>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<ModulatorRt>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<ModulatorRt>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					else if(isTokenInTopic(topic, "/hist-")){
						obj = (Blob::SetRequest_t<ModulatorSearchFilter>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<ModulatorSearchFilter>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<ModulatorSearchFilter>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<ModulatorSearchFilter>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_OCPPManager_Enabled)
				else if(isTokenInTopic(topic, "/ocpp")){
					obj = (Blob::SetRequest_t<ocpp_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<ocpp_manager>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<ocpp_manager>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<ocpp_manager>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_EVStateMachine_Enabled)
				else if(isTokenInTopic(topic, "/evsm")){
					obj = (Blob::SetRequest_t<evsm_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<evsm_manager>));
					MBED_ASSERT(obj);
					if(getSetRequestFromJson(*(Blob::SetRequest_t<evsm_manager>*) (obj), json_obj)){
						*size = sizeof(Blob::SetRequest_t<evsm_manager>);
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				#endif
				#if defined(JsonParser_ModbusMap_Enabled)
				else if(isTokenInTopic(topic, "/modbus")){
					if(isTokenInTopic(topic, "/cfg/") || isTokenInTopic(topic, "/value/")){
						obj = (Blob::SetRequest_t<ModbusMapObj>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<ModbusMapObj>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<ModbusMapObj>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<ModbusMapObj>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
						goto _gofdt_exit;
					}
				}
				#endif
				#if defined(JsonParser_WSClient_Enabled)
				else if(isTokenInTopic(topic, "/wscli") || isTokenInTopic(topic, "/wslog")){
					if(isTokenInTopic(topic, "/connect") || isTokenInTopic(topic, "/disconnect") || isTokenInTopic(topic, "/start-log") || isTokenInTopic(topic, "/stop-log")){
						obj = (Blob::SetRequest_t<WSClientUri>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<WSClientUri>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<WSClientUri>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<WSClientUri>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
						goto _gofdt_exit;
					}
				}
				#endif

				#if defined(JsonParser_SolarManager_Enabled)
				if(isTokenInTopic(topic, "/solar")){
					if(isTokenInTopic(topic, "/cfg/") || isTokenInTopic(topic, "/value/")){
						obj = (Blob::SetRequest_t<solar_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<solar_manager>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<solar_manager>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<solar_manager>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					goto _gofdt_exit;
				}
				#endif

				#if defined(JsonParser_HMIManager_Enabled)
				if(isTokenInTopic(topic, "/hmi")){
					if(isTokenInTopic(topic, "/cfg/")){
						obj = (Blob::SetRequest_t<hmi_manager>*)Heap::memAlloc(sizeof(Blob::SetRequest_t<hmi_manager>));
						MBED_ASSERT(obj);
						if(getSetRequestFromJson(*(Blob::SetRequest_t<hmi_manager>*) (obj), json_obj)){
							*size = sizeof(Blob::SetRequest_t<hmi_manager>);
						}
						else{
							*size = 0;
							Heap::memFree(obj);
							obj = NULL;
						}
					}
					goto _gofdt_exit;
				}
				#endif

				DEBUG_TRACE_E(true, "[JsonParser]....", "No se encuentra el modulo");
				goto _gofdt_exit;
			}
			else if(isTokenInTopic(topic, "stat/"))
			{
				#if defined(JsonParser_MQTTClient_Enabled)
				if(isTokenInTopic(topic, "/conn/mqtt")){
					obj = (Blob::MqttStatusFlags*)Heap::memAlloc(sizeof(Blob::MqttStatusFlags));
					MBED_ASSERT(obj);
					if(getObjFromJson(*(Blob::MqttStatusFlags*)(obj), json_obj)){
						*size = sizeof(Blob::MqttStatusFlags);				
					}
					else{
						*size = 0;
						Heap::memFree(obj);
						obj = NULL;
					}
					goto _gofdt_exit;
				}
				#endif
				DEBUG_TRACE_E(true, "[JsonParser]....", "getObjectFromDataTopic: topic stat no controlado");

			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getObjectFromDataTopic: topic no controlado");
			}
		}
_gofdt_exit:
		if(std::is_same<U,char>::value){
			cJSON_Delete(json_obj);
		}
		return obj;
	}



	static cJSON* getDataFromObjTopic(char* topic, void* data, uint16_t size){
		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = NULL;
		if(size == sizeof(Blob::GetRequest_t)){
			json_obj = getJsonFromGetRequest(*(Blob::GetRequest_t*)data);
			return json_obj;
		}
		#if defined(JsonParser_AMManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/energy")){
			if(size == sizeof(Blob::Response_t<metering_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<metering_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<metering_manager>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "analyzers")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<metering_manager>*)data, ObjSelectStateSub);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: metering-response");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<metering_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<metering_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<metering_manager>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "analyzers")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<metering_manager>*)data, ObjSelectStateSub);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: metering-notification");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: metering");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_RequestsManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/reqman")){
			if(size == sizeof(Blob::Response_t<requests_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<requests_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<requests_manager>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "tagid")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<requests_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: RequestsManager");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::Response_t<request_update_tag_file>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<request_update_tag_file>*)data);
			}
			else if(size == sizeof(Blob::NotificationData_t<requests_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<requests_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<requests_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: RequestsManager");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::Response_t<requests_element>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<requests_element>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<requests_element>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: RequestsElement");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<requests_element>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<requests_element>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value") || isTokenInTopic(topic, "start") || isTokenInTopic(topic, "stop") || isTokenInTopic(topic, "permiss")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<requests_element>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: RequestsElement");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<requests_element_stat>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<requests_element_stat>*)data);
			}
			else if(isTokenInTopic(topic, "tag_id")){
				json_obj = cJSON_CreateObject();
			}
			else if(isTokenInTopic(topic, "_tagid_check")){
				json_obj = cJSON_CreateObject();
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: RequestsManager, tipo mensaje no controlado");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		if(isTokenInTopic(topic, "set") && isTokenInTopic(topic, "/reqman")){
			if(size == sizeof(Blob::SetRequest_t<requests_manager>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<requests_manager>*)data);
			}
			else if(size == sizeof(Blob::SetRequest_t<requests_element>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<requests_element>*)data);
			}
			else if(size == sizeof(Blob::SetRequest_t<RequestsSourcesActv>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<RequestsSourcesActv>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: RequestsManager, tipo mensaje no controlado");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_EVStateMachine_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/evsm")){
			if(isTokenInTopic(topic, "evt")){
				if(size == sizeof(Blob::Response_t<connector_manager>)){
					json_obj = getJsonFromResponse(*(Blob::Response_t<connector_manager>*)data);
				}
				else if(size == sizeof(Blob::NotificationData_t<connector_manager>)){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<connector_manager>*)data);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: evsm");
					json_obj = cJSON_CreateObject();
				}
			}
			else if (isTokenInTopic(topic, "value")){
				if(size == sizeof(Blob::Response_t<connector_manager>)){
					json_obj = getJsonFromResponse(*(Blob::Response_t<connector_manager>*)data);
				}
				else if(size == sizeof(Blob::NotificationData_t<connector_manager>)){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<connector_manager>*)data);
				}
				else if(size == sizeof(Blob::Response_t<evsm_connector_list>)){
					json_obj = getJsonFromResponse(*(Blob::Response_t<evsm_connector_list>*)data);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: evsm");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(isTokenInTopic(topic, "cfg")){
				if(size == sizeof(Blob::Response_t<evsm_manager>)){
					json_obj = getJsonFromResponse(*(Blob::Response_t<evsm_manager>*)data);
				}
				else if(size == sizeof(Blob::NotificationData_t<evsm_manager>)){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<evsm_manager>*)data);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: evsm");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: evsm");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_AstCalendar_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/astcal")){
			if(size == sizeof(Blob::Response_t<calendar_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<calendar_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<calendar_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: calendar-response");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<calendar_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<calendar_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<calendar_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: calendar-notification");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: calendar");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_LightManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/light")){
			if(size == sizeof(Blob::NotificationData_t<light_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<light_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<light_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: light-notification");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::Response_t<light_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<light_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<light_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: light-response");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: light");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_FwUpdater_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/fwupd")){
			if(size == sizeof(Blob::NotificationData_t<fwupd_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<fwupd_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value") || isTokenInTopic(topic, "start")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<fwupd_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: fwupd-notification");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::Response_t<fwupd_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<fwupd_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value") || isTokenInTopic(topic, "start")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<fwupd_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: fwupd-response");
					json_obj = cJSON_CreateObject();
				}
			}

			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: light");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_MQTTClient_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/mqtt")){
			if(size == sizeof(Blob::NotificationData_t<mqtt_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<mqtt_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<mqtt_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: mqtt-notification");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::Response_t<mqtt_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<mqtt_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<mqtt_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: mqtt-response");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::MqttStatusFlags)){
				json_obj = JsonParser::getJsonFromObj(*(Blob::MqttStatusFlags*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: mqtt");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		if(isTokenInTopic(topic, "set") && isTokenInTopic(topic, "/mqtt")){
			if(size == sizeof(Blob::SetRequest_t<mqtt_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<mqtt_manager>*)data);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: mqtt-notification");
					json_obj = cJSON_CreateObject();
				}
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_ServerSocket_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/socket")){
			if(size == sizeof(Blob::NotificationData_t<srvsock_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<srvsock_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<srvsock_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: socket-notification");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::Response_t<srvsock_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<srvsock_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<srvsock_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: socket-response");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: socket");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif



		#if defined(JsonParser_SchedulerManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/schedman")){
			if(size == sizeof(Blob::Response_t<scheduler_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<scheduler_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<scheduler_manager>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "boot")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<scheduler_manager>*)data, ObjSelectAll);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: scheduler");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::Response_t<scheduler_element>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<scheduler_element>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<scheduler_element>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "boot")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<scheduler_element>*)data, ObjSelectAll);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: scheduler");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<scheduler_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<scheduler_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<scheduler_manager>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "boot")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<scheduler_manager>*)data, ObjSelectAll);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: scheduler");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<scheduler_element>)){
				if(isTokenInTopic(topic, "start") || isTokenInTopic(topic, "stop") || isTokenInTopic(topic, "enable") || isTokenInTopic(topic, "disable") || 
				   isTokenInTopic(topic, "start_power") || isTokenInTopic(topic, "stop_power")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<scheduler_element>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<scheduler_element>*)data, ObjSelectCfg);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: scheduler");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::Response_t<scheduler_element_cfg>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<scheduler_element_cfg>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: scheduler_element_cfg");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		if(isTokenInTopic(topic, "set") && isTokenInTopic(topic, "/schedman")){
			if(size == sizeof(Blob::SetRequest_t<scheduler_manager>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<scheduler_manager>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: scheduler, tipo mensaje no controlado");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif

		#if defined(JsonParser_SysManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/sys")){
			if(size == sizeof(Blob::Response_t<sys_manager>) && (isTokenInTopic(topic, "cfg") || isTokenInTopic(topic, "value") || isTokenInTopic(topic, "all"))){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<sys_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<sys_manager>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "all")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<sys_manager>*)data, ObjSelectAll);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: SysManager");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<sys_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<sys_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<sys_manager>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "all")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<sys_manager>*)data, ObjSelectAll);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: SysManager");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<sys_boot>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<sys_boot>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::Response_t<sys_boot>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<sys_boot>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::Response_t<rfid_manager>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<rfid_manager>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::Response_t<sys_fwUpdate_data>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<sys_fwUpdate_data>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::NotificationData_t<sys_fwUpdate_data>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<sys_fwUpdate_data>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::Response_t<sys_simulator>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<sys_simulator>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::Response_t<sys_reset_data>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<sys_reset_data>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::Response_t<int>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<int>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: SysManager, tipo mensaje no controlado");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		if(isTokenInTopic(topic, "set") && isTokenInTopic(topic, "/sys")){
			if(size == sizeof(Blob::SetRequest_t<sys_manager>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<sys_manager>*)data);
			}
			else if(size == sizeof(Blob::SetRequest_t<sys_simulator>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<sys_simulator>*)data);
			}
			else if(size == sizeof(Blob::SetRequest_t<sys_fwUpdate_data>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<sys_fwUpdate_data>*)data);
			}
			else if(size == sizeof(Blob::SetRequest_t<sys_reset_data>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<sys_reset_data>*)data);
			}
			else if(size == sizeof(Blob::SetRequest_t<rfid_manager>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<rfid_manager>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: SysManager, tipo mensaje no controlado");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_ModulatorManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/modulator")){
			if(isTokenInTopic(topic, "/historic/") && size == sizeof(Blob::NotificationData_t<ModulatorHistoric>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<ModulatorHistoric>*)data, ObjSelectAll);
			}
			else if(isTokenInTopic(topic, "/hist-search/")){
				if(size == sizeof(Blob::Response_t<ModulatorHistFile>)){
					json_obj = getJsonFromResponse(*(Blob::Response_t<ModulatorHistFile>*)data, ObjSelectAll);
				}
			}
			else if(isTokenInTopic(topic, "/hist-erase/")){
				if(size == sizeof(Blob::Response_t<ModulatorEraseReport>)){
					json_obj = getJsonFromResponse(*(Blob::Response_t<ModulatorEraseReport>*)data, ObjSelectAll);
				}
			}
			else if(size == sizeof(Blob::Response_t<modulator_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<modulator_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<modulator_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: Modulator");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<modulator_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<modulator_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<modulator_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: Modulator");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<ModulatorStatProcesses>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<ModulatorStatProcesses>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::Response_t<ModulatorStatProcesses>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<ModulatorStatProcesses>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::Response_t<ModulatorRt>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<ModulatorRt>*)data, ObjSelectAll);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: Modulator, tipo mensaje no controlado");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_ShuckoManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/schuko")){
			if(size == sizeof(Blob::Response_t<shucko_manager>)){
				if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<shucko_manager>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<shucko_manager>*)data, ObjSelectCfg);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: schuko");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: schuko");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_MennekesManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/mennekes")){
			if(size == sizeof(Blob::Response_t<mennekes_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<mennekes_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value") || isTokenInTopic(topic, "connector")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<mennekes_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: Mennekes");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<mennekes_manager>)){
				if(isTokenInTopic(topic, "connector")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<mennekes_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getJsonFromNotification: Mennekes");
					json_obj = cJSON_CreateObject();
				}
			}
			return json_obj;
		}
		#endif

		#if defined(JsonParser_OCPPManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/ocpp")){
			if(size == sizeof(Blob::Response_t<ocpp_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<ocpp_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<ocpp_manager>*)data, ObjSelectState);
				}
				else if(isTokenInTopic(topic, "all")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<ocpp_manager>*)data, ObjSelectAll);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: OCPPManager");
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<ocpp_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<ocpp_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<ocpp_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: OCPPManager");
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: OCPPManager, tipo mensaje no controlado");
			}
			return json_obj;
		}
		if(isTokenInTopic(topic, "set") && isTokenInTopic(topic, "/ocpp")){
			if(size == sizeof(Blob::SetRequest_t<ocpp_manager>)){
				json_obj = getJsonFromSetRequest(*(Blob::SetRequest_t<ocpp_manager>*)data);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: scheduler, tipo mensaje no controlado");
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_SolarManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/solar")){
			if(size == sizeof(Blob::Response_t<solar_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<solar_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<solar_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: Modulator");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<solar_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<solar_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<solar_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: Solar");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: Solar, tipo mensaje no controlado");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif

		#if defined(JsonParser_ModbusMap_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/modbus")){
			if(size == sizeof(Blob::Response_t<ModbusMapObj>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<ModbusMapObj>*)data, ObjSelectCfg);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: modbus-response");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<ModbusMapObj>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<ModbusMapObj>*)data, ObjSelectCfg);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: modbus-notification");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: modbus");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_WSClient_Enabled)
		if(isTokenInTopic(topic, "stat") && (isTokenInTopic(topic, "/wscli") || isTokenInTopic(topic, "/wslog"))){
			if(size == sizeof(Blob::Response_t<WSClientUri>)){
				json_obj = getJsonFromResponse(*(Blob::Response_t<WSClientUri>*)data, ObjSelectAll);
			}
			else if(size == sizeof(Blob::NotificationData_t<WSClientUri>)){
				json_obj = getJsonFromNotification(*(Blob::NotificationData_t<WSClientUri>*)data, ObjSelectAll);
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: wscli | wslog");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_HMIManager_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/hmi")){
			if(size == sizeof(Blob::Response_t<hmi_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<hmi_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<hmi_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: HMI");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<hmi_manager>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<hmi_manager>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<hmi_manager>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: HMI");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: HMI, tipo mensaje no controlado");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif
		#if defined(JsonParser_EmbWeb_Enabled)
		if(isTokenInTopic(topic, "stat") && isTokenInTopic(topic, "/embweb")){
			if(size == sizeof(Blob::Response_t<embweb>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<embweb>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromResponse(*(Blob::Response_t<embweb>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getResponseFromObjTopic: EmbWeb");
					json_obj = cJSON_CreateObject();
				}
			}
			else if(size == sizeof(Blob::NotificationData_t<embweb>)){
				if(isTokenInTopic(topic, "cfg")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<embweb>*)data, ObjSelectCfg);
				}
				else if(isTokenInTopic(topic, "value")){
					json_obj = getJsonFromNotification(*(Blob::NotificationData_t<embweb>*)data, ObjSelectState);
				}
				else{
					DEBUG_TRACE_E(true, "[JsonParser]....", "getNotificationFromObjTopic: EmbWeb");
					json_obj = cJSON_CreateObject();
				}
			}
			else{
				DEBUG_TRACE_E(true, "[JsonParser]....", "getDataFromObjTopic: EmbWeb, tipo mensaje no controlado");
				json_obj = cJSON_CreateObject();
			}
			return json_obj;
		}
		#endif

		DEBUG_TRACE_W(true, "[JsonParser]....", "getDataFromObjTopic: topic no controlado");
		json_obj = cJSON_CreateObject();
		return json_obj;
	}



	static void printBinaryObject(char* topic, void* data, uint16_t size, bool formatted = false){
		#if JSONPARSER_ENABLE_PrintBinaryObject == true
		// obtengo objeto json en funci�n del tipo
		cJSON *json_obj = getDataFromObjTopic(topic, data, size);

		char* jsonMsg;
		if(formatted)
			jsonMsg = cJSON_Print(json_obj);
		else
			jsonMsg = cJSON_PrintUnformatted(json_obj);
		cJSON_Delete(json_obj);
		
		if(json_obj != NULL){
			DEBUG_TRACE_D(true, "[JsonParser]....", "Topic: %s, Msg: %s", topic, jsonMsg);
		}
		Heap::memFree(jsonMsg);
		#endif
	}

};	// end class Parser





#endif
