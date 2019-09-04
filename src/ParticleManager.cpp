//
//  ParticleManager.cpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/18/19.
//

#include "ParticleManager.hpp"

ParticleManager::ParticleManager(){
    bShaders = false;
    attractor.set(ofVec3f(0,0,200), 200);
    gravity.set(0,-0.5,0);
    dampening = 0.995;
    homing = 10;
    pthShaders120 = ofFilePath::join("shaders", "glsl120");
    pthShaders330 = ofFilePath::join("shaders", "glsl330");
    mshBall.set(50, 5);
    
    attractorMagnet.x.setAttracted(&attractor.position.x);
    attractorMagnet.y.setAttracted(&attractor.position.y);
    attractorMagnet.z.setAttracted(&attractor.position.z);
    
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
    attractorMagnet.update();
    ps.update();
}

void ParticleManager::onPsUpdate(ofShader &_shd){
    _shd.setUniformTexture("texStartPos", fboStartPos.getTexture(), 2);
    _shd.setUniform3fv("gravity", gravity.getPtr());
    _shd.setUniform1f("attFrc", attractor.force);
    _shd.setUniform1f("dampening", dampening);
    _shd.setUniform1f("homing", homing);
    
    //ofVec3f mouse(ofGetMouseX() - .5f * ofGetWidth(), .5f * ofGetHeight() - ofGetMouseY() , 0.f);
    //attractor.position = mouse;
    _shd.setUniform3fv("attractor", attractor.position.getPtr());
    _shd.setUniform1f("elapsed", ofGetLastFrameTime());
    _shd.setUniform1f("radiusSquared", attractor.getRadiusSquared());
}

void ParticleManager::onPsDraw(ofShader &_shd){
    _shd.setUniformTexture("texFrame", fboFrame.getTexture(), 2);
}

void ParticleManager::draw(){
    ps.draw();
}

void ParticleManager::drawDebug(){
    attractor.draw();
    
    ofPushStyle();
    ofSetColor(ofColor::red);
    ofPushMatrix();
    ofTranslate(attractorMagnet.x.value, attractorMagnet.y.value, attractorMagnet.z.value);
    mshBall.drawWireframe();
    ofPopMatrix();
    ofPopStyle();
}

void ParticleManager::save(ofxXmlSettings &_xml){
    _xml.addTag("particles");
    _xml.pushTag("particles");
    attractor.save(_xml);
    _xml.setValue("homing", homing);
    _xml.setValue("dampening", dampening);
    attractorMagnet.save(_xml);
    _xml.popTag();
}

void ParticleManager::load(ofxXmlSettings &_xml){
    if(_xml.tagExists("particles")){
        _xml.pushTag("particles");
        attractor.load(_xml);
        homing = _xml.getValue("homing", homing);
        dampening = _xml.getValue("dampening", dampening);
        _xml.popTag();
    }else{
        ofLogError("ParticleManager::load", "no particles tag");
    }
}
