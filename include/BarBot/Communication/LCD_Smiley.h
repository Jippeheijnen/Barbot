#ifndef BARBOT_LCD_SMILEY_H
#define BARBOT_LCD_SMILEY_H


#include <nIels2C/nIels2C.h>

/**
 * Library to easily show smileyfaces on an I2C LCD :)
 */
class LCD_Smiley {
private:
    nIels2C* nI2C;
    int currSmiley;
    int leftLooking;
    int waitingForLoop;
public:
    int nextSmiley;
    bool lookingAround;

    void init();
    void displayHappy();
    void displayAngry();
    void displayStraight();
    void displayLeft();
    void displayRight();
    void changeSmiley(int nextSmiley);
    void lookAround();
    void waitingForLoopIteration();

    LCD_Smiley();
};


#endif //BARBOT_LCD_SMILEY_H
