#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    // Webcam setup;
    ofSetFrameRate(60);
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640,480);
    
    // Style Setup;
    ofSetCircleResolution(60);
    
    // Width/Height Vars;
    width = ofGetWidth();
    height = ofGetHeight();
    
    // Setup Game, Menus, Transitions;
    manageTransitions.setup();
    
    // Settings and GUI Setup;
    showSettings = false;
    settingsPanel.setup();
    settingsPanel.add(musicVolSlider.setup("Music Volume", 40, 0, 100));
    settingsPanel.add(sfxVolSlider.setup("Sound Effects Volume", 50, 0, 100));
    settingsPanel.add(textDullSlider.setup("Text Dullness", 10, 0, 100));
    settingsGuiUpdate();
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update Settings Slider Values;
    settingsGuiUpdate();
    
    // Update Vid Grabber;
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()){
        // Update Current Frame ofImage;
        currentFrame = vidGrabber.getPixels();
        currentFrame.mirror(false, true);

        // Update image size;
        imgW = currentFrame.getWidth();
        imgH = currentFrame.getHeight();
    }
    
    // Update Transition Manager;
    manageTransitions.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw Webcam (Sized);
    ofPushStyle();
    ofSetColor(255);
    currentFrame.draw(0, 0, width, height);
    ofPopStyle();
    
    // Draw Game and Menus;
    manageTransitions.draw();
    
    // Show Settings GUI;
    if (showSettings) {
        settingsPanel.draw();
    }
    
}
//--------------------------------------------------------------
void ofApp::settingsGuiUpdate() {
    // Map Music Volume and pass down;
    mapMusicVol = ofMap(musicVolSlider, 0, 100, 0, 0.5);
    manageTransitions.drawGameplay.scoringDetection.coinSystem.musicVolSlider = mapMusicVol;
    // Map sfx vol and pass down to floor sounds;
    mapFloorSoundVol = ofMap(sfxVolSlider, 0, 100, 0, 1.5);
    manageTransitions.drawGameplay.scoringDetection.coinSystem.sfxVolSlider = mapFloorSoundVol;
    // Map sfx vol and pass down to catchcoin sound;
    mapCatchCoinVol = ofMap(sfxVolSlider, 0, 100, 0, 0.3);
    manageTransitions.drawGameplay.scoringDetection.sfxVolSlider = mapCatchCoinVol;
    // Map Dullness and pass to Menu Strings;
    mapDullness = ofMap(textDullSlider, 0, 100, 0, 1, true);
    manageTransitions.dullAmnt = mapDullness;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // FOR DEBUGGING;
    
    // Show Settings;
    if (key == 's' || key == 'S') {
        showSettings = !showSettings;
    }
    
    // P activates Game Sequence;
    if (key == 'p' || key == 'P') {
        // Only Activate if in resting home screen;
        if (manageTransitions.titleScreenOpac == 255) {
            // And Instructions aren't showing!;
            if (manageTransitions.h2pShow == false) {
                // Reset the time, and init the Game sequence;
                ofResetElapsedTimeCounter();
                manageTransitions.trigGameSequence = true;
                manageTransitions.trigFadeToGame = true;
            }
        }
    }
    
    // Press I for Instructions;
    if (key == 'i' || key == 'I') {
        manageTransitions.h2pShow = !manageTransitions.h2pShow;
    }
    
}
//--------------------------------------------------------------
