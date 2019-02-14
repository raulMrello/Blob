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
const char * JsonParser::p_aPow			= "aPow";
const char * JsonParser::p_ast			= "ast";
const char * JsonParser::p_astcal		= "astcal";
const char * JsonParser::p_astCorr		= "astCorr";
const char * JsonParser::p_calibData	= "calibData";
const char * JsonParser::p_bootCondition= "bootCondition";
const char * JsonParser::p_cfg			= "cfg";
const char * JsonParser::p_channel		= "channel";
const char * JsonParser::p_code			= "code";
const char * JsonParser::p_current		= "current";
const char * JsonParser::p_curve		= "curve";
const char * JsonParser::p_data			= "data";
const char * JsonParser::p_date			= "date";
const char * JsonParser::p_descr		= "descr";
const char * JsonParser::p_devCount		= "devCount";
const char * JsonParser::p_devList		= "devList";
const char * JsonParser::p_enabled		= "enabled";
const char * JsonParser::p_energy		= "energy";
const char * JsonParser::p_energyValues	= "energyValues";
const char * JsonParser::p_error		= "error";
const char * JsonParser::p_evtFlags		= "evtFlags";
const char * JsonParser::p_flags		= "flags";
const char * JsonParser::p_freq			= "freq";
const char * JsonParser::p_fwSize		= "fwSize";
const char * JsonParser::p_fwUrl		= "fwUrl";
const char * JsonParser::p_fwv			= "fwv";
const char * JsonParser::p_groupMask	= "groupMask";
const char * JsonParser::p_header		= "header";
const char * JsonParser::p_hwv			= "hwv";
const char * JsonParser::p_id			= "id";
const char * JsonParser::p_idTrans		= "idTrans";
const char * JsonParser::p_job			= "job";
const char * JsonParser::p_jobId		= "jobId";
const char * JsonParser::p_keys			= "keys";
const char * JsonParser::p_latitude		= "latitude";
const char * JsonParser::p_light		= "light";
const char * JsonParser::p_longitude	= "longitude";
const char * JsonParser::p_lux			= "lux";
const char * JsonParser::p_luxLevel		= "luxLevel";
const char * JsonParser::p_mac			= "mac";
const char * JsonParser::p_max			= "max";
const char * JsonParser::p_measPeriod	= "measPeriod";
const char * JsonParser::p_measRegs		= "measRegs";
const char * JsonParser::p_measureValues= "measureValues";
const char * JsonParser::p_meshId		= "meshId";
const char * JsonParser::p_meshPasswd	= "meshPasswd";
const char * JsonParser::p_meterRegs	= "meterRegs";
const char * JsonParser::p_min			= "min";
const char * JsonParser::p_minmaxData	= "minmaxData";
const char * JsonParser::p_mode			= "mode";
const char * JsonParser::p_mqttPort		= "mqttPort";
const char * JsonParser::p_mqttUrl		= "mqttUrl";
const char * JsonParser::p_msPow		= "msPow";
const char * JsonParser::p_netCfg		= "netCfg";
const char * JsonParser::p_netReady		= "netReady";
const char * JsonParser::p_now			= "now";
const char * JsonParser::p_numActions	= "numActions";
const char * JsonParser::p_outData		= "outData";
const char * JsonParser::p_outValue		= "outValue";
const char * JsonParser::p_period		= "period";
const char * JsonParser::p_periods		= "periods";
const char * JsonParser::p_pfactor		= "pfactor";
const char * JsonParser::p_phase		= "phase";
const char * JsonParser::p_reactive		= "reactive";
const char * JsonParser::p_reductionStart= "reductionStart";
const char * JsonParser::p_reductionStop= "reductionStop";
const char * JsonParser::p_rPow			= "rPow";
const char * JsonParser::p_samples		= "samples";
const char * JsonParser::p_seasonCfg	= "seasonCfg";
const char * JsonParser::p_serial		= "serial";
const char * JsonParser::p_since		= "since";
const char * JsonParser::p_staEssid		= "staEssid";
const char * JsonParser::p_staPasswd	= "staPasswd";
const char * JsonParser::p_stat			= "stat";
const char * JsonParser::p_thres		= "thres";
const char * JsonParser::p_time			= "time";
const char * JsonParser::p_timestamp	= "timestamp";
const char * JsonParser::p_until		= "until";
const char * JsonParser::p_updFlags		= "updFlags";
const char * JsonParser::p_voltage		= "voltage";
const char * JsonParser::p_wdowDawnStart= "wdowDawnStart";
const char * JsonParser::p_wdowDawnStop	= "wdowDawnStop";
const char * JsonParser::p_wdowDuskStart= "wdowDuskStart";
const char * JsonParser::p_wdowDuskStop	= "wdowDuskStop";


