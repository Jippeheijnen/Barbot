//
// Created by niels on 4/7/2019.
//

#ifndef BARBOT_LOGGER_H
#define BARBOT_LOGGER_H

#include <iostream>
#include <vector>


/**
 * Class for logging to stdout
 * Filters log by sender (tag), and formats log messages
 */
class Logger {
private:
    static std::vector<std::string> logShow;
public:
    /**
     * Alters the tags whose logs should be shown.
     * When given an empty list, all logs will be shown
     * @param ls List of TAG strings
     */
    static void setLogShow(std::vector<std::string> ls);

    /**
     * Log a message. If tag is present in the logShow list, or the list is empty, the log will be printed to stdout
     * @param tag The log tag to use for this message
     * @param message Message to log
     */
    static void log(std::string tag, std::string message);
};


#endif //BARBOT_LOGGER_H
