#include <string>

#include "net/socket.h"
#include "util/thread_pool.h"
#include "net/callback.h"

namespace nanorpc {
namespace net {

class Handler;

class Server {
public:
    Server(const std::string &url);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    void Run();

    void SetMessageCallback(const MessageCallback &cb) {
        message_callback_ = cb;
    }

    void SetErrorCallback(const ErrorCallback &cb) {
        error_callback_ = cb;
    }

private:
    std::string url_;
    Socket socket_;
    ThreadPool thread_pool_;

    MessageCallback message_callback_;    
    ErrorCallback error_callback_;
};

}
}
