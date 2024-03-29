//
//  ParticleManager.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/18/19.
//

#pragma once
#include "ofMain.h"
#include "ofxGpuParticles.h"
#include "Attractor.hpp"
#include "Vec3Magnet.h"
#include "ofxXmlSettings.h"

class ParticleManager{
public:
    ParticleManager();
    void setup(float _w, float _h);
    void update();
    void draw();
    void drawDebug();
    
    void beginFrame(){fboFrame.begin(); ofClear(0, 0, 0, 0);}
    void endFrame(){fboFrame.end();}
    
    void save(ofxXmlSettings & _xml);
    void load(ofxXmlSettings & _xml);
    
    Attractor attractor;
    Vec3Magnet attractorMagnet;
    ofVec3f gravity;
    float dampening;
    float homing;
protected:
    void initShaders();
    float * makeFrameFloats(int _nChans=4);
    void destroyFrameFloats(float * _f);
    float * makeStartPosFloats();
    void loadDataFbo(ofFbo & _fbo, float * _data);
    
    void onPsUpdate(ofShader & _shd);
    void onPsDraw(ofShader & _shd);
    
    ofSpherePrimitive mshBall;
    ofxGpuParticles ps;
    ofFbo fboFrame;
    ofFbo fboStartPos;
    ofVec2f frameSz;
    float rAttractor;
    string pthShaders120;
    string pthShaders330;
    bool bShaders;
};
