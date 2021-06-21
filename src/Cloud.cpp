//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "Cloud.h"

//-------------------------------------------------------
Cloud::Cloud()
{
    
}

//--------------------------------------------------------
void Cloud::setup(int cloudX, int cloudSize_)   {
    width = ofGetWidth();
    height = ofGetHeight();
    
    cloudHeight = cloudSize_ * 0.4;
    cloudLoc = glm::vec2(cloudX, cloudHeight + height/15);
    white = ofColor::white;
    cloudSize = cloudSize_;
    cloudSpeed = ofMap(cloudSize, width/10, width/5, 2.5, 1, true);
    
    // Setup Cloud Cirlces Ratios;
    setupCloudSize();
}
//--------------------------------------------------------------
void Cloud::setupCloudSize() {
    // Setup Cloud Circles Ratios;
    blcSize = cloudSize * 0.1;
    rectHeight = blcSize * 2;
    brcSize = cloudSize * 0.15;
    mainSize = cloudSize * 0.27;
    rfcSize = cloudSize * 0.16;
    lfbcSize = cloudSize * 0.15;
    lfssSize = cloudSize * 0.11;
}
//--------------------------------------------------------------
void Cloud::update() {
    cloudLoc.x += cloudSpeed;
    cloudLeftEdge = cloudLoc.x - blcSize;
    cloudRightEdge = cloudLoc.x + cloudSize + brcSize;
    cloudMid = cloudLoc.x + cloudSize/2 + brcSize/2;
    
    if (cloudLeftEdge < 0 || cloudRightEdge > width) {
        cloudSpeed *= -1;
    }
}
//--------------------------------------------------------------
void Cloud::draw(){
    drawCloud();
}
//--------------------------------------------------------------
void Cloud::drawCloud(){
    // DRAW OUTLINES;
        ofSetColor(0);
        
        // Bottom left circle;
        ofDrawCircle(cloudLoc.x, cloudLoc.y, blcSize);
        
        // Base Rectangle;
        ofDrawRectangle(cloudLoc.x, cloudLoc.y - blcSize, cloudSize, rectHeight);
        
        // Bottom right circle;
        ofDrawCircle(cloudLoc.x + cloudSize, cloudLoc.y + blcSize - brcSize, brcSize);
        
        // Main circle;
        ofDrawCircle(cloudLoc.x + cloudSize * 0.58, cloudLoc.y - mainSize, mainSize);
        
        // Right filler circle;
        ofDrawCircle(cloudLoc.x + cloudSize * 0.84, cloudLoc.y - rfcSize, rfcSize);
        
        // Left filler bigget circle;
        ofDrawCircle(cloudLoc.x + cloudSize * 0.24, cloudLoc.y - lfbcSize, lfbcSize);
        
        // Left filler smaller circle;
        ofDrawCircle(cloudLoc.x + cloudSize * 0.09, cloudLoc.y - lfssSize/2, lfssSize);

    
    
    // DRAW CIRCLES;
        ofSetColor(white);
        
        // Bottom left circle;
        ofDrawCircle(cloudLoc.x, cloudLoc.y, blcSize - 1);
        
        // Base Rectangle;
        ofDrawRectangle(cloudLoc.x, cloudLoc.y - blcSize, cloudSize - 1, rectHeight - 1);
        
        // Bottom right circle;
        ofDrawCircle(cloudLoc.x + cloudSize, cloudLoc.y + blcSize - brcSize, brcSize - 1);
        
        // Main circle;
        ofDrawCircle(cloudLoc.x + cloudSize * 0.58, cloudLoc.y - mainSize, mainSize - 1);
        
        // Right filler circle;
        ofDrawCircle(cloudLoc.x + cloudSize * 0.84, cloudLoc.y - rfcSize, rfcSize - 1);
        
        // Left filler bigget circle;
        ofDrawCircle(cloudLoc.x + cloudSize * 0.24, cloudLoc.y - lfbcSize, lfbcSize - 1);
        
        // Left filler smaller circle;
        ofDrawCircle(cloudLoc.x + cloudSize * 0.09, cloudLoc.y - lfssSize/2, lfssSize - 1);

}
//--------------------------------------------------------------
