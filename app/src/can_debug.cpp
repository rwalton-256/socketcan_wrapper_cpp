#include <iomanip>

#include <socketcan_wrapper/can_debug.hpp>

std::ostream& operator<<( std::ostream& os, const can_frame& frame )
{
    os << "Can Frame:" << std::endl;
    os << "DLC: " << std::hex << +frame.can_dlc << std::endl;
    os << "ID: " << std::hex << frame.can_id << std::endl;
    os << "Data:";
    for( uint8_t i=0; i<frame.can_dlc; i++ )
    {
        os << " " << std::hex << std::setfill( '0' ) << std::setw( 2 ) << +frame.data[i];
    }
    os << std::endl;
    return os;
}
