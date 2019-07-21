//
//  Vec3Magnet.h
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/21/19.
//

#pragma once
#include "FloatMagnet.h"

class Vec3Magnet{
public:
    Vec3Magnet(){}
    Vec3Magnet(FloatMagnet _x, FloatMagnet _y, FloatMagnet _z){x=_x;y=_y;z=_z;}
    
    void update(){
        x.update();
        y.update();
        z.update();
    }
    
    FloatMagnet x;
    FloatMagnet y;
    FloatMagnet z;
};

