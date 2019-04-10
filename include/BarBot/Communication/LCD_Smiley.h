#ifndef BARBOT_LCD_SMILEY_H
#define BARBOT_LCD_SMILEY_H


/**
 * Library to easily show smileyfaces on an I2C LCD :)
 */
class LCD_Smiley {
private:
    int leftLooking;
    int waitingForLoop;
public:
    int nextSmiley;
    bool lookingAround;

    void init();
    void displayHappy();
    void displayAngry();
    void displayStraight();
    void isplayLeft();
    void displayRight();
    void changeSmiley(nextSmiley);
    void lookAround();
    void waitingForLoopIteration();
};


#endif //BARBOT_LCD_SMILEY_H
