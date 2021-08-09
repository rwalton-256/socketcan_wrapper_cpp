# CMakeLists files in this project can
cmake_minimum_required (VERSION 2.8.11)

project( socketcan_wrapper )

add_library (
    socketcan_wrapper
    app/src/socketcan_wrapper.cpp
    app/src/can_debug.cpp
    )

target_compile_options( socketcan_wrapper PUBLIC -std=c++11 )

target_include_directories (socketcan_wrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/app/include)

add_executable(
    socketcan_wrapper_test
    test/test.cpp
)

target_link_libraries( socketcan_wrapper_test socketcan_wrapper )
