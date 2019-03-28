
#include  <iostream>

#include <iomanip>
#include <csignal>
#include <zconf.h>

#include "LineFollow.h"
#include "Movement.h"

LineFollow LF;
Movement M;


int main() {
    while (1) {
        LF.follow();
    }

}