#ifndef BARBOT_PWM_H
#define BARBOT_PWM_H


#include <stdint-gcc.h>

/**
 * Code for Arduino
 * Class to drive a motor connected to an IBT_2 motor driver
 * This code assumes both enable pins are connected to a HIGH signal
 */
class PWMMotor {
private:
    uint8_t pinA;
    uint8_t pinB;
    uint8_t speed = 0;
    bool forwardRotation = true;
public:
    /**
     * Initialize PWMMotor class
     * @param pinA First PWM pim the driver is connected to
     * @param pinB Second PWM pim the driver is connected to
     */
    PWMMotor(uint8_t pinA, uint8_t pinB);

    /**
     * Changes the first pin the PWM driver is connected to
     * @param pinA Pin number
     */
    void setPinA(uint8_t pinA);

    /**
     * Changes the second pin the PWM driver is connected to
     * @param pinB Pin number
     */
    void setPinB(uint8_t pinB);

    /**
     * Changes the speed the motor is rotating at
     * @param speed The speed to set to (0-255)
     */
    void setSpeed(uint8_t speed);

    /**
     * Changes the rotation direction on the PWM driver.
     * @param forwardRotation True if the direction should be forward, false if it should be backwards
     */
    void setForwardRotation(bool forwardRotation);

    /**
     * Updates the pins with the currently set values
     */
    void update();



};


#endif //BARBOT_PWM_H
