


#include <BarBot/BarBot.h>
#include <BarBot/Communication/LCD_Smiley.h>
#include <BarBot/Util/Logger.h>
#include <csignal>


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

int main()
{


    Logger::setLogShow({
        SpeechRecognition::TAG,
        SpeechRecognition::TAG_PYTHON,
        SpeechInterpretation::TAG
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
    bot.setNoReadings(true);
    bot.setLogSensorData(true);

    bot.init();



    signal(SIGINT, exit_handler);

    Logger::log("Main", "Bot Initialized");
    Logger::log("main", "Initializing Smiley");

    bot.movement->speed(120, false);
    bot.lineFollow->pause();
while(bot.running) {
        bot.step();
        usleep(10000);
    }
}