// File Name: tool.cpp
// Author: lei
// Created Time: 2018-03-12 01:32:42
#include "net/tool.h"
#include "nanomsg/nn.h"

namespace nanorpc {
namespace net {

bool FreeMessage(void *buffer) {
    int ret = nn_freemsg(buffer); 
    return (ret == 0);
}

int GetErrorNo() {
    return nn_errno();
}

const char* GetStrError() {
    return nn_strerror(GetErrorNo());
}

}
}
