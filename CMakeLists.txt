cmake_minimum_required(VERSION 3.7.2)
project(BarBot)

set(CMAKE_CXX_STANDARD 14)
include(DownloadProject.cmake)
include_directories(include)
if(POLICY CMP0076)
    cmake_policy(SET CMP0076 OLD)
endif (POLICY CMP0076)



################################################ Target: PlibSys

download_project(PROJ                plibsys
        GIT_REPOSITORY      https://github.com/saprykin/plibsys
        GIT_TAG             master
        UPDATE_DISCONNECTED 1
        QUIET
        )
add_subdirectory(${plibsys_SOURCE_DIR} ${plibsys_BINARY_DIR} EXCLUDE_FROM_ALL)
configure_file(${CMAKE_BINARY_DIR}/plibsysconfig.h ${CMAKE_BINARY_DIR}/plibsys-src/src)



################################################ Target: LCD_IP Display
add_executable(LCD_Display "lib/LCD_IPDisplay/LCD_IPDisplay.cpp")


target_sources(LCD_Display
        PUBLIC
        ./include/nIels2C/nIels2C.cpp
        ./include/nIels2C/nIels2C.h
        )

################################################ Target: Barbot
add_executable(Barbot "lib/BarBot/main.cpp")

target_link_libraries(Barbot plibsys)

target_include_directories(Barbot PRIVATE ${plibsys_SOURCE_DIR} )
if (UNIX)
    target_link_libraries(Barbot wiringPi)
    target_sources(
            Barbot
            PUBLIC
            ./include/BrickPI3/Raspi/BrickPi3.cpp
            ./lib/BarBot/Connectivity/BluetoothSocket.cpp
            ./lib/BarBot/Connectivity/AppControlService.cpp
            ./lib/BarBot/Communication/SpeechRecognition.cpp
            ./lib/BarBot/Movement/ArduinoMotor.cpp
    )
    target_link_libraries(Barbot bluetooth)
else (UNIX)
    cmake_policy(SET CMP0076 NEW)
    target_sources(
            Barbot
            PUBLIC
            ./include/BrickPI3/Windows/BrickPi3.cpp
            lib/BarBot/Connectivity/AppControlService.windows.cpp
            ./lib/BarBot/Communication/SpeechRecognition.windows.cpp
            ./lib/BarBot/Movement/ArduinoMotor.windows.cpp
    )
    add_executable(GitInspector "lib/GitInspector/GitInspector_Check.cpp")
endif (UNIX)

target_sources(
        Barbot
        PUBLIC
        ./lib/BarBot/BarBot.cpp
        ./lib/BarBot/Movement/Movement.cpp
        ./lib/BarBot/Sensors/LineDetection.cpp
        ./lib/BarBot/Scripts/LineFollow.cpp
        ./lib/BarBot/Scripts/SpeechInterpretation.cpp
        ./lib/NulVersie/nulVersie.cpp
        ./lib/BarBot/Sensors/CupDetection.cpp
        lib/BarBot/Connectivity/DrinkService.cpp
        lib/BarBot/Connectivity/AppRequestService.cpp
        ./lib/BarBot/Connectivity/SocketConnection.cpp
        ./lib/BarBot/Communication/SpeechSynthesis.cpp
        ./lib/BarBot/Scripts/Pathing.cpp
        ./lib/BarBot/Util/Logger.cpp
)




