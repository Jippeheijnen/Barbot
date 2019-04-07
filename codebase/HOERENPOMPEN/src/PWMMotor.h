#ifndef BARBOT_PWM_H
#define BARBOT_PWM_H


#include <stdint-gcc.h>

class PWMMotor {
private:
    uint8_t pinA;
    uint8_t pinB;
    uint8_t speed = 0;
    bool forwardRotation = true;
public:
    PWMMotor(uint8_t pinA, uint8_t pinB);

    void setPinA(uint8_t pinA);

    void setPinB(uint8_t pinB);

    void setSpeed(uint8_t speed);

    void setForwardRotation(bool forwardRotation);

    void setRotation(bool r);

    void update();



};


#endif //BARBOT_PWM_H
