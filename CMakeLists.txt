cmake_minimum_required(VERSION 4.1)
project(40_cli)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(40_cli
        Carta40.cpp
        Carta40.h
        Cortana.cpp
        Cortana.h
        Jugador.cpp
        Jugador.h
        main.cpp
        Usuario.cpp
        Usuario.h)
