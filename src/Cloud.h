//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"

class Cloud{

    public:
    Cloud();
    
            // Functions
            void setup(int cloudX, int cloudSize_);
            void update();
            void setupCloudSize();
            void draw();
            void drawCloud();

            // Variables
            ofColor white;
            glm::vec2 cloudLoc;
            int cloudSize;
            float cloudSpeed;
            float cloudMinSpeed;
            float cloudMaxSpeed;
            int cloudHeight;

            // Update Cloud Pos;
            float cloudLeftEdge;
            float cloudRightEdge;
            float cloudMid;

            // CLOUD CIRCLE SIZES
            float blcSize, rectHeight, brcSize, mainSize, rfcSize, lfbcSize, lfssSize;
    
            // Width and Height Variables;
            float width, height;
};
