#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(100,100,100);
    
    gui.setup();
    gui.setPosition(50, 500);
    gui.add(backgroundColor.set("BGColor", ofColor(0,0,0),ofColor(0,0,0), ofColor(255,255,255)));

    fbo.allocate(mywidth, myheigh);
    
    serial.listDevices();
    serial.setup("/dev/tty.wchusbserial210", 115200);
    
    Particle tmp;
    tmp.setup(mywidth/2, myheigh/2);
    p.push_back(tmp);
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int n=0; n < p.size(); n++){
        p[n].update();
        //境界条件 バウンダリーコンディション
        if(p[n].pos.x>mywidth||p[n].pos.x<0)p[n].speed.x*=-1.0;
        if(p[n].pos.y>myheigh||p[n].pos.y<0)p[n].speed.y*=-1.0;
    }
    
    
    //fboを設定しますーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
    fbo.begin();
    ofClear(0,0,0);
    ofBackground(100, 200, 100);
    ofSetColor(backgroundColor);
    
    ofDrawCircle(mywidth/2, myheigh/2, 100);
    
    for(int n=0; n < p.size(); n++){
        ofSetColor(p[n].color);
        p[n].draw();
        
        for(int k=n; k<p.size(); k++){
            float length = sqrt((p[n].pos.x - p[k].pos.x)*(p[n].pos.x - p[k].pos.x)
            + abs(p[n].pos.y - p[k].pos.y)*abs(p[n].pos.y - p[k].pos.y));
            if(length<400)ofDrawLine(p[n].pos.x, p[n].pos.y, p[k].pos.x, p[k].pos.y);
        }
    }
    
    fbo.end();
    //fboの設定が終わりましたよーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
    
    
    
    // 通信
    send[0]++;
    serial.writeByte((unsigned char)250);
    for(int i=0; i<4; i++){
        if(send[i]==250)send[i]=251;
        serial.writeByte(send[i]);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(backgroundColor);
    fbo.draw(100, 100);
    gui.draw();
    
    fbo.draw(1512,162);
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
    tmp.setup(mywidth/2, myheigh/2);
    p.push_back(tmp);
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
