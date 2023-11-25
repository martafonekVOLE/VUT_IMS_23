cmake_minimum_required(VERSION 3.25)
project(Doprava)

set(CMAKE_CXX_STANDARD 17)

add_executable(Doprava main.cpp arg_parse.cpp arg_parse.h Classes/Accident.cpp Classes/Accident.h Classes/BusStop.cpp Classes/BusStop.h Classes/FirstBusStop.cpp Classes/FirstBusStop.h Classes/SecondBusStop.cpp Classes/SecondBusStop.h Classes/Bus.cpp Classes/Bus.h)
