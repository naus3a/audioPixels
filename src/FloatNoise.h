//
//  FloatNoise.h
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/22/19.
//

#pragma once
#include "ofMain.h"
#include "FloatRange.hpp"

class FloatNoise{
public:
    FloatNoise(){
        range = NULL;
        speed = 0.5;
        value = 0;
    }
    
    float update(){
        value = ofSignedNoise(ofGetElapsedTimef()*speed);
        if(range!=NULL){
            value *= range->getRange();
            value = range->getCenter()+value;
        }
        return value;
    }
    
    FloatRange * range;
    float speed;
protected:
    float value;
};
