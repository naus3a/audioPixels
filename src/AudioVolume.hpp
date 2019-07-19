//
//  AudioVolume.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/19/19.
//

#pragma once
#include "ofMain.h"

class AudioVolume{
public:
    AudioVolume();
    void setup(int _bufSz, int _volHistSize=400);
    void onAudioIn(ofSoundBuffer & input);
    void draw();
protected:
    float getRootMeanSquared(ofSoundBuffer & input);
    void updateAndSmooth(float & _runningVal, float _newVal);
    void updateVolumeHistory();
    void drawHistory(vector<float> & _ff);
    
    vector<float> lx;
    vector<float> rx;
    vector<float> volHist;
    float vol;
    int volHistIdx;
};
