#pragma once

#include "ofMain.h"
#include "ScoringDetection.h"
#include "Umbrella.h"
#include "Cloud.h"
#include "CoinSystem.h"
#include "Coin.h"
#include "ofxOsc.h"
#include "OSCReceiver.h"
#include "ofxGui.h"
#include "DrawGameplay.h"
#include "ManageTransitions.h"
#include "PointerUmb.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void settingsGuiUpdate();
        void transToGame();
        void transToMenu();
		void keyPressed(int key);
    
    // Webcam Vars
    ofVideoGrabber vidGrabber;
    ofImage currentFrame;
    
    // Window Size Updates;
    float width, height;
    float imgW, imgH;
    
    // Transitions;
    ManageTransitions manageTransitions;
    bool showSettings;
    int gameOpac, menuOpac;
    
    // Settings GUI;
    ofxPanel settingsPanel;
    ofxIntSlider musicVolSlider;
    ofxIntSlider sfxVolSlider;
    ofxIntSlider textDullSlider;
    float mapMusicVol;
    float mapCatchCoinVol;
    float mapFloorSoundVol;
    float mapDullness;
};
