#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofAppGLFWWindow setting;
    setting.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&setting, 3840, 1080, OF_FULLSCREEN);
    ofRunApp(new ofApp());
    
    //ofRunMainLoop();
}
