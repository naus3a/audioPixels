//
//  AudioInput.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/19/19.
//

#pragma once
#include "ofMain.h"
#include "AudioVolume.hpp"
#include "FftManager.hpp"
#include "ofxXmlSettings.h"

class AudioInput{
public:
    AudioInput();
    bool setup(string _devInName, int _sampleRate=44100, int _bufferSize=256);
    bool setup(){return setup(devInName);}
    void audioIn(ofSoundBuffer & input);
    void update();
    void draw();
    
    void save(ofxXmlSettings & _xml);
    void load(ofxXmlSettings & _xml);
    
    AudioVolume volume;
    FftManager fft;
protected:
    
    ofSoundStream sStream;
    string devInName;
    int sampRate;
    int bufSz;
    bool bSetup;
};
