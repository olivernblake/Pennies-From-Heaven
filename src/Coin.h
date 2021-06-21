//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"

class Coin{

    public:
        Coin();
    
            // Functions
            void setup(glm::vec2 _position);
            void draw();
            void update();
            void edgeDetection();
            void applyForce(glm::vec2 _force);
            
            // Different Coin Types;
            void chooseCoinType();
            void draw2Pound();
            void draw1Pound();
            void draw50p();
            void draw20p();
            void draw10p();
            void draw5p();
            void draw2p();
            void draw1pence();
            
            // Drawing Stuff
            float radius;
            string coinType;
            float worth;
            float bounce;
            ofColor gold, silver, copper;
            ofColor shinyGold, shinySilver, shinyCopper;
            ofColor dullGold, dullSilver, dullCopper;
            ofColor black;
            float adjustedMass;
            int circleRes;
            float dullAmnt;
            float minDullAmnt, maxDullAmnt;
            int opac;
            int fade, fadeStart, fadeEnd;
            bool coinFaded;

            // Physics stuff
            int mass;
            glm::vec2 position;
            glm::vec2 velocity;
            glm::vec2 accel;
            glm::vec2 gravity;
            glm::vec2 friction;
    
            // SoundFX Stuff
            bool playFloorSound;
            float sfxVol;
};
