#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofAppGLFWWindow setting;
    setting.setMultiDisplayFullscreen(true);
//    ofSetupOpenGL(&setting, 3840, 1080, OF_FULLSCREEN);
    ofSetupOpenGL(&setting, 840, 480, OF_WINDOW);
    ofRunApp(new ofApp());
    
    //ofRunMainLoop();
}
