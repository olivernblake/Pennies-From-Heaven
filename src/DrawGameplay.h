//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"
#include "ScoringDetection.h"
#include "Umbrella.h"
#include "Cloud.h"
#include "CoinSystem.h"
#include "Coin.h"
#include "ofxOsc.h"
#include "OSCReceiver.h"

class DrawGameplay{

    public:
    DrawGameplay();
    
        // Functions
        void setup();
        void update(float _umbOpac);
        void draw();
        
        // Scoring Detection Vars;
        ScoringDetection scoringDetection;
        glm::vec2 umbPosL, umbPosR;
        
        // OSC Vars;
        OSCReceiver oscReceiver;
        glm::vec2 leftWristPos, rightWristPos;
    
        // Transition Vars;
        float umbOpac;
        
};
