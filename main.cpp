
#include  <iostream>

#include <iomanip>
#include <csignal>
#include <zconf.h>

#include "codebase/LineFollow.h"
#include "codebase/Movement.h"

LineFollow LF;
Movement M;


int main() {
    while (1) {
        LF.follow();
    }

}