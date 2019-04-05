//
// Created by niels on 4/2/2019.
//

#include <iostream>
#include "PumpService.h"

/**
 * Pour Drink By ID.
 * @param drink Drink ID to be poured
 * @return True if pouring was possible, False if not all ingredients are connected or when an error occured
 */
bool PumpService::pour(int drink) {

    std::vector<std::string> result = connection.command({"pour", std::to_string(drink)});
    return (!result.empty() && result[0] == "success");

}

/**
 * Transforms vector of strings to vector of fluids.
 * @param data This is the vector containing strings.
 * @return Returns vector with fluids (obviously).
 */
std::vector<fluid> parse_fluids(const std::vector<std::string> & data) {
    std::vector<fluid> fluids = {};
    for(size_t i = 0; i < data.size(); i++) {
        fluids.push_back({
            stoi(data[i]),
            data[i+1]
        });
        i+=1;
    }
    return fluids;
}

/**
 * Get all known fluids
 * @return List of Fluids
 */
std::vector<fluid> PumpService::get_fluids() {

    return parse_fluids(connection.command({"get_fluids"}));

}

/**
 * Get all fluids that are currently connected
 * @return List of Fluids
 */
std::vector<fluid> PumpService::get_connected_fluids() {

    return parse_fluids(connection.command({"get_connected_fluids"}));

}

/**
 * Get all known Drinks.
 * @return List Of Drinks
 */
std::vector<drink> PumpService::get_drinks() {
    std::vector<std::string> response = connection.command({"get_drinks"});
    std::vector<drink> drinkList = {};

    for(size_t i = 0; i < response.size(); i++) {
        drink d = {
                stoi(response[i]),
                response[i+1],
                {}
        };
        i+= 2;
        while(i < response.size() && response[i] != "::end::") {
            d.fluids.push_back({
                stoi(response[i]),
                response[i+1],
                stoi(response[i+2]),
            });
            i+= 3;
        }
        drinkList.push_back(d);

    }

    return drinkList;

}

/**
 * Initialize connection to the Pump API
 */
void PumpService::init() {
    connection.init();
}


/**
 * Close connection
 */
void PumpService::close() {
    connection.close();
}


