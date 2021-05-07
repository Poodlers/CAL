cmake_minimum_required(VERSION 3.17)
project(CAL_MP1_ALGO)

set(CMAKE_CXX_STANDARD 14)

add_executable(CAL_MP1_ALGO main.cpp client.cpp productprovider.cpp node.cpp deliveryCar.cpp utils.h utils.cpp)