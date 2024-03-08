#ifndef MSG_CREATOR_H
#define MSG_CREATOR_H

#include "JsonParserBlob.h"

namespace Msg {
	//CREATERS MSGS
    static Blob::GetRequest_t* createGetRequestMsg(const char* topic, void* msg, uint16_t msg_len, bool _json_supported = false){
		Blob::GetRequest_t* resp = NULL;

		bool json_decoded = false;
		if(_json_supported){
			resp = (Blob::GetRequest_t*)Heap::memAlloc(sizeof(Blob::GetRequest_t));
			MBED_ASSERT(resp);
			if(!(json_decoded = JsonParser::getGetRequestFromJson(*resp, *(cJSON**)msg))){
				Heap::memFree(resp);
				DEBUG_TRACE_W(true, "[Message]....", "ERR_JSON. Decodificando el mensaje");
			}
		}

		// en primer lugar asegura que los datos tienen el tama�o correcto
		if(!json_decoded && msg_len != sizeof(Blob::GetRequest_t)){
			DEBUG_TRACE_W(true, "[Message]....", "ERR_MSG Men. Error en el n� de datos del mensaje, topic [%s]", topic);
			return NULL;
		}

		if(!json_decoded){
			// el mensaje es un blob tipo metering_manager
			resp = (Blob::GetRequest_t*)Heap::memAlloc(sizeof(Blob::GetRequest_t));
			MBED_ASSERT(resp);
			*resp = *((Blob::GetRequest_t*)msg);
		}

		return resp;
	}

	static Blob::SetRequest_t* createSetRequestMsg(const char* topic, void* msg, uint16_t msg_len, bool _json_supported = false){
		Blob::SetRequest_t* resp = NULL;

		bool json_decoded = false;
		if(_json_supported){
			resp = (Blob::SetRequest_t*)Heap::memAlloc(sizeof(Blob::SetRequest_t));
			MBED_ASSERT(resp);
			if(!(json_decoded = JsonParser::getSetRequestFromJson(*resp, *(cJSON**)msg))){
				Heap::memFree(resp);
				DEBUG_TRACE_W(true, "[Message]....", "ERR_JSON. Decodificando el mensaje");
			}
		}

		// en primer lugar asegura que los datos tienen el tama�o correcto
		if(!json_decoded && msg_len != sizeof(Blob::SetRequest_t)){
			DEBUG_TRACE_W(true, "[Message]....", "ERR_MSG Men. Error en el n� de datos del mensaje, topic [%s]", topic);
			return NULL;
		}

		if(!json_decoded){
			// el mensaje es un blob tipo metering_manager
			resp = (Blob::SetRequest_t*)Heap::memAlloc(sizeof(Blob::SetRequest_t));
			MBED_ASSERT(resp);
			*resp = *((Blob::SetRequest_t*)msg);
		}

		return resp;
	}

	//SUBSCRIPTIONS
	static void subcriptionToEvent_GetReq(uint64_t event, const char* topic, void* msg, uint16_t msg_len, GlobalActiveModule* obj){
        Blob::GetRequest_t* req = NULL;
        bool json_decoded = false;
        if(obj->isJSONSupported()){
			req = (Blob::GetRequest_t*)Heap::memAlloc(sizeof(Blob::GetRequest_t));
			MBED_ASSERT(req);
			cJSON* msgDup = *(cJSON**)msg;
			if(!(json_decoded = JsonParser::getObjFromJson(*req, msgDup))){
				Heap::memFree(req);
			}
        }

        // Antes de nada, chequea que el tama�o de la zona horaria es correcto, en caso contrario, descarta el topic
        if(!json_decoded && msg_len != sizeof(Blob::GetRequest_t)){
        	DEBUG_TRACE_W(obj->getLogActive(), obj->getLogName(), "ERR_MSG. Error en el n� de datos del mensaje, topic [%s]", topic);
			return;
        }

        // crea el mensaje para publicar en la m�quina de estados
        State::Msg* op = (State::Msg*)Heap::memAlloc(sizeof(State::Msg));
        MBED_ASSERT(op);

        // el mensaje es un blob tipo Blob::GetRequest_t
        if(!json_decoded){
        	req = (Blob::GetRequest_t*)Heap::memAlloc(sizeof(Blob::GetRequest_t));
        	MBED_ASSERT(req);
        	*req = *((Blob::GetRequest_t*)msg);
        }
		op->sig = event;
		// apunta a los datos
		op->msg = req;

		// postea en la cola de la m�quina de estados
		if(obj->putMessage(op) != osOK){
			DEBUG_TRACE_E(obj->getLogActive(), obj->getLogName(), "ERR_PUT. al procesar el topic[%s]", topic);
			if(op->msg){
				Heap::memFree(op->msg);
			}
			Heap::memFree(op);
		}
        return;
    }

	static void subcriptionToEvent_SetReq(uint64_t event, const char* topic, void* msg, uint16_t msg_len, GlobalActiveModule* obj){
        Blob::SetRequest_t* req = NULL;
        bool json_decoded = false;
		if(obj->isJSONSupported()){
			req = (Blob::SetRequest_t*)Heap::memAlloc(sizeof(Blob::SetRequest_t));
			MBED_ASSERT(req);
			cJSON* msgDup = *(cJSON**)msg;
			if(!(json_decoded = JsonParser::getSetRequestFromJson(*req, msgDup))){
				Heap::memFree(req);
			}
		}

        // Antes de nada, chequea que el tama�o de la zona horaria es correcto, en caso contrario, descarta el topic
        if(!json_decoded && msg_len != sizeof(Blob::SetRequest_t)){
        	DEBUG_TRACE_W(obj->getLogActive(), obj->getLogName(), "ERR_MSG. Error en el n� de datos del mensaje, topic [%s]", topic);
			return;
        }

        // crea el mensaje para publicar en la m�quina de estados
        State::Msg* op = (State::Msg*)Heap::memAlloc(sizeof(State::Msg));
        MBED_ASSERT(op);

        // el mensaje es un blob tipo mqtt_manager
        if(!json_decoded){
			DEBUG_TRACE_W(obj->getLogActive(), obj->getLogName(), "Construyo otro SetRequest?");
        	req = (Blob::SetRequest_t*)Heap::memAlloc(sizeof(Blob::SetRequest_t));
        	MBED_ASSERT(req);
			req->clone(*(Blob::SetRequest_t*)msg);
        }
        op->sig = event;
		// apunta a los datos
		op->msg = req;

		// postea en la cola de la m�quina de estados
		if(obj->putMessage(op) != osOK){
			DEBUG_TRACE_E(obj->getLogActive(), obj->getLogName(), "ERR_PUT. al procesar el topic[%s]", topic);
			if(op->msg){
				Heap::memFree(op->msg);
			}
			Heap::memFree(op);
		}
        return;
	}

	static void subcriptionToEvent_None(uint64_t event, const char* topic, void* msg, uint16_t msg_len, GlobalActiveModule* obj){
		// crea el mensaje para publicar en la m�quina de estados
		State::Msg* op = (State::Msg*)Heap::memAlloc(sizeof(State::Msg));
		MBED_ASSERT(op);

		op->sig = event;
		// apunta a los datos
		op->msg = NULL;

		// postea en la cola de la m�quina de estados
		if(obj->putMessage(op) != osOK){
			if(op->msg){
				Heap::memFree(op->msg);
			}
			Heap::memFree(op);
		}
	}

	static void subcriptionToEvent_BaseMsg(uint64_t event, const char* topic, void* msg, uint16_t msg_len, GlobalActiveModule* obj){
		// crea el mensaje para publicar en la m�quina de estados
		State::Msg* op = (State::Msg*)Heap::memAlloc(sizeof(State::Msg));
		MBED_ASSERT(op);

		Blob::BaseMsg_t * mq_msg = (Blob::BaseMsg_t *)Heap::memAlloc(sizeof(Blob::BaseMsg_t));
		MBED_ASSERT(mq_msg);
		mq_msg->topic = (char*)Heap::memAlloc(strlen(topic)+1);
		MBED_ASSERT(mq_msg->topic);
		strcpy(mq_msg->topic, topic);
		MBED_ASSERT(mq_msg->topic);

		mq_msg->topic_len = strlen(topic)+1;

		if(obj->isJSONSupported()){
			cJSON *jData = cJSON_Duplicate(*(cJSON**)msg, true);

			mq_msg->data = jData;
			mq_msg->data_len = sizeof(cJSON*);
		}
		else{
			mq_msg->data = (void*)Heap::memAlloc(msg_len);
			MBED_ASSERT(mq_msg->data);
			memcpy(mq_msg->data, msg, msg_len);
			mq_msg->data_len = msg_len;
		}
		
		op->sig = event;
		op->msg = mq_msg;
		
		// postea en la cola de la m�quina de estados
		if(obj->putMessage(op) != osOK)
		{
			DEBUG_TRACE_E(obj->getLogActive(), obj->getLogName(), "[%s:%d] ERR_PUT", __FUNCTION__, __LINE__);
			Heap::memFree(mq_msg->topic);
			if(obj->isJSONSupported())
				cJSON_Delete((cJSON*)mq_msg->data);
			else
				Heap::memFree(mq_msg->data);
			if(op->msg)
				Heap::memFree(op->msg);
			Heap::memFree(op);
		}
	}

	static void subscriptionToEvent(Blob::GlobalMessageType type, uint64_t event, const char* topic, void* msg, uint16_t msg_len, GlobalActiveModule* obj){
		DEBUG_TRACE_D(obj->getLogActive(), obj->getLogName(), "Recibido topic %s", topic);
		switch (type)
		{
		case Blob::GlobalMessageType::GetRequest:
			return subcriptionToEvent_GetReq(event, topic, msg, msg_len, obj);
			break;

		case Blob::GlobalMessageType::SetRequest:
			return subcriptionToEvent_SetReq(event, topic, msg, msg_len, obj);
			break;

		case Blob::GlobalMessageType::None:
			return subcriptionToEvent_None(event, topic, msg, msg_len, obj);
			break;

		case Blob::GlobalMessageType::BaseMsg:
			return subcriptionToEvent_BaseMsg(event, topic, msg, msg_len, obj);
			break;
		
		default:
			DEBUG_TRACE_D(obj->getLogActive(), obj->getLogName(), "Tipo de globalMessage no valido");
			break;
		}
	}

	//PUBLICATIONS
	static void publicateResponseMsg(string topic, uint32_t idTrans, Blob::ErrorData_t error, MessageInterface* msg, MQ::PublishCallback _publicationCb, GlobalActiveModule* obj){
		Blob::Response_t* resp = new Blob::Response_t(idTrans, error, msg);

		ObjDataSelection objType = ObjDataSelection::ObjSelectAll;
		if(topic.find("/cfg/")!= string::npos){
			objType = ObjSelectCfg;
		}
		else if(topic.find("/value/")!= string::npos){
			objType = ObjSelectState;
		}

		if(obj->isJSONSupported()){
			cJSON* jresp = JsonParser::getJsonFromResponse(*resp, objType);
			if(jresp){
				char* jmsg = cJSON_PrintUnformatted(jresp);
				cJSON_Delete(jresp);
				MQ::MQClient::publish(topic.c_str(), jmsg, strlen(jmsg)+1, &_publicationCb);
				Heap::memFree(jmsg);
				delete(resp);
			}
		}
		else{
			MQ::MQClient::publish(topic.c_str(), resp, sizeof(Blob::Response_t), &_publicationCb);
			delete(resp);
		}
		
		if(objType == ObjSelectCfg){
			DEBUG_TRACE_D(obj->getLogActive(), obj->getLogName(), "Enviada respuesta con cfg solicitada");
		}
		else if(objType == ObjSelectState){
			DEBUG_TRACE_D(obj->getLogActive(), obj->getLogName(), "Enviada respuesta con stat solicitada");
		}
		else{
			DEBUG_TRACE_D(obj->getLogActive(), obj->getLogName(), "Enviada respuesta con datos solicitados");
		}
	}
}

#endif