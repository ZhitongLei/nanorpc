#ifndef SOCKET_H 
#define SOCKET_H

#include <string>

namespace nanorpc {
namespace net {

class Socket {
public:
    Socket() noexcept;
    Socket(int fd) noexcept;
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket &&rhs) noexcept;
    Socket& operator=(Socket &&rhs) noexcept;

    // Destruction will close the underlying socket
    ~Socket();

    inline int fd() const { return fd_; }

    bool Create(int domain, int protocol);
    bool IsActived() const { return (fd_ >= 0); }
    
    // Bind and listen synchronously
    int Bind(const std::string &url);

    int Connect(const std::string &url);

    // 1. if succeeds, return the number of bytes in the message is returned
    // 2. if failed, -1 is returned and errno is set
    int Send(const void *buffer, size_t len, int flags);
    
    // Return value: the same as Send
    int Recv(void *buffer, size_t len, int flags);

    void Detach() { fd_ = -1; }
    bool Close();

private:
    int fd_;
};

}
}

#endif
