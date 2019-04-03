#ifndef BARBOT_PWM_H
#define BARBOT_PWM_H


class PWM {
private:
    uint8_t pwmspeed;
public:
    /**
     * Initiates the PPWM settings
     */
    void init();

    /**
     * Gets signal and sends it over PWM to motors
     * @param pwmspeed Number between 0 and 255
     */
    void sendPWM(uint8_t pwmspeed);

};


#endif //BARBOT_PWM_H
