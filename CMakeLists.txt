cmake_minimum_required(VERSION 3.2)


set (CMAKE_CXX_STANDARD 11)

include_directories(libblinkt)

add_executable(blinktest 
                blinktest.c
                libblinkt/blinkt.c
                libblinkt/bcm2835.c
                )

target_link_libraries(blinktest rt m)