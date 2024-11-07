#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    Particle tmp;
    tmp.setup(0);
    pA.push_back(tmp);
    tmp.setup(1);
    pB.push_back(tmp);
    
    serial.listDevices();
    serial.setup("/dev/tty.wchusbserial10", 230400);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    bool A_ue_flg = false;
    bool A_shita_flg = false;
    bool B_ue_flg = false;
    bool B_shita_flg = false;
    //メインディスプレイ側
    for(int n=0; n < pA.size(); n++){
        pA[n].update();
        //境界条件 バウンダリーコンディション
        if(pA[n].pos.x>2628||pA[n].pos.x<1115)pA[n].speed.x*=-1.0;
        if(pA[n].pos.y>982||pA[n].pos.y<0)pA[n].speed.y*=-1.0;
        
        if(pA[n].pos.x<1115 && pA[n].pos.y<0+200){

            pA[n].is = false;
            A_shita_flg = true;
        };
    }
    //ipad側
    for(int n=0; n < pB.size(); n++){
        pB[n].update();
        //境界条件 バウンダリーコンディション
        if(pB[n].pos.x>1115||pB[n].pos.x<0)pB[n].speed.x*=-1.0;
        if(pB[n].pos.y>982||pB[n].pos.y<162)pB[n].speed.y*=-1.0;
    }
    
    
    if(A_ue_flg){
        if(!ledFlg[0])ledFlg[0]=true;
        else if(!ledFlg[1])ledFlg[1]=true;
        A_ue_flg = false;
    }
    if(A_shita_flg){
        if(!ledFlg[2])ledFlg[2]=true;
        else if(!ledFlg[3])ledFlg[3]=true;
        A_shita_flg = false;
    }
    
    for(int i=0; i<4; i++){
        if(ledFlg[i]){
            ledNum[i]++;
            if(ledNum[i]==600){
                ledNum[i] = 0;
                ledFlg[i]=false;
            }
        }
    }
    
    
    for(int i=0; i<4; i++){
        send[i] = ledNum[0]/5;
    }
    
    serial.writeByte((unsigned char)250);
    for(int i=0; i<4; i++){
        if(send[i]==250)send[i]=251;
        serial.writeByte(send[i]);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(150,200,255);
    
    
    ofSetColor(255, 255, 255);
//    ofRect(0,162,1115,815);
    
//    printf("%d\n",ofGetHeight());
    
    for(int n=0; n < pA.size(); n++){
        ofSetColor(pA[n].color);
        pA[n].draw();
        for(int k=n; k<pA.size(); k++){
            float length = sqrt((pA[n].pos.x - pA[k].pos.x)*(pA[n].pos.x - pA[k].pos.x)
            + abs(pA[n].pos.y - pA[k].pos.y)*abs(pA[n].pos.y - pA[k].pos.y));
            if(length<400)ofDrawLine(pA[n].pos.x, pA[n].pos.y, pA[k].pos.x, pA[k].pos.y);
        }
    }
    for(int n=0; n < pB.size(); n++){
        ofSetColor(pB[n].color);
        pB[n].draw();
        for(int k=n; k<pB.size(); k++){
            float length = sqrt((pB[n].pos.x - pB[k].pos.x)*(pB[n].pos.x - pB[k].pos.x)
            + abs(pB[n].pos.y - pB[k].pos.y)*abs(pB[n].pos.y - pB[k].pos.y));
            if(length<400)ofDrawLine(pB[n].pos.x, pB[n].pos.y, pB[k].pos.x, pB[k].pos.y);
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
    if(selct){
        tmp.setup(0);
        pA.push_back(tmp);
    }else{
        tmp.setup(1);
        pB.push_back(tmp);
    }
    selct = !selct;
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
