#include <assert.h>
#include <math.h>

#include <cstring>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <socketcan_wrapper/socketcan_wrapper.hpp>

/**
 * @brief Construct a new SocketCAN_Wrapper::SocketCAN_Wrapper object
 * 
 * @param _aIfaceName Name of can interface desired (ex: can0)
 * @param _mTimeoutSec Timeout (in seconds) desired for send and receive operations
 */
SocketCAN_Wrapper::SocketCAN_Wrapper( const std::string& _aIfaceName, float _mTimeoutSec )
{
    _mSocket = ::socket( PF_CAN, SOCK_RAW, CAN_RAW );
    assert( _mSocket > 0 );

    int nbytes, ret;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    strcpy( ifr.ifr_name, _aIfaceName.c_str() );
    ::ioctl( _mSocket, SIOCGIFINDEX, &ifr );

    memset( &addr, 0, sizeof(addr) );
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    ret = bind( _mSocket, (struct sockaddr *)&addr, sizeof(addr) );
    assert( ret == 0 );

    if( _mTimeoutSec >= 0.0F )
    {
        timeval tv;
        tv.tv_sec = static_cast<time_t>( _mTimeoutSec );
        tv.tv_usec =  static_cast<time_t>( fmod( _mTimeoutSec, 1.0F ) * 1000000.0F ) ;
        setsockopt(  _mSocket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv) );
    }
}

/**
 * @brief Sends can frame over socketCAN
 * 
 * @param _aFrame 
 */
void SocketCAN_Wrapper::send_frame( const can_frame& _aFrame )
{
    int nbytes;
    nbytes = write( _mSocket, &_aFrame, sizeof(can_frame) );
}

/**
 * @brief Receives can frame from socketCAN
 * 
 * @param _aFrame 
 */
void SocketCAN_Wrapper::receive_frame( can_frame& _aFrame )
{
    int nbytes;
	nbytes = read( _mSocket, &_aFrame, sizeof(can_frame) );

    assert( nbytes == sizeof(can_frame) );
}
