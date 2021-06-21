//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "PointerUmb.h"

//-------------------------------------------------------
PointerUmb::PointerUmb()
{
    
}

//--------------------------------------------------------
void PointerUmb::setup(string _hand)  {
    width = ofGetWidth();
    height = ofGetHeight();
    hand = _hand;
    umbrellaSize = width/12;
    umbrellaHeight = umbrellaSize/2.5;
    poleCol = ofColor(180);
    umbrellaPos = glm::vec2(0, 0);
    
    // Transition Vars;
    opac = 255;
    
    if (hand == "left") {
        leftSeg = ofColor(199, 0, 57);
        midSeg = ofColor(255, 87, 51);
        rightSeg = ofColor(255, 195, 0);
    }
    
    if (hand == "right") {
        leftSeg = ofColor(7, 82, 140);
        midSeg = ofColor(26, 142, 186);
        rightSeg = ofColor(77, 191, 218);
    }
    
    // Draw Umbrella Variables;
    oneSixth = umbrellaSize/6;
    handleThickness = umbrellaSize/15;
    poleHeight = umbrellaHeight * 1.25;

    sensorSize = umbrellaSize/2;
    sensorHeight = 15;
    updatePos();
    
    setUmbrellaDrawInfo();
}
//--------------------------------------------------------------
void PointerUmb::update() {
    updatePos();
}
//--------------------------------------------------------------
void PointerUmb::draw(){
    ofPushMatrix();
    
    // Translate to Umbrella Position;
    ofTranslate(umbrellaPos);
    
    // Draw Umbrella;
    drawUmbrella();
    
    ofPopMatrix();
}
//--------------------------------------------------------------
void PointerUmb::updatePos() {
    umbLeft = umbrellaPos.x - sensorSize;
    umbRight = umbrellaPos.x + sensorSize;
    sensorTop = umbrellaPos.y - sensorHeight;
    sensorBottom = umbrellaPos.y + sensorHeight;
}
//--------------------------------------------------------------
void PointerUmb::drawUmbrella() {
    // Pole;
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(poleCol, opac);
    ofDrawRectangle(0, 0, handleThickness, poleHeight * 2);
    ofPopStyle();
    
    // Hook;
    hook.setColor(ofColor(poleCol, opac));
    hook.draw();
    
    // Left shape;
    left.setColor(ofColor(leftSeg, opac));
    left.draw();
    
    // Middle shape;
    middle.setColor(ofColor(midSeg, opac));
    middle.draw();
    
    // Right shape;
    right.setColor(ofColor(rightSeg, opac));
    right.draw();
}
//--------------------------------------------------------------
void PointerUmb::setUmbrellaDrawInfo() {
    // Only need to do this once!;
    // CANOPY POINTS;
        glm::vec2 tip1(-sensorSize, -sensorHeight);
        glm::vec2 dip1(-sensorSize + oneSixth, sensorHeight);
        glm::vec2 tip2(-oneSixth, -sensorHeight);
        glm::vec2 dip2(0, sensorHeight);
        glm::vec2 tip3(oneSixth, -sensorHeight);
        glm::vec2 dip3(sensorSize - oneSixth, sensorHeight);
        glm::vec2 tip4(sensorSize, -sensorHeight);
        glm::vec2 bottomJoin(0, umbrellaHeight);
    
    
    // HANDLE POINTS;
        float halfHandle = handleThickness/2;
        
        glm::vec2 hookStart(0, -poleHeight);
        glm::vec2 hookTop(-oneSixth/2, -poleHeight - oneSixth);
        glm::vec2 hookEnd(tip2.x, -poleHeight);

        glm::vec2 hookStartOuter(hookStart.x + halfHandle, hookStart.y);
        glm::vec2 hookTopOuter(hookTop.x, hookTop.y - halfHandle);
        glm::vec2 hookEndOuter(hookEnd.x - halfHandle, hookEnd.y);
        glm::vec2 hookEndInner(hookEnd.x + halfHandle, hookEnd.y);
        glm::vec2 hookTopInner(hookTop.x, hookTop.y + halfHandle);
        glm::vec2 hookStartInner(hookStart.x - halfHandle, hookStart.y);
        
        // Pole;
        // (all done in drawUmbrella();

        // Hook;
        hook.setColor(ofColor(poleCol, opac));
        hook.moveTo(hookStartOuter);
        hook.bezierTo(hookStartOuter, glm::vec2(hookStartOuter.x, hookTopOuter.y), hookTopOuter);
        hook.bezierTo(hookTopOuter, glm::vec2(hookEndOuter.x, hookTopOuter.y), hookEndOuter);
        hook.moveTo(hookEndInner);
        hook.bezierTo(hookEndInner, glm::vec2(hookEndInner.x, hookTopInner.y), hookTopInner);
        hook.bezierTo(hookTopInner, glm::vec2(hookStartInner.x, hookTopInner.y), hookStartInner);
        hook.close();

    
    // LEFT shape;
        left.setColor(ofColor(leftSeg, opac));
        left.moveTo(bottomJoin);
        left.bezierTo(bottomJoin, glm::vec2(tip1.x, bottomJoin.y), tip1);
        left.bezierTo(tip1, dip1, tip2);
        left.bezierTo(tip2, glm::vec2(tip2.x, bottomJoin.y), bottomJoin);
        left.close();
    
    // MIDDLE shape;
        middle.setColor(ofColor(midSeg, opac));
        middle.moveTo(bottomJoin);
        middle.bezierTo(bottomJoin, glm::vec2(tip2.x, bottomJoin.y), tip2);
        middle.bezierTo(tip2, dip2, tip3);
        middle.bezierTo(tip3, glm::vec2(tip3.x, bottomJoin.y), bottomJoin);
        middle.close();
    
    // RIGHT shape;
        right.setColor(ofColor(rightSeg, opac));
        right.moveTo(bottomJoin);
        right.bezierTo(bottomJoin, glm::vec2(tip3.x, bottomJoin.y), tip3);
        right.bezierTo(tip3, dip3, tip4);
        right.bezierTo(tip4, glm::vec2(tip4.x, bottomJoin.y), bottomJoin);
        right.close();
}
//--------------------------------------------------------------
