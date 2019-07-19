//
//  FftManager.cpp
//  audioPixels
//
//  Created by naus3a on 7/19/19.
//

#include "FftManager.hpp"

void FftManager::setup(){
    fft.setup();
}

void FftManager::update(){
    fft.update();
}

void FftManager::draw(){
    fft.drawBars();
    fft.drawDebug();
}
