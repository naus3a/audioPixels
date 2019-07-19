#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

#define PROGRAMMABLE_RENDERER

//========================================================================
int main( ){
#ifdef PROGRAMMABLE_RENDERER
    ofGLFWWindowSettings winSettings;
    winSettings.setGLVersion(4, 1);
    winSettings.setSize(1920, 1080);
    ofCreateWindow(winSettings);
#else
    ofAppGlutWindow win;
    ofSetupOpenGL(&win, 1920, 1080, OF_WINDOW);
#endif
    ofRunApp(new ofApp());
}
