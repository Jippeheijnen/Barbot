
#ifndef BARBOT_LINEDETECTION_H
#define BARBOT_LINEDETECTION_H

#include <BarBot/Movement/Movement.h>
#include "BrickPI3/BrickPi3.h"

#define INPUT_BLACKCOLOR    1
#define INPUT_BLUECOLOR     2
#define INPUT_GREENCOLOR    3
#define INPUT_YELLOWCOLOR   4
#define INPUT_REDCOLOR      5
#define INPUT_WHITECOLOR    6

struct ColorReading {
    bool hasChanged = true;
    int8_t color;
};

class LineDetection {
private:
    double LIGHT_SENSOR_FACTOR = 0.2;
    sensor_light_t LIGHT_SENSOR_DATA;

    uint8_t LIGHT_SENSOR_PORT = PORT_4;


    ColorReading lastColorReading = {};
    sensor_color_t COLOR_SENSOR_DATA;
    uint8_t COLOR_SENSOR_PORT = PORT_3;
    BrickPi3* brickPi3;
    Movement* movement;

public:
    static const std::string TAG;
    int16_t target, margin;



/**
     * Initializes LineDetection with a line threshold
     * @param target The target value
     * @param margin Error margin for detection
     */
    void init(BrickPi3 *bp3, Movement *mov, int16_t tar, int16_t mar);


    /**
     * Checks if a given color matches the currently scanned color within a threshold
     * @param c
     * @return
     */
    ColorReading readColor();


    /**
     * @return (arbitrary) value that indicates distance to the line. Positive values indicate the line is on the right
     * whereas negative values indicate the line is on the left
     */
    double getLineDirection();


};


#endif //BARBOT_LINEDETECTION_H
