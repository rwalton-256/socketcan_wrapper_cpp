# CMakeLists files in this project can
cmake_minimum_required (VERSION 2.8.11)

add_library (
    socketcan_wrapper
    src/socketcan_wrapper.cpp
    )

target_compile_options( socketcan_wrapper PUBLIC -std=c++11 )

target_include_directories (socketcan_wrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(
    socketcan_wrapper_test
    test/test.cpp
)

target_compile_options( socketcan_wrapper PUBLIC -std=c++11 )

target_link_libraries( socketcan_wrapper_test socketcan_wrapper )
