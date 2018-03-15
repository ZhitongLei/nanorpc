#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include "event.h"

namespace nanorpc {
namespace net {

class Channel {
public:
    Channel(int fd);
    Channel(const Channel&) = delete;
    Channel& operator=(const Channel&) = delete;

    typedef std::function<void()> EventCallback; 
    void SetReadCallback(EventCallback cb);
    void SetCloseCallback(EventCallback cb);
    void SetErrorCallback(EventCallback cb);

    //void EnableRead() { event_ |= kReadEvent; }
    //void DisableRead() { event_ &= ~kReadEvent; }
    //void EnableWrite() { event_ |= kWriteEvent; }
    //void DisableWrite() { event_ &= ~kWriteEvent; }
    void SetRevent(int16_t event) { revent_ = event; }

private:
    const int fd_;

    int16_t event_;
    int16_t revent_;

    EventCallback read_callback_;
    EventCallback error_callback_;
}; 

}
}

#endif
