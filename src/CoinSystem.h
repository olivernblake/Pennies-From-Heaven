//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"
#include "Coin.h"
#include "Umbrella.h"
#include "Cloud.h"

class CoinSystem{

    public:
        CoinSystem();
    
            // Functions
            void setup(float _countdownTimer);
            void update(float _countdownTimer);
            void draw();
            void addCoins(int i);
            void trigFloorSound();
            void initGameSequence();
            void gameStarts();

            // Cloud Variables;
            deque<Cloud> clouds;
            int amountOfClouds;
            int maxCloudSize;
            int cloudRandomOffset;

            // Coin Variables
            deque<Coin> coins;
            
            // Dropping Variables;
            bool dropCoins;
            int dropFrequency;
            vector<int> startingFrame;
            vector<int> frameDrop;
            vector<int> nextCoinDrop;
            int frameOffsetNum;
            int frameTimer;
            float countdownTimer;
            int elapsedTimeOffset;
            float score;
    
            // Window Size Vars;
            float width, height;
    
            // Sound Vars;
            bool triggerFloorSound;
            float floorSoundVol;
            float sfxVolSlider;
            deque<ofSoundPlayer> floorSounds;
            ofSoundPlayer levelMusic;
            float levelMusicVol;
            float musicVolSlider;
    
            // Game Sequence Vars;
            bool triggerGameSequence;
            int pregameLength;
            int pregameOffset;
            int pregameCountInt;
            float pregameCountFloat;
            float remainder;
            float pregameFontSize;
            float pregameStringOpac;
            ofTrueTypeFont pregame;
};
