#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    
    settings.multiMonitorFullScreen = true;
    settings.windowMode = OF_FULLSCREEN;
    auto window = ofCreateWindow(settings);
    
//    ofSetupOpenGL(&setting, 38 40, 1080, OF_FULLSCREEN);
//    ofSetupOpenGL(&setting, 840, 480, OF_WINDOW);
    ofRunApp(window, std::make_shared<ofApp>());
    ofRunMainLoop();
}
