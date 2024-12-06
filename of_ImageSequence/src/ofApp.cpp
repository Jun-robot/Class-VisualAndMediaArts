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
    
    Particle tmp;
    tmp.setup();
    p.push_back(tmp);
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int n=0; n < p.size(); n++){
        p[n].update();
        //境界条件 バウンダリーコンディション
        if(p[n].pos.x>ofGetWidth()||p[n].pos.x<0)p[n].speed.x*=-1.0;
        if(p[n].pos.y>ofGetHeight()||p[n].pos.y<0)p[n].speed.y*=-1.0;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    exp.begin();
    ofClear(0,0,0); //ofxExportImageSequenceの中でFBOが呼ばれている。
                    //FBOを使う時は、最初に真っ黒に塗り直さないといけない。
    
    ofSetColor(255, 255, 255);
    for(int n=0; n < p.size(); n++){
        ofSetColor(p[n].color);
        p[n].draw();
        
        for(int k=n; k<p.size(); k++){
            float length = sqrt((p[n].pos.x - p[k].pos.x)*(p[n].pos.x - p[k].pos.x)
            + abs(p[n].pos.y - p[k].pos.y)*abs(p[n].pos.y - p[k].pos.y));
            if(length<400)ofDrawLine(p[n].pos.x, p[n].pos.y, p[k].pos.x, p[k].pos.y);
        }
    }
//    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, radius);
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
