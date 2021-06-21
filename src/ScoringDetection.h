//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"
#include "CoinSystem.h"
#include "Umbrella.h"
#include "Cloud.h"

class ScoringDetection{

    public:
    ScoringDetection();
    
            // Functions
            void setup(glm::vec2 umbPosL, glm::vec2 umbPosR);
            void update(glm::vec2 umbPosL, glm::vec2 umbPosR);
            void draw();
            void checkIfScored();
            void trigCatchCoin();
            void trigPregameCountdown();
            void updateStrings();

            // Width and height vars;
            int height;
            int width;
            
            // Create objects;
            CoinSystem coinSystem;
            Umbrella umbL;
            Umbrella umbR;
    
            glm::vec2 localUmbPosL, localUmbPosR;
            glm::vec2 origin;
            
            // Score Variables;
            float highScore;
            float score;
            float countdownTimer;
            int timerLength;
            int timerLengthMillis;
            int elapsedTimeOffset;
            int adjElapsedTime;
    
            // SoundFX Vars;
            ofSoundPlayer catchCoin;
            bool triggerCatchCoin;
            float catchCoinVolume;
            float sfxVolSlider;
    
            // Strings Vars;
            string highScoreString, lastScoreString, timeRemString, scoreString;
};
