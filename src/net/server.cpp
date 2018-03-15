#include "net/server.h"

#include <assert.h>

#include "nanomsg/nn.h"
#include "nanomsg/reqrep.h"

#include "net/tool.h"
#include "net/handler.h"
#include "util/thread_pool.h"

namespace nanorpc {
namespace net {

Server::Server(const std::string &url)
    : url_(url),
      thread_pool_(10) {
    socket_.Create(AF_SP, NN_REP);
    assert(socket_.IsActived());
}

void Server::Run() {
    int ret = socket_.Bind(url_);
    if (ret == -1) {
        fprintf(stderr, "[Error] nanomsg bind url(%s) error, ret %d(%s)\n", url_.c_str(), ret, GetStrError());
        return;
    }

    while (true) {
        /*
        struct nn_iovec iov;
        struct nn_msghdr hdr;
        void *control = nullptr, *buffer = nullptr;
        memset (&hdr, 0, sizeof (hdr));
        iov.iov_base = &buffer;
        iov.iov_len = NN_MSG;
        hdr.msg_iov = &iov;
        hdr.msg_iovlen = 1;
        hdr.msg_control = &control;
        hdr.msg_controllen = NN_MSG;
        ret = nn_recvmsg (socket_.fd(), &hdr, 0);
        */
        void *buffer = nullptr;
        ret = socket_.Recv(&buffer, NN_MSG, 0);
        if (ret < 0) {
            int error = GetErrorNo();
            const char *error_message = GetStrError();
            if (error == EBADF) {
                fprintf(stderr, "[Error] Socket have been closed.\n");
                return;
            } else if (error == EAGAIN) {
                fprintf(stderr, "Non-blocking mode was requested and there’s no message to receive\n");
                continue;
            }
            error_callback_(socket_, error, error_message);
            fprintf (stderr, "nn_recv: %s\n", error_message);
            break;
        }
        // XXX send to channel
        message_callback_(socket_, (char*)buffer, ret, std::time_t(nullptr));
        fprintf(stdout, "Receive new message: %s\n", (char *)buffer);
        char *response = "Here comes the reply";
        socket_.Send(response, 20, 0);
        FreeMessage(buffer);
    }
}

}
}
