//
//  Vec3Range.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/21/19.
//

#pragma once
#include "ofMain.h"
#include "FloatRange.hpp"

class Vec3Range{
public:
    Vec3Range(){}
    Vec3Range(FloatRange _x, FloatRange _y, FloatRange _z){set(_x, _y, _z);}
    void set(FloatRange _x, FloatRange _y, FloatRange _z){x=_x; y=_y; z=_z;}
    FloatRange x;
    FloatRange y;
    FloatRange z;
};
