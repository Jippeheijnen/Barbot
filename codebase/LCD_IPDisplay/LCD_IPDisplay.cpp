//
// Created by niels on 2/25/2019.
//
#include <chrono>
#include <thread>
#include "../../include/nIels2C/nIels2C.h"
#include <sys/unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ifaddrs.h>


void show_ips(nIels2C lcd) {
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs(&ifap);
//    lcd.clear();
    uint8_t i = 1;
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family == AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            lcd.display_string(addr, i++);
        }
    }

    freeifaddrs(ifap);
}

void exiting() {
}

int main() {
    nIels2C lcd(0x3f, 4, 20);
//    lcd.clear();
    time_t start, end;
    time(&start);
    std::atexit(exiting);

    while (true) {
        show_ips(lcd);
        time(&end);
        double dif = difftime(end, start);
        lcd.display_string("Uptime: " + std::to_string(dif), 4);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }


}
