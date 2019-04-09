//
// Created by Niels on 4/2/2019.
//

#include <iostream>
#include <BarBot/Util/Logger.h>
#include "BarBot/Connectivity/SocketConnection.h"

const std::string SocketConnection::TAG = "SocketConnection";

void SocketConnection::init(std::string IP, int port) {
    p_libsys_init();

    PSocketAddress *address;

    Logger::log(TAG, "Creating Address");
    if ((address = p_socket_address_new(IP.c_str(), port)) == nullptr) {
        cleanup("Error setting socket address", address);
        return;
    }

    Logger::log(TAG, "Making Socket");
    if ((socket = p_socket_new(P_SOCKET_FAMILY_INET, P_SOCKET_TYPE_STREAM, P_SOCKET_PROTOCOL_TCP, NULL)) == nullptr) {
        cleanup("Error creating socket", address);
        return;
    }

    Logger::log(TAG, "Connecting to socket");
    if (!p_socket_connect(socket, address, nullptr)) {
        cleanup("Error connecting to socket", address);
        return;
    }

    Logger::log(TAG, "Making Socket Blocking");
    p_socket_set_blocking(socket, true);
}

void SocketConnection::cleanup(const std::string &message, PSocketAddress *address) {
    Logger::log(TAG, message);
    if (address != nullptr)
        p_socket_address_free(address);
    if (socket != nullptr)
        p_socket_free(socket);
}

std::vector<std::string> SocketConnection::read_line() {
    std::vector<std::string> ret = {};
    pssize bytesread = p_socket_receive(socket, buffer, 1024, nullptr);

    std::string buff;
    buff.append(buffer, bytesread);

    size_t pos = 0;
    std::string token;
    while ((pos = buff.find(":-:")) != std::string::npos) {
        token = buff.substr(0, pos);
        ret.push_back(token);
        buff.erase(0, pos + 3);
    }
    if(ret.empty() && buff == "buff")
        return {};
    ret.push_back(buff);
    return ret;
}

void SocketConnection::send_line(const std::vector<std::string> &command) {
    std::string toSend = command[0];
    for(size_t i = 1; i < command.size(); i++)
    {
        toSend.append(":-:");
        toSend.append(command[i]);
    }
    p_socket_send(socket, toSend.c_str(), toSend.size(), nullptr);
}

std::vector<std::string> SocketConnection::command(const std::vector<std::string> &command) {
    send_line(command);
    return read_line();
}

void SocketConnection::close() {
    p_socket_close(socket, nullptr);
    cleanup("Cleaning Up Socket", nullptr);
}
