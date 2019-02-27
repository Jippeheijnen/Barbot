cmake_minimum_required(VERSION 3.7.2)
project(BarBot)

set(CMAKE_CXX_STANDARD 14)



add_executable(Barbot "nulversie/main.cpp")

target_sources(Barbot
        PUBLIC
            include/BrickPi3.cpp
        )


add_executable(LCD_Display "lcd_leven/lcd_display.cpp")


target_sources(LCD_Display
        PUBLIC
            include/nIels2C/nIels2C.cpp
            include/nIels2C/nIels2C.h
        )