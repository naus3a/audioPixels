//
//  FloatRange.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/21/19.
//

#pragma once
#include "ofMain.h"

class FloatRange{
public:
    FloatRange(){}
    FloatRange(float _min, float _max){set(_min, _max);}
    void set(float _min, float _max){min=_min;max=_max;}
    float getRange(){return (max-min);}
    float getPctInRange(float _pct){return ofMap(_pct,0,1,min,max);}
    float min;
    float max;
};
