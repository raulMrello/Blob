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


/**
 * Decodifica un objeto JSON tipo GetRequest
 * @param req Objeto decodificado en binario
 * @param json_data Objeto JSON a decodificar
 * @return True si el objeto se decodifica correctamente
 */
bool decodeGetRequest(Blob::GetRequest_t& req, char* json_data);


/** Parsea un objeto Blob::GetRequest en un mensaje JSON
 * 	@param req Objeto a parsear
 * 	@return Objeto JSON generado
 */
cJSON* parseGetRequest(const Blob::GetRequest_t& req);


/** Parsea un objeto Blob::SetRequest_t<Blob::AstCalCfgData_t> en un mensaje JSON
 *  @param idTrans Identificador de la transaccción
 * 	@param key Nombre del objeto a insertar
 * 	@param item Objeto JSON a insertar
 * 	@param data_keys Flags de datos actualizados para el SetRequest
 * 	@return Objeto JSON generado
 */
cJSON* parseSetRequest(uint32_t idTrans, const char* key, cJSON* item, uint32_t data_keys=0);



}	/** End of namespace JSON */





#endif
