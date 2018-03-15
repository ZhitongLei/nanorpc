#ifndef __NET_CALLBACK_H__
#define __NET_CALLBACK_H__

#include <ctime>
#include <memory>
#include <functional>

namespace nanorpc {
namespace net {

class Socket;
using SocketPtr = std::shared_ptr<Socket>;
using MessageCallback = std::function<void (Socket &s, char *buffer, int len, const std::time_t &t)>;

using ErrorCallback = std::function<void (Socket &s, int error, const char *error_message)>; 

}
}

#endif
