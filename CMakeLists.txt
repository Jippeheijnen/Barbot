cmake_minimum_required(VERSION 3.7.2)
project(BarBot)

set(CMAKE_CXX_STANDARD 14)


add_executable(Barbot "codebase/BarBot/main.cpp")

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
    add_executable(GitInspector "codebase/GitInspector/GitInspector_Check.cpp")
endif (UNIX)

target_sources(
        Barbot
        PUBLIC
        codebase/BarBot/Movement.cpp
        codebase/BarBot/LineDetection.cpp
        codebase/BarBot/LineFollow.cpp
        codebase/NulVersie/nulVersie.cpp
        codebase/BarBot/CupDetection.cpp
)


add_executable(LCD_Display "codebase/LCD_IPDisplay/LCD_IPDisplay.cpp")


target_sources(LCD_Display
        PUBLIC
        ./include/nIels2C/nIels2C.cpp
        ./include/nIels2C/nIels2C.h
        )



