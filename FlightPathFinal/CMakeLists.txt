cmake_minimum_required(VERSION 3.23)
project(FlightPathFinal)

set(CMAKE_CXX_STANDARD 17)

add_executable(FlightPathFinal main.cpp Route.h Route.cpp Airport.h Airport.cpp)
