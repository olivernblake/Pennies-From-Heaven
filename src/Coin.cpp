//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "Coin.h"

//-------------------------------------------------------
Coin::Coin()
{
    
}

//--------------------------------------------------------
void Coin::setup(glm::vec2 _position)  {
    // What kind of coin is created?
    chooseCoinType();
    
    // Pass position from Clouds (CoinSystem);
    position = _position;
    
    // Setup Physics;
    velocity = glm::vec2(0, 1);
    accel = glm::vec2(0, 0);
    gravity = glm::vec2(0, 0.3);
    adjustedMass = ofMap(mass, 3.25, 12, 12, 3.25, true);
    bounce = 0.3;
    
    // Scale radius
    radius *= 1.2;
    
    // How shiny?
    dullAmnt = ofRandom(minDullAmnt, maxDullAmnt);
    
    // Fadeout variables;
    fade = 0;
    fadeStart = 100;
    fadeEnd = 300;
    opac = 255;
    coinFaded = false;
    
    // Setup Colours;
    shinyGold = ofColor(255, 215, 0);
    dullGold = ofColor(187, 161, 79);
    shinySilver = ofColor(192);
    dullSilver = ofColor(161);
    shinyCopper = ofColor(183, 115, 51);
    dullCopper = ofColor(121, 85, 61);
    black = ofColor(0);
    
    // Adjust Colours (except black) as per Dull Amount;
    gold = shinyGold.getLerped(dullGold, dullAmnt);
    silver = shinySilver.getLerped(dullSilver, dullAmnt);
    copper = shinyCopper.getLerped(dullCopper, dullAmnt);
    
    // SoundFX
    playFloorSound = false;
}

//--------------------------------------------------------------
void Coin::draw(){
    if (coinType == "£2") draw2Pound();
    if (coinType == "£1") draw1Pound();
    if (coinType == "50p") draw50p();
    if (coinType == "20p") draw20p();
    if (coinType == "10p") draw10p();
    if (coinType == "5p") draw5p();
    if (coinType == "2p") draw2p();
    if (coinType == "1p") draw1pence();
}

//--------------------------------------------------------------
void Coin::update(){
    // Apply Forces;
    applyForce(gravity);
    
    // Physics Engine;
    velocity += accel;
    position += velocity;
    
    // Apply Edge Detection;
    edgeDetection();
    
    // Reset Acceleration;
    accel = glm::vec2(0, 0);
    
    // Adjust fade variable and apply to opacity;
    opac = ofMap(fade, fadeStart, fadeEnd, 255, 0, true);
    black = ofColor(0, opac);
    gold = ofColor(gold, opac);
    silver = ofColor(silver, opac);
    copper = ofColor(copper, opac);
    
    // Remove faded coins from deque (in CoinSystem);
    if (opac == 0) coinFaded = true;
}
//--------------------------------------------------------------
void Coin::edgeDetection() {
    playFloorSound = false;
    
    // Bounce back off walls & floor;
    if (position.y > ofGetHeight() - radius) {
        sfxVol = ofMap(velocity.y, 0, 12, 0, 0.1);
        if (sfxVol > 0.01) playFloorSound = true;
        // Bounce Coin;
        velocity.y *= -bounce;
    }
    
    if (position.x > ofGetWidth() - radius) {
        velocity.x *= -bounce;
    }
    
    // Stop from sinking off screen, and fade;
    if (position.y > ofGetHeight() - radius) {
        // Hold at bottom of screen;
        position.y = ofGetHeight() - radius;
        // Start fading out;
        fade++;
    }
}
//--------------------------------------------------------------
void Coin::applyForce(glm::vec2 _force)   {
    glm::vec2 force = _force / adjustedMass;
    accel += force;
}
//--------------------------------------------------------------
void Coin::chooseCoinType() {
    // Roll the dice!;
    int roll = ofRandom(8);

    // 1 PENCE;
    if (roll == 0) {
        coinType = "1p";
        worth = 0.01;
        mass = 3.564;
        radius = 20.3;
        minDullAmnt = 0.3;
        maxDullAmnt = 1;
    }
    
    // 2 PENCE;
    if (roll == 1) {
        coinType = "2p";
        worth = 0.02;
        mass = 7.12;
        radius = 25.9;
        minDullAmnt = 0.2;
        maxDullAmnt = 1;
    }
    
    // 5 PENCE;
    if (roll == 2) {
        coinType = "5p";
        worth = 0.05;
        mass = 3.25;
        radius = 18;
        minDullAmnt = 0;
        maxDullAmnt = 1;
    }
    
    // 10 PENCE;
    if (roll == 3) {
        coinType = "10p";
        worth = 0.10;
        mass = 6.5;
        radius = 24.5;
        minDullAmnt = 0;
        maxDullAmnt = 1;
    }
    
    // 20 PENCE;
    if (roll == 4) {
        coinType = "20p";
        worth = 0.20;
        mass = 5;
        radius = 21.4;
        circleRes = 7;
        minDullAmnt = 0.1;
        maxDullAmnt = 1;
    }
    
    // 50 PENCE;
    if (roll == 5) {
        coinType = "50p";
        worth = 0.50;
        mass = 8;
        radius = 27.3;
        circleRes = 7;
        minDullAmnt = 0;
        maxDullAmnt = 0.7;
    }
    
    // ONE POUND;
    if (roll == 6) {
        coinType = "£1";
        worth = 1.00;
        mass = 8.75;
        radius = 23.43;
        circleRes = 12;
        minDullAmnt = 0;
        maxDullAmnt = 0.4;
    }
    
    // TWO POUNDS;
    if (roll == 7) {
        coinType = "£2";
        worth = 2.00;
        mass = 12;
        radius = 28.4;
        minDullAmnt = 0.4;
        maxDullAmnt = 1;
    }
}
//--------------------------------------------------------------
void Coin::draw2Pound(){
    ofPushStyle();
    
    // Black outline;
    ofSetColor(black);
    ofDrawCircle(position, radius);
    
    // Gold outer cirlce;
    ofSetColor(gold);
    ofDrawCircle(position, radius-1);
    
    // Silver inner cirlce;
    ofSetColor(silver);
    ofDrawCircle(position, (radius-1) * 0.75);
    
    ofPopStyle();
}
//--------------------------------------------------------
void Coin::draw1Pound(){
    ofPushStyle();
    // Make 12 sided;
    ofSetCircleResolution(circleRes);
    
    // Black outline;
    ofSetColor(black);
    ofDrawCircle(position, radius);
    
    // Gold outer cirlce;
    ofSetColor(gold);
    ofDrawCircle(position, radius-1);
    
    // Silver inner cirlce;
    ofSetColor(silver);
    ofDrawCircle(position, (radius-1) * 0.6);
    
    ofPopStyle();
}
//--------------------------------------------------------
void Coin::draw50p(){
    ofPushStyle();
    // Make 7 sided;
    ofSetCircleResolution(circleRes);
    
    // Black outline;
    ofSetColor(black);
    ofDrawCircle(position, radius);
    
    // All silver;
    ofSetColor(silver);
    ofDrawCircle(position, radius-1);
    
    ofPopStyle();
}
//--------------------------------------------------------
void Coin::draw20p(){
    ofPushStyle();
    // Make 7 sided;
    ofSetCircleResolution(circleRes);
    
    // Black outline;
    ofSetColor(black);
    ofDrawCircle(position, radius);
    
    // All silver;
    ofSetColor(silver);
    ofDrawCircle(position, radius-1);
    
    ofPopStyle();
}
//--------------------------------------------------------
void Coin::draw10p(){
    ofPushStyle();
    
    // Black outline;
    ofSetColor(black);
    ofDrawCircle(position, radius);
    
    // All silver;
    ofSetColor(silver);
    ofDrawCircle(position, radius-1);
    
    ofPopStyle();
}
//--------------------------------------------------------
void Coin::draw5p(){
    ofPushStyle();
    
    // Black outline;
    ofSetColor(black);
    ofDrawCircle(position, radius);
    
    // All silver;
    ofSetColor(silver);
    ofDrawCircle(position, radius-1);
    
    ofPopStyle();
}
//--------------------------------------------------------
void Coin::draw2p(){
    ofPushStyle();
    
    // Black outline;
    ofSetColor(black);
    ofDrawCircle(position, radius);
    
    // All silver;
    ofSetColor(copper);
    ofDrawCircle(position, radius-1);
    
    ofPopStyle();
}
//--------------------------------------------------------
void Coin::draw1pence(){
    ofPushStyle();
    
    // Black outline;
    ofSetColor(black);
    ofDrawCircle(position, radius);
    
    // All silver;
    ofSetColor(copper);
    ofDrawCircle(position, radius-1);
    
    ofPopStyle();
}
//--------------------------------------------------------

