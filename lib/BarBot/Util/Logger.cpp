//
// Created by niels on 4/7/2019.
//

#include "BarBot/Util/Logger.h"
#include <iostream>
#include <typeinfo>


std::vector<std::string> Logger::logShow;



void Logger::setLogShow(std::vector<std::string> ls) {
    Logger::logShow = ls;
}


void Logger::log(std::string tag, std::string message) {
    bool found = false;
    for (std::string ls : logShow) {
        if (tag == ls) {
            found = true;
            break;
        }
    }

    if(found) {
        for(size_t i = tag.size(); i < 25; i++)
            tag.append(" ");
        tag.append(":");
        std::cout << tag << message << std::endl;
    }
}

