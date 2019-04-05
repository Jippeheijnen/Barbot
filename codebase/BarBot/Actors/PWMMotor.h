#ifndef BARBOT_PWM_H
#define BARBOT_PWM_H


class PWMMotor {
private:
    uint8_t pwmspeed;
    int pinPWM = 16;
    int pinEnableCLK = 18;
    int pinEnableCCLK = 20;
    int pinEnabled;
    bool rotation;
public:


    PWMMotor(int pinPWM, int pinEnableCLK, int pinEnableCCLK);

/**
     * Gets signal and sends it over PWM to motors
     * @param pwmspeed Number between 0 and 255
     */
    void sendPWM(uint8_t pwmspeed);

    /**
     * Sets the GPIO pin to HIGH if motor driver direction Enable pin needs to be on
     * @param rotation Boolean that defines the rotation. Clockwise or Counter Clockwise
     */
    void setRotation(bool rotation);

    /**
     * Gets signal and sends it over PWM to motors for in the corners
     * @param pwmspeed Number between 0 and
     */
    void sendCornerPWM(uint8_t pwmspeed);

};


#endif //BARBOT_PWM_H
