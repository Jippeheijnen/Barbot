//
// Created by niels on 4/7/2019.
//

#ifndef BARBOT_LOGGER_H
#define BARBOT_LOGGER_H

#include <iostream>
#include <vector>


class Logger {
private:
    static std::vector<std::string> logShow;
public:
    static void setLogShow(std::vector<std::string> ls);
    static void log(std::string, std::string message);
};


#endif //BARBOT_LOGGER_H
