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
#include "codebase/LineFollow.h"

Movement M;
LineFollow LF;
LineDetection L;

int main() {
    M.init();
    L.init(0,0);
    M.speed(20);
    LF.Follow();
}