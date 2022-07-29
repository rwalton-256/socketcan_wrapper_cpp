#include <socketcan_wrapper/socketcan_wrapper.hpp>

#include <iostream>
#include <assert.h>
#include <cstring>
#include <cmath>

int main ( int argc, char** argv )
{
    auto delay = std::chrono::seconds( 1 );
    // Need to initialize this virtual can port before it works
    // sudo modprobe vcan
    // sudo ip link add dev vcan0 type vcan0
    // sudo ip link set vcan0 up
    SocketCAN_Wrapper a( "vcan0" ), b( "vcan0", delay );

    can_frame bar, foo =
    {
        .can_id = 0xf,
        .can_dlc = CAN_MAX_DLC,
        .data = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 }
    };

    assert( a.send_frame( foo ) == sizeof(can_frame) );
    assert( b.receive_frame( bar ) == sizeof(can_frame) );
    assert( memcmp( &foo, &bar, sizeof(can_frame) ) == 0 );
    auto tp = std::chrono::high_resolution_clock::now();
    bool timeout = false;
    try
    {
        b.receive_frame( bar );
    }
    catch(SocketCAN_Wrapper::Timeout)
    {
        timeout = true;
    }
    assert(timeout);
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - tp;
    assert( fabs( elapsed.count() - std::chrono::duration_cast<std::chrono::duration<double>>( delay ).count() ) < 0.1 );

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
