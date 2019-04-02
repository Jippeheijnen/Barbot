//
// Created by niels on 4/2/2019.
//

#include <iostream>
#include <fstream>

void validate_restcpp();

int main(){
    validate_restcpp();
}



void validate_restcpp() {
    std::cout << "Checking if rest-cpp is already downloaded" << std::endl;
    std::ifstream restcpp("include/rest-cpp/README.MD");
    if(!restcpp.good()) {
        std::cout << "* Rest-CPP is not here :(" << std::endl;
        std::cout << "* Cloning the Rest-CPP repository, hold on" << std::endl;
        system("git clone https://github.com/mrtazz/restclient-cpp include/rest-cpp");
    } else {
        std::cout << "* Rest-CPP is already here, nice!" << std::endl;
    }
    std::cout << std::endl;
    restcpp.close();
}