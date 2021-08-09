#include <iostream>
#include <assert.h>

#include <cstring>

#include <socketcan_wrapper/socketcan_wrapper.hpp>

int main ( int argc, char** argv )
{
    // Need to initialize this virtual can port before it works
    SocketCAN_Wrapper a( "vcan0" ), b( "vcan0" );

    can_frame bar, foo =
    {
        .can_id = 0xf,
        .can_dlc = CAN_MAX_DLC,
        .data = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 }
    };

    a.send_frame( foo );
    b.receive_frame( bar );
    assert( memcmp( &foo, &bar, sizeof(can_frame) ) == 0 );

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
