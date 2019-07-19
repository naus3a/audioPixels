//
//  Attractor.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/19/19.
//

#pragma once
#include "ofMain.h"

class Attractor{
public:
    Attractor(){init();}
    Attractor(ofVec3f _pos, float _r){init();set(_pos, _r);}
    
    void draw(){
        ofPushStyle();
        ofSetColor(ofColor::yellow);
        ofPushMatrix();
        ofTranslate(position);
        ofScale(radius);
        msh.drawWireframe();
        ofPopMatrix();
        ofPopStyle();
    }
    
    void set(ofVec3f _pos, float _r){
        position = _pos;
        setRadius(_r);
    }
    
    void setRadius(float _r){
        radius = _r;
        radiusSq = radius*radius;
    }
    
    float getRadius(){return radius;}
    float getRadiusSquared(){return radiusSq;}
    
    ofVec3f position;
    float force;
protected:
    void init(){msh.set(1,5);force=500;}
    
    ofSpherePrimitive msh;
    float radius;
    float radiusSq;
};
