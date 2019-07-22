//
//  AudioInput.cpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/19/19.
//

#include "AudioInput.hpp"

AudioInput::AudioInput(){
    devInName = "default";
    bSetup = false;
}

bool AudioInput::setup(string _devInName, int _sampleRate, int _bufferSize){
    bSetup = false;
    devInName = _devInName;
    sampRate = _sampleRate;
    bufSz = _bufferSize;
    vector<ofSoundDevice> _dd = sStream.getDeviceList();//sStream.getMatchingDevices(devInName);
    if(_dd.empty()){
        ofLogError("AudioInput::setup","no input device named "+devInName);
        return false;
    }
    
    /*ofSoundStreamSettings sss;
    sss.setInDevice(_dd[0]);
    sss.sampleRate = sampRate;
    sss.numOutputChannels = 0;
    sss.numInputChannels = 2;
    sss.bufferSize = bufSz;
    sss.setInListener(this);*/
    
    //sStream.setup(sss);
    fft.setup();
    volume.setup(bufSz);
    
    bSetup = true;
    return true;
}

void AudioInput::audioIn(ofSoundBuffer &input){
    volume.onAudioIn(input);
}

void AudioInput::update(){
    fft.update();
}

void AudioInput::draw(){
    //volume.draw();
    fft.draw();
}

void AudioInput::save(ofxXmlSettings &_xml){
    _xml.addTag("audioin");
    _xml.pushTag("audioin");
    fft.range.save(_xml);
    _xml.popTag();
}

void AudioInput::load(ofxXmlSettings & _xml){
    if(_xml.tagExists("audioin")){
        _xml.pushTag("audioin");
        fft.range.load(_xml);
        _xml.popTag();
    }else{
        ofLogError("AudioInput::load","no audioin tag");
    }
}
