//
// Created by Niels on 4/2/2019.
//

#ifndef BARBOT_SOCKETCONNECTION_H
#define BARBOT_SOCKETCONNECTION_H
#ifdef __linux__
//linux code goes here
#elif _WIN32
    #define WSMAN_API_VERSION_1_0
    #include <winsock2.h>
    #include <windows.h>
    #include <wsman.h>
#else

#endif

#include <iostream>
#include <vector>
#include <plibsys.h>
#include <psocket.h>


class SocketConnection {
private:
    PSocket * socket;
    char buffer[1025];

    void cleanup(const std::string & message, PSocketAddress * address);
public:
    static const std::string TAG;
    void init(std::string IP, int port);
    void close();
    std::vector<std::string> read_line();
    void send_line(const std::vector<std::string> & command);
    std::vector<std::string> command(const std::vector<std::string> &command);
};


#endif //BARBOT_SOCKETCONNECTION_H
