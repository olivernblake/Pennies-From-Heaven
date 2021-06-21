//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "ScoringDetection.h"

//-------------------------------------------------------
ScoringDetection::ScoringDetection()
{
    
}

//--------------------------------------------------------
void ScoringDetection::setup(glm::vec2 umbPosL, glm::vec2 umbPosR)  {
    timerLength = 20;
    timerLengthMillis = timerLength * 1000;
    countdownTimer = 0;
    score = 0;
    highScore = 0;
    elapsedTimeOffset = 0;
    origin = glm::vec2(0, 0);
    
    // Setup Coin System;
    coinSystem.setup(countdownTimer);
    
    // Setup Umbrellas;
    localUmbPosL = umbPosL;
    localUmbPosR = umbPosR;
    umbL.setup(localUmbPosL, "left");
    umbR.setup(localUmbPosR, "right");
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    // SoundFX Vars;
    triggerCatchCoin = false;
    catchCoin.load("Coin In Umb.mp3");
    catchCoin.setMultiPlay(true);
    catchCoin.setVolume(sfxVolSlider);

}
//--------------------------------------------------------------
void ScoringDetection::update(glm::vec2 umbPosL, glm::vec2 umbPosR) {
    // Adjust High Score if necessary;
    if (score >= highScore) highScore = score;
    
    // Adjust Start Time of Timer;
    elapsedTimeOffset = coinSystem.elapsedTimeOffset;
    adjElapsedTime = ofGetElapsedTimeMillis() - elapsedTimeOffset;
    countdownTimer = ofMap(adjElapsedTime, 0, timerLengthMillis, timerLength, 0, true);
    if (countdownTimer == 0) coinSystem.dropCoins = false;
    
    // Update Coin System and Umbrella;
    coinSystem.update(countdownTimer);
    localUmbPosL = umbPosL;
    localUmbPosR = umbPosR;
    umbL.update(localUmbPosL);
    umbR.update(localUmbPosR);
    
    // Run Score Detection;
    checkIfScored();
    
    // Update Score Strings;
    updateStrings();
}
//--------------------------------------------------------------
void ScoringDetection::updateStrings() {
    highScoreString = ("High Score: " + ofToString(highScore) + " Pounds");
    lastScoreString = ("Last Score: " + ofToString(score) + " Pounds");
    scoreString = ("Score: " + ofToString(score) + " Pounds");
    timeRemString = ("Time Remaining: " + ofToString(countdownTimer, 2) + " seconds");
}
//--------------------------------------------------------------
void ScoringDetection::draw(){
    // Draw Coin System;
    coinSystem.draw();
    
    // Draw Umbrellas;
    umbL.draw();
    umbR.draw();
}
//--------------------------------------------------------------
void ScoringDetection::checkIfScored(){
    // Reset SoundFX vars;
    triggerCatchCoin = false;
    
    // Loop over coins deque (in CoinSystem);
    for (int i = 0; i < coinSystem.coins.size(); i++) {
        glm::vec2 coinPos = coinSystem.coins[i].position;
        
        // Check it's not on the floor!! No cheating in THIS game!;
        if (coinPos.y < height - coinSystem.coins[i].radius) {
            
            // Check if passes LEFT sensor;
            if (coinPos.y > umbL.sensorTop && coinPos.y <  umbL.sensorBottom) {
                if (coinPos.x > umbL.umbLeft && coinPos.x < umbL.umbRight) {
                    score += coinSystem.coins[i].worth;
                    coinSystem.coins.erase(coinSystem.coins.begin() + i);
                    triggerCatchCoin = true;
                }
            }
            
            // Check if passes RIGHT sensor;
            if (coinPos.y > umbR.sensorTop && coinPos.y <  umbR.sensorBottom) {
                if (coinPos.x > umbR.umbLeft && coinPos.x < umbR.umbRight) {
                    score += coinSystem.coins[i].worth;
                    coinSystem.coins.erase(coinSystem.coins.begin() + i);
                    triggerCatchCoin = true;
                }
            }
        }
    }
    
    // If a Coin has passed the sensor, play CatchCoin soundFX
    if (triggerCatchCoin) {
        trigCatchCoin();
    }
}
//--------------------------------------------------------------
void ScoringDetection::trigCatchCoin() {
    catchCoin.setVolume(sfxVolSlider);
    catchCoin.play();
}
//--------------------------------------------------------------
void ScoringDetection::trigPregameCountdown() {
    score = 0;
    coinSystem.pregameCountInt = 4;
    coinSystem.triggerGameSequence = true;
    coinSystem.pregameOffset = ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
