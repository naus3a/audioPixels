#pragma once

#include "ofMain.h"
#include "ParticleManager.hpp"
#include "AudioInput.hpp"
#include "ofxDatGui.h"
#include "ofxProcessFFT.h"
#include "ofxXmlSettings.h"

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

    void save();
    void load();
    void refreshGui();
    
    void setupGui();
    void setGui(bool _b){_b?showGui():hideGui();}
    void showGui();
    void hideGui();
    void toggleGui(){setGui(!bGui);}
    
    void onBut(ofxDatGuiButtonEvent e);
    void onButSave(ofxDatGuiButtonEvent e){save();}
    void onButLoad(ofxDatGuiButtonEvent e){load();}
    void onSliAttRadius(ofxDatGuiSliderEvent e){pm.attractor.setRadius(e.value);}
    void onSliAttForce(ofxDatGuiSliderEvent e){pm.attractor.force = e.value;}
    void onSliHomForce(ofxDatGuiSliderEvent e){pm.homing = e.value;}
    void onSliDamp(ofxDatGuiSliderEvent e){pm.dampening = e.value;}
    void onSliGravity(ofxDatGuiSliderEvent e);
    void onSliFftMagStrX(ofxDatGuiSliderEvent e){pm.attractorMagnet.x.strength=e.value;}
    void onSliFftMagStrY(ofxDatGuiSliderEvent e){pm.attractorMagnet.y.strength=e.value;}
    void onSliFftMagStrZ(ofxDatGuiSliderEvent e){pm.attractorMagnet.z.strength=e.value;}
    void onSliFftRangeX(ofxDatGuiSliderEvent e){ai.fft.range.x.adjustRange(e.value);}
    void onSliFftRangeY(ofxDatGuiSliderEvent e){ai.fft.range.y.adjustRange(e.value);}
    void onSliFftRangeZ(ofxDatGuiSliderEvent e){ai.fft.range.z.adjustRange(e.value);}
    void onSliFftCtrX(ofxDatGuiSliderEvent e){ai.fft.range.x.adjustCenter(e.value);}
    void onSliFftCtrY(ofxDatGuiSliderEvent e){ai.fft.range.y.adjustCenter(e.value);}
    void onSliFftCtrZ(ofxDatGuiSliderEvent e){ai.fft.range.z.adjustCenter(e.value);}
    
    ofxDatGui * gui;
    ofxDatGuiButton * butSave;
    ofxDatGuiButton * butLoad;
    ofxDatGuiSlider * sliAttRadius;
    ofxDatGuiSlider * sliAttForce;
    ofxDatGuiSlider * sliHomForce;
    ofxDatGuiSlider * sliDamp;
    ofxDatGuiSlider * sliGravity;
    ofxDatGuiSlider * sliFftMagStrX;
    ofxDatGuiSlider * sliFftMagStrY;
    ofxDatGuiSlider * sliFftMagStrZ;
    ofxDatGuiSlider * sliFftRangeX;
    ofxDatGuiSlider * sliFftRangeY;
    ofxDatGuiSlider * sliFftRangeZ;
    ofxDatGuiSlider * sliFftCtrX;
    ofxDatGuiSlider * sliFftCtrY;
    ofxDatGuiSlider * sliFftCtrZ;
    
    //ProcessFFT fft;
    
    ParticleManager pm;
    AudioInput ai;
    ofEasyCam cam;
    ofVideoGrabber vid;
    string pthXml;
    bool bGui;
};
