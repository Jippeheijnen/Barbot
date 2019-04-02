cmake_minimum_required(VERSION 3.7.2)
project(BarBot)

set(CMAKE_CXX_STANDARD 14)

add_executable(Barbot "codebase/BarBot/main.cpp")

add_executable(DownloadRestCPP "include/DownloadRestCPP.cpp")

add_custom_target(DownloadRestCPP_Ex
        COMMAND DownloadRestCPP
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Downloading Rest-CPP"
        SOURCES "include/DownloadRestCPP.cpp"
        )

add_dependencies(Barbot DownloadRestCPP_Ex)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} )

#add_subdirectory(include/curl)
add_subdirectory(include/rest-cpp)
add_dependencies(Barbot restclient-cpp)



if (UNIX)
    target_sources(
            Barbot
            PUBLIC
            include/BrickPI3/Raspi/BrickPi3.cpp
#            codebase/BarBot/Bluetooth.cpp
#            codebase/Bluetooth/BluetoothSocket.cpp
    )
else (UNIX)
    cmake_policy(SET CMP0076 NEW)
    target_link_libraries(Barbot STATIC "C:\\Program Files\\CUrl\\lib")
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
        codebase/BarBot/Pumps.cpp
)


add_executable(LCD_Display "codebase/LCD_IPDisplay/LCD_IPDisplay.cpp")


target_sources(LCD_Display
        PUBLIC
        ./include/nIels2C/nIels2C.cpp
        ./include/nIels2C/nIels2C.h
        )



