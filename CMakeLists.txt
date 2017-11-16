cmake_minimum_required(VERSION 3.8)


set (CMAKE_CXX_STANDARD 11)

include_directories(libblinkt)

add_executable(blinktest 
                blinktest.c
                libblinkt/blinkt.c
                libblinkt/bcm2835.c
                )
