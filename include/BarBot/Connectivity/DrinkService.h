//
// Created by niels on 4/2/2019.
//

#ifndef BARBOT_DRINKSERVICE_H
#define BARBOT_DRINKSERVICE_H
#include <vector>
#include "SocketConnection.h"


/**
 * Fluid from the database.
 * Note: amount should only be set for a fluid in a drink, unused fluids don't have an amount
 */
struct fluid {
    int id;
    std::string name;
    int amount = 0;
};

/**
 * A drink from the database. Includes all fluids of which it consists
 */
struct drink {
    int id;
    std::string name;
    std::vector<fluid> fluids;
};

/**
 * Connection to the drink server for retrieving fluid and drink data
 * Can also send a command to pour a drink
 */
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
