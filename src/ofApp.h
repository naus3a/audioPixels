#pragma once

#include "ofMain.h"
#include "ParticleManager.hpp"
#include "AudioInput.hpp"
#include "ofxDatGui.h"
#include "ofxProcessFFT.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    void setupGui();
    void setGui(bool _b){_b?showGui():hideGui();}
    void showGui();
    void hideGui();
    void toggleGui(){setGui(!bGui);}
    
    void onSliAttRadius(ofxDatGuiSliderEvent e){pm.attractor.setRadius(e.value);}
    void onSliAttForce(ofxDatGuiSliderEvent e){pm.attractor.force = e.value;}
    void onSliHomForce(ofxDatGuiSliderEvent e){pm.homing = e.value;}
    void onSliDamp(ofxDatGuiSliderEvent e){pm.dampening = e.value;}
    void onSliGravity(ofxDatGuiSliderEvent e);
    
    ofxDatGui * gui;
    ofxDatGuiSlider * sliAttRadius;
    ofxDatGuiSlider * sliAttForce;
    ofxDatGuiSlider * sliHomForce;
    ofxDatGuiSlider * sliDamp;
    ofxDatGuiSlider * sliGravity;
    
    //ProcessFFT fft;
    
    ParticleManager pm;
    AudioInput ai;
    ofEasyCam cam;
    ofVideoGrabber vid;
    bool bGui;
};
