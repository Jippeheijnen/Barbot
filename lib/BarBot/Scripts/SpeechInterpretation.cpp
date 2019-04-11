//
// Created by Niels on 4/8/2019.
//

#include "BarBot/Scripts/SpeechInterpretation.h"
#include <vector>
#include <BarBot/Communication/SpeechRecognition.h>
#include <BarBot/Communication/SpeechSynthesis.h>
#include <bits/stdc++.h>
#include <zconf.h>
#include <BarBot/Util/Logger.h>

const std::string SpeechInterpretation::TAG = "SpeechInterpretation";

void SpeechInterpretation::init(LineFollow *lF, CupDetection *cD, DrinkService *pS, SpeechRecognition * sR, LCD_Smiley *lS) {
    speechRecognition = sR;
    lineFollow = lF;
    cupDetection = cD;
    pumpService = pS;
    lcdSmiley = lS;
}

void SpeechInterpretation::listen(){
    std::vector<std::string> heard = speechRecognition->poll();
    if((std::find(heard.begin(), heard.end(), "barbot") != heard.end()) && (std::find(heard.begin(), heard.end(), "stop") != heard.end())){
        Logger::log(TAG, "We Moeten stoppen");

        std::vector<drink> drinks = pumpService->get_drinks();
        lineFollow->pause();
        lcdSmiley->happy(500);
        SpeechSynthesis::speak("Wat wilt u drinken?");
        bool drankjeGevonden =false;
        while(!drankjeGevonden) {
            heard = speechRecognition->poll();
            for (size_t i = 0; i < drinks.size(); i++) {
                if ((std::find(heard.begin(), heard.end(), drinks[i].name) != heard.end())) {
                    SpeechSynthesis::speak("Komt eraan");
                    Logger::log(TAG, "User asked for " + drinks[i].name);
                    drankjeGevonden = true;
                    int count = 0;
                    while (true) {
                        if (cupDetection->isCupPlaced()) {
                            Logger::log(TAG, "Cup Detected");
                            Logger::log(TAG, "Dispensing " + drinks[i].name);

                            lcdSmiley->happy(7000);
                            usleep(2000000);
                            pumpService->pour(drinks[i].id);
                            while(cupDetection->isCupPlaced() != 1){
                                usleep(1000);
                            }
                            SpeechSynthesis::speak("Tot de volgende keer!");
                            lineFollow->resume();
                            break;
                        } else if (count == 7000) {
                            count = 0;
                            lcdSmiley->sad(700);
                            Logger::log(TAG, "Asking to place a cup ");
                            SpeechSynthesis::speak("Plaats alstublieft een beker");
                        } else {
                            count++;
                            usleep(1);
                        }
                    }
                    lcdSmiley->isDifferentFace = 1;
                    break;
                }
            }
            usleep(1000);
        }
    }
}