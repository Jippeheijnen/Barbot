
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

/**
 * Struct for colorreading, holds a color, and an indication if the color changed since last reading
 */
struct ColorReading {
    bool hasChanged = true;
    int8_t color = -1;
};

/**
 * Uses a Lego Light Sensor and a Color Sensor to follow a Line on the Ground
 * Finds color markings along the line
 */
class LineDetection {
private:
    bool logSensorData, noReadings;
    double LIGHT_SENSOR_FACTOR = 0.2;
    sensor_light_t LIGHT_SENSOR_DATA;

    uint8_t LIGHT_SENSOR_PORT = PORT_1;


    ColorReading lastColorReading = {};
    sensor_color_t COLOR_SENSOR_DATA;
    uint8_t COLOR_SENSOR_PORT = PORT_2;
    BrickPi3* brickPi3;
    Movement* movement;

public:
    static const std::string TAG;
    int16_t target, margin;

     /**
      * Initializes LineDetection with a line threshold.
      * Readings will be centered around this threshold
      * @param bp3 Reference to the bot's brickpi3 instance
      * @param mov  Reference to the bot's movement instance
      * @param tar Target light reflection value of the border between the line and the ground
      * @param mar Minimum distance needed for detection
      * @param lSD Additional logging: If true, all sensor readings will be logged
      */
    void init(BrickPi3 *bp3, Movement *mov, int16_t tar, int16_t mar, bool lSD = false, bool nR = false);


    /**
     * Reads a color from the color sensor. Will return a ColorReading, which also indicates if the color has changed since the last reading.
     * @return A ColorReading containing the measured color, and if it has changed
     */
    ColorReading readColor();


    /**
     * Uses the light sensor to calculate an arbitrary value indicating on which side the line is
     *
     * @return Value that indicates distance to the line. Positive values indicate the bot is closer to the center of the line
     * whereas negative values indicate the bot is further away
     */
    double getLineDirection();


};


#endif //BARBOT_LINEDETECTION_H
