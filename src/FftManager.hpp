//
//  FftManager.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/19/19.
//

#pragma once
#include "ofMain.h"
#include "ofxProcessFFT.h"

class FftManager{
public:
    void setup();
    void update();
    void draw();
protected:
    ProcessFFT fft;
};
