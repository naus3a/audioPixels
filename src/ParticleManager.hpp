//
//  ParticleManager.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/18/19.
//

#pragma once
#include "ofMain.h"
#include "ofxGpuParticles.h"

class ParticleManager{
public:
    ParticleManager();
    void setup(float _w, float _h);
    void update();
    void draw();
    
    void beginFrame(){fboFrame.begin(); ofClear(0, 0, 0, 0);}
    void endFrame(){fboFrame.end();}
protected:
    void initShaders();
    float * makeFrameFloats(int _nChans=4);
    void destroyFrameFloats(float * _f);
    float * makeStartPosFloats();
    void loadDataFbo(ofFbo & _fbo, float * _data);
    
    void onPsUpdate(ofShader & _shd);
    void onPsDraw(ofShader & _shd);
    
    ofxGpuParticles ps;
    ofFbo fboFrame;
    ofFbo fboStartPos;
    string pthShaders120;
    string pthShaders330;
    ofVec2f frameSz;
    bool bShaders;
};
