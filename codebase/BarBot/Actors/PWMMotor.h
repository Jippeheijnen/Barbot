#ifndef BARBOT_PWM_H
#define BARBOT_PWM_H

#include <cstdint>

class PWMMotor {
private:
    uint8_t pwmspeed;
    int pinPWM = 16;
    int pinEnableCLK = 18;
    int pinEnableCCLK = 20;
    int pinEnabled;
    bool rotation;
public:

    //Constructor
    PWMMotor(int pinPWM, int pinEnableCLK, int pinEnableCCLK);

    /**
     * Sends PWM signal to motors.
     * @param pwmspeed Int between 0 and 255
     */
    void sendPWM(uint8_t pwmspeed);

    /**
     * Sets the GPIO Direction pin to HIGH.
     * @param rotation Boolean that defines the rotation. Clockwise (true) or Counter Clockwise (False).
     */
    void setRotation(bool rotation);

    /**
     * Sends PWM signal to motors for reduced speed.
     * @param pwmspeed Number between 0 and
     */
    void sendReducedPWM(uint8_t pwmspeed);

};


#endif //BARBOT_PWM_H
