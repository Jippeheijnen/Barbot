//
// Created by niels on 4/5/2019.
//


#include <BarBot/Util/Logger.h>
#include "BarBot/Movement/ArduinoMotor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <stdbool.h>
#include <stropts.h>
#include <errno.h>
#include <cstdint>
#include <termios.h>


#define BAUDRATE B9600

#define MODEMDEVICE "/dev/ttyUSB0"


int set_interface_attribs (int fd, int speed, int parity)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        std::string msg = "Error while setting attributes: ";
        Logger::log(ArduinoMotor::TAG, msg.append(std::to_string(errno)));
        return -1;
    }

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        return -1;
    }
    return 0;
}

void set_blocking (int fd, int should_block)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        std::string msg = "Error while setting Blocking: ";
        Logger::log(ArduinoMotor::TAG, msg.append(std::to_string(errno)));
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        std::string msg = "Error setting term attributes: ";
        Logger::log(ArduinoMotor::TAG, msg.append(std::to_string(errno)));
    }
}


///////////////////////////////



const std::string ArduinoMotor::TAG = "ArduinoMotor";

void ArduinoMotor::command(const std::string & pack) {
    write(fileDescriptor, pack.c_str(), pack.size());
    clear();
}




void ArduinoMotor::setSpeed(uint8_t speed) {
    Logger::log(TAG, "Motor speed: " + std::to_string(speed));
    std::string cmd = "s";
    cmd.append(std::to_string(int(speed)));

    cmd.append("\n");

    command(cmd);

}

void ArduinoMotor::setDirection(bool rot) {
    std::string dir = rot ? "forward": "backward";
//    Logger::log(TAG, "Motor direction: " + dir);
    std::string cmd = "d";
    cmd.append(std::to_string(!rot)).append("\n");
    command(cmd);
}

void ArduinoMotor::init() {
//     open the device
    fileDescriptor = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fileDescriptor == 0)
    {
        perror(MODEMDEVICE);
        std::string msg = "Error: Failed to open /dev/ttyUSB0: ";
        Logger::log(ArduinoMotor::TAG, msg.append(std::to_string(errno)));
        exit(-1);
    }

    set_interface_attribs (fileDescriptor, BAUDRATE, 0);  // set speed to 19200 bps, 8n1 (no parity)
    set_blocking (fileDescriptor, 0);                // set no blocking

//     Open STREAMS device.
    fds[0].fd = fileDescriptor;
    fds[0].events = POLLRDNORM;
}

void ArduinoMotor::clear() {
    int ret = poll(fds, 1, 1);		//wait for response

    if (ret > 0)
    {
//         An event on one of the fds has occurred.
        if (fds[0].revents & POLLHUP)
        {
            printf("Hangup\n");
        }
        if (fds[0].revents & POLLRDNORM)
        {
            int res = read(fileDescriptor,buffer,255);
            buffer[res]=0;		// terminate buffer
            sscanf(buffer,"%d\n",&variable);
        }
    }
}








