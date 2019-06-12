/*
 * common_objects.cpp
 *
 * Implementación de los codecs JSON-OBJ
 *
 *  Created on: Feb 2019
 *      Author: raulMrello
 */

#include "JsonParserBlob.h"

//------------------------------------------------------------------------------------
//-- PRIVATE TYPEDEFS ----------------------------------------------------------------
//------------------------------------------------------------------------------------

static const char* _MODULE_ = "[common_objs]...";
#define _EXPR_	(!IS_ISR())


namespace JSON{


//------------------------------------------------------------------------------------
cJSON* getJsonFromRangeMinMaxThresDouble(const common_range_minmaxthres_double& obj){
	cJSON* json = NULL;

	if((json=cJSON_CreateObject()) == NULL){
		return NULL;
	}
	cJSON_AddNumberToObject(json, JsonParser::p_min, obj.min);
	cJSON_AddNumberToObject(json, JsonParser::p_max, obj.max);
	cJSON_AddNumberToObject(json, JsonParser::p_thres, obj.thres);

	return json;
}


//------------------------------------------------------------------------------------
uint32_t getRangeMinMaxThresDoubleFromJson(common_range_minmaxthres_double &obj, cJSON* json){
	cJSON* value = NULL;
	uint32_t keys = 0;
	if(json == NULL){
		return 0;
	}

	if((value = cJSON_GetObjectItem(json,JsonParser::p_min)) != NULL){
		obj.min = value->valuedouble;
		keys |= (1<<0);
	}
	if((value = cJSON_GetObjectItem(json,JsonParser::p_max)) != NULL){
		obj.max = value->valuedouble;
		keys |= (1<<1);
	}
	if((value = cJSON_GetObjectItem(json,JsonParser::p_thres)) != NULL){
		obj.thres = value->valuedouble;
		keys |= (1<<2);
	}
	return keys;
}


}	// end namespace JSON

