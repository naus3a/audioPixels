//
//  AudioVolume.cpp
//  audioPixels
//
//  Created by naus3a on 7/19/19.
//

#include "AudioVolume.hpp"

AudioVolume::AudioVolume(){
    vol = 0;
}

void AudioVolume::setup(int _bufSz, int _volHistSize){
    lx.assign(_bufSz, 0);
    rx.assign(_bufSz, 0);
    volHist.assign(_volHistSize, 0);
    volHistIdx = 0;
}

void AudioVolume::onAudioIn(ofSoundBuffer & input){
    float f = getRootMeanSquared(input);
    updateAndSmooth(vol, f);
    updateVolumeHistory();
}

float AudioVolume::getRootMeanSquared(ofSoundBuffer &input){
    float f = 0;
    int n = 0;
    for(int i=0;i<input.getNumFrames();i++){
        lx[i] = input[i*2]*0.5;
        rx[i] = input[i*2+1]*0.5;
        
        f+=lx[i]*lx[i];
        f+=rx[i]*rx[i];
        n+=2;
    }
    //the mean part of rms...
    f/=(float)n;
    //...the root part of rms.
    f=sqrt(f);
    return f;
}

void AudioVolume::updateAndSmooth(float & _runningVal, float _newVal){
    _runningVal *= 0.93;
    _runningVal += 0.07 * _newVal;
}

void AudioVolume::updateVolumeHistory(){
    if(volHistIdx>=volHist.size()){
        volHistIdx = 0;
    }
    volHist[volHistIdx] = vol;
    volHistIdx++;
}

void AudioVolume::draw(){
    ofPushMatrix();
    ofTranslate(350, 20);
    ofPushStyle();
    ofSetColor(ofColor::cyan);
    ofNoFill();
    ofSetLineWidth(10);
    ofDrawRectangle(0, 0, volHist.size(), volHist.size()/2);
    drawHistory(volHist);
    ofSetLineWidth(1);
    ofDrawCircle(volHist.size()/2, volHist.size()/4, ofMap(vol, 0, 0.17, 0, volHist.size()/6));
    ofDrawBitmapString("volume: "+ofToString(vol,2), 10, volHist.size()/2);
    ofPopStyle();
    ofPopMatrix();
}

void AudioVolume::drawHistory(vector<float> &_ff){
    ofBeginShape();
    ofVertex(0, 0);
    for(int i=0;i<_ff.size();i++){
        ofVertex(i, 1000*volHist[i]);
    }
    ofVertex(_ff.size()-1, 0);
    ofEndShape(false);
}
