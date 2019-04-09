//
// Created by niels on 4/2/2019.
//

#ifndef BARBOT_DRINKSERVICE_H
#define BARBOT_DRINKSERVICE_H
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

class DrinkService {
private:
    SocketConnection* drinkServerConnection;
public:
    static const std::string TAG;
    void init(SocketConnection* dsC);
    void close();
    bool pour(int drink);
    std::vector<fluid> get_fluids();
    std::vector<fluid> get_connected_fluids();
    std::vector<drink> get_drinks();
};


#endif //BARBOT_DRINKSERVICE_H
