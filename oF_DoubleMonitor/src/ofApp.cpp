#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    Particle tmp;
    tmp.setup();
    p.push_back(tmp);
    
    serial.listDevices();
    serial.setup("/dev/tty.wchusbserial210", 230400);
    
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
    //ofSetColor(255, 255, 255);
    
    for(int n=0; n < p.size(); n++){
        ofSetColor(p[n].color);
        p[n].draw();
        
        for(int k=n; k<p.size(); k++){
            float length = sqrt((p[n].pos.x - p[k].pos.x)*(p[n].pos.x - p[k].pos.x)
            + abs(p[n].pos.y - p[k].pos.y)*abs(p[n].pos.y - p[k].pos.y));
            if(length<400)ofDrawLine(p[n].pos.x, p[n].pos.y, p[k].pos.x, p[k].pos.y);
        }
    }
    
    
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
    Particle tmp;
    tmp.setup();
    p.push_back(tmp);
    
    
    hoge++;
    send[0] = hoge;
    send[1] = 59-hoge;
    send[2] = 20+hoge;
    send[3] = 30-hoge;
    
    serial.writeByte((unsigned char)250);
    for(int i=0; i<4; i++){
        if(send[i]==250)send[i]=251;
        serial.writeByte(send[i]);
    }
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
