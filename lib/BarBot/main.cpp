


#include <BarBot/BarBot.h>
#include <BarBot/Communication/LCD_Smiley.h>
#include <BarBot/Util/Logger.h>
#include <csignal>
#include <sys/time.h>


BarBot bot;

void exit_handler(int signo) {
    if (signo == SIGINT) {
        bot.movement->steer(true, 0);
        bot.brickPi3->reset_all();
        bot.drinkService->close();
        bot.appControlService->close_connection();
        bot.motor->setSpeed(0);
        exit(-2);
    }
};

long get_millis() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

int main()
{
//    LCD_Smiley smile;
//
//    smile.init();
//
//    long ms = get_millis();
//    while(true) {
//        smile.updateFace();
//        if (get_millis() > ms + 2000) {
//            ms = get_millis() + 1000000;
//            std::cout << "YOLOO" << std::endl;
//            smile.sad(500);
//        }
//        usleep(10000);
//    }


    Logger::setLogShow({
        SpeechRecognition::TAG,
        SpeechRecognition::TAG_PYTHON,
        SpeechInterpretation::TAG,
        Movement::TAG
    });

    bot.setCupDetectionDistance(10);
    bot.setDrinkServer("83.87.164.152", 8444);
    bot.setLineDetectionTarget(1900);
    bot.setLineDetectionMargin(1);
    bot.setMovementKickStartPower(200);
    bot.setPathingColorOrder({
        INPUT_BLUECOLOR,
        INPUT_GREENCOLOR,
        INPUT_YELLOWCOLOR
    });
    bot.setNoReadings(false);
    bot.setLogSensorData(false);

    bot.init();

    signal(SIGINT, exit_handler);

    Logger::log("Main", "Bot Initialized");
    Logger::log("main", "Initializing Smiley");

//    bot.movement->speed(50, false);
    bot.lineFollow->pause();
while(bot.running) {
        bot.step();
        usleep(10000);
    }
}