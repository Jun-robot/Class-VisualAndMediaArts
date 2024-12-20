#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "particle.hpp"
#include "led.hpp"

//#include "ofxImageSequenceExport.h"
#include "ofxExportImageSequence.h"

class ofApp : public ofBaseApp{
    
    public:
        void setup() override;
        void update() override;
        void draw() override;
        void exit() override;
        
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void mouseMoved(int x, int y ) override;
        void mouseDragged(int x, int y, int button) override;
        void mousePressed(int x, int y, int button) override;
        void mouseReleased(int x, int y, int button) override;
        void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
        void mouseEntered(int x, int y) override;
        void mouseExited(int x, int y) override;
        void windowResized(int w, int h) override;
        void dragEvent(ofDragInfo dragInfo) override;
        void gotMessage(ofMessage msg) override;
    
    ofxExportImageSequence exp;
    bool takeMovie=true;
    
    vector<Particle> p;
    
    //LED
    int LedArray[60]={0};
    vector<LED> l;
    
    //GUI
    ofxPanel gui;
    ofParameter<ofColor> backgroundColor;
    ofParameter<ofColor> particleColor;
    ofParameter<float> radius;
    ofParameter<int> particleNum;
    ofParameter<int> ledNum;
    ofParameter<float> ledSpeed;
    ofParameter<float> patSpeed;
    ofParameter<unsigned char> sendA;
    ofParameter<unsigned char> sendB;
    ofParameter<unsigned char> sendC;
    ofParameter<unsigned char> sendD;
    
    //FrameBufferObject
    ofFbo fbo;
//    int mywidth = 1116; //1512;
    int mywidth = 1180;
    int myheigh = 820; //982;
    
    //Serial
    ofSerial serial;
    unsigned char send[4]={0};
    
};
