#include <socketcan_wrapper/socketcan_wrapper.hpp>

#include <math.h>
#include <cstring>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

/**
 * @brief Construct a new SocketCAN_Wrapper::SocketCAN_Wrapper object
 * 
 * @param _aIfaceName Name of can interface desired (ex: can0)
 * @param _mTimeout Timeout desired for send and receive operations
 */
SocketCAN_Wrapper::SocketCAN_Wrapper( const std::string& _aIfaceName, std::chrono::duration<double> _mTimeout )
{
    _mSocket = ::socket( PF_CAN, SOCK_RAW, CAN_RAW );
    if( _mSocket <= 0 ) throw( Initialization_Error( "Create socket err: " + std::to_string( errno ) ) );

    int nbytes, err;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    ::strcpy( ifr.ifr_name, _aIfaceName.c_str() );
    err = ::ioctl( _mSocket, SIOCGIFINDEX, &ifr );
    if( err != 0 ) throw( Initialization_Error( "Ioctl err: " + std::to_string( errno ) ) );

    ::memset( &addr, 0, sizeof(addr) );
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    err = ::bind( _mSocket, (struct sockaddr *)&addr, sizeof(addr) );
    if( err != 0 ) throw( Initialization_Error( "Bind err: " + std::to_string( errno ) ) );

    if( _mTimeout != std::chrono::duration<double>::max() )
    {
        std::chrono::seconds timeout_sec = std::chrono::duration_cast<std::chrono::seconds>( _mTimeout );
        std::chrono::microseconds timeout_us = std::chrono::duration_cast<std::chrono::microseconds>( _mTimeout - timeout_sec );
        timeval tv;
        tv.tv_sec = static_cast<time_t>( timeout_sec.count() );
        tv.tv_usec =  static_cast<time_t>( timeout_us.count() ) ;
        err = ::setsockopt( _mSocket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv) );
        if( err != 0 ) throw( Initialization_Error( "Setsockopt err: " + std::to_string( errno ) ) );
    }
}

/**
 * @brief Destroy the SocketCAN_Wrapper::SocketCAN_Wrapper object
 * 
 */
SocketCAN_Wrapper::~SocketCAN_Wrapper()
{
    ::close( _mSocket );
}

/**
 * @brief Sends can frame over socketCAN
 * 
 * @param _aFrame
 * @returns Number of bytes sent, or -1 for errors
 */
ssize_t SocketCAN_Wrapper::send_frame( const can_frame& _aFrame )
{
    ssize_t err = ::write( _mSocket, &_aFrame, sizeof(can_frame) );
    if( err == -1 && errno == EAGAIN ) throw Timeout();
    return err;
}

/**
 * @brief Receives can frame from socketCAN
 * 
 * @param _aFrame
 * @returns Number of bytes received, or -1 for errors
 */
ssize_t SocketCAN_Wrapper::receive_frame( can_frame& _aFrame )
{
	ssize_t err = ::read( _mSocket, &_aFrame, sizeof(can_frame) );
    if( err == -1 && errno == EAGAIN ) throw Timeout();
    return err;
}
