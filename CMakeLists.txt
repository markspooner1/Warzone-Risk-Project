cmake_minimum_required(VERSION 3.23)
project(COMP345_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(COMP345_Project Player.cpp Orders.cpp Map.cpp Cards.cpp Player.cpp MapDriver.cpp)
