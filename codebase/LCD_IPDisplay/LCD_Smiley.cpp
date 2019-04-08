#include "LCD_Smiley.h"
#include "../../include/nIels2C/nIels2C.h"

void LCD_Smiley::init() {
    nIels2C lcd(0x3f, 4, 20);
//    lcd.clear();
    time_t start, end;
    time(&start);
    std::atexit(exiting);
    changeSmiley(0);
}

void LCD_Smiley::displayHappy(){  //0
    lcd.display_string("  /\\            /\\ ", 0);
    lcd.display_string(" /  \\          /  \\ ", 1);
    lcd.display_string("     \\________/     ", 3);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void LCD_Smiley::displayAngry(){ //1
    lcd.display_string("   /            \\   ", 0);
    lcd.display_string("  /   |      |   \\  ", 1);
    lcd.display_string("      ________      ", 2);
    lcd.display_string("     /        \\     ", 3);
}

void LCD_Smiley::displayStraight(){ //2
    lcd.display_string("  /¯¯\\        /¯¯\\  ", 0);
    lcd.display_string("  \\__/        \\__/  ", 1);
    lcd.display_string("     \\________/     ", 3);
}

void LCD_Smiley::displayLeft(){ //3
    lcd.display_string("/¯¯\\        /¯¯\\    ", 0);
    lcd.display_string("\\__/        \\__/    ", 1);
    lcd.disolay_string("     \\________/     ", 3);
}

void LCD_Smiley::displayRight(){ //4
    lcd.display_string("    /¯¯\\        /¯¯\\", 0);
    lcd.display_string("    \\__/        \\__/", 1);
    lcd.display_string("     \\________/     ", 3);
}

void LCD_Smiley::changeSmiley(nextSmiley){
    lcd.clear();
    switch(nextSmiley){
        case 0: displayHappy();
        case 1: displayAngry();
        case 2: displayStraight();
        case 3: displayLeft();
        case 4: displayRight();
    }
}

void LCD_Smiley::lookAround(){
    if(lookingAround){
        leftLooking = 4;
        switch(currSmiley){
            case 0: changeSmiley(2);
            case 1: changeSmilet(2);
            case 2: changeSmilet(3);
            case 3: changeSmiley(4);
            case 4: changeSmiley(0);
        }
        leftLooking =leftLooking-1
        if(leftLooking == 0){
            lookingAround=0;
        }
        waitingForLoop = 4
    }
}

void LCD_Smiley::waitingForLoopIretation{
    if(waitinfForLoop==0){
        lookAround();
    }
    waitingForLoop = waitingForLoop - 1;
};