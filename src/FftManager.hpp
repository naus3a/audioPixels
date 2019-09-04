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
    void setup(int _devId=0);
    void update();
    void draw();
    
    void setDeviceId(int _devId){fft.setDevId(_devId);}
    
    float getBandIdPct(int _bId);
    float getNormalizedBand(int _bId);
    float loudestBandToX();
    float loudestBandValueToZ();
    
    Vec3Range range;
protected:
    void drawBars();
    
    Fft fft;
};
