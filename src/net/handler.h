#ifndef __NET_HANDLER_H__
#define __NET_HANDLER_H__

#include "net/callback.h"

namespace nanorpc {
namespace net {

class Handler {
public:
    void SetMessageCallback(const MessageCallback &cb) {
        message_callback_ = cb;
    }

    void SetErrorCallback(const ErrorCallback &cb) {
        error_callback_ = cb;
    }

private:
    MessageCallback message_callback_;    
    ErrorCallback error_callback_;
};

}
}

#endif
