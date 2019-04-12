#include <chrono>
#include <thread>
#include <BarBot/Communication/LCD_Smiley.h>

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


void LCD_Smiley::show(const std::string & txt, uint8_t line) {
    nI2C->display_string("                   ", line);
    nI2C->display_string(txt, line);
}

/**
 * Displays A generic happy smile
 */
void LCD_Smiley::displayHappy(){  //0

    show("  /\\            /\\ ", 1);
    show(" /  \\          /  \\ ", 2);
    show("                    ", 3);
    show("     \\________/     ", 4);
}

/**
 * Displays a generic angry smile
 */
void LCD_Smiley::displaySad(){ //1
    show("   __          __   ", 1);
    show("  ||||        ||||  ", 2);
    show("        ____        ", 3);
    show("       |    |       ", 4);
}

/**
 * Display a straight smile
 */
void LCD_Smiley::displayStraight(){ //2
    show("   __          __   ", 1);
    show("  ||||        ||||  ", 2);
    show("                    ", 3);
    show("       |____|       ", 4);
}

/**
 * Display a smiling smiley on the left side
 */
void LCD_Smiley::displayLeft(){ //3
    show(" __          __     ", 1);
    show("||||        ||||    ", 2);
    show("                    ", 3);
    show("       |____|       ", 4);
}

/**
  * Display a smiling smiley on the right side
 */
void LCD_Smiley::displayRight(){ //4
    show("     __          __ ", 1);
    show("    ||||        ||||", 2);
    show("                    ", 3);
    show("       |____|       ", 4);
}

/**
  * Changes the smiley by index
 */
void LCD_Smiley::changeSmiley(int nextSmiley){
//    nI2C->clear();
    switch(nextSmiley){
        case 0:
            displayHappy();
            break;
        case 1:
            displaySad();
            break;
        case 2:
        case 4:
            displayStraight();
            break;
        case 3:
            displayLeft();
            break;
        case 5:
            displayRight();
            break;
    }
}

/**
  * Show smileys that are looking around on the LCD
 */
void LCD_Smiley::updateFace(){
    if(isDifferentFace)
    {
        differentFaceTimer--;
        if(differentFaceTimer <= 0) {
            isDifferentFace = false;
        }
    }

    lookingAroundTimer++;

    if(lookingAroundTimer > 30)
        lookingAroundTimer = 0;
    else
        return;


    if(!isDifferentFace) {
        currentFace++;
        if(currentFace < 2 || currentFace > 5)
            currentFace = 2;
    }
    else {
        return;
    }
    changeSmiley(currentFace);


//    if(isDifferentFace){
//        leftLooking = 4;
//        switch(currSmiley){
//            case 0: changeSmiley(2);
//            case 1: changeSmiley(2);
//            case 2: changeSmiley(3);
//            case 3: changeSmiley(4);
//            case 4: changeSmiley(2);
//        }
//        leftLooking =leftLooking-1;
//        waitingForLoop = 4;
//    }
}

/**
 *
 */
void LCD_Smiley::waitingForLoopIteration() {
    if(waitingForLoop==0){
        updateFace();
        leftLooking = 4;
    }
    waitingForLoop = waitingForLoop - 1;
}

LCD_Smiley::LCD_Smiley() {}

void LCD_Smiley::happy(int duration) {
    displayHappy();
    isDifferentFace = true;
    differentFaceTimer = duration;
    currentFace = 0;
}

void LCD_Smiley::sad(int duration) {
    displaySad();
    isDifferentFace = true;
    differentFaceTimer = duration;
    currentFace = 1;
}

void LCD_Smiley::straight(int duration) {
    displayStraight();
    isDifferentFace = true;
    differentFaceTimer = duration;
    currentFace = 2;
}

void LCD_Smiley::left(int duration) {
    displayLeft();
    isDifferentFace = true;
    differentFaceTimer = duration;
    currentFace = 3;
}

void LCD_Smiley::right(int duration) {
    displayRight();
    isDifferentFace = true;
    differentFaceTimer = duration;
    currentFace = 5;
}


