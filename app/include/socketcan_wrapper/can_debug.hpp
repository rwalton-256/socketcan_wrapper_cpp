#pragma once

#include <iostream>

#include <linux/can.h>
#include <linux/can/raw.h>

std::ostream& operator<<( std::ostream& os, const can_frame& frame );
