#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    pm.setup(1280, 720);
    ai.setup();
    
    vid.setup(1280, 720);
    
    setupGui();
}

void ofApp::setupGui(){
    bGui = false;
    
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    
    sliAttRadius = new ofxDatGuiSlider("Attractor radius", 0,200, pm.attractor.getRadius());
    sliAttRadius->onSliderEvent(this, &ofApp::onSliAttRadius);
    
    sliAttForce = new ofxDatGuiSlider("Attractor force", 0,1000, pm.attractor.force);
    sliAttForce->onSliderEvent(this, &ofApp::onSliAttForce);
    
    sliHomForce = new ofxDatGuiSlider("Homing force", 0,1000, pm.homing);
    sliHomForce->onSliderEvent(this, &ofApp::onSliHomForce);
    
    sliDamp = new ofxDatGuiSlider("Force dampening", 0,1, pm.dampening);
    sliDamp->onSliderEvent(this, &ofApp::onSliDamp);
    
    //sliAttRadius = new ofxDatGuiSlider("Attractor radius", 0,200, pm.attractor.getRadius());
    //sliAttRadius->onSliderEvent(this, &ofApp::onSliAttRadius);
    
    gui->attachItem(sliAttRadius);
    gui->attachItem(sliAttForce);
    gui->attachItem(sliHomForce);
    gui->attachItem(sliDamp);
    
    gui->setVisible(false);
}

void ofApp::showGui(){
    if(bGui)return;
    bGui = true;
    gui->setVisible(bGui);
}

void ofApp::hideGui(){
    if(!bGui)return;
    bGui = false;
    gui->setVisible(bGui);
}

//--------------------------------------------------------------
void ofApp::update(){
    vid.update();
    ai.update();
    if(vid.isFrameNew()){
        pm.beginFrame();
        vid.draw(0, 0, 1280, 720);
        pm.endFrame();
    }
    pm.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    pm.draw();
    if(bGui)pm.drawDebug();
    //ofDisableBlendMode();
    //ofDrawBox(0, 0, 0, 100, 100, 100);
    cam.end();
    if(bGui)ai.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'g':
            toggleGui();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
