cmake_minimum_required(VERSION 3.23)
project(COMP345_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(COMP345_Project
        Cards.cpp
        Cards.h
        CardsDriver.cpp
        GameEngine.cpp
        GameEngine.h
        GameEngineDriver.cpp
        Map.cpp
        Map.h
        MapDriver.cpp
        Orders.cpp
        Orders.h
        OrdersDriver.cpp
        Player.cpp
        Player.h
        PlayerDriver.cpp)
