#include <stdio.h>
#include <string>

#include "net/socket.h"
#include "net/tool.h"

#include "nanomsg/reqrep.h"

using namespace std;
using namespace nanorpc::net;

int main() {
    Socket s;
    if (!s.Create(AF_SP, NN_REQ)) {
        fprintf(stderr, "bind error: %s\n", GetStrError());
        return 1;
    }

    string url("tcp://127.0.0.1:19875");
    int ret = s.Connect(url);
    if (ret < 0) {
        fprintf(stderr, "bind error %d\n", ret);
        return 1;
    }

    string message("hello, nanorpc");
    ret = s.Send(message.c_str(), message.length(), 0);
    fprintf(stderr, "send ret %d\n", ret);
    
    void *buffer = nullptr;
    s.Recv(&buffer, NN_MSG, 0);
    fprintf(stdout, "Receive new message: %s\n", (char *)buffer);
    FreeMessage(buffer);
    return 0;
}
