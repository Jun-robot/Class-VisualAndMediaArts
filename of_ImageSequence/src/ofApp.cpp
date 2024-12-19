#include "ofApp.h"
#define takeMovie

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true); //垂直同期
    ofEnableAlphaBlending();
    ofBackground(100);
    
    gui.setup();
    gui.setPosition(50, 500);
    gui.add(backgroundColor.set("BGColor", ofColor(50,50,50), ofColor(0,0,0), ofColor(255,255,255)));
    gui.add(particleColor.set("particleColor", ofColor(240,240,240), ofColor(0,0,0), ofColor(255,255,255)));
    gui.add(radius.set("radius", 20.0, 0.0, 50.0));
    gui.add(particleNum.set("particleNum", 3, 0, 1000.0));
    gui.add(ledNum.set("ledNum", 3, 0, 30));
    gui.add(ledSpeed.set("ledSpeed", 0.15, 0.0, 0.3));
    gui.add(patSpeed.set("patSpeed", 0.7, 0.0, 3.0));
    gui.add(sendA.set("sendA", 3, 0, 60));
    gui.add(sendB.set("sendB", 3, 0, 60));
    gui.add(sendC.set("sendC", 3, 0, 60));
    gui.add(sendD.set("sendD", 3, 0, 60));

    fbo.allocate(mywidth, myheigh+50);
    
    serial.listDevices();
    serial.setup("/dev/tty.wchusbserial110", 115200);
    
    Particle tmp;
    tmp.setup(mywidth/2, myheigh/2, ofRandom(-3,3) , ofRandom(-3,3));
    p.push_back(tmp);
  
    exp.setup(mywidth,myheigh+50,60);//--ExportImageSequence--
    
#ifdef takeMovie
    //--ImageSequenceExport--
    //exp.setup(ofGetWidth(), ofGetHeight(), "png", GL_RGB, 4);
    //exp.setMaxThreads(6);
    
    //--ExportImageSequence-- rosetta2環境が必要
    exp.setOverwriteSequence(true);
    exp.setFrameRange(0,3000); //範囲, 指定しなければ全て
    exp.setOutputDir("aaa");
    //exp.setAutoExit(true);
    exp.startExport();
#endif

}

//--------------------------------------------------------------
void ofApp::update(){
    for(int n=0; n < p.size(); n++){
        p[n].setSpeedGain(patSpeed);
        p[n].setSpeedNoise();
        p[n].update();
        
        //境界条件 バウンダリーコンディション
        if(p[n].pos.x>mywidth||p[n].pos.x<0)p[n].speed.x*=-1.0;
        if(p[n].pos.y>myheigh||p[n].pos.y<0)p[n].speed.y*=-1.0;
    }
    for (int n = p.size()-1; n>=0; --n) {  // 後ろから順にチェック
        if (p[n].pos.x<30 && p[n].pos.y<30) {//左上
            p.erase(p.begin() + n);
            
            LED foo;
            foo.setup(0, ledSpeed);
            l.push_back(foo);
        }else if (p[n].pos.x>mywidth-30 && p[n].pos.y<30) {//右上
            p.erase(p.begin() + n);
            
            LED foo;
            foo.setup(60, -1.0 * ledSpeed);
            l.push_back(foo);
        }
    }
    particleNum = p.size();//デバッグ用
    ledNum = l.size();//デバッグ用
    
    
    for(int n=l.size()-1; n>=0; --n){
        l[n].update();
        if(l[n].speed>0 && l[n].pos>60){//右上
            l.erase(l.begin()+n);
            
            Particle tmp;
            tmp.setup(mywidth-40, 40, ofRandom(-3,0) , ofRandom(0,3));
            p.push_back(tmp);
        }else if(l[n].speed<0 && l[n].pos<-1.0){//左上
            l.erase(l.begin()+n);
            
            Particle tmp;
            tmp.setup(40, 40, ofRandom(0,3) , ofRandom(0,3));
            p.push_back(tmp);
        }
    }
    
    
    //fboを設定しますーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
    fbo.begin();
    ofClear(0,0,0);
    ofBackground(backgroundColor);
    
    for(int n=0; n < p.size(); n++){
        p[n].setColor(particleColor);
        
        ofSetColor(p[n].color);
        p[n].draw( radius );
        
//        for(int k=n; k<p.size(); k++){
//            float length = sqrt((p[n].pos.x - p[k].pos.x)*(p[n].pos.x - p[k].pos.x)
//            + abs(p[n].pos.y - p[k].pos.y)*abs(p[n].pos.y - p[k].pos.y));
//            if(length<400)ofDrawLine(p[n].pos.x, p[n].pos.y, p[k].pos.x, p[k].pos.y);
//        }
    }
    //LEDの表示用
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, myheigh+1, mywidth, 50);
    //LEDの場所を確認する
    for(int n=0; n<60; n++){
        LedArray[n] = 0;
    }
    for(int n=0; n<l.size(); n++){
        int a = l[n].getPos()%60;
        LedArray[a] = 1;
    }
    
    for(int n=0; n<60; n++){
        if(LedArray[n]==1){
            ofSetColor(100, 100, 100);
        }else{
            ofSetColor(0, 0, 0);
        }
        ofDrawRectangle(15*n, myheigh+1, 15, 50);
    }
    
    
    fbo.end();
    //fboの設定が終わりましたよーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
    
    
    
    int LedPos[60] = {0};
    int hoge=0;
    for(int n=0; n<60; n++){
        if(LedArray[n] == 1){
            LedPos[hoge] = n;
            hoge++;
        }
    }
    
    for(int n=0; n<4; n++){
        send[n] = LedPos[n];
    }
    
    
    // 通信
    serial.writeByte((unsigned char)250);
    for(int i=0; i<4; i++){
        if(send[i]==250)send[i]=251;
        serial.writeByte(send[i]);
    }
    //デバッグ用
    sendA = send[0];
    sendB = send[1];
    sendC = send[2];
    sendD = send[3];
}

//--------------------------------------------------------------
void ofApp::draw(){
    exp.begin();
    ofClear(0,0,0); //ofxExportImageSequenceの中でFBOが呼ばれている。
                    //FBOを使う時は、最初に真っ黒に塗り直さないといけない。
    fbo.draw(0,0);
    exp.end(); //保存
    
    fbo.draw(100,100); //表示
    
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
    tmp.setup(mywidth/2, myheigh/2, ofRandom(-3,3) , ofRandom(-3,3));
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
