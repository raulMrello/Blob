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

enum MsgInterface : uint32_t {
	MsgIfaceUnknown = 0,
	MsgIfaceMqtt = (1u << 0),
	MsgIfaceMqttUser = (1u << 1),
	MsgIfaceEmbeddedWeb = (1u << 2),
	MsgIfaceNetworkManager = (1u << 3),
	MsgIfaceLocal = (1u << 4),
	MsgIfaceAll = (1u << 31)
};


struct RoutingData_t{
	uint32_t iface;
	RoutingData_t(uint32_t msg_iface = (MsgIfaceLocal | MsgIfaceAll))
		: iface(msg_iface) {}
};

/** Estructura de datos para env�o de cabecera incluyendo routing, timestamp, etc...
 */
struct HeaderData_t{
	Blob::RoutingData_t routing;
	time_t timestamp;
	uint32_t heapFree;
	HeaderData_t(uint32_t msg_iface = (MsgIfaceLocal | MsgIfaceAll))
		: routing(msg_iface), timestamp(time(NULL)), heapFree(Heap::getFreeHeap()) {}
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
template <typename T>
struct SetRequest_t{
	Blob::RoutingData_t routing;
	uint32_t idTrans;
	uint32_t keys;
	T data;
	Blob::ErrorData_t _error;
	SetRequest_t(const T& dat, uint32_t x_id=0, uint32_t iface=(MsgIfaceLocal | MsgIfaceAll))
		: routing(iface), idTrans(x_id), keys(0), data(dat) {
		_error.code = ErrOK;
		_error.descr[0] = 0;
	}
};

template <typename T>
struct SetRequestElement_t {
    Blob::SetRequest_t<T>* setReq;
    char* element;
};


/** Estructura de datos relativa a una operaci�n GetRequest
 */
struct GetRequest_t{
	Blob::RoutingData_t routing;
	uint32_t idTrans;
	Blob::ErrorData_t _error;
	// Por defecto los stat de respuesto a los get no se env�an a todos los interfaces, sino solo al local, para evitar que se reenv�en por la red de forma innecesaria
	GetRequest_t(uint32_t x_id=0, uint32_t iface=(MsgIfaceLocal))
		: routing(iface), idTrans(x_id) {
		_error.code = ErrOK;
		_error.descr[0] = 0;
	}
};

struct GetRequestElement_t {
    Blob::GetRequest_t* getReq;
    char* element;
};


/** Estructura de datos relativa a una operaci�n Response sin errores
 */
template <typename T>
struct Response_t{
	uint32_t idTrans;
	Blob::HeaderData_t header;
	Blob::ErrorData_t error;
	T data;
	Response_t() : idTrans(0), header(Blob::MsgIfaceAll) {}
	Response_t(uint32_t idt, const Blob::ErrorData_t& err, const T& dat, uint32_t routing_iface = Blob::MsgIfaceAll)
		: idTrans(idt), header(routing_iface), error(err), data(dat) {}
};


/** Estructura de datos relativa a una operaci�n Notification
 */
template <typename T>
struct NotificationData_t{
	Blob::HeaderData_t header;
	T data;
	NotificationData_t() : header(Blob::MsgIfaceLocal | Blob::MsgIfaceAll) {}
	NotificationData_t(const T& dat) : header(Blob::MsgIfaceLocal | Blob::MsgIfaceAll), data(dat) {}
};

template <typename T>
struct NotificationDataElement_t {
    Blob::NotificationData_t<T>* notif;
    char* element;
};


/** Estructura de datos de un mensaje NetworkManager y MQTTClient */
struct BaseMsg_t
{
    char* topic;
    void *data;
    uint16_t topic_len;
    uint16_t data_len;

    ~BaseMsg_t() {
        if(topic) {
            Heap::memFree(topic);
            topic = NULL;
        }
        if(data) {
            Heap::memFree(data);
            data = NULL;
        }
        topic_len = 0;
        data_len = 0;
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


// template<typename T>
// static inline void setMessageOrigin(T& msg, uint32_t origin){
// 	msg.routing.iface = origin;
// }


// template<typename T>
// static inline void setMessageDestination(T& msg, uint32_t destination){
// 	msg.routing.iface = destination;
// }


// template<typename T>
// static inline void setMessageRouting(T& msg, uint32_t iface){
// 	msg.routing.iface = iface;
// }


// template<typename T>
// static inline void setGetRequestRouting(T& msg, uint32_t iface){
// 	msg.routing.iface = iface;
// }


// template<typename T>
// static inline void setSetRequestRouting(T& msg, uint32_t iface){
// 	msg.routing.iface = iface;
// 	if(iface != MsgIfaceUnknown){
// 		msg.routing.iface |= MsgIfaceAll;
// 	}
// }


// template<typename T>
// static inline const Blob::RoutingData_t& getMessageRouting(const T& msg){
// 	return msg.routing;
// }


// static inline bool isDestinationMatch(uint32_t routing_iface, uint32_t iface){
// 	return (routing_iface == MsgIfaceUnknown || (routing_iface & MsgIfaceAll) != 0 || ((routing_iface & iface) != 0));
// }


// static inline bool shouldForwardMessage(const Blob::RoutingData_t& routing, uint32_t iface){
// 	return isDestinationMatch(routing.iface, iface);
// }


// static inline bool getRoutingFromBinary(const void* data, uint16_t data_len, Blob::RoutingData_t& routing){
// 	if(data == NULL || data_len < sizeof(Blob::RoutingData_t)){
// 		routing = Blob::RoutingData_t();
// 		return false;
// 	}
// 	memcpy(&routing, data, sizeof(Blob::RoutingData_t));
// 	return true;
// }


// static inline bool shouldForwardBinaryMessage(const void* data, uint16_t data_len, uint32_t iface){
// 	Blob::RoutingData_t routing;
// 	if(!getRoutingFromBinary(data, data_len, routing)){
// 		return true;
// 	}
// 	return shouldForwardMessage(routing, iface);
// }


// template <typename T>
// static inline Blob::SetRequest_t<T>* makeSetRequest(const T& dat, uint32_t x_id = 0, uint32_t iface = (MsgIfaceLocal | MsgIfaceAll)){
// 	Blob::SetRequest_t<T>* req = new Blob::SetRequest_t<T>(dat, x_id, iface);
// 	MBED_ASSERT(req);
// 	setSetRequestRouting(*req, iface);
// 	return req;
// }


// static inline Blob::GetRequest_t makeGetRequest(uint32_t x_id = 0, uint32_t iface = (MsgIfaceLocal | MsgIfaceAll)){
// 	Blob::GetRequest_t req(x_id, iface);
// 	return req;
// }


// template <typename T>
// static inline Blob::NotificationData_t<T>* makeNotification(const T& dat, uint32_t iface = (MsgIfaceLocal | MsgIfaceAll)){
// 	Blob::NotificationData_t<T>* notif = new Blob::NotificationData_t<T>(dat);
// 	MBED_ASSERT(notif);
// 	setMessageRouting(*notif, iface);
// 	return notif;
// }


}



#endif
