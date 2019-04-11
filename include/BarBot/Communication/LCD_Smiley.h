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
    void displayHappy();
    void displaySad();
    void displayStraight();
    void displayLeft();
    void displayRight();
    void show(const std::string & txt, uint8_t line);
public:
    void happy(int duration);
    void sad(int duration);
    void straight(int duration);
    void left(int duration);
    void right(int duration);

    int nextSmiley;
    int lookingAroundTimer, differentFaceTimer, currentFace;
    bool isDifferentFace;

    void init();

    void changeSmiley(int nextSmiley);
    void updateFace();
    void waitingForLoopIteration();

    LCD_Smiley();
};


#endif //BARBOT_LCD_SMILEY_H
