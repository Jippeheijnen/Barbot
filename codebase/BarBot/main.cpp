
#include  <iostream>

#include <iomanip>
#include <csignal>
#include <zconf.h>

#include "../../include/BrickPI3/BrickPi3.h"
BrickPi3 BP3;

#include "Pumps.h"
#include "Movement.h"
Movement M;
#include "LineDetection.h"
LineDetection LD;
#include "LineFollow.h"

LineFollow LF;

void mainInit() {
    //Todo: init all relevant libraries.
    M.init(BP3);

}

int main() {
    Pumps p;
    p.pour(3);
}