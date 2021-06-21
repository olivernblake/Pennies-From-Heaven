//
//  Coin.h
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#pragma once
#include "ofMain.h"

class Umbrella{

    public:
    Umbrella();
    
            // Functions
            void setup(glm::vec2 _position, string _hand);
            void update(glm::vec2 _position);
            void draw();
            void updatePos();
            void drawUmbrella();
            void setUmbrellaDrawInfo();
    
            // Umbrella Draw Variables;
            int umbrellaSize;
            string hand;
            float holdPoles;
            float oneSixth;
            float handleThickness;
            float poleHeight;
            ofPath hook;
            ofPath left, middle, right;
            ofColor poleCol;
            ofColor leftSeg, midSeg, rightSeg;

            // Umbrella Position Variables;
            glm::vec2 umbrellaPos;
            float umbLeft;
            float umbRight;
            float umbrellaHeight;
            int handleLength;
            
            // Sensor Variables;
            int sensorHeight;
            int sensorSize;
            float sensorTop;
            float sensorBottom;
    
            // Width and Height Vars;
            int width, height;
    
            // Transition Vars;
            float opac;
};
