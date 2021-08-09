#pragma once

#include <thread>
#include <string>
#include <atomic>
#include <queue>

#include <linux/can.h>
#include <linux/can/raw.h>

class SocketCAN_Wrapper
{
public:
    SocketCAN_Wrapper( const std::string& _aIfaceName, float _mTimeoutSec = -1.0F );

    void send_frame( const can_frame& _aFrame );
    void receive_frame( can_frame& _aFrame );
private:
    int _mSocket = 0;
};
