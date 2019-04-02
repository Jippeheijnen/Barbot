//
// Created by niels on 4/2/2019.
//

#include <iostream>
#include "Pumps.h"

void Pumps::pour(int drink) {
    char url [50] ;
    sprintf(url, "http://sitewolfe.com:8443/pour/%d", drink);
    RestClient::Response res = RestClient::get(url);
    std::cout << res.body << std::endl;
}
