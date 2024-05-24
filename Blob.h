/*
 * Blob.h
 *
 *  Created on: Ene 2018
 *      Author: raulMrello
 *
 *	Blob es un m�dulo que agrupa todos los objetos de datos (estructuras, enumeraciones, etc...) utilizadas de forma
 *	general en una aplicaci�n y que son reutilizados por m�ltiples m�dulos. De esta forma, el acceso a todos estos
 *	datos es sencilla mediante la importaci�n de la librer�a <blob.h>, en lugar de ir incluyendo todos los m�dulos
 *	que definen cada uno de los datos.
 */
 
#ifndef BLOB_H
#define BLOB_H

#include "mbed.h"
#include "MessageInterface.h"
  


namespace Blob {

//---------------------------------------------------------------------------------
//- Definiciones comunes ----------------------------------------------------------
//---------------------------------------------------------------------------------

/** Lista de errores comunes */
enum ErrorCode{
	ErrOK,				//!< Sin errores
	ErrJsonMalformed,	//!< Objeto json incorrecto
	ErrIdTransInvalid,	//!< Identificaci�n de transacci�n inv�lida
	ErrStringFormat,	//!< Cadena de texto con formato incorrecto
	ErrEmptyContent,	//!< Contenido vac�o
	ErrRangeValue,		//!< Rango incorrecto
	ErrAllocJson,		//!< No se permite la creaci�n del objeto
	ErrJsonUnhandled,	//!< Objeto Json sin maneajador
	ErrUidInvalid,		//!< UID Inv�lido
	ErrElementInvalid,	//!< Element invalido
	ErrElementMaxTasks,	//!< Element invalido
	MaxNumErrorCodes,
	ErrFile,
	ErrorOTACar,
	ErrConection
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
	"uid invalid",
	"element invalid",
	"elem num max data",
	"max num error",
	"error: file",
	"OTA error: car connected",
	"connection error"
};

enum GlobalMessageType{
	None,
	SetRequest,
	GetRequest,
	Response,
	Notification,
	BaseMsg
};

static GlobalMessageType checkType(int size);


/** Tama�o m�ximo de un objeto BLOB. En este caso viene determinado por el tama�o de
 * 	los datos de usuario que viajan por el paquete MQNet_Message_t eliminando el tama�o
 * 	del topic_id.
 */
static const uint32_t MaxBlobSize = 224;

/** Tama�o por defecto de los textos de descripci�n de errores */
static const uint16_t DefaultErrDescrLen = 64;

/** Define un valor idtrans sin uso */
static const uint32_t UnusedIdTrans = 0;

/** Tama�o m�ximo del timestamp en segundos para calcular una fecha y una hora concreta
 *  de un a�o. Se considera que todos los a�os tiene 366 d�as y siempre existe el 29 de
 *  febrero.
 */
static const uint32_t TimestampSecondsYearLimit = (366 * 24 * 3600);

/** Tama�o m�ximo del timestamp en minutos para calcular una hora concreta
 *  de un d�a.
 */
static const uint16_t TimestampMinutesDayLimit = (24 * 60);

/** Estructura de datos para env�o de cabecera incluyendo el tiemstamp, etc...
 */
struct HeaderData_t{
	time_t timestamp;
	uint32_t heapFree;
};


/** Estructura de datos para env�o de errores
 */
struct ErrorData_t{
	uint32_t code;
	char descr[DefaultErrDescrLen];
	ErrorData_t(){
		code = ErrOK;
		descr[0] = 0;
	}
};


/** Estructura de datos relativa a una operaci�n SetRequest
 */

class GlobalMessage_t{
	public:
		virtual GlobalMessage_t(){
			DEBUG_TRACE_E(true, "[JsonParser]....", "constructor GlobalMessage_t");
		}
		virtual ~GlobalMessage_t(){
			DEBUG_TRACE_E(true, "[JsonParser]....", "destructor GlobalMessage_t");
		}
};

struct SetRequest_t : public GlobalMessage_t{
	uint32_t idTrans;
	uint32_t keys;
	MessageInterface* data;
	Blob::ErrorData_t _error;
	SetRequest_t(){
		DEBUG_TRACE_I(true, "[JsonParser]....", "constructor SetRequest_t");
		idTrans = 0;
		data = NULL;
		_error.code = ErrOK;
		_error.descr[0] = 0;
	}
	SetRequest_t(MessageInterface* dat, uint32_t x_id=0){
		DEBUG_TRACE_I(true, "[JsonParser]....", "constructor SetRequest_t idTrans: %ld", x_id);
		idTrans = x_id;
		data = dat;
		_error.code = ErrOK;
		_error.descr[0] = 0;
	}
	SetRequest_t(SetRequest_t* req){
		DEBUG_TRACE_E(true, "[JsonParser]....", "clone SetRequest_t idTrans: %ld", req->idTrans);
		idTrans = req->idTrans;
		keys = req->keys;
		data = req->data->clone();
		_error = req->_error;
	}
	~SetRequest_t() {
		DEBUG_TRACE_E(true, "[JsonParser]....", "destructor SetRequest_t idTrans: %ld", idTrans);
		if(data && !data->isPersistent())
    		delete(data);
  	}
};

struct SetRequestElement_t : public GlobalMessage_t{
    Blob::SetRequest_t* setReq;
    char* element;
};


/** Estructura de datos relativa a una operaci�n GetRequest
 */
struct GetRequest_t : public GlobalMessage_t{
	uint32_t idTrans;
	Blob::ErrorData_t _error;
	GetRequest_t(uint32_t x_id=0){
		DEBUG_TRACE_I(true, "[JsonParser]....", "constructor GetRequest_t idTrans: %ld", x_id);
		idTrans = x_id;
		_error.code = ErrOK;
		_error.descr[0] = 0;
	}
	GetRequest_t(GetRequest_t* req){
		DEBUG_TRACE_E(true, "[JsonParser]....", "clone GetRequest_t idTrans: %ld", req->idTrans);
		idTrans = req->idTrans;
		_error = req->_error;
	}
	~GetRequest_t() {
		DEBUG_TRACE_E(true, "[JsonParser]....", "destructor GetRequest_t idTrans: %ld", idTrans);
	}
};

struct GetRequestElement_t : public GlobalMessage_t{
    Blob::GetRequest_t* getReq;
    char* element;
};


/** Estructura de datos relativa a una operaci�n Response sin errores
 */
struct Response_t : public GlobalMessage_t{
	uint32_t idTrans;
	Blob::HeaderData_t header;
	Blob::ErrorData_t error;
	MessageInterface* data;
	Response_t() : idTrans(0) { 
		DEBUG_TRACE_I(true, "[JsonParser]....", "constructor Response_t");
		header.timestamp = time(NULL); 
	}
	Response_t(uint32_t idt, const Blob::ErrorData_t& err, MessageInterface* dat) : idTrans(idt), error(err), data(dat) { 
		DEBUG_TRACE_I(true, "[JsonParser]....", "constructor Response_t idTrans: %ld", idTrans);
		header.timestamp = time(NULL); header.heapFree = Heap::getFreeHeap(); 
	}
	Response_t(Response_t* req){
		DEBUG_TRACE_E(true, "[JsonParser]....", "clone Response_t idTrans: %ld", req->idTrans);
		idTrans = req->idTrans;
		header = req->header;
		data = req->data->clone();
		error = req->error;
	}
	~Response_t() {
		DEBUG_TRACE_E(true, "[JsonParser]....", "destructor Response_t idTrans: %ld", idTrans);
		if(data && !data->isPersistent())
			delete(data);
  	}
};


/** Estructura de datos relativa a una operaci�n Notification
 */
struct NotificationData_t : public GlobalMessage_t{
	Blob::HeaderData_t header;
	MessageInterface* data;
	NotificationData_t() { header.timestamp = time(NULL); header.heapFree = Heap::getFreeHeap(); }
	NotificationData_t(MessageInterface* dat) : data(dat) { header.timestamp = time(NULL); header.heapFree = Heap::getFreeHeap(); }
	NotificationData_t(NotificationData_t* req){
		DEBUG_TRACE_E(true, "[JsonParser]....", "clone NotificationData_t");
		header = req->header;
		data = req->data->clone();
	}
	~NotificationData_t() {
		DEBUG_TRACE_E(true, "[JsonParser]....", "destructor NotificationData_t");
		if(data && !data->isPersistent())
			delete(data);
  	}
};

struct NotificationDataElement_t : public GlobalMessage_t{
    Blob::NotificationData_t* notif;
    char* element;
};


/** Estructura de datos de un mensaje NetworkManager y MQTTClient */
struct BaseMsg_t : public GlobalMessage_t
{
    char* topic;
    void *data;
    uint16_t topic_len;
	// -5 determina que es un mensaje de tipo cJSON*
    int data_len;
	BaseMsg_t(){
		DEBUG_TRACE_E(true, "[JsonParser]....", "constructor BaseMsg_t");
		topic = NULL;
		data = NULL;
		topic_len = 0;
		data_len = 0;
	}
	~BaseMsg_t(){
		DEBUG_TRACE_E(true, "[JsonParser]....", "destructor BaseMsg_t");
		DEBUG_TRACE_W(true, "[JsonParser]....", "size topic: %d", topic_len);
		DEBUG_TRACE_W(true, "[JsonParser]....", "topic: %s", topic);
		DEBUG_TRACE_W(true, "[JsonParser]....", "data_len: %d", data_len);
		if(topic)
			Heap::memFree(topic);
		if(data){
			// -5 determina que es un mensaje de tipo cJSON*
			if(data_len == -5)
				cJSON_Delete((cJSON*)data);
			else if(checkType(data_len)==GlobalMessageType::None)
				Heap::memFree(data);
			else
				delete((Blob::GlobalMessage_t*)data);
		}
	}
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

static GlobalMessageType checkType(int size){
	if(size == sizeof(Blob::SetRequest_t)){
		return Blob::SetRequest;
	}
	else if(size == sizeof(Blob::GetRequest_t)){
		return Blob::GetRequest;
	}
	else if(size == sizeof(Blob::Response_t)){
		return Blob::Response;
	}
	else if(size == sizeof(Blob::NotificationData_t)){
		return Blob::Notification;
	}
	else if(size == sizeof(Blob::BaseMsg_t)){
		return Blob::BaseMsg;
	}
	else{
		return Blob::None;
	}
}

}



#endif
