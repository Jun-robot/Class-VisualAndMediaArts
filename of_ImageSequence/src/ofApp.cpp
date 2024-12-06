#include "ofApp.h"
#define takeMovie

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true); //垂直同期
    ofEnableAlphaBlending();
    ofBackground(22);
  
    exp.setup(1024,768,60);//--ExportImageSequence--
    
#ifdef takeMovie
    //--ImageSequenceExport--
    //exp.setup(ofGetWidth(), ofGetHeight(), "png", GL_RGB, 4);
    //exp.setMaxThreads(6);
    
    //--ExportImageSequence-- rosetta2環境が必要
    exp.setOverwriteSequence(true);
    exp.setFrameRange(0,300); //範囲, 指定しなければ全て
    exp.setOutputDir("aaa");
    //exp.setAutoExit(true);
    exp.startExport();
#endif

}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    exp.begin();
    ofClear(0,0,0); //ofxExportImageSequenceの中でFBOが呼ばれている。
                    //FBOを使う時は、最初に真っ黒に塗り直さないといけない。
    
    ofSetColor(255, 255, 255);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 100*sin(++cnt/60.0));
    
    exp.end(); //保存
    exp.draw(0,0); //表示
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
