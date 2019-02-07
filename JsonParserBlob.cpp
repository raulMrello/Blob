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

enum ParamKeys{
	p_IDTRANS,
	p_ERROR,
	p_CODE,
	p_DESCR,
	p_KEYS,
	p_TIMESTAMP,
	p_HEADER,
	p_DATA,
	MaxNumParamKeys
};

//------------------------------------------------------------------------------------
static const char *keys[] = {
	"idTrans",
	"error",
	"code",
	"descr",
	"keys",
	"timestamp",
	"header",
	"data",
};



//------------------------------------------------------------------------------------
//-- PUBLIC METHODS IMPLEMENTATION ---------------------------------------------------
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
uint32_t getGetRequestFromJson(Blob::GetRequest_t &req, cJSON* json){
	cJSON* cfg = NULL;
	cJSON* stat = NULL;

	if(json == NULL){
		return 0;
	}
	cJSON *idtrans = NULL;
	if((idtrans = cJSON_GetObjectItem(json, keys[p_IDTRANS])) == NULL){
		return 0;
	}
	req.idTrans = idtrans->valueint;
	req._error.code = Blob::ErrOK;
	strcpy(req._error.descr, Blob::errList[req._error.code]);
	return 1;
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

