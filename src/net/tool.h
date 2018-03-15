#ifndef __TOOL_H__
#define __TOOL_H__

namespace nanorpc {
namespace net {

bool FreeMessage(void *buffer);
int GetErrorNo();
const char* GetStrError();

}
}

#endif
