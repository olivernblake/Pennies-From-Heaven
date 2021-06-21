//
//  Coin.cpp
//  t2p_PFHPhysics
//
//  Created by Oliver Blake on 26/03/2021.
//

#include "ManageTransitions.h"

//-------------------------------------------------------
ManageTransitions::ManageTransitions()
{
    
}

//--------------------------------------------------------
void ManageTransitions::setup()   {
    // Setup Gameplay;
    drawGameplay.setup();
    
    // Setup Strings/Fonts;
    setupTitleFonts();
    setuph2pFonts();
    setupScoreFonts();
    h2pShow = false;
    
    // Setup Default Opacities;
    titleScreenOpac = 255;
    umbOpac = 0;
    scoresOpac = 0;
    
    // Setup Transition Times;
    transitionTimes();
    
    // Set Game Sequence to False;
    trigGameSequence = false;
    
    // Set Up Colours
    shinyGold = ofColor(255, 215, 0);
    dullGold = ofColor(187, 161, 79);
    shinySilver = ofColor(192);
    dullSilver = ofColor(161);
    shinyCopper = ofColor(183, 115, 51);
    dullCopper = ofColor(121, 85, 61);
    
    dullAmnt = 0.5;
    
    // Adjust Colours (except black) as per Dull Amount;
    gold = shinyGold.getLerped(dullGold, dullAmnt);
    silver = shinySilver.getLerped(dullSilver, dullAmnt);
    copper = shinyCopper.getLerped(dullCopper, dullAmnt);
    
    // Menu Select Vars;
    select1 = 0;
    select2 = 0;
    select3 = 0;
    selectTime = 200;
    
    // Pointer Umbrella
    pointer.setup("right");
}
//--------------------------------------------------------------
void ManageTransitions::update() {
    // Run Select Pos;
    if (titleScreenOpac == 255) {
        pointer.update();
        trackMenuSelect(drawGameplay.rightWristPos);
    }
    
    // Update Time Var;
    t = ofGetElapsedTimeMillis();
    
    // Update Gameplay;
    drawGameplay.update(umbOpac);
    
    // Update Strings;
    updateStrings();
}
//--------------------------------------------------------------
void ManageTransitions::draw(){
    // Always Draw Gameplay;
    drawGameplay.draw();
    
    // Draw Game Sequence;
    if (trigGameSequence) {
        initGameSequence();
    } else {
        drawTitleScreen();
    }
    
    // Draw Pointer for Selecting;
    if (titleScreenOpac == 255) {
        ofPushMatrix();
        ofTranslate(drawGameplay.rightWristPos);
        ofRotateDeg(145);
        pointer.draw();
        ofPopMatrix();
    }
}
//--------------------------------------------------------------
void ManageTransitions::initGameSequence() {
    if (trigFadeToGame) {
        // Fade Title Screen Out and Game Screen Up;
        titleScreenOpac = ofMap(t, fadeTitleOutTime, fadeGameInTime, 255, 0, true);
        umbOpac = ofMap(t, fadeGameInTime, pregameCountdownTime, 0, 255, true);
        if (umbOpac == 255) {
            drawGameplay.scoringDetection.trigPregameCountdown();
            trigFadeToGame = false;
        }
        // Draw Title Screen;
        drawTitleScreen();
    }
    
    // When Game starts, display scores at full Opac;
    if (drawGameplay.scoringDetection.coinSystem.dropCoins) {
        scoresOpac = 255;
        displayGameScores = true;
    }
    if (displayGameScores) {
        drawGameStrings();
    }
    
    if (t > postgameScoreTime && t <= fadePostgameTime) {
        displayGameScores = false;
        growScore();
    }
    
    if (t > fadePostgameTime && t <= fadeTitleInTime) {
        scoresOpac = ofMap(t, fadePostgameTime, fadeTitleInTime, 255, 0, true);
        umbOpac = ofMap(t, fadePostgameTime, fadeTitleInTime, 255, 0, true);
        growScore();
    }
    
    if (t > fadeTitleInTime) {
        titleScreenOpac = ofMap(t, fadeTitleInTime, titleFullOpacTime, 0, 255, true);
        drawTitleScreen();
        // If returned to full opacity, sequence over. Rest in Title Screen;
        if (titleScreenOpac == 255) trigGameSequence = false;
    }
}
//--------------------------------------------------------------
void ManageTransitions::growScore() {
    // After Game Finishes, grow Score to middle;
    ofPushStyle();
    // Set Colour;
    ofSetColor(gold, scoresOpac);
    // Check timer and Map values;
    int scoreSizeBiggest = 84;
    scoreGrowSize = ofMap(t, postgameScoreTime, fadePostgameTime, titleScoreSize, scoreSizeBiggest, true);
    float posX = ofMap(t, postgameScoreTime, fadePostgameTime, scoresPosX, ofGetWidth()/2 - (loraGrow.stringWidth(currentScoreString)/2), true);
    float posY = ofMap(t, postgameScoreTime, fadePostgameTime, scorePosY, ofGetHeight()/2 + (loraGrow.stringHeight(currentScoreString)/2), true);
    loraGrow.load("Lora-Regular.ttf", scoreGrowSize);
    // Draw the String;
    loraGrow.drawString(currentScoreString, posX, posY);
    ofPopStyle();
}
//--------------------------------------------------------------
void ManageTransitions::setupTitleFonts() {
    // Load Title & Instructions;
    titleSize = 48;
    loraTitle.load("Lora-Bold.ttf", titleSize);
    title1 = "P E N N I E S  F R O M";
    title2 = "H    E    A    V    E    N";
    
    menuSize = 32;
    loraMenu.load("Lora-Bold.ttf", menuSize);
    menu1 = "New Game";
    menu2 = "Instructions";
    menu3 = "Back to Menu";
    
    // Box Vars;
    boxWidth = 400;
    boxHeight = 100;
    boxXpos = 440;
    box1y = 440;
    box2y = 600;
    box3y = 840;
    h2pBoxWidth = 640;
    h2pBoxHeight = 420;
    h2pBoxX = (ofGetWidth()/2) - (h2pBoxWidth/2);
    h2pBoxY = 385;
    
    titlePosY = ofGetHeight()/3.5;
    
    scoresPosX = 10;
    titleScoreSize = 24;
    loraScore.load("Lora-Bold.ttf", titleScoreSize);
}
//--------------------------------------------------------------
void ManageTransitions::setuph2pFonts() {
    h2pSize = 28;
    lorah2p.load("Lora-Bold.ttf", h2pSize);
    h2p1 = "Stand back so your arm-span is";
    h2p2 = "the width of the window";
    h2p3 = "When the game begins, Coins will";
    h2p4 = "start falling from the clouds...";
    h2p5 = "Catch as many as you can";
    h2p6 = "in your Umbrellas!";
    h2p7 = "Press I to return to Title Screen";
    h2pPosY = titlePosY * 1.6;
}
//--------------------------------------------------------------
void ManageTransitions::setupScoreFonts() {
    // Score Display Font vars;
    titleScoreSize = 14;
    loraScore.load("Lora-Bold.ttf", titleScoreSize);
    highScorePosY = drawGameplay.scoringDetection.coinSystem.clouds[0].cloudLoc.y * 1.97;
    lineSpacing = 1.25;
    scoresSpaces = loraScore.stringHeight(highScoreString) * lineSpacing;
    scorePosY = highScorePosY + scoresSpaces;
    timeRemPosY = scorePosY + scoresSpaces;
}
//--------------------------------------------------------------
void ManageTransitions::transitionTimes() {
    fadeTitleOutTime = 0;
    fadeGameInTime = 2000;
    pregameCountdownTime = fadeGameInTime + 2000;
    postgameScoreTime = pregameCountdownTime + 23000;
    fadePostgameTime = postgameScoreTime + 2000;
    fadeTitleInTime = fadePostgameTime + 3000;
    titleFullOpacTime = fadeTitleInTime + 2500;
}
//--------------------------------------------------------------
void ManageTransitions::updateStrings() {
    // Update Colours as per Dull Amount;
    gold = shinyGold.getLerped(dullGold, dullAmnt);
    silver = shinySilver.getLerped(dullSilver, dullAmnt);
    copper = shinyCopper.getLerped(dullCopper, dullAmnt);
    
    // From Scoring Detection;
    highScoreString = drawGameplay.scoringDetection.highScoreString;
    lastScoreString = drawGameplay.scoringDetection.lastScoreString;
    currentScoreString = drawGameplay.scoringDetection.scoreString;
    timeRemString = drawGameplay.scoringDetection.timeRemString;
}
//--------------------------------------------------------------
void ManageTransitions::drawTitleScreen() {
    // Draw Title Screen;
    ofPushStyle();
    
    // Draw Title;
    ofSetColor(gold, titleScreenOpac);
    loraTitle.drawString(title1, ofGetWidth()/2 - loraTitle.stringWidth(title1)/2, titlePosY);
    loraTitle.drawString(title2, ofGetWidth()/2 - loraTitle.stringWidth(title2)/2, titlePosY + loraTitle.stringHeight(title1) * 1.5);
    
    // Draw Menu;
    if (h2pShow == false) {
        // Draw Boxes;
        ofFill();
        ofSetColor(copper, titleScreenOpac - 150);
        ofDrawRectangle(boxXpos, box1y, boxWidth, boxHeight);
        ofDrawRectangle(boxXpos, box2y, boxWidth, boxHeight);
        
        // Draw Box Outline;
        ofNoFill();
        ofSetColor(silver, titleScreenOpac);
        ofSetLineWidth(3);
        ofDrawRectangle(boxXpos, box1y, boxWidth, boxHeight);
        ofDrawRectangle(boxXpos, box2y, boxWidth, boxHeight);
        
        // Draw Selections Bars;
        ofFill();
        ofSetColor(silver, titleScreenOpac);
        select1width = ofMap(select1, 0, selectTime, 0, boxWidth, true);
        ofDrawRectangle(boxXpos, box1y, select1width, boxHeight);
        select2width = ofMap(select2, 0, selectTime, 0, boxWidth, true);
        ofDrawRectangle(boxXpos, box2y, select2width, boxHeight);
        
        // Draw Strings;
        ofSetColor(gold, titleScreenOpac);
        menuPosY = box1y + boxHeight/2;
        loraMenu.drawString(menu1, ofGetWidth()/2 - loraMenu.stringWidth(menu1)/2, menuPosY + loraMenu.stringHeight(menu1)/2);
        menu2PosY = box2y + boxHeight/2;
        loraMenu.drawString(menu2, ofGetWidth()/2 - loraMenu.stringWidth(menu2)/2, menu2PosY + loraMenu.stringHeight(menu2)/2);
    }
    
    // Draw How 2 Play;
    if (h2pShow) {
        // Draw Background box;
        ofFill();
        ofSetColor(copper, titleScreenOpac - 150);
        ofDrawRectangle(h2pBoxX, h2pBoxY, h2pBoxWidth, h2pBoxHeight);
        
        // Draw Background Box Outline
        ofNoFill();
        ofSetColor(silver, titleScreenOpac);
        ofDrawRectangle(h2pBoxX, h2pBoxY, h2pBoxWidth, h2pBoxHeight);
        
        // Draw Strings;
        ofSetColor(gold, titleScreenOpac);
        h2pSpaces = lorah2p.stringHeight(h2p1) * lineSpacing;
        lorah2p.drawString(h2p1, ofGetWidth()/2 - lorah2p.stringWidth(h2p1)/2, h2pPosY);
        lorah2p.drawString(h2p2, ofGetWidth()/2 - lorah2p.stringWidth(h2p2)/2, h2pPosY + h2pSpaces);
        lorah2p.drawString(h2p3, ofGetWidth()/2 - lorah2p.stringWidth(h2p3)/2, h2pPosY + (h2pSpaces * 3));
        lorah2p.drawString(h2p4, ofGetWidth()/2 - lorah2p.stringWidth(h2p4)/2, h2pPosY + (h2pSpaces * 4));
        lorah2p.drawString(h2p5, ofGetWidth()/2 - lorah2p.stringWidth(h2p5)/2, h2pPosY + (h2pSpaces * 6));
        lorah2p.drawString(h2p6, ofGetWidth()/2 - lorah2p.stringWidth(h2p6)/2, h2pPosY + (h2pSpaces * 7));
        
        // Draw "BACK" Box;
        ofFill();
        ofSetColor(copper, titleScreenOpac - 150);
        ofDrawRectangle(boxXpos, box3y, boxWidth, boxHeight);
        // Draw Box Outline;
        ofNoFill();
        ofSetColor(silver, titleScreenOpac);
        ofSetLineWidth(3);
        ofDrawRectangle(boxXpos, box3y, boxWidth, boxHeight);
        // Draw Selection Bar;
        ofFill();
        ofSetColor(silver, titleScreenOpac);
        select3width = ofMap(select3, 0, selectTime, 0, boxWidth, true);
        ofDrawRectangle(boxXpos, box3y, select3width, boxHeight);
        // Draw "Back" String;
        ofSetColor(gold, titleScreenOpac);
        menu3PosY = box3y + boxHeight/2;
        loraMenu.drawString(menu3, ofGetWidth()/2 - loraMenu.stringWidth(menu3)/2, menu3PosY + loraMenu.stringHeight(menu3)/2);
    }

    
    // Draw Title Screen Scores;
    ofSetColor(gold, titleScreenOpac);
    scoresSpaces = loraScore.stringHeight(highScoreString) * lineSpacing;
    scorePosY = highScorePosY + scoresSpaces;
    loraScore.drawString(highScoreString, scoresPosX, highScorePosY);
    loraScore.drawString(lastScoreString, scoresPosX, scorePosY);
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ManageTransitions::drawGameStrings() {
    ofPushStyle();
    ofSetColor(gold, scoresOpac);
    // Update Positioning;
    scoresSpaces = loraScore.stringHeight(highScoreString) * lineSpacing;
    scorePosY = highScorePosY + scoresSpaces;
    timeRemPosY = scorePosY + scoresSpaces;
    // Draw Strings;
    loraScore.drawString(highScoreString, scoresPosX, highScorePosY);
    loraScore.drawString(currentScoreString, scoresPosX, scorePosY);
    loraScore.drawString(timeRemString, scoresPosX, timeRemPosY);
    ofPopStyle();
}
//--------------------------------------------------------------
void ManageTransitions::trackMenuSelect(glm::vec2 _selectPos) {
    glm::vec2 selectPos = _selectPos;
    
    // Draw the Pointer;
//    umbPointer.draw(selectPos);

    // Run Boxes 1 and 2 during regular menu;
    if (h2pShow == false) {
        // Is the selector in any of the boxes?
        // Within X range;
        if (selectPos.x > boxXpos && selectPos.x < boxXpos + boxWidth) {
            // Within Y range;
            if (selectPos.y > box1y && selectPos.y < box1y + boxHeight) {
                inside1 = true;
            } else if (selectPos.y > box2y && selectPos.y < box2y + boxHeight) {
                inside2 = true;
            } else {
                inside1 = false;
                inside2 = false;
            }
        } else {
            inside1 = false;
            inside2 = false;
        }
        
        if (inside1) {
            // If reaches the selectTime var of frames, init Game Sequence;
            if (select1 == selectTime) {
                // Reset the time, and init the Game sequence;
                ofResetElapsedTimeCounter();
                trigGameSequence = true;
                trigFadeToGame = true;
                select1 = 0;
            } else {
                select1++;
            }
        } else if (inside1 == false) {
            select1 = 0;
        }
        
        if (inside2) {
            select2++;
            if (select2 == selectTime) {
                h2pShow = true;
            }
        } else if (inside2 == false) {
            select2 = 0;
        }
    }
    
    // Run Box 3 when in instructions;
    if (h2pShow) {
        // Is the selector the box?
        // Within X range;
        if (selectPos.x > boxXpos && selectPos.x < boxXpos + boxWidth) {
            // Within Y range;
            if (selectPos.y > box3y && selectPos.y < box3y + boxHeight) {
                inside3 = true;
            } else inside3 = false;
        } else {
            inside3 = false;
        }
        
        if (inside3) {
            select3++;
            if (select3 == selectTime) {
                h2pShow = false;
            }
        } else if (inside3 == false) {
            select3 = 0;
        }
    }
}
//--------------------------------------------------------------
