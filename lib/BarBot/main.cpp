


#include <BarBot/BarBot.h>
#include <BarBot/Communication/LCD_Smiley.h>
#include <BarBot/Util/Logger.h>
#include <csignal>

const int16_t LINEDETECTION_THRESHOLD = 1720;
const int16_t LINEDETECTION_MARGIN = 10;

const int16_t CUPDETECTION_DISTANCE = 10;


//BrickPi3 *brickPi3 = new BrickPi3();
//ArduinoMotor *motor = new ArduinoMotor();
//Movement *movement = new Movement(brickPi3);
//LineDetection *lineDetection = new LineDetection(brickPi3, movement);
//LineFollow *lineFollow = new LineFollow(movement, lineDetection);
//CupDetection *cupDetection = new CupDetection(brickPi3);
//DrinkService *drinkService = new DrinkService();
//AppControlService *appControlService = new AppControlService(lineFollow);
//SpeechRecognition *speechRecognition = new SpeechRecognition(lineFollow, drinkService, cupDetection);


//
//void mainInit() {
//    Logger::setLogShow({
////                               BluetoothConnection::TAG,
//                               Movement::TAG,
//                               LineDetection::TAG
////                               ArduinoMotor::TAG
//                       });
//
//    motor->init();
//
//    brickPi3->detect();
//
//    lineDetection->init(LINEDETECTION_THRESHOLD, nullptr, LINEDETECTION_MARGIN, 0);
//
//    cupDetection->init(CUPDETECTION_DISTANCE);
//
//    movement->init(motor, BrickPi3());
//
////    std::cout << "Initializing Pump Service" << std::endl;
////    pumpService->init();
//
//    appControlService->init(nullptr);
//
//    Logger::log("Main", "Setting SIG Exit");
//    signal(SIGINT, exit_handler);
//
//}

//long get_millis() {
//    struct timeval tp;
//    gettimeofday(&tp, NULL);
//    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
//}

BarBot bot;

void exit_handler(int signo) {
    if (signo == SIGINT) {
        bot.movement->steer(true, 0);
        bot.brickPi3->reset_all();
//        pumpService->close();
        bot.motor->setSpeed(0);
        exit(-2);
    }
};

int main()
{
        Logger::setLogShow({
//            AppControlService::TAG,
            Movement::TAG
        });

    bot.setCupDetectionDistance(10);
    bot.setDrinkServer("83.87.164.152", 8444);
    bot.setLineDetectionTarget(1700);
    bot.setLineDetectionMargin(10);
    bot.setPathingColorOrder({
        INPUT_BLUECOLOR,
        INPUT_GREENCOLOR,
        INPUT_YELLOWCOLOR
    });
    bot.setLogSensorData(false);

    bot.init();



    signal(SIGINT, exit_handler);

    Logger::log("Main", "Bot Initialized");
    Logger::log("main", "Initializing Smiley");

    while(bot.running) {
//        bot.step();

        usleep(10000);
    }
}