#include "net/socket.h"
#include "nanomsg/nn.h"

namespace nanorpc {
namespace net {

Socket::Socket() noexcept
    : fd_(-1) { 
}

Socket::Socket(int fd) noexcept
    : fd_(fd) {
}

Socket::Socket(Socket &&rhs) noexcept 
    : fd_(rhs.fd_) {
    rhs.Detach();
}

Socket& Socket::operator=(Socket &&rhs) noexcept {
    if (this != &rhs) {
        fd_ = rhs.fd_;
        rhs.Detach();
    }
    return *this;
}

Socket::~Socket() {
    Close();
    // TODO: Add err log
}

bool Socket::Create(int domain, int protocol) {
    fd_ = nn_socket(domain, protocol);
    return IsActived();
}

int Socket::Connect(const std::string &url) {
    return nn_connect(fd_, url.c_str());
}

int Socket::Bind(const std::string &url) {
    return nn_bind(fd_, url.c_str());
}

int Socket::Send(const void *buffer, size_t len, int flags) {
    return nn_send(fd_, buffer, len, flags);
}

int Socket::Recv(void *buffer, size_t len, int flags) {
    return nn_recv(fd_, buffer, len, flags);
}

bool Socket::Close() {
    int ret = 0;
    if (IsActived()) {
        ret = nn_close(fd_);
        Detach();
    }
    return (ret == 0);
}

}
}
