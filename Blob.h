/*
 * Blob.h
 *
 *  Created on: Ene 2018
 *      Author: raulMrello
 *
 *	Blob es un módulo que agrupa todos los objetos de datos (estructuras, enumeraciones, etc...) utilizadas de forma
 *	general en una aplicación y que son reutilizados por múltiples módulos. De esta forma, el acceso a todos estos
 *	datos es sencilla mediante la importación de la librería <blob.h>, en lugar de ir incluyendo todos los módulos
 *	que definen cada uno de los datos.
 */
 
#ifndef BLOB_H
#define BLOB_H

#include "mbed.h"
  


namespace Blob {

//---------------------------------------------------------------------------------
//- Definiciones comunes ----------------------------------------------------------
//---------------------------------------------------------------------------------

/** Lista de errores comunes */
enum ErrorCode{
	ErrOK,				//!< Sin errores
	ErrJsonMalformed,	//!< Objeto json incorrecto
	ErrIdTransInvalid,	//!< Identificación de transacción inválida
	ErrStringFormat,	//!< Cadena de texto con formato incorrecto
	ErrEmptyContent,	//!< Contenido vacío
	ErrRangeValue,		//!< Rango incorrecto
	ErrAllocJson,		//!< No se permite la creación del objeto
	ErrJsonUnhandled,	//!< Objeto Json sin maneajador
	MaxNumErrorCodes
};
static const char* errList[] = {
	"", 					//ErrOk
	"json malformed",		//ErrJsonMalformed
	"idTrans missing", 		//ErrIdTransInvalid
	"string malformed",		//ErrStringFormat
	"json is empty",		//ErrEmptyContent
	"value out of range",	//ErrRangeValue
	"json alloc failed",	//ErrAllocJson
	"json unhandled",		//ErrJsonUnhandled
};

/** Tamaño máximo de un objeto BLOB. En este caso viene determinado por el tamaño de
 * 	los datos de usuario que viajan por el paquete MQNet_Message_t eliminando el tamaño
 * 	del topic_id.
 */
static const uint32_t MaxBlobSize = 224;

/** Tamaño por defecto de los textos de descripción de errores */
static const uint16_t DefaultErrDescrLen = 64;

/** Define un valor idtrans sin uso */
static const uint32_t UnusedIdTrans = 0;

/** Tamaño máximo del timestamp en segundos para calcular una fecha y una hora concreta
 *  de un año. Se considera que todos los años tiene 366 días y siempre existe el 29 de
 *  febrero.
 */
static const uint32_t TimestampSecondsYearLimit = (366 * 24 * 3600);

/** Tamaño máximo del timestamp en minutos para calcular una hora concreta
 *  de un día.
 */
static const uint16_t TimestampMinutesDayLimit = (24 * 60);

/** Estructura de datos para envío de cabecera incluyendo el tiemstamp, etc...
 */
struct HeaderData_t{
	time_t timestamp;
};


/** Estructura de datos para envío de errores
 */
struct ErrorData_t{
	uint32_t code;
	char descr[DefaultErrDescrLen];
	ErrorData_t(){
		code = ErrOK;
		descr[0] = 0;
	}
};


/** Estructura de datos relativa a una operación SetRequest
 */
template <typename T>
struct SetRequest_t{
	uint32_t idTrans;
	uint32_t keys;
	T data;
	Blob::ErrorData_t _error;
};


/** Estructura de datos relativa a una operación GetRequest
 */
struct GetRequest_t{
	uint32_t idTrans;
	Blob::ErrorData_t _error;
	GetRequest_t(uint32_t x_id=0){
		idTrans = x_id;
		_error.code = ErrOK;
		_error.descr[0] = 0;
	}
};


/** Estructura de datos relativa a una operación Response sin errores
 */
template <typename T>
struct Response_t{
	uint32_t idTrans;
	Blob::HeaderData_t header;
	Blob::ErrorData_t error;
	T data;
	Response_t(uint32_t idt, const Blob::ErrorData_t& err, const T& dat) : idTrans(idt), error(err), data(dat) { header.timestamp = time(NULL); }
};


/** Estructura de datos relativa a una operación Notification
 */
template <typename T>
struct NotificationData_t{
	Blob::HeaderData_t header;
	T data;
	NotificationData_t(const T& dat) : data(dat) { header.timestamp = time(NULL); }
};


/** Estructura de datos de un mensaje NetworkManager y MQTTClient */
struct BaseMsg_t
{
    char* topic;
    void *data;
    uint16_t topic_len;
    uint16_t data_len;
};


static uint32_t getCRC32(void* data, uint32_t size){
    uint32_t crc = 0;
    uint8_t* udata = (uint8_t*)data;
    for(int i=0;i<size;i++){
        if((i&3) == 0){
            crc ^= (((uint32_t)udata[i]) & 0x000000ff);
        }
        else if((i&3) == 1){
            crc ^= ((((uint32_t)udata[i]) << 8) & 0x0000ff00);
        }
        else if((i&3) == 2){
			crc ^= ((((uint32_t)udata[i]) << 16) & 0x00ff0000);
		}
        else {
			crc ^= ((((uint32_t)udata[i]) << 24) & 0xff000000);
		}
    }
    return crc;
}


}



#endif
