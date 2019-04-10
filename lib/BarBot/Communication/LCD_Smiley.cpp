#include <chrono>
#include <thread>
#include "../../../include/BarBot/Communication/LCD_Smiley.h"
#include "../../../include/nIels2C/nIels2C.h"

/**
 * Initialize LCD display, shows the default happy smiley
 */
void LCD_Smiley::init() {
    nI2C = new nIels2C(0x3f, 4, 20);
    nI2C->clear();
    time_t start, end;
    time(&start);
    changeSmiley(0);
}

/**
 * Displays A generic happy smile
 */
void LCD_Smiley::displayHappy(){  //0
    nI2C->display_string("  /\\            /\\ ", 0);
    nI2C->display_string(" /  \\          /  \\ ", 1);
    nI2C->display_string("     \\________/     ", 3);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

/**
 * Displays a generic angry smile
 */
void LCD_Smiley::displayAngry(){ //1
    nI2C->display_string("   /            \\   ", 0);
    nI2C->display_string("  /   |      |   \\  ", 1);
    nI2C->display_string("      ________      ", 2);
    nI2C->display_string("     /        \\     ", 3);
}

/**
 * Display a straight smile
 */
void LCD_Smiley::displayStraight(){ //2
    nI2C->display_string("  /¯¯\\        /¯¯\\  ", 0);
    nI2C->display_string("  \\__/        \\__/  ", 1);
    nI2C->display_string("     \\________/     ", 3);
}

/**
 * Display a smiling smiley on the left side
 */
void LCD_Smiley::displayLeft(){ //3
    nI2C->display_string("/¯¯\\        /¯¯\\    ", 0);
    nI2C->display_string("\\__/        \\__/    ", 1);
    nI2C->display_string("     \\________/     ", 3);
}

/**
  * Display a smiling smiley on the right side
 */
void LCD_Smiley::displayRight(){ //4
    nI2C->display_string("    /¯¯\\        /¯¯\\", 0);
    nI2C->display_string("    \\__/        \\__/", 1);
    nI2C->display_string("     \\________/     ", 3);
}

/**
  * Changes the smiley by index
 */
void LCD_Smiley::changeSmiley(int nextSmiley){
    nI2C->clear();
    switch(nextSmiley){
        case 0: displayHappy();
        case 1: displayAngry();
        case 2: displayStraight();
        case 3: displayLeft();
        case 4: displayRight();
    }
}

/**
  * Show smileys that are looking around on the LCD
 */
void LCD_Smiley::lookAround(){
    if(lookingAround){
        leftLooking = 4;
        switch(currSmiley){
            case 0: changeSmiley(2);
            case 1: changeSmiley(2);
            case 2: changeSmiley(3);
            case 3: changeSmiley(4);
            case 4: changeSmiley(2);
        }
        leftLooking =leftLooking-1;
        waitingForLoop = 4;
    }
}

/**
 *
 */
void LCD_Smiley::waitingForLoopIteration() {
    if(waitingForLoop==0){
        lookAround();
        leftLooking = 4;
    }
    waitingForLoop = waitingForLoop - 1;
}

LCD_Smiley::LCD_Smiley() {}
