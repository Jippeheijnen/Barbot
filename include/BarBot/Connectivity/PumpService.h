//
// Created by niels on 4/2/2019.
//

#ifndef BARBOT_PUMPSERVICE_H
#define BARBOT_PUMPSERVICE_H
#include <vector>
#include "SocketConnection.h"


struct fluid {
    int id;
    std::string name;
    int amount = 0;
};

struct drink {
    int id;
    std::string name;
    std::vector<fluid> fluids;
};

class PumpService {
private:
    SocketConnection connection;
public:
    static const std::string TAG;
    void init();
    void close();
    bool pour(int drink);
    std::vector<fluid> get_fluids();
    std::vector<fluid> get_connected_fluids();
    std::vector<drink> get_drinks();
};


#endif //BARBOT_PUMPSERVICE_H
