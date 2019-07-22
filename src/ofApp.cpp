#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    pthXml = ofFilePath::join("xml","settings.xml");
    pm.setup(1280, 720);
    ai.setup();
    
    vid.setup(1280, 720);
    
    setupGui();
}

void ofApp::setupGui(){
    bGui = false;
    
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    gui->onButtonEvent(this, &ofApp::onBut);
    
    butSave = new ofxDatGuiButton("save");
    butLoad = new ofxDatGuiButton("load");
    
    sliAttRadius = new ofxDatGuiSlider("Attractor radius", 0,200, pm.attractor.getRadius());
    sliAttRadius->onSliderEvent(this, &ofApp::onSliAttRadius);
    
    sliAttForce = new ofxDatGuiSlider("Attractor force", 0,1000, pm.attractor.force);
    sliAttForce->onSliderEvent(this, &ofApp::onSliAttForce);
    
    sliHomForce = new ofxDatGuiSlider("Homing force", 0,1000, pm.homing);
    sliHomForce->onSliderEvent(this, &ofApp::onSliHomForce);
    
    sliDamp = new ofxDatGuiSlider("Force dampening", 0,1, pm.dampening);
    sliDamp->onSliderEvent(this, &ofApp::onSliDamp);
    
    //sliAttRadius = new ofxDatGuiSlider("Attractor radius", 0,200, pm.attractor.getRadius());
    //sliAttRadius->onSliderEvent(this, &ofApp::onSliAttRadius);
    
    sliFftMagStrX = new ofxDatGuiSlider("X strenght",0,1,pm.attractorMagnet.x.strength);
    sliFftMagStrY = new ofxDatGuiSlider("Y strenght",0,1,pm.attractorMagnet.y.strength);
    sliFftMagStrZ = new ofxDatGuiSlider("Z strenght",0,1,pm.attractorMagnet.z.strength);
    sliFftMagStrX->onSliderEvent(this, &ofApp::onSliFftMagStrX);
    sliFftMagStrY->onSliderEvent(this, &ofApp::onSliFftMagStrY);
    sliFftMagStrZ->onSliderEvent(this, &ofApp::onSliFftMagStrZ);
    
    sliFftRangeX = new ofxDatGuiSlider("Range X", 0, 1280, ai.fft.range.x.getRange());
    sliFftRangeY = new ofxDatGuiSlider("Range Y", 0, 720, ai.fft.range.y.getRange());
    sliFftRangeZ = new ofxDatGuiSlider("Range Z", 0, 720, ai.fft.range.z.getRange());
    sliFftRangeX->onSliderEvent(this, &ofApp::onSliFftRangeX);
    sliFftRangeY->onSliderEvent(this, &ofApp::onSliFftRangeY);
    sliFftRangeZ->onSliderEvent(this, &ofApp::onSliFftRangeZ);
    
    sliFftCtrX = new ofxDatGuiSlider("Ctr X", -640, 640, 1);
    sliFftCtrY = new ofxDatGuiSlider("Ctr Y", -360, 360, 1);
    sliFftCtrZ = new ofxDatGuiSlider("Ctr Z", -360, 360, 1);
    sliFftCtrX->onSliderEvent(this, &ofApp::onSliFftCtrX);
    sliFftCtrY->onSliderEvent(this, &ofApp::onSliFftCtrY);
    sliFftCtrZ->onSliderEvent(this, &ofApp::onSliFftCtrZ);
    
    gui->attachItem(butSave);
    gui->attachItem(butLoad);
    gui->addBreak();
    gui->addLabel("particles");
    gui->attachItem(sliAttRadius);
    gui->attachItem(sliAttForce);
    gui->attachItem(sliHomForce);
    gui->attachItem(sliDamp);
    gui->addBreak();
    gui->addLabel("FFT magnet");
    gui->attachItem(sliFftMagStrX);
    gui->attachItem(sliFftMagStrY);
    gui->attachItem(sliFftMagStrZ);
    gui->addBreak();
    gui->addLabel("FFT range");
    gui->attachItem(sliFftRangeX);
    gui->attachItem(sliFftRangeY);
    gui->attachItem(sliFftRangeZ);
    gui->addLabel("FFT center");
    gui->attachItem(sliFftCtrX);
    gui->attachItem(sliFftCtrY);
    gui->attachItem(sliFftCtrZ);
    
    gui->setVisible(false);
    
    load();
}

void ofApp::refreshGui(){
    sliAttRadius->setValue(pm.attractor.getRadius());
    sliAttForce->setValue(pm.attractor.force);
    sliHomForce->setValue(pm.homing);
    sliDamp->setValue(pm.dampening);
    sliFftMagStrX->setValue(pm.attractorMagnet.x.strength);
    sliFftMagStrY->setValue(pm.attractorMagnet.y.strength);
    sliFftMagStrZ->setValue(pm.attractorMagnet.z.strength);
    sliFftRangeX->setValue(ai.fft.range.x.getRange());
    sliFftRangeY->setValue(ai.fft.range.y.getRange());
    sliFftRangeZ->setValue(ai.fft.range.z.getRange());
    sliFftCtrX->setValue(ai.fft.range.x.getCenter());
    sliFftCtrY->setValue(ai.fft.range.y.getCenter());
    sliFftCtrZ->setValue(ai.fft.range.z.getCenter());
    
}

void ofApp::onBut(ofxDatGuiButtonEvent e){
    if(e.target==butSave){
        onButSave(e);
    }else if(e.target==butLoad){
        onButLoad(e);
    }
}

void ofApp::showGui(){
    if(bGui)return;
    bGui = true;
    gui->setVisible(bGui);
    refreshGui();
}

void ofApp::hideGui(){
    if(!bGui)return;
    bGui = false;
    gui->setVisible(bGui);
}

void ofApp::save(){
    ofxXmlSettings xml;
    xml.addTag("settings");
    xml.pushTag("settings");
    pm.save(xml);
    ai.save(xml);
    xml.popTag();
    xml.save(pthXml);
}

void ofApp::load(){
    ofxXmlSettings xml;
    if(xml.load(pthXml)){
        if(xml.tagExists("settings")){
            xml.pushTag("settings");
            pm.load(xml);
            ai.load(xml);
            xml.popTag();
            refreshGui();
        }else{
            ofLogError("malformed xml: no settings tag");
        }
    }else{
        ofLogError("cannot load "+pthXml);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    vid.update();
    ai.update();
    if(vid.isFrameNew()){
        pm.beginFrame();
        vid.draw(0, 0, 1280, 720);
        pm.endFrame();
    }
    pm.attractorMagnet.x.value = ai.fft.loudestBandToX();
    pm.attractorMagnet.z.value = ai.fft.loudestBandValueToZ();
    pm.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    pm.draw();
    if(bGui)pm.drawDebug();
    //ofDisableBlendMode();
    //ofDrawBox(0, 0, 0, 100, 100, 100);
    cam.end();
    if(bGui)ai.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'g':
            toggleGui();
            break;
        case 's':
            save();
            break;
        case 'l':
            load();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
