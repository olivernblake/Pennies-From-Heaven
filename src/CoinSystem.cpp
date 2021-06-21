//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "CoinSystem.h"

//-------------------------------------------------------
CoinSystem::CoinSystem(){
    
}
//--------------------------------------------------------
void CoinSystem::setup(float _countdownTimer){
    amountOfClouds = 3;
    countdownTimer = _countdownTimer;
    frameTimer = 0;
    elapsedTimeOffset = 0;
    
    // Game Sequence Vars;
    pregameLength = 3000;
    
    // Width and Height Vars;
    width = ofGetWidth();
    height = ofGetHeight();
    
    // Cloud Size Vars;
    maxCloudSize = width/5;
    cloudRandomOffset = ofRandom(-maxCloudSize, maxCloudSize);
    
    // Add Coin Variables;
    dropCoins = false;
    dropFrequency = 30;
    
    // Populate Clouds Deque;
    for (int i = 0; i < amountOfClouds; i++) {
        Cloud tempCloud;
        tempCloud.setup(ofRandom(width/4, width/4*3), maxCloudSize - (maxCloudSize/5 * i));
        clouds.push_front(tempCloud);
        startingFrame.push_back(0);
        frameDrop.push_back(10);
        nextCoinDrop.push_back(ofRandom(1, dropFrequency));
    }
    
    // Floor Sounds Deque;
    for (int i = 1; i < 5; i++) {
        ofSoundPlayer floorSoundi;
        floorSoundi.load("FloorSound" + ofToString(i) + ".mp3");
        floorSoundi.setMultiPlay(true);
        floorSounds.push_back(floorSoundi);
    }
    
    // Load Level Music;
    levelMusic.load("Pennies-8-Bit-2.mp3");
    levelMusic.setMultiPlay(false);
    levelMusic.setVolume(musicVolSlider);
    
    // Load Font info;
    pregameFontSize = 0;
    pregame.load("Lora-Bold.ttf", pregameFontSize);
}
//--------------------------------------------------------------
void CoinSystem::update(float _countdownTimer)  {
    // Update Sound Volumes;
    levelMusic.setVolume(musicVolSlider);
    
    // Update Countdown (from Scoring Detection);
    countdownTimer = _countdownTimer;

    // Reset Floor Sound Bool;
    triggerFloorSound = false;
    floorSoundVol = 0;
    
    // Update Coins;
    for (int i = 0; i < coins.size(); i++) {
        // Update Coin Positions;
        coins[i].update();
        
        // Check if Coin has faded. If so, remove from deque;
        if (coins[i].coinFaded) coins.erase(coins.begin() + i);
        
        // Check if any SoundFX;
        if (coins[i].playFloorSound) {
            // Set to true, and play after loop (to avoid multi-triggering)
            triggerFloorSound = true;
            // Play only the loudest floor hit;
            if (coins[i].sfxVol > floorSoundVol) {
                floorSoundVol = coins[i].sfxVol;
            }
        }
    }
    
    // If any coins hit floor, play floor sound;
    if (triggerFloorSound) {
        trigFloorSound();
    }
    
    // Update Cloud Position;
    for (int i = 0; i < clouds.size(); i++) {
        clouds[i].update();
    }
    
    // Update Frame Timer for Coin Dropping;
    frameTimer++;
}
//--------------------------------------------------------------
void CoinSystem::trigFloorSound() {
    // Map which Pitch plays based on speed of coins;
    int num = ofMap(floorSoundVol, 0.01, 0.1, 0, 3, true);
    // Set Volume based on speed (and multiply by SFX Slider);
    floorSounds[num].setVolume(floorSoundVol * sfxVolSlider);
    // Play SFX;
    floorSounds[num].play();
}
//--------------------------------------------------------------
void CoinSystem::draw() {
    // Transition Vars;
    if (triggerGameSequence) {
        initGameSequence();
    }
    
    // Draw Coins;
    for (int i = 0; i < coins.size(); i++) {
        coins[i].draw();
    }
    
    // Clouds;
    for (int i = 0; i < clouds.size(); i++) {
        // If game active, drop Coins;
        if (dropCoins) addCoins(i);
        // Draw Clouds;
        clouds[i].draw();
    }
}
//--------------------------------------------------------------
void CoinSystem::addCoins(int i)    {
    // Add New Coin objects to coins array;
    int coinSpread = 15;
    if (countdownTimer > 0) {
        if (frameTimer == startingFrame[i] + frameDrop[i]) {
            Coin tempCoin;
            glm::vec2 dropZone(clouds[i].cloudMid + ofRandom(-coinSpread, coinSpread), clouds[i].cloudLoc.y);
            tempCoin.setup(dropZone);
            coins.push_back(tempCoin);
            
            nextCoinDrop[i] = ofRandom(1, dropFrequency);
            frameDrop[i] += nextCoinDrop[i];
        }
    }
}
//--------------------------------------------------------------
void CoinSystem::gameStarts() {
    // Start Coins Dropping;
    dropCoins = true;
    
    // Adjust Timer Start Time;
    elapsedTimeOffset = ofGetElapsedTimeMillis();
    
    // Adjust FrameTimer and start time;
    frameTimer = 0;
    for (int i = 0; i < clouds.size(); i++) {
        frameDrop[i] = ofRandom(1, dropFrequency);
    }
}
//--------------------------------------------------------------
void CoinSystem::initGameSequence() {
    // Check Countdown Status;
    if (pregameCountInt == 0) {
        // If finished, trigger game to start;
        gameStarts();
        // Then turn off Game Sequence;
        triggerGameSequence = false;
    }
    
    if (pregameCountInt == 4) {
        // Start Music!;
        levelMusic.setPosition(0);
        levelMusic.play();
    }
    
    // Map 3 seconds;
    pregameCountFloat = ofMap(ofGetElapsedTimeMillis(), pregameOffset, pregameOffset + pregameLength, 4, 0, true);
    // Convert To Integer;
    pregameCountInt = pregameCountFloat;
    // Find Remainder;
    remainder = pregameCountFloat - pregameCountInt;
    pregameFontSize = ofMap(remainder, 1, 0, 96, 72, true);
    pregameStringOpac = ofMap(remainder, 1, 0, 255, 0, true);
    
    // Draw the Countdown;
    if (pregameCountInt > 0) {
        ofPushStyle();
        pregame.load("Lora-Bold.ttf", pregameFontSize);
        ofSetColor(255, pregameStringOpac);
        string pregameCountString = ofToString(pregameCountInt);
        pregame.drawString(pregameCountString, ofGetWidth()/2 - pregame.stringWidth(pregameCountString), ofGetHeight()/2 + pregame.stringHeight(pregameCountString));
        ofPopStyle();
    }
    
}
//--------------------------------------------------------------
