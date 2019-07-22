//
//  FftManager.cpp
//  audioPixels
//
//  Created by naus3a on 7/19/19.
//

#include "FftManager.hpp"

FftManager::FftManager(){
    range.set(
              FloatRange(-640,640),
              FloatRange(-360,360),
              FloatRange(-200,200)
    );
}

void FftManager::setup(){
    fft.setup();
}

void FftManager::update(){
    fft.update();
}

void FftManager::draw(){
    drawBars();
    
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(ofColor::cyan);
    ofSetLineWidth(5);
    ofTranslate(ofGetWidth()/2+range.x.min, ofGetHeight()/2);
    ofDrawLine(0, range.y.min, 0, range.y.max);
    //ofDrawLine(0, 0, range.z.min, 0, 0, range.z.max);
    ofPopStyle();
    ofPopMatrix();
}

void FftManager::drawBars(){
    ofPushMatrix();
    
    float xx = ofGetWidth()/2+range.x.min;
    float yy = ofGetHeight();
    float ww = range.x.getRange()/fft.getNumFFTbins();
    ofPushStyle();
    ofSetLineWidth(2);
    ofNoFill();
    vector<float> spectrum = fft.getSpectrum();
    for(int i=0;i<spectrum.size();i++){
        ofSetColor((i==fft.getLoudestBandId())?ofColor::red:ofColor::cyan);
        ofDrawRectangle(xx, yy, ww, -ofMap(spectrum[i],0,fft.getVolumeRange(),0,200));
        ofTranslate(ww, 0);
    }
    ofPopStyle();
    ofPopMatrix();
}

float FftManager::getNormalizedBand(int _bId){
    return ofMap(fft.getSpectrumRef()[_bId],0,fft.getVolumeRange(),0,1);
}

float FftManager::getBandIdPct(int _bId){
    return ofMap(_bId,0,fft.getNumFFTbins()-1,0,1);
}

float FftManager::loudestBandToX(){
    return range.x.getPctInRange(getBandIdPct(fft.getLoudestBandId()));
}

float FftManager::loudestBandValueToZ(){
    return range.z.getPctInRange(getNormalizedBand(fft.getLoudestBandId()));
}
