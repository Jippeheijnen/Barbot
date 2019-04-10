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


void SpeechInterpretation::init(LineFollow *lF, CupDetection *cD, DrinkService *pS, LCD_Smiley *lS) {
    lineFollow = lF;
    cupDetection = cD;
    pumpService = pS;
    speechRecognition = new SpeechRecognition();
    lcdSmiley = lS;
}

void SpeechInterpretation::listen(){
    std::vector<std::string> heard = speechRecognition->poll();
    std::vector<drink> drinks = pumpService->get_drinks();
    if((std::find(heard.begin(), heard.end(), "barbot") != heard.end()) && (std::find(heard.begin(), heard.end(), "stop") != heard.end())){
        lineFollow->pause();
        lcdSmiley->lookingAround = 0;
        lcdSmiley->changeSmiley(0);
        SpeechSynthesis::speak("Wat wilt u drinken?");
        heard = speechRecognition->poll();

        for(size_t i=0; i < drinks.size()-1; i++){
            if((std::find(heard.begin(), heard.end(), drinks[i].name) != heard.end())){
                SpeechSynthesis::speak("Komt eraan");

                int count = 0;
                while(true) {
                    if (cupDetection->isCupPlaced()) {
                        pumpService->pour(drinks[i].id);
                        lineFollow->resume();
                        break;
                    } else if (count == 7000) {
                        count = 0;
                        lcdSmiley->changeSmiley(1);
                        SpeechSynthesis::speak("Plaats alstublieft een beker");
                    }else{
                        count++;
                        usleep(1);
                    }
                }
                lcdSmiley->lookingAround = 1;
                break;
            }
        }
    }
}