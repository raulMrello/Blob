
#ifndef __MessageInterface__H
#define __MessageInterface__H

#include "mbed.h"
#include "cJSON.h"
#include "common_objects.h"

namespace Msg {
    enum class MessageType : uint32_t {
        undefined,
        hmi_manager,
        hmi_manager_cfg,
        hmi_manager_stat,
        stm32updater,
        mqtt_manager,
    };
    
    static const char* p_uid = "uid";
    static const char* p_cfg = "cfg";
    static const char* p_stat = "stat";
}

static int idMessage = 0;

class MessageInterface {
    public:
        MessageInterface(){
            _idMsg = idMessage++;
            DEBUG_TRACE_E(true, "[MsgInter]....", "constructor MessageInterface %d", _idMsg);
            _keys = 0;
            _persistent = false;
        }
		MessageInterface(cJSON *json){
			_keys = 0;
            parse(json);
            _persistent = false;
		}
        virtual ~MessageInterface() {
            DEBUG_TRACE_E(true, "[MsgInter]....", "destructor MessageInterface %d", _idMsg);
        }
        virtual bool parse(cJSON *json) = 0;
        virtual cJSON* getJson(ObjDataSelection type = ObjSelectAll) = 0;
        virtual MessageInterface* clone() = 0;
        bool isPersistent(){return _persistent;};
        void setPersistent(bool persistent){_persistent = persistent;};

        uint32_t getKeys(){return _keys;}
        Msg::MessageType getMsgType(){return _message_type;}

    protected:
        int _idMsg;
        Msg::MessageType _message_type;
        uint32_t _keys;
        bool _persistent;
};

#endif
