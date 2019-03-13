//
// amended by Jippe Heijnen on 2/27/2019.
//

#include <iostream>
#include <iomanip>
#include <csignal>
#include <zconf.h>
#include "codebase/Movement.h"
#include "codebase/LineDetection.h"
#include "include/BrickPI3/BrickPi3.h"

Movement M;
LineDetection S;

int main() {
    M.init();
    M.speed(60);
    usleep(1000000);
    M.stop();
    return 0;
}