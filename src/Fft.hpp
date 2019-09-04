//
//  Fft.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/21/19.
//

#pragma once
#include "ofxProcessFFT.h"

class Fft : public ProcessFFT{
public:
    //void setup(int _devId){
    //    fft.stream.setDeviceID(_devId);
    //    fft.setup();
    //}
    
    void setDevId(int _devId){
        fft.stream.setDeviceID(_devId);
    }
    
    vector<float> & getSpectrumRef(){return fftSpectrum;}
    float getVolumeRange(){return volumeRange;}
    int getLoudestBandId(){return loudestBand;}
};
