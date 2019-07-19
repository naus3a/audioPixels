//
//  ParticleManager.cpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/18/19.
//

#include "ParticleManager.hpp"

ParticleManager::ParticleManager(){
    bShaders = false;
    pthShaders120 = ofFilePath::join("shaders", "glsl120");
    pthShaders330 = ofFilePath::join("shaders", "glsl330");
    
    initShaders();
}

void ParticleManager::initShaders(){
    if(bShaders)return;
    
    if(ofIsGLProgrammableRenderer()){
        cout<<"Particles: using programmable renderer"<<endl;
        ps.loadShaders(ofFilePath::join(pthShaders330, "update"), ofFilePath::join(pthShaders330, "draw"));
    }else{
        cout<<"Particles: using old school non programmable renderer"<<endl;
        ps.loadShaders(ofFilePath::join(pthShaders120, "update"), ofFilePath::join(pthShaders120, "draw"));
        //TODO
    }
    bShaders = true;
}

float * ParticleManager::makeFrameFloats(int _nChans){
    int _n = frameSz.x*frameSz.y*_nChans;
    float * _f = new float[_n];
    return _f;
}

void ParticleManager::destroyFrameFloats(float *_f){
    if(_f==NULL)return;
    delete [] _f;
}

float * ParticleManager::makeStartPosFloats(){
    float startX = -frameSz.x/2;
    float startY = -frameSz.y/2;
    float * _f = makeFrameFloats();
    for(int y=0;y<frameSz.y;y++){
        for(int x=0;x<frameSz.x;x++){
            unsigned _idx = y*frameSz.x+x;
            _f[_idx*4] = startX+x; //x
            _f[_idx*4+1] = startY+y; //y
            _f[_idx*4+2] = 0; //z
            _f[_idx*4+3] = 0; //unused
        }
    }
    return _f;
}

void ParticleManager::loadDataFbo(ofFbo &_fbo, float *_data){
    _fbo.getTexture().bind();
    glTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, _fbo.getWidth(), _fbo.getHeight(), GL_RGBA, GL_FLOAT, _data);
    _fbo.getTexture().unbind();
}

void ParticleManager::setup(float _w, float _h){
    frameSz.set(_w, _h);
    ps.init(frameSz.x, frameSz.y);
    initShaders();
    
    fboFrame.allocate(frameSz.x, frameSz.y, GL_RGBA);
    fboFrame.begin();
    ofClear(0, 0, 0, 0);
    fboFrame.end();
    
    float * startPos = makeStartPosFloats();
    ps.loadDataTexture(ofxGpuParticles::POSITION, startPos);
    fboStartPos.allocate(ps.getFboSettings(2));
    loadDataFbo(fboStartPos, startPos);
    destroyFrameFloats(startPos);
    
    ps.zeroDataTexture(ofxGpuParticles::VELOCITY);
    ofAddListener(ps.updateEvent, this, &ParticleManager::onPsUpdate);
    ofAddListener(ps.drawEvent, this, &ParticleManager::onPsDraw);
}

void ParticleManager::update(){
    ps.update();
}

void ParticleManager::onPsUpdate(ofShader &_shd){
    _shd.setUniformTexture("texStartPos", fboStartPos.getTexture(), 2);
    
    ofVec3f mouse(ofGetMouseX() - .5f * ofGetWidth(), .5f * ofGetHeight() - ofGetMouseY() , 0.f);
    _shd.setUniform3fv("mouse", mouse.getPtr());
    _shd.setUniform1f("elapsed", ofGetLastFrameTime());
    _shd.setUniform1f("radiusSquared", 200.f * 200.f);
}

void ParticleManager::onPsDraw(ofShader &_shd){
    _shd.setUniformTexture("texFrame", fboFrame.getTexture(), 2);
}

void ParticleManager::draw(){
    ps.draw();
}
