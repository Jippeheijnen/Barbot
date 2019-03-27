cmake_minimum_required(VERSION 3.7.2)
project(BarBot)

set(CMAKE_CXX_STANDARD 14)


add_executable(Barbot "main.cpp")

target_sources(Barbot
        PUBLIC
        )

if (UNIX)
    target_sources(
            Barbot
            PUBLIC
            include/BrickPI3/Raspi/BrickPi3.cpp
    )
else (UNIX)
    cmake_policy(SET CMP0076 NEW)
    target_sources(
            Barbot
            PUBLIC
            include/BrickPI3/Windows/BrickPi3.cpp
    )
endif (UNIX)

target_sources(
        Barbot
        PUBLIC
        codebase/Movement.cpp
        codebase/LineDetection.cpp
        codebase/LineFollow.cpp
        nulversie/nulVersie.cpp
)


add_executable(LCD_Display "lcd_leven/lcd_display.cpp")


target_sources(LCD_Display
        PUBLIC
        ./include/nIels2C/nIels2C.cpp
        ./include/nIels2C/nIels2C.h
        )
