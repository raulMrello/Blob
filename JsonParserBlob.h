/*
 * JsonParserBlob.h
 *
 *  Created on: Abr 2018
 *      Author: raulMrello
 *
 *	JsonParserBlob es el mÃ³dulo encargado de traducir las estructuras de datos utilizadas en MQLib a mensajes JSON entendidos
 *	por el enlace MQTT y viceversa.
 */
 
#ifndef JSONPARSERBLOB_H
#define JSONPARSERBLOB_H

#include "mbed.h"
#include "Blob.h"
#include "cJSON.h"
  

namespace JSON {


/** Parsea un objeto Blob::GetRequest_t en un mensaje JSON
 *  @param req Solicitud a convertir a json
 * 	@return Objeto JSON generado
 */
cJSON* getJsonFromGetRequest(const Blob::GetRequest_t &req);


/** Parsea un objeto Blob::SetRequest_t<T> en un mensaje JSON
 *  @param req Solicitud a convertir a json
 * 	@param name Nombre del objeto json a insertar en el SetRequest
 * 	@return Objeto JSON generado
 */
template <typename T>
cJSON* getJsonFromSetRequest(const Blob::SetRequest_t<T> &req, const char* name){
	cJSON *root = cJSON_CreateObject();

	if(!root){
		return NULL;
	}

	// key: idTrans
	cJSON_AddNumberToObject(root, keys[p_IDTRANS], req.idTrans);
	cJSON_AddNumberToObject(root, keys[p_KEYS], req.keys);

	// key: object
	cJSON* obj = getJsonFromObj<T>(req.data);
	if(!obj){
		cJSON_Delete(root);
		return NULL;
	}
	cJSON_AddItemToObject(root, name, obj);
	return root;
}


/** Parsea un objeto Blob::Response_t<T> en un mensaje JSON
 *  @param resp Respuresta a convertir a json
 * 	@param name Nombre del objeto json a insertar en el Response
 * 	@return Objeto JSON generado
 */
template <typename T>
cJSON* getJsonFromResponse(const Blob::Response_t<T> &resp, const char* name){
	// keys: root, idtrans, header, error
	cJSON *header = NULL;
	cJSON *error = NULL;
	cJSON *value = NULL;
	cJSON *root = cJSON_CreateObject();

	if(!root){
		return NULL;
	}

	// key: idTrans sólo se envía si está en uso
	if(resp.idTrans != Blob::UnusedIdTrans){
		cJSON_AddNumberToObject(root, keys[p_IDTRANS], resp.idTrans);
	}

	// key: header
	if((header=cJSON_CreateObject()) == NULL){
		cJSON_Delete(root);
		return NULL;
	}
	cJSON_AddNumberToObject(header, keys[p_TIMESTAMP], resp.header.timestamp);
	cJSON_AddItemToObject(root, keys[p_HEADER], header);

	// key: error sólo se envía si el error es distinto de Blob::ErrOK
	if(resp.error.code != Blob::ErrOK){
		if((error=cJSON_CreateObject()) == NULL){
			cJSON_Delete(root);
			return NULL;
		}
		cJSON_AddNumberToObject(error, keys[p_CODE], resp.error.code);
		if((value=cJSON_CreateString(resp.error.descr)) == NULL){
			cJSON_Delete(error);
			cJSON_Delete(root);
			return NULL;
		}
		cJSON_AddItemToObject(error, keys[p_DESCR], value);
		// añade objeto
		cJSON_AddItemToObject(root, keys[p_ERROR], error);
	}

	// key: object
	cJSON* obj = getJsonFromObj<T>(resp.data);
	if(!obj){
		cJSON_Delete(root);
		return NULL;
	}
	cJSON_AddItemToObject(root, name, obj);
	return root;
}


/**
 * Codifica la configuración actual en un objeto JSON. Dependiendo del tipo de dato, delega
 * al módulo correspondiente.
 * @param cfg Configuración
 * @return Objeto JSON o NULL en caso de error
 */
template <typename T>
cJSON* getJsonFromObj(const T& obj){
	if (Blob::is_same<T, Blob::GetRequest_t>::value){
		return getJsonFromGetRequest(obj);
	}
	//-----
	if (Blob::is_same<T, Blob::AstCalCfgData_t>::value){
		return getJsonFromAstCalCfg(obj);
	}
	if (Blob::is_same<T, Blob::AstCalStatData_t>::value){
		return getJsonFromAstCalStat(obj);
	}
	if (Blob::is_same<T, Blob::AstCalBootData_t>::value){
		return getJsonFromAstCalBoot(obj);
	}
	//-----
	if (Blob::is_same<T, Blob::AMCfgData_t>::value){
		return getJsonFromAMCfg(obj);
	}
	if (Blob::is_same<T, Blob::AMStatData_t>::value){
		return getJsonFromAMStat(obj);
	}
	if (Blob::is_same<T, Blob::AMBootData_t>::value){
		return getJsonFromAMBoot(obj);
	}
	//-----
	if (Blob::is_same<T, Blob::LightCfgData_t>::value){
		return getJsonFromLightCfg(obj);
	}
	if (Blob::is_same<T, Blob::LightStatData_t>::value){
		return getJsonFromLightStat(obj);
	}
	if (Blob::is_same<T, Blob::LightBootData_t>::value){
		return getJsonFromLightBoot(obj);
	}
	return NULL;
}


/** Decodifica el mensaje JSON en un objeto Blob::GetRequest_t
 * @param req Recibe el objeto decodificado
 * @param json Objeto JSON a decodificar
 * @return keys Parámetros decodificados o 0 en caso de error
 */
uint32_t getGetRequestFromJson(Blob::GetRequest_t &req,cJSON* json);


/** Decodifica el mensaje JSON en un objeto Blob::SetRequest_t<T>
 *  @param req Recibe el objeto decodificado
 * @param json Objeto JSON a decodificar
 * @return keys Parámetros decodificados o 0 en caso de error
 */
template <typename T>
uint32_t getSetRequestFromJson(Blob::SetRequest_t<T> &req, cJSON* json){
	cJSON *obj = NULL;
	req.keys = 0;
	req._error.code = Blob::ErrOK;
	strcpy(req._error.descr, Blob::errList[req._error.code]);

	if(json == NULL){
		return 0;
	}

	// key: idTrans
	if((obj = cJSON_GetObjectItem(json, keys[p_IDTRANS])) == NULL){
		return 0;
	}
	req.idTrans = obj->valueint;

	// key:obj
	if((obj = cJSON_GetObjectItem(json, keys[p_DATA])) == NULL){
		return 0;
	}
	req.keys = getObjFromJson<T>(req.data, obj);
	return req.keys;
}


/** Decodifica el mensaje JSON en un objeto Blob::SetRequest_t<T>
 *  @param req Recibe el objeto decodificado
 * @param json Objeto JSON a decodificar
 * @return keys Parámetros decodificados o 0 en caso de error
 */
template <typename T>
uint32_t getResponseFromJson(Blob::Response_t<T> &resp, cJSON* json){
	cJSON *obj = NULL;
	cJSON *value = NULL;
	cJSON *root = NULL;
	resp._error.code = Blob::ErrOK;
	strcpy(resp._error.descr, Blob::errList[resp._error.code]);

	if(json == NULL){
		return 0;
	}

	// key: idTrans
	if((obj = cJSON_GetObjectItem(json, keys[p_IDTRANS])) != NULL){
		return 0;
	}
	resp.idTrans = obj->valueint;

	// key: header
	if((obj = cJSON_GetObjectItem(json, keys[p_HEADER])) == NULL){
		return 0;
	}
	// key: timestamp
	if((value = cJSON_GetObjectItem(obj, keys[p_TIMESTAMP])) == NULL){
		return 0;
	}
	resp.header.timestamp = (time_t)obj->valuedouble;

	// key: error
	if((obj = cJSON_GetObjectItem(json, keys[p_ERROR])) != NULL){
		// key: code
		if((value = cJSON_GetObjectItem(obj, keys[p_CODE])) == NULL){
			return 0;
		}
		resp.error.code = obj->valueint;
		// key: descr
		if((value = cJSON_GetObjectItem(obj, keys[p_DESCR])) == NULL){
			return 0;
		}
		strncpy(resp.error.descr, obj->valuestring, Blob::DefaultErrDescrLen);
	}

	// key:obj
	if((obj = cJSON_GetObjectItem(json, keys[p_DATA])) == NULL){
		return 0;
	}
	return getObjFromJson<T>(resp.data, obj);
}


/**
 * Decodifica el mensaje JSON en un objeto
 * @param obj Recibe el objeto decodificado
 * @param json Objeto JSON a decodificar
 * @return keys Parámetros decodificados o 0 en caso de error
 */
template <typename T>
uint32_t getObjFromJson(T &obj, cJSON* json){
	uint32_t result = 0;
	// decodifica objeto de configuración
	if (Blob::is_same<T, Blob::GetRequest_t>::value){
		return getGetRequestFromJson(obj, json);
	}
	//----
	// decodifica objeto de configuración
	if (Blob::is_same<T, Blob::AstCalCfgData_t>::value){
		return getAstCalCfgFromJson(obj, json);
	}
	// decodifica objeto de estado
	if (Blob::is_same<T, Blob::AstCalStatData_t>::value){
		return getAstCalStatFromJson(obj, json);
	}
	// decodifica objeto de arranque
	if (Blob::is_same<T, Blob::AstCalBootData_t>::value){
		return getAstCalBootFromJson(obj, json);
	}
	//----
	// decodifica objeto de configuración
	if (Blob::is_same<T, Blob::AMCfgData_t>::value){
		return getAMCfgFromJson(obj, json);
	}
	// decodifica objeto de estado
	if (Blob::is_same<T, Blob::AMStatData_t>::value){
		return getAMStatFromJson(obj, json);
	}
	// decodifica objeto de arranque
	if (Blob::is_same<T, Blob::AMBootData_t>::value){
		return getAMBootFromJson(obj, json);
	}
	//----
	// decodifica objeto de configuración
	if (Blob::is_same<T, Blob::LightCfgData_t>::value){
		return getLightCfgFromJson(obj, json);
	}
	// decodifica objeto de estado
	if (Blob::is_same<T, Blob::LightStatData_t>::value){
		return getLightStatFromJson(obj, json);
	}
	// decodifica objeto de arranque
	if (Blob::is_same<T, Blob::LightBootData_t>::value){
		return getLightBootFromJson(obj, json);
	}
}


}	/** End of namespace JSON */





#endif
