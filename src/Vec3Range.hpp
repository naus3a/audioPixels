//
//  Vec3Range.hpp
//  audioPixels
//
//  Created by enrico<naus3a>viola on 7/21/19.
//

#pragma once
#include "ofMain.h"
#include "FloatRange.hpp"
#include "ofxXmlSettings.h"

class Vec3Range{
public:
    Vec3Range(){}
    Vec3Range(FloatRange _x, FloatRange _y, FloatRange _z){set(_x, _y, _z);}
    void set(FloatRange _x, FloatRange _y, FloatRange _z){x=_x; y=_y; z=_z;}
    
    void save(ofxXmlSettings & _xml){
        _xml.addTag("range");
        _xml.pushTag("range");
        saveRangeTag(_xml, "x", x);
        saveRangeTag(_xml, "y", y);
        saveRangeTag(_xml, "z", z);
        _xml.popTag();
    }
    
    void load(ofxXmlSettings & _xml){
        if(_xml.tagExists("range")){
            _xml.pushTag("range");
            loadRangeTag(_xml, "x", x);
            loadRangeTag(_xml, "y", y);
            loadRangeTag(_xml, "z", z);
            _xml.popTag();
        }else{
            ofLogError("Vec3Range::load", "no range tag");
        }
    }
    
    void saveRangeTag(ofxXmlSettings & _xml, string _tagName, FloatRange & _fr){
        _xml.addTag(_tagName);
        _xml.addAttribute(_tagName, "min", _fr.min,0);
        _xml.addAttribute(_tagName, "max", _fr.max,0);
    }
    
    void loadRangeTag(ofxXmlSettings & _xml, string _tagName, FloatRange & _fr){
        _fr.min = _xml.getAttribute(_tagName, "min", _fr.min, 0);
        _fr.max = _xml.getAttribute(_tagName, "max", _fr.max, 0);
    }
    
    FloatRange x;
    FloatRange y;
    FloatRange z;
};
