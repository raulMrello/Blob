/*
 * JsonParserBlob.h
 *
 *  Created on: Abr 2018
 *      Author: raulMrello
 *
 *	JsonParserBlob es el módulo encargado de traducir las estructuras de datos utilizadas en MQLib a mensajes JSON entendidos
 *	por el enlace MQTT y viceversa.
 */
 
#ifndef JSONPARSERBLOB_H
#define JSONPARSERBLOB_H

#include "mbed.h"
#include "Blob.h"
#include "cJSON.h"
#include "AMManagerBlob.h"
#include "AstCalendarBlob.h"
#include "LightManagerBlob.h"
#include "SysManagerBlob.h"

  

namespace Blob {

//---------------------------------------------------------------------------------
//- Errores -----------------------------------------------------------------------
//---------------------------------------------------------------------------------


//---------------------------------------------------------------------------------
//- Definiciones comunes ----------------------------------------------------------
//---------------------------------------------------------------------------------

/** Decodifica un mensaje JSON en funci�n del topic al que va dirigido y de su contenido
 * 	para formar un objeto Blob del tipo que corresponda.
 * 	@param topic Topic
 * 	@param json_data Mensaje json
 * 	@param data_len Tama�o del objeto construido por el decodificador o 0 en caso de error
 * 	@param debug Flag para habilitar la depuraci�n
 * 	@return Puntero al objeto Blob creado o NULL en caso de error
 */
void* DecodeJson(char* topic, char* json_data, int* data_len, bool debug = false);

/** Parsea un objeto Blob en un mensaje JSON en funci�n del topic al que va dirigido y de su contenido
 * 	@param topic Topic
 * 	@param data Objeto Blob
 * 	@param data_len Tama�o del objeto blob
 * 	@param header Cabecera a incluir en el objeto
 * 	@param debug Flag para habilitar la depuraci�n
 * 	@return Puntero al mensaje json creado o NULL en caso de error
 */
char* ParseJson(char* topic, void* data, int data_len, bool debug = false);


}	/** End of namespace Blob */





#endif
