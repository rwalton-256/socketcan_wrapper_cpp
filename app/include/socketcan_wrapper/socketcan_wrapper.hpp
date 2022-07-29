#pragma once

#include <thread>
#include <string>
#include <atomic>
#include <queue>
#include <exception>
#include <chrono>

#include <linux/can.h>
#include <linux/can/raw.h>

/**
 * @brief Linux Socket CAN c++ wrapper
 * 
 */
class SocketCAN_Wrapper
{
public:
    class Initialization_Error : public std::exception
    {
        std::string _mWhat;
    public:
        Initialization_Error( const std::string& _aWhat ) : _mWhat( _aWhat ) {}
        const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
        {
            return _mWhat.c_str();
        }
    };
    class Timeout : public std::exception {};
    SocketCAN_Wrapper( const std::string& _aIfaceName, std::chrono::duration<double> _mTimeout = std::chrono::duration<double>::max() );

    SocketCAN_Wrapper( const SocketCAN_Wrapper& ) = delete;
    SocketCAN_Wrapper( SocketCAN_Wrapper&& ) = delete;
    SocketCAN_Wrapper& operator=( const SocketCAN_Wrapper& ) = delete;

    ~SocketCAN_Wrapper();

    ssize_t send_frame( const can_frame& _aFrame );
    ssize_t receive_frame( can_frame& _aFrame );
private:
    int _mSocket = 0;
};
