#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    pm.setup(1280, 720);
    
    vid.setup(1280, 720);
}

//--------------------------------------------------------------
void ofApp::update(){
    vid.update();
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
    //ofDisableBlendMode();
    //ofDrawBox(0, 0, 0, 100, 100, 100);
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
