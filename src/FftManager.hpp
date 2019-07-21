//
//  FftManager.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/19/19.
//

#pragma once
#include "ofMain.h"
#include "Fft.hpp"
#include "Vec3Range.hpp"

class FftManager{
public:
    FftManager();
    void setup();
    void update();
    void draw();
    
    float getBandIdPct(int _bId);
    float getNormalizedBand(int _bId);
    float loudestBandToX();
    float loudestBandValueToZ();
    
    Vec3Range range;
protected:
    void drawBars();
    
    Fft fft;
};
