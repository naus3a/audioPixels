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
    vector<float> & getSpectrumRef(){return fftSpectrum;}
    float getVolumeRange(){return volumeRange;}
    int getLoudestBandId(){return loudestBand;}
};
