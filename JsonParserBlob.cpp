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



//---------------------------------------------------------------------------------
//- Param Keys --------------------------------------------------------------------
//---------------------------------------------------------------------------------

const char * JsonParser::p_actions		= "actions";
const char * JsonParser::p_active		= "active";
const char * JsonParser::p_alsData		= "alsData";
const char * JsonParser::p_ampacity		= "ampacity";
const char * JsonParser::p_analyzer		= "analyzer";
const char * JsonParser::p_analyzers	= "analyzers";
const char * JsonParser::p_aPow			= "aPow";
const char * JsonParser::p_assignment	= "assignment";
const char * JsonParser::p_ast			= "ast";
const char * JsonParser::p_astcal		= "astcal";
const char * JsonParser::p_astCorr		= "astCorr";
const char * JsonParser::p_barMode		= "barMode";
const char * JsonParser::p_blinkOn		= "blinkOn";
const char * JsonParser::p_blinkOff		= "blinkOff";
const char * JsonParser::p_bootCondition= "bootCondition";
const char * JsonParser::p_bootVers		= "bootVers";
const char * JsonParser::p_calibData	= "calibData";
const char * JsonParser::p_cardFile		= "cardFile";
const char * JsonParser::p_cfg			= "cfg";
const char * JsonParser::p_channel		= "channel";
const char * JsonParser::p_chargeProcess= "chargeProcess";
const char * JsonParser::p_childSync	= "childSync";
const char * JsonParser::p_clock		= "clock";
const char * JsonParser::p_code			= "code";
const char * JsonParser::p_connCfg      = "connCfg";
const char * JsonParser::p_connector	= "connector";
const char * JsonParser::p_connectorId	= "connectorId";
const char * JsonParser::p_connectorName= "connectorName";
const char * JsonParser::p_connectorType= "connectorType";
const char * JsonParser::p_coords		= "coords";
const char * JsonParser::p_current		= "current";
const char * JsonParser::p_curve		= "curve";
const char * JsonParser::p_data			= "data";
const char * JsonParser::p_date			= "date";
const char * JsonParser::p_dawn			= "dawn";
const char * JsonParser::p_delay		= "delay";
const char * JsonParser::p_descr		= "descr";
const char * JsonParser::p_devCount		= "devCount";
const char * JsonParser::p_devList		= "devList";
const char * JsonParser::p_dusk			= "dusk";
const char * JsonParser::p_enabled		= "enabled";
const char * JsonParser::p_energy		= "energy";
const char * JsonParser::p_energyValues	= "energyValues";
const char * JsonParser::p_eocMode		= "eocMode";
const char * JsonParser::p_error		= "error";
const char * JsonParser::p_eth			= "ethernet";
const char * JsonParser::p_ethDhcpen    = "ethDhcpen";
const char * JsonParser::p_ethipstatic  = "ethipstatic";
const char * JsonParser::p_ethmask      = "ethmask";
const char * JsonParser::p_ethgw        = "ethgw";
const char * JsonParser::p_ethdns       = "ethdns";
const char * JsonParser::p_evtFlags		= "evtFlags";
const char * JsonParser::p_extraInfo	= "extraInfo";
const char * JsonParser::p_flags		= "flags";
const char * JsonParser::p_freq			= "freq";
const char * JsonParser::p_fwSize		= "fwSize";
const char * JsonParser::p_fwUrl		= "fwUrl";
const char * JsonParser::p_fwv			= "fwv";
const char * JsonParser::p_fwvPot		= "fwv_pot";
const char * JsonParser::p_fwvCortex	= "fwv_cortex";
const char * JsonParser::p_geoloc		= "geoloc";
const char * JsonParser::p_groupMask	= "groupMask";
const char * JsonParser::p_guiMode		= "guiMode";
const char * JsonParser::p_header		= "header";
const char * JsonParser::p_holdCount	= "holdCount";
const char * JsonParser::p_hwv			= "hwv";
const char * JsonParser::p_hwvPot		= "hwv_pot";
const char * JsonParser::p_iconMode		= "iconMode";
const char * JsonParser::p_id			= "id";
const char * JsonParser::p_idTag		= "idTag";
const char * JsonParser::p_idTrans		= "idTrans";
const char * JsonParser::p_inDomo		= "inDomo";
const char * JsonParser::p_isRoot		= "isRoot";
const char * JsonParser::p_job			= "job";
const char * JsonParser::p_jobId		= "jobId";
const char * JsonParser::p_keepAlive	= "keepAlive";
const char * JsonParser::p_keys			= "keys";
const char * JsonParser::p_last			= "last";
const char * JsonParser::p_latitude		= "latitude";
const char * JsonParser::p_leakage		= "leakage";
const char * JsonParser::p_light		= "light";
const char * JsonParser::p_limited		= "limited";
const char * JsonParser::p_loadPercent	= "loadPercent";
const char * JsonParser::p_localtime	= "localtime";
const char * JsonParser::p_longitude	= "longitude";
const char * JsonParser::p_lux			= "lux";
const char * JsonParser::p_luxLevel		= "luxLevel";
const char * JsonParser::p_mac			= "mac";
const char * JsonParser::p_max			= "max";
const char * JsonParser::p_maxAmpacity	= "maxAmpacity";
const char * JsonParser::p_measPeriod	= "measPeriod";
const char * JsonParser::p_measRegs		= "measRegs";
const char * JsonParser::p_measureValues= "measureValues";
const char * JsonParser::p_meshId		= "meshId";
const char * JsonParser::p_meshPasswd	= "meshPasswd";
const char * JsonParser::p_meterRegs	= "meterRegs";
const char * JsonParser::p_min			= "min";
const char * JsonParser::p_minCurrent	= "minCurrent";
const char * JsonParser::p_minmaxData	= "minmaxData";
const char * JsonParser::p_minPower		= "minPower";
const char * JsonParser::p_minPwm		= "minPwm";
const char * JsonParser::p_mode			= "mode";
const char * JsonParser::p_modules		= "modules";
const char * JsonParser::p_mqttPort		= "mqttPort";
const char * JsonParser::p_mqttUrl		= "mqttUrl";
const char * JsonParser::p_mqttUser		= "mqttUser";
const char * JsonParser::p_mqttPass		= "mqttPass";
const char * JsonParser::p_mqttData		= "mqttData";
const char * JsonParser::p_mqttClientId	= "mqttClientId";
const char * JsonParser::p_msPow		= "msPow";
const char * JsonParser::p_netCfg		= "netCfg";
const char * JsonParser::p_netReady		= "netReady";
const char * JsonParser::p_notifCycle	= "notifCycle";
const char * JsonParser::p_now			= "now";
const char * JsonParser::p_numActions	= "numActions";
const char * JsonParser::p_nvsId		= "nvsId";
const char * JsonParser::p_outData		= "outData";
const char * JsonParser::p_outValue		= "outValue";
const char * JsonParser::p_passwd		= "passwd";
const char * JsonParser::p_period		= "period";
const char * JsonParser::p_periods		= "periods";
const char * JsonParser::p_pfactor		= "pfactor";
const char * JsonParser::p_plugPresent	= "plugPresent";
const char * JsonParser::p_plugLimit	= "plugLimit";
const char * JsonParser::p_phase		= "phase";
const char * JsonParser::p_pwm			= "pwm";
const char * JsonParser::p_qos			= "qos";
const char * JsonParser::p_reactive		= "reactive";
const char * JsonParser::p_reductionStart= "reductionStart";
const char * JsonParser::p_reductionStop= "reductionStop";
const char * JsonParser::p_request		= "request";
const char * JsonParser::p_requestStart	= "requestStart";
const char * JsonParser::p_requestStop	= "requestStop";
const char * JsonParser::p_relOverload	= "relOverload";
const char * JsonParser::p_rfid			= "rfid";
const char * JsonParser::p_rfidCfg		= "rfidCfg";
const char * JsonParser::p_rPow			= "rPow";
const char * JsonParser::p_rst_reason   = "rst_reason";
const char * JsonParser::p_samples		= "samples";
const char * JsonParser::p_seasonCfg	= "seasonCfg";
const char * JsonParser::p_serial		= "serial";
const char * JsonParser::p_selectorPosition	= "selectorPosition";
const char * JsonParser::p_shucko		= "schuko";
const char * JsonParser::p_since		= "since";
const char * JsonParser::p_solarPriority= "solarPriority";
const char * JsonParser::p_staEssid		= "staEssid";
const char * JsonParser::p_staPasswd	= "staPasswd";
const char * JsonParser::p_lastStaEssid		= "lastStaEssid";
const char * JsonParser::p_lastStaPasswd	= "lastStaPasswd";
const char * JsonParser::p_start		= "start";
const char * JsonParser::p_status		= "status";
const char * JsonParser::p_stat			= "stat";
const char * JsonParser::p_thdA			= "thdA";
const char * JsonParser::p_thdV			= "thdV";
const char * JsonParser::p_thres		= "thres";
const char * JsonParser::p_time			= "time";
const char * JsonParser::p_timeout		= "timeout";
const char * JsonParser::p_timestamp	= "timestamp";
const char * JsonParser::p_heapFree		= "heapFree";
const char * JsonParser::p_timezone		= "timezone";
const char * JsonParser::p_topic		= "topic";
const char * JsonParser::p_type			= "type";
const char * JsonParser::p_uid			= "uid";
const char * JsonParser::p_until		= "until";
const char * JsonParser::p_updFlags		= "updFlags";
const char * JsonParser::p_updProgress	= "updProgress";
const char * JsonParser::p_url			= "url";
const char * JsonParser::p_username		= "username";
const char * JsonParser::p_verbosity	= "verbosity";
const char * JsonParser::p_version		= "version";
const char * JsonParser::p_voltage		= "voltage";
const char * JsonParser::p_wdowDawnStart= "wdowDawnStart";
const char * JsonParser::p_wdowDawnStop	= "wdowDawnStop";
const char * JsonParser::p_wdowDuskStart= "wdowDuskStart";
const char * JsonParser::p_wdowDuskStop	= "wdowDuskStop";
const char * JsonParser::p_wifi_sta		= "wifi_sta";
const char * JsonParser::p_wifiDhcpen   = "wifiDhcpen";
const char * JsonParser::p_wifiipstatic = "wifiipstatic";
const char * JsonParser::p_wifimask     = "wifimask";
const char * JsonParser::p_wifigw       = "wifigw";
const char * JsonParser::p_wifidns      = "wifidns";
const char * JsonParser::p_ssid		    = "ssid";
const char * JsonParser::p_pass	        = "pass";
const char * JsonParser::p_ip		    = "ip";
const char * JsonParser::p_port	        = "port";
const char * JsonParser::p_state	    = "state";
const char * JsonParser::p_idCharge	    = "idCharge";
const char * JsonParser::p_user 	    = "user";
const char * JsonParser::p_dataAnalyzer = "dataAnalyzer";
const char * JsonParser::p_source       = "source";
const char * JsonParser::p_priority     = "priority";
const char * JsonParser::p_action       = "action";
const char * JsonParser::p_group        = "group";
const char * JsonParser::p_elements     = "elements";
const char * JsonParser::p_name         = "name";
const char * JsonParser::p_tasks        = "tasks";
const char * JsonParser::p_initTime     = "initTime";
const char * JsonParser::p_endTime      = "endTime";
const char * JsonParser::p_day          = "day";
const char * JsonParser::p_month        = "month";
const char * JsonParser::p_weekday      = "weekday";
const char * JsonParser::p_timeList     = "timeList";
const char * JsonParser::p_hour         = "hourMin";
const char * JsonParser::p_duration     = "duration";
const char * JsonParser::p_defaultState = "defaultState";
const char * JsonParser::p_modeUser     = "modeUser";
const char * JsonParser::p_modeElements = "modeElements";
const char * JsonParser::p_modeActivation= "modeActivation";
const char * JsonParser::p_sources      = "sources";
const char * JsonParser::p_childs       = "childs";
const char * JsonParser::p_event       = "event";
const char * JsonParser::p_permis       = "permission";
const char * JsonParser::p_iconError       = "iconError";
const char * JsonParser::p_iconConn       = "iconConn";
const char * JsonParser::p_iconPlug       = "iconPlug";
const char * JsonParser::p_iconModul       = "iconModul";
const char * JsonParser::p_iconSched       = "iconSched";
const char * JsonParser::p_iconSched2       = "iconSched2";
const char * JsonParser::p_limitPower       = "limitPower";
const char * JsonParser::p_maxPower         = "maxPower";
const char * JsonParser::p_totalPower       = "totalPower";
const char * JsonParser::p_homePower       = "homePower";
const char * JsonParser::p_evsePower       = "evsePower";
const char * JsonParser::p_evseLimitPower      = "evseLimitPower";
const char * JsonParser::p_evseTotalPower      = "evseTotalPower";
const char * JsonParser::p_ownLimitPower   = "ownLimitPower";
const char * JsonParser::p_selectorPower   = "selectorPower";
const char * JsonParser::p_model		   = "model";
const char * JsonParser::p_localOperations   = "localOperations";
const char * JsonParser::p_remoteOperations   = "remoteOperations";
const char * JsonParser::p_count   				= "count";
const char * JsonParser::p_body   				= "body";
const char * JsonParser::p_inverse   			= "inverse";
const char * JsonParser::p_erased   			= "erased";
const char * JsonParser::p_remaining   			= "remaining";
const char * JsonParser::p_restore   			= "restore";
const char * JsonParser::p_totalCurrent	       	= "totalCurrent";
const char * JsonParser::p_serverUrl			= "serverUrl";
const char * JsonParser::p_pingInterval			= "pingInterval";
const char * JsonParser::p_bootInterval			= "bootInterval";
const char * JsonParser::p_connectionTimeOut			= "connectionTimeOut";
const char * JsonParser::p_splCfg			= "splCfg";
const char * JsonParser::p_network			= "network";
const char * JsonParser::p_mac_wifi 		= "mac_wifi";
const char * JsonParser::p_mac_eth 		    = "mac_ethernet";
const char * JsonParser::p_spl 		    = "spl";
const char * JsonParser::p_conn					= "connectors";

const char * JsonParser::p_listAPs					= "listAPs";
const char * JsonParser::p_midAnalyzers				= "midAnalyzers";
const char * JsonParser::p_timezoneCode		= "timezoneCode";
const char * JsonParser::p_wsConnected		= "wsConnected";
const char * JsonParser::p_wifiConnected		= "wifiConnected";
const char * JsonParser::p_ethConnected		= "ethConnected";
