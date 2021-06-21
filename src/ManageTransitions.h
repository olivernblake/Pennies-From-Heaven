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
#include "DrawGameplay.h"
#include "PointerUmb.h"

class ManageTransitions{

    public:
    ManageTransitions();
    
        // Functions
        void setup();
        void update();
        void draw();
        void drawTitleScreen();
        void drawGameStrings();
        // Font Functions;
        void updateStrings();
        void setupTitleFonts();
        void setupScoreFonts();
        void setuph2pFonts();
        // Transition Functions;
        void transitionTimes();
        void initGameSequence();
        void growScore();
        // Menu Selection Funcion;
        void trackMenuSelect(glm::vec2 _selectPos);
    
    // Draw Gameplay
    DrawGameplay drawGameplay;
    
    // Menu Selection Vars;
    bool inside1, inside2, inside3;
    float select1, select2, select3;
    float select1width, select2width, select3width;
    int selectTime;
    PointerUmb pointer;
    
    // SETUP STRINGS/FONTS
        // Title;
        ofTrueTypeFont loraTitle;
        int titleSize;
        float titlePosY;
        string title1, title2;
        
        // Menu Options;
        ofTrueTypeFont loraMenu;
        int menuSize;
        float menuPosY, menu2PosY, menu3PosY;
        string menu1, menu2, menu3;
        float boxXpos, box1y, box2y, box3y;
        float boxWidth, boxHeight;
        
        // How to play;
        ofTrueTypeFont lorah2p;
        int h2pSize;
        float h2pSpaces;
        float h2pPosY, h2p2PosY, h2p3PosY;
        string h2p1, h2p2, h2p3, h2p4, h2p5, h2p6, h2p7;
        bool h2pShow;
        float h2pBoxX, h2pBoxY, h2pBoxWidth, h2pBoxHeight;
        
        // Titlescreen Scores;
        ofTrueTypeFont loraScore;
        int titleScoreSize;
        float scoresPosX;
        float highScorePosY;
        float scorePosY;
        float lineSpacing;
        float scoresSpaces;
        
        // Gameplay Scores;
        ofTrueTypeFont loraGrow;
        float scoreGrowSize;
        float timeRemPosY;
        
        // Strings;
        string highScoreString;
        string lastScoreString;
        string currentScoreString;
        string timeRemString;
    
    // Transition Variables;
    float titleScreenOpac;
    float umbOpac;
    float scoresOpac;
    int t;
    
    // Transition Sections & Timings;
    bool trigGameSequence;
    bool trigFadeToGame;
    bool displayGameScores;
    int fadeTitleOutTime;
    int fadeGameInTime;
    int pregameCountdownTime;
    int postgameScoreTime;
    int fadePostgameTime;
    int fadeTitleInTime;
    int titleFullOpacTime;
    
    // Colours
    ofColor shinyGold;
    ofColor shinySilver;
    ofColor shinyCopper;
    ofColor dullGold;
    ofColor dullSilver;
    ofColor dullCopper;
    ofColor gold, silver, copper;
    float dullAmnt;
    
};
