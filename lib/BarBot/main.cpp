


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
    Logger::setLogShow({
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
    bot.setLineFollowDisabled(true);
    bot.setLogSensorData(false);

    bot.init();

    signal(SIGINT, exit_handler);

    Logger::log("Main", "Bot Initialized");

//    bot.movement->speed(180, false);
    bot.lineFollow->pause();
    long ms = get_millis();
while(bot.running) {
//    if(ms > get_millis() + 5000)
//    {
//        bot.movement->speed(180, false);
//        ms = get_millis()+50000000;
//    }
        bot.step();
        usleep(10000);
    }
}