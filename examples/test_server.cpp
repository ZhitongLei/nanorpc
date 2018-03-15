#include <stdio.h>
#include <string>

#include "net/server.h"

using namespace std;
using namespace nanorpc::net;

int main() {
    string url("tcp://127.0.0.1:19875");
    Server s(url);
    s.Run();
    return 0;
}
