// /*
//  * test_Blob.cpp
//  *
//  *	Test unitario para el m�dulo Blob
//  */


// //------------------------------------------------------------------------------------
// //-- TEST HEADERS --------------------------------------------------------------------
// //------------------------------------------------------------------------------------

// #include "unity.h"
// #include "Blob.h"
// #include "JsonParserBlob.h"

// //------------------------------------------------------------------------------------
// //-- REQUIRED HEADERS & COMPONENTS FOR TESTING ---------------------------------------
// //------------------------------------------------------------------------------------

// #include "AppConfig.h"
// #include "FSManager.h"
// #include "AstCalendarBlob.h"
// #include "AMManagerBlob.h"
// #include "LightManagerBlob.h"
// #include "FwUpdaterBlob.h"
// #include "HMIManager.h"
// #include "MQTTClientBlob.h"
// #include "NetworkManagerBlob.h"
// #include "SysManagerBlob.h"
// #include "MQlib.h"

// Blob::AstCalBootData_t astcal_boot;
// Blob::AMBootData_t am_boot;
// Blob::AMLoadData_t am_load;
// Blob::LightBootData_t light_boot;
// Blob::LightLuxLevel light_lux;
// Blob::LightTimeData_t light_time;
// Blob::FwUpdBootData_t fwupd_boot;
// Blob::FwUpdJob_t fwupd_job;
// Blob::HmiLedData_t hmi_led;
// Blob::HmiEvtFlags hmi_flags;
// Blob::MqttStatusFlags mqtt_stat;




// //------------------------------------------------------------------------------------
// //-- SPECIFIC COMPONENTS FOR TESTING -------------------------------------------------
// //------------------------------------------------------------------------------------

// static const char* _MODULE_ = "[TEST_Blob].....";
// #define _EXPR_	(true)
// static void executePrerequisites();
// static bool s_executed_prerequisites = false;



// //------------------------------------------------------------------------------------
// //-- TEST CASES ----------------------------------------------------------------------
// //------------------------------------------------------------------------------------

// //---------------------------------------------------------------------------
// /**
//  * @brief Verificaci�n de conversi�n a Json de objetos simples
//  */
// TEST_CASE("Get Json <--> Objects with max arrays ..", "[Blob]") {

// 	cJSON* json = NULL;
// 	char* msg = NULL;
// 	uint32_t result = 0;

// 	// ejecuta requisitos previos
// 	executePrerequisites();

// 	// limita arrays
// 	light_boot.cfg.outData.numActions = Blob::MaxAllowedActionDataInArray;
// 	light_boot.cfg.outData.curve.samples = Blob::LightCurveSampleCount;
// 	fwupd_boot.stat.job.devCount = Blob::FwUpdMaxDevicesPerJob;

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromGetRequest... ");
// 	Blob::GetRequest_t req;
// 	json = JsonParser::getJsonFromObj(req);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getGetRequestFromJson... ");
// 	result = JsonParser::getObjFromJson(req, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAstCalStat... ");
// 	json = JsonParser::getJsonFromObj(astcal_boot.stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAstCalStatFromJson... ");
// 	result = JsonParser::getObjFromJson(astcal_boot.stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);


// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAstCalCfg... ");
// 	json = JsonParser::getJsonFromObj(astcal_boot.cfg);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAstCalCfgFromJson... ");
// 	result = JsonParser::getObjFromJson(astcal_boot.cfg, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAstCalBoot... ");
// 	json = JsonParser::getJsonFromObj(astcal_boot);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAstCalBootFromJson... ");
// 	result = JsonParser::getObjFromJson(astcal_boot, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAMStat... ");
// 	json = JsonParser::getJsonFromObj(am_boot.stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAMStatFromJson... ");
// 	result = JsonParser::getObjFromJson(am_boot.stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);


// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAMCfg... ");
// 	json = JsonParser::getJsonFromObj(am_boot.cfg);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAMCfgFromJson... ");
// 	result = JsonParser::getObjFromJson(am_boot.cfg, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAMBoot... ");
// 	json = JsonParser::getJsonFromObj(am_boot);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAMBootFromJson... ");
// 	result = JsonParser::getObjFromJson(am_boot, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAMLoad... ");
// 	json = JsonParser::getJsonFromObj(am_load);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAMLoadFromJson... ");
// 	result = JsonParser::getObjFromJson(am_load, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightStat... ");
// 	json = JsonParser::getJsonFromObj(light_boot.stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightStatFromJson... ");
// 	result = JsonParser::getObjFromJson(light_boot.stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);


// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightCfg... ");
// 	json = JsonParser::getJsonFromObj(light_boot.cfg);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightCfgFromJson... ");
// 	result = JsonParser::getObjFromJson(light_boot.cfg, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightBoot... ");
// 	json = JsonParser::getJsonFromObj(light_boot);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightBootFromJson... ");
// 	result = JsonParser::getObjFromJson(light_boot, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightLux... ");
// 	json = JsonParser::getJsonFromObj(light_lux);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightLuxFromJson... ");
// 	result = JsonParser::getObjFromJson(light_lux, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightTime... ");
// 	json = JsonParser::getJsonFromObj(light_time);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightTimeFromJson... ");
// 	result = JsonParser::getObjFromJson(light_time, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromFwUpdStat... ");
// 	json = JsonParser::getJsonFromObj(fwupd_boot.stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getFwUpdStatFromJson... ");
// 	result = JsonParser::getObjFromJson(fwupd_boot.stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);


// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromFwUpdCfg... ");
// 	json = JsonParser::getJsonFromObj(fwupd_boot.cfg);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getFwUpdCfgFromJson... ");
// 	result = JsonParser::getObjFromJson(fwupd_boot.cfg, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromFwUpdBoot... ");
// 	json = JsonParser::getJsonFromObj(fwupd_boot);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getFwUpdBootFromJson... ");
// 	result = JsonParser::getObjFromJson(fwupd_boot, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromFwUpdJob... ");
// 	json = JsonParser::getJsonFromObj(fwupd_job);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getFwUpdJobFromJson... ");
// 	result = JsonParser::getObjFromJson(fwupd_job, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromHMILed... ");
// 	json = JsonParser::getJsonFromObj(hmi_led);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getHMILedFromJson... ");
// 	result = JsonParser::getObjFromJson(hmi_led, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromHMIEvent... ");
// 	json = JsonParser::getJsonFromObj(hmi_flags);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getHMIEventFromJson... ");
// 	result = JsonParser::getObjFromJson(hmi_flags, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromMqttStat... ");
// 	json = JsonParser::getJsonFromObj(mqtt_stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getMqttStatFromJson... ");
// 	result = JsonParser::getObjFromJson(mqtt_stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// }

// /**
//  * @brief Verificaci�n de conversi�n a Json de objetos simples
//  */
// TEST_CASE("Get Json <--> Objects with null arrays ..", "[Blob]") {

// 	cJSON* json = NULL;
// 	char* msg = NULL;
// 	uint32_t result = 0;

// 	// ejecuta requisitos previos
// 	executePrerequisites();

// 	// limita arrays
// 	light_boot.cfg.outData.numActions = 0;
// 	light_boot.cfg.outData.curve.samples = 0;
// 	fwupd_boot.stat.job.devCount = 0;

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromGetRequest... ");
// 	Blob::GetRequest_t req;
// 	json = JsonParser::getJsonFromObj(req);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getGetRequestFromJson... ");
// 	result = JsonParser::getObjFromJson(req, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAstCalStat... ");
// 	json = JsonParser::getJsonFromObj(astcal_boot.stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAstCalStatFromJson... ");
// 	result = JsonParser::getObjFromJson(astcal_boot.stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);


// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAstCalCfg... ");
// 	json = JsonParser::getJsonFromObj(astcal_boot.cfg);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAstCalCfgFromJson... ");
// 	result = JsonParser::getObjFromJson(astcal_boot.cfg, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAstCalBoot... ");
// 	json = JsonParser::getJsonFromObj(astcal_boot);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAstCalBootFromJson... ");
// 	result = JsonParser::getObjFromJson(astcal_boot, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAMStat... ");
// 	json = JsonParser::getJsonFromObj(am_boot.stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAMStatFromJson... ");
// 	result = JsonParser::getObjFromJson(am_boot.stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);


// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAMCfg... ");
// 	json = JsonParser::getJsonFromObj(am_boot.cfg);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAMCfgFromJson... ");
// 	result = JsonParser::getObjFromJson(am_boot.cfg, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAMBoot... ");
// 	json = JsonParser::getJsonFromObj(am_boot);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAMBootFromJson... ");
// 	result = JsonParser::getObjFromJson(am_boot, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromAMLoad... ");
// 	json = JsonParser::getJsonFromObj(am_load);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getAMLoadFromJson... ");
// 	result = JsonParser::getObjFromJson(am_load, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightStat... ");
// 	json = JsonParser::getJsonFromObj(light_boot.stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightStatFromJson... ");
// 	result = JsonParser::getObjFromJson(light_boot.stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);


// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightCfg... ");
// 	json = JsonParser::getJsonFromObj(light_boot.cfg);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightCfgFromJson... ");
// 	result = JsonParser::getObjFromJson(light_boot.cfg, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightBoot... ");
// 	json = JsonParser::getJsonFromObj(light_boot);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightBootFromJson... ");
// 	result = JsonParser::getObjFromJson(light_boot, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightLux... ");
// 	json = JsonParser::getJsonFromObj(light_lux);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightLuxFromJson... ");
// 	result = JsonParser::getObjFromJson(light_lux, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromLightTime... ");
// 	json = JsonParser::getJsonFromObj(light_time);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getLightTimeFromJson... ");
// 	result = JsonParser::getObjFromJson(light_time, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromFwUpdStat... ");
// 	json = JsonParser::getJsonFromObj(fwupd_boot.stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getFwUpdStatFromJson... ");
// 	result = JsonParser::getObjFromJson(fwupd_boot.stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);


// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromFwUpdCfg... ");
// 	json = JsonParser::getJsonFromObj(fwupd_boot.cfg);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getFwUpdCfgFromJson... ");
// 	result = JsonParser::getObjFromJson(fwupd_boot.cfg, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromFwUpdBoot... ");
// 	json = JsonParser::getJsonFromObj(fwupd_boot);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getFwUpdBootFromJson... ");
// 	result = JsonParser::getObjFromJson(fwupd_boot, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromFwUpdJob... ");
// 	json = JsonParser::getJsonFromObj(fwupd_job);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getFwUpdJobFromJson... ");
// 	result = JsonParser::getObjFromJson(fwupd_job, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromHMILed... ");
// 	json = JsonParser::getJsonFromObj(hmi_led);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getHMILedFromJson... ");
// 	result = JsonParser::getObjFromJson(hmi_led, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromHMIEvent... ");
// 	json = JsonParser::getJsonFromObj(hmi_flags);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getHMIEventFromJson... ");
// 	result = JsonParser::getObjFromJson(hmi_flags, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromMqttStat... ");
// 	json = JsonParser::getJsonFromObj(mqtt_stat);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getMqttStatFromJson... ");
// 	result = JsonParser::getObjFromJson(mqtt_stat, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// }


// //---------------------------------------------------------------------------
// /**
//  * @brief Verificaci�n de conversi�n a Json de objetos SetRequest
//  */
// TEST_CASE("Get Json <--> SetRequest max arrays ....", "[Blob]") {

// 	cJSON* json = NULL;
// 	char* msg = NULL;
// 	uint32_t result = 0;


// 	// ejecuta requisitos previos
// 	executePrerequisites();

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAstCalStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::AstCalStatData_t> sr;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAstCalStat... ");
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAstCalCfg... ");
// 	{
// 	Blob::SetRequest_t<Blob::AstCalCfgData_t> sr;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAstCalBoot... ");
// 	{
// 	Blob::SetRequest_t<Blob::AstCalBootData_t> sr;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAMStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::AMStatData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAMCfg... ");
// 	{
// 	Blob::SetRequest_t<Blob::AMCfgData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAMBoot... ");
// 	{
// 	Blob::SetRequest_t<Blob::AMBootData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAMLoad... ");
// 	{
// 	Blob::SetRequest_t<Blob::AMLoadData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightStatData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightCfg... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightCfgData_t> sr;
// 	// limita arrays
// 	sr.data.outData.numActions = Blob::MaxAllowedActionDataInArray;
// 	sr.data.outData.curve.samples = Blob::LightCurveSampleCount;

// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightBoot... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightBootData_t> sr;
// 	// limita arrays
// 	sr.data.cfg.outData.numActions = Blob::MaxAllowedActionDataInArray;
// 	sr.data.cfg.outData.curve.samples = Blob::LightCurveSampleCount;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightLux... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightLuxLevel> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightTime... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightTimeData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestFwUpdStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::FwUpdStatData_t> sr;
// 	// limita arrays
// 	sr.data.job.devCount = Blob::FwUpdMaxDevicesPerJob;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestFwUpdCfg... ");
// 	{
// 	Blob::SetRequest_t<Blob::FwUpdCfgData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestFwUpdBoot... ");
// 	{
// 	Blob::SetRequest_t<Blob::FwUpdBootData_t> sr;
// 	// limita arrays
// 	sr.data.stat.job.devCount = Blob::FwUpdMaxDevicesPerJob;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestFwUpdJob... ");
// 	{
// 	Blob::SetRequest_t<Blob::FwUpdJob_t> sr;
// 	// limita arrays
// 	sr.data.devCount = Blob::FwUpdMaxDevicesPerJob;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestHMILed... ");
// 	{
// 	Blob::SetRequest_t<Blob::HmiLedData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestHMIEvent... ");
// 	{
// 	Blob::SetRequest_t<Blob::HmiEvtFlags> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestMqttStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::MqttStatusFlags> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}
// }


// //---------------------------------------------------------------------------
// /**
//  * @brief Verificaci�n de conversi�n a Json de objetos SetRequest
//  */
// TEST_CASE("Get Json <--> SetRequest null arrays ....", "[Blob]") {

// 	cJSON* json = NULL;
// 	char* msg = NULL;
// 	uint32_t result = 0;


// 	// ejecuta requisitos previos
// 	executePrerequisites();

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAstCalStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::AstCalStatData_t> sr;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAstCalStat... ");
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAstCalCfg... ");
// 	{
// 	Blob::SetRequest_t<Blob::AstCalCfgData_t> sr;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAstCalBoot... ");
// 	{
// 	Blob::SetRequest_t<Blob::AstCalBootData_t> sr;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAMStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::AMStatData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAMCfg... ");
// 	{
// 	Blob::SetRequest_t<Blob::AMCfgData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAMBoot... ");
// 	{
// 	Blob::SetRequest_t<Blob::AMBootData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestAMLoad... ");
// 	{
// 	Blob::SetRequest_t<Blob::AMLoadData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightStatData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightCfg... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightCfgData_t> sr;
// 	// limita arrays
// 	sr.data.outData.numActions = 0;
// 	sr.data.outData.curve.samples = 0;

// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightBoot... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightBootData_t> sr;
// 	// limita arrays
// 	sr.data.cfg.outData.numActions = 0;
// 	sr.data.cfg.outData.curve.samples = 0;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightLux... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightLuxLevel> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestLightTime... ");
// 	{
// 	Blob::SetRequest_t<Blob::LightTimeData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestFwUpdStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::FwUpdStatData_t> sr;
// 	// limita arrays
// 	sr.data.job.devCount = 0;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestFwUpdCfg... ");
// 	{
// 	Blob::SetRequest_t<Blob::FwUpdCfgData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestFwUpdBoot... ");
// 	{
// 	Blob::SetRequest_t<Blob::FwUpdBootData_t> sr;
// 	// limita arrays
// 	sr.data.stat.job.devCount = 0;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestFwUpdJob... ");
// 	{
// 	Blob::SetRequest_t<Blob::FwUpdJob_t> sr;
// 	// limita arrays
// 	sr.data.devCount = 0;
// 	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestHMILed... ");
// 	{
// 	Blob::SetRequest_t<Blob::HmiLedData_t> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestHMIEvent... ");
// 	{
// 	Blob::SetRequest_t<Blob::HmiEvtFlags> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromSetRequestMqttStat... ");
// 	{
// 	Blob::SetRequest_t<Blob::MqttStatusFlags> sr;	json = JsonParser::getJsonFromSetRequest(sr);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getSetRequestFromJson... ");
// 	result = JsonParser::getSetRequestFromJson(sr, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}
// }



// //---------------------------------------------------------------------------
// /**
//  * @brief Verificaci�n de conversi�n a Json de objetos Notification
//  */
// TEST_CASE("Get Json <--> Notification max arrays ....", "[Blob]") {

// 	cJSON* json = NULL;
// 	char* msg = NULL;
// 	uint32_t result = 0;


// 	// ejecuta requisitos previos
// 	executePrerequisites();

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAstCalStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::AstCalStatData_t> notif;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAstCalStat... ");
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAstCalCfg... ");
// 	{
// 	Blob::NotificationData_t<Blob::AstCalCfgData_t> notif;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAstCalBoot... ");
// 	{
// 	Blob::NotificationData_t<Blob::AstCalBootData_t> notif;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAMStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::AMStatData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAMCfg... ");
// 	{
// 	Blob::NotificationData_t<Blob::AMCfgData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAMBoot... ");
// 	{
// 	Blob::NotificationData_t<Blob::AMBootData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAMLoad... ");
// 	{
// 	Blob::NotificationData_t<Blob::AMLoadData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightStatData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightCfg... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightCfgData_t> notif;
// 	// limita arrays
// 	notif.data.outData.numActions = Blob::MaxAllowedActionDataInArray;
// 	notif.data.outData.curve.samples = Blob::LightCurveSampleCount;

// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightBoot... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightBootData_t> notif;
// 	// limita arrays
// 	notif.data.cfg.outData.numActions = Blob::MaxAllowedActionDataInArray;
// 	notif.data.cfg.outData.curve.samples = Blob::LightCurveSampleCount;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightLux... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightLuxLevel> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightTime... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightTimeData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationFwUpdStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::FwUpdStatData_t> notif;
// 	// limita arrays
// 	notif.data.job.devCount = Blob::FwUpdMaxDevicesPerJob;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationFwUpdCfg... ");
// 	{
// 	Blob::NotificationData_t<Blob::FwUpdCfgData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationFwUpdBoot... ");
// 	{
// 	Blob::NotificationData_t<Blob::FwUpdBootData_t> notif;
// 	// limita arrays
// 	notif.data.stat.job.devCount = Blob::FwUpdMaxDevicesPerJob;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationFwUpdJob... ");
// 	{
// 	Blob::NotificationData_t<Blob::FwUpdJob_t> notif;
// 	// limita arrays
// 	notif.data.devCount = Blob::FwUpdMaxDevicesPerJob;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationHMILed... ");
// 	{
// 	Blob::NotificationData_t<Blob::HmiLedData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationHMIEvent... ");
// 	{
// 	Blob::NotificationData_t<Blob::HmiEvtFlags> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationMqttStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::MqttStatusFlags> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}
// }


// //---------------------------------------------------------------------------
// /**
//  * @brief Verificaci�n de conversi�n a Json de objetos Notification
//  */
// TEST_CASE("Get Json <--> Notification null arrays ....", "[Blob]") {

// 	cJSON* json = NULL;
// 	char* msg = NULL;
// 	uint32_t result = 0;


// 	// ejecuta requisitos previos
// 	executePrerequisites();

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAstCalStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::AstCalStatData_t> notif;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAstCalStat... ");
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAstCalCfg... ");
// 	{
// 	Blob::NotificationData_t<Blob::AstCalCfgData_t> notif;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAstCalBoot... ");
// 	{
// 	Blob::NotificationData_t<Blob::AstCalBootData_t> notif;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAMStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::AMStatData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAMCfg... ");
// 	{
// 	Blob::NotificationData_t<Blob::AMCfgData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAMBoot... ");
// 	{
// 	Blob::NotificationData_t<Blob::AMBootData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationAMLoad... ");
// 	{
// 	Blob::NotificationData_t<Blob::AMLoadData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightStatData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightCfg... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightCfgData_t> notif;
// 	// limita arrays
// 	notif.data.outData.numActions = 0;
// 	notif.data.outData.curve.samples = 0;

// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightBoot... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightBootData_t> notif;
// 	// limita arrays
// 	notif.data.cfg.outData.numActions = 0;
// 	notif.data.cfg.outData.curve.samples = 0;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightLux... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightLuxLevel> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationLightTime... ");
// 	{
// 	Blob::NotificationData_t<Blob::LightTimeData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationFwUpdStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::FwUpdStatData_t> notif;
// 	// limita arrays
// 	notif.data.job.devCount = 0;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationFwUpdCfg... ");
// 	{
// 	Blob::NotificationData_t<Blob::FwUpdCfgData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationFwUpdBoot... ");
// 	{
// 	Blob::NotificationData_t<Blob::FwUpdBootData_t> notif;
// 	// limita arrays
// 	notif.data.stat.job.devCount = 0;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationFwUpdJob... ");
// 	{
// 	Blob::NotificationData_t<Blob::FwUpdJob_t> notif;
// 	// limita arrays
// 	notif.data.devCount = 0;
// 	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationHMILed... ");
// 	{
// 	Blob::NotificationData_t<Blob::HmiLedData_t> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationHMIEvent... ");
// 	{
// 	Blob::NotificationData_t<Blob::HmiEvtFlags> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromNotificationMqttStat... ");
// 	{
// 	Blob::NotificationData_t<Blob::MqttStatusFlags> notif;	json = JsonParser::getJsonFromNotification(notif);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getNotificationFromJson... ");
// 	result = JsonParser::getNotificationFromJson(notif, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}
// }





// //---------------------------------------------------------------------------
// /**
//  * @brief Verificaci�n de conversi�n a Json de objetos Response
//  */
// TEST_CASE("Get Json <--> Response max arrays ....", "[Blob]") {

// 	cJSON* json = NULL;
// 	char* msg = NULL;
// 	uint32_t result = 0;


// 	// ejecuta requisitos previos
// 	executePrerequisites();

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAstCalStat... ");
// 	{
// 	Blob::Response_t<Blob::AstCalStatData_t> resp;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAstCalCfg... ");
// 	{
// 	Blob::Response_t<Blob::AstCalCfgData_t> resp;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAstCalBoot... ");
// 	{
// 	Blob::Response_t<Blob::AstCalBootData_t> resp;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAMStat... ");
// 	{
// 	Blob::Response_t<Blob::AMStatData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAMCfg... ");
// 	{
// 	Blob::Response_t<Blob::AMCfgData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAMBoot... ");
// 	{
// 	Blob::Response_t<Blob::AMBootData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAMLoad... ");
// 	{
// 	Blob::Response_t<Blob::AMLoadData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightStat... ");
// 	{
// 	Blob::Response_t<Blob::LightStatData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightCfg... ");
// 	{
// 	Blob::Response_t<Blob::LightCfgData_t> resp;
// 	// limita arrays
// 	resp.data.outData.numActions = Blob::MaxAllowedActionDataInArray;
// 	resp.data.outData.curve.samples = Blob::LightCurveSampleCount;

// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightBoot... ");
// 	{
// 	Blob::Response_t<Blob::LightBootData_t> resp;
// 	// limita arrays
// 	resp.data.cfg.outData.numActions = Blob::MaxAllowedActionDataInArray;
// 	resp.data.cfg.outData.curve.samples = Blob::LightCurveSampleCount;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightLux... ");
// 	{
// 	Blob::Response_t<Blob::LightLuxLevel> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightTime... ");
// 	{
// 	Blob::Response_t<Blob::LightTimeData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseFwUpdStat... ");
// 	{
// 	Blob::Response_t<Blob::FwUpdStatData_t> resp;
// 	// limita arrays
// 	resp.data.job.devCount = Blob::FwUpdMaxDevicesPerJob;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseFwUpdCfg... ");
// 	{
// 	Blob::Response_t<Blob::FwUpdCfgData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseFwUpdBoot... ");
// 	{
// 	Blob::Response_t<Blob::FwUpdBootData_t> resp;
// 	// limita arrays
// 	resp.data.stat.job.devCount = Blob::FwUpdMaxDevicesPerJob;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseFwUpdJob... ");
// 	{
// 	Blob::Response_t<Blob::FwUpdJob_t> resp;
// 	// limita arrays
// 	resp.data.devCount = Blob::FwUpdMaxDevicesPerJob;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseHMILed... ");
// 	{
// 	Blob::Response_t<Blob::HmiLedData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseHMIEvent... ");
// 	{
// 	Blob::Response_t<Blob::HmiEvtFlags> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseMqttStat... ");
// 	{
// 	Blob::Response_t<Blob::MqttStatusFlags> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}
// }


// //---------------------------------------------------------------------------
// /**
//  * @brief Verificaci�n de conversi�n a Json de objetos Response
//  */
// TEST_CASE("Get Json <--> Response null arrays ....", "[Blob]") {

// 	cJSON* json = NULL;
// 	char* msg = NULL;
// 	uint32_t result = 0;


// 	// ejecuta requisitos previos
// 	executePrerequisites();

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAstCalStat... ");
// 	{
// 	Blob::Response_t<Blob::AstCalStatData_t> resp;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAstCalStat... ");
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAstCalCfg... ");
// 	{
// 	Blob::Response_t<Blob::AstCalCfgData_t> resp;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAstCalBoot... ");
// 	{
// 	Blob::Response_t<Blob::AstCalBootData_t> resp;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAMStat... ");
// 	{
// 	Blob::Response_t<Blob::AMStatData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAMCfg... ");
// 	{
// 	Blob::Response_t<Blob::AMCfgData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAMBoot... ");
// 	{
// 	Blob::Response_t<Blob::AMBootData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseAMLoad... ");
// 	{
// 	Blob::Response_t<Blob::AMLoadData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightStat... ");
// 	{
// 	Blob::Response_t<Blob::LightStatData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightCfg... ");
// 	{
// 	Blob::Response_t<Blob::LightCfgData_t> resp;
// 	// limita arrays
// 	resp.data.outData.numActions = 0;
// 	resp.data.outData.curve.samples = 0;

// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightBoot... ");
// 	{
// 	Blob::Response_t<Blob::LightBootData_t> resp;
// 	// limita arrays
// 	resp.data.cfg.outData.numActions = 0;
// 	resp.data.cfg.outData.curve.samples = 0;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightLux... ");
// 	{
// 	Blob::Response_t<Blob::LightLuxLevel> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseLightTime... ");
// 	{
// 	Blob::Response_t<Blob::LightTimeData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseFwUpdStat... ");
// 	{
// 	Blob::Response_t<Blob::FwUpdStatData_t> resp;
// 	// limita arrays
// 	resp.data.job.devCount = 0;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseFwUpdCfg... ");
// 	{
// 	Blob::Response_t<Blob::FwUpdCfgData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseFwUpdBoot... ");
// 	{
// 	Blob::Response_t<Blob::FwUpdBootData_t> resp;
// 	// limita arrays
// 	resp.data.stat.job.devCount = 0;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseFwUpdJob... ");
// 	{
// 	Blob::Response_t<Blob::FwUpdJob_t> resp;
// 	// limita arrays
// 	resp.data.devCount = 0;
// 	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseHMILed... ");
// 	{
// 	Blob::Response_t<Blob::HmiLedData_t> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseHMIEvent... ");
// 	{
// 	Blob::Response_t<Blob::HmiEvtFlags> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}

// 	//-----------
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getJsonFromResponseMqttStat... ");
// 	{
// 	Blob::Response_t<Blob::MqttStatusFlags> resp;	json = JsonParser::getJsonFromResponse(resp);
// 	TEST_ASSERT_NOT_NULL(json);
// 	msg = cJSON_PrintUnformatted(json);
// 	TEST_ASSERT_NOT_NULL(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "%s\r\n", msg);
// 	Heap::memFree(msg);
// 	DEBUG_TRACE_I(_EXPR_, _MODULE_, "getResponseFromJson... ");
// 	result = JsonParser::getResponseFromJson(resp, json);
// 	TEST_ASSERT_NOT_EQUAL(result, 0);
// 	cJSON_Delete(json);
// 	}
// }



// //------------------------------------------------------------------------------------
// //-- PREREQUISITES -------------------------------------------------------------------
// //------------------------------------------------------------------------------------


// //------------------------------------------------------------------------------------
// static void executePrerequisites(){
// 	if(!s_executed_prerequisites){

// 		// marca flag de prerequisitos completado
// 		s_executed_prerequisites = true;
// 	}
// }


