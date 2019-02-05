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
	MaxNumParamKeys
};

//------------------------------------------------------------------------------------
static const char *keys[] = {
	"idTrans",
	"error",
	"code",
	"descr",
	"keys"
};



//------------------------------------------------------------------------------------
//-- PUBLIC METHODS IMPLEMENTATION ---------------------------------------------------
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
bool decodeGetRequest(Blob::GetRequest_t &req, char* json_data){
	cJSON *root = NULL;
	req.idTrans = 0;
	req._error.code = Blob::ErrJsonMalformed;

	// json_data = {"idTrans": xxx}
	if((root = cJSON_Parse(json_data)) != NULL){
		cJSON *idtrans = NULL;
		if((idtrans = cJSON_GetObjectItem(root, keys[p_IDTRANS])) != NULL){
			req.idTrans = idtrans->valueint;
			req._error.code = Blob::ErrOK;
			goto _decodeGetRequest_Exit;
		}
		req._error.code = Blob::ErrIdTransInvalid;
	}
_decodeGetRequest_Exit:
	strcpy(req._error.descr, Blob::errList[req._error.code]);
	if(root){
		cJSON_Delete(root);
	}
	if(req._error.code == Blob::ErrOK){
		DEBUG_TRACE_D(_EXPR_, _MODULE_, "Procesado GetRequest con idTrans=%d", req.idTrans);
		return true;
	}
	DEBUG_TRACE_W(_EXPR_, _MODULE_, "Error procesando GetRequest: %s", req._error.descr);
	return false;
}


//------------------------------------------------------------------------------------
cJSON* parseGetRequest(const Blob::GetRequest_t& req){
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


//------------------------------------------------------------------------------------
cJSON* parseSetRequest(uint32_t idTrans, const char* key, cJSON* item, uint32_t data_keys){
	cJSON *root = cJSON_CreateObject();

	if(!root){
		return NULL;
	}

	// key: idTrans
	cJSON_AddNumberToObject(root, keys[p_IDTRANS], idTrans);
	cJSON_AddNumberToObject(root, keys[p_KEYS], data_keys);

	// key: item
	cJSON_AddItemToObject(root, key, item);
	return root;
}



//------------------------------------------------------------------------------------
//-- STATIC METHODS IMPLEMENTATION ---------------------------------------------------
//------------------------------------------------------------------------------------



}	/** End of namespace JSON */

