//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "DrawGameplay.h"

//-------------------------------------------------------
DrawGameplay::DrawGameplay()
{
    
}

//--------------------------------------------------------
void DrawGameplay::setup()   {
    // OSC Receiver setup;
    oscReceiver.setup();
    leftWristPos = glm::vec2(0, 0);
    rightWristPos = glm::vec2(0, 0);
    
    // Scoring Detection;
    umbPosL = leftWristPos;
    umbPosR = rightWristPos;
    scoringDetection.setup(umbPosL, umbPosR);
    
    // Transition Vars;
    umbOpac = 0;
}
//--------------------------------------------------------------
void DrawGameplay::update(float _umbOpac) {
    // Transition Vars - Update Opac;
    umbOpac = _umbOpac;
    scoringDetection.umbL.opac = umbOpac;
    scoringDetection.umbR.opac = umbOpac;
    
    // Update OSC Receiver;
    oscReceiver.update();
    leftWristPos = oscReceiver.leftWristPos;
    rightWristPos = oscReceiver.rightWristPos;
    
    // Update Scoring Detection;
    umbPosL = leftWristPos;
    umbPosR = rightWristPos;
    scoringDetection.update(umbPosL, umbPosR);
}
//--------------------------------------------------------------
void DrawGameplay::draw(){
    // Scoring Detection;
    scoringDetection.draw();
}
//--------------------------------------------------------------
