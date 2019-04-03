cmake_minimum_required(VERSION 3.7.2)
project(BarBot)

set(CMAKE_CXX_STANDARD 14)

add_executable(Barbot "codebase/BarBot/main.cpp")

include(DownloadProject.cmake)
download_project(PROJ                plibsys
                GIT_REPOSITORY      https://github.com/saprykin/plibsys
                GIT_TAG             master
                UPDATE_DISCONNECTED 1
                QUIET
)


add_subdirectory(${plibsys_SOURCE_DIR} ${plibsys_BINARY_DIR} EXCLUDE_FROM_ALL)

target_include_directories(Barbot PRIVATE ${plibsys_SOURCE_DIR} )
target_link_libraries(Barbot plibsys)
configure_file(${CMAKE_BINARY_DIR}/plibsysconfig.h ${CMAKE_BINARY_DIR}/plibsys-src/src)

if (UNIX)
    target_sources(
            Barbot
            PUBLIC
            include/BrickPI3/Raspi/BrickPi3.cpp
    )
    target_link_libraries(Barbot bluetooth)
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
        codebase/BarBot/Actors/Movement.cpp
        codebase/BarBot/Sensors/LineDetection.cpp
        codebase/BarBot/Events/LineFollow.cpp
        codebase/NulVersie/nulVersie.cpp
        codebase/BarBot/Sensors/CupDetection.cpp
        codebase/BarBot/API/PumpService.cpp
        codebase/BarBot/API/SocketConnection.cpp
        codebase/BarBot/App/BluetoothSocket.cpp
        codebase/BarBot/App/BluetoothConnection.cpp
        codebase/BarBot/Actors/PWM.cpp
)


add_executable(LCD_Display "codebase/LCD_IPDisplay/LCD_IPDisplay.cpp")


target_sources(LCD_Display
        PUBLIC
        ./include/nIels2C/nIels2C.cpp
        ./include/nIels2C/nIels2C.h
        )



