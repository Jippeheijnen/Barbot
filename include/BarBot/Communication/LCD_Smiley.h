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
    /**
     * Displays the happy smiley
     */
    void displayHappy();
    /**
     * Displays the sad smiley
     */
    void displaySad();
    /**
     * Displays the straight smilet
     */
    void displayStraight();
    /**
     * Displays the looking to the left smiley
     */
    void displayLeft();
    /**
     * Displays the looking to the right smiley
     */
    void displayRight();
    /**
     * Shorthand to write lines to LCD
     * @param txt Text you want to display
     * @param line The line you want to display
     */
    void show(const std::string & txt, uint8_t line);
public:
    /**
     * Display the happy smiley for a duration. This needs the eventloop
     * @param duration Duration for display
     */
    void happy(int duration);
    /**
    * Display the sad smiley for a duration. This needs the eventloop
    * @param duration Duration for display
    */
    void sad(int duration);
    /**
    * Display the straight smiley for a duration. This needs the eventloop
    * @param duration Duration for display
    */
    void straight(int duration);
    /**
    * Display the left smiley for a duration. This needs the eventloop
    * @param duration Duration for display
    */
    void left(int duration);
    /**
    * Display the right smiley for a duration. This needs the eventloop
    * @param duration Duration for display
    */
    void right(int duration);

    int nextSmiley;
    int lookingAroundTimer, differentFaceTimer, currentFace;
    bool isDifferentFace;
    /**
     * Initiates the smiley functions
     */
    void init();


    /**
     * Changes the smiley and displays it at the same time
     * @param nextSmiley The smiley you want the smiley to change to
     */
    void changeSmiley(int nextSmiley);

    /**
     * The function to use with the eventloop
     */
    void updateFace();

    /**
     * Waits for the eventloop and updates the smiley accordingly to the last smiley
     */
    void waitingForLoopIteration();

    LCD_Smiley();
};


#endif //BARBOT_LCD_SMILEY_H
