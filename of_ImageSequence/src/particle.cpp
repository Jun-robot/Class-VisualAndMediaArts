//
//  particle.cpp
//  of_GUI
//
//  Created by 齋藤淳平 on 2024/11/08.
//

#include "particle.hpp"

Particle::Particle(){
    
}

void Particle::setup(int x, int y, float speedX, float speedY, ofColor clr){
    pos.set(x, y);
//    speed.set(ofRandom(-3,3) , ofRandom(-3,3));
    speed.set(speedX, speedY);
    color.set(clr);
    setSpeedNoise();
    for(int n=0; n<posN; n++){
        prePos[n].set(pos.x, pos.y);
    }
}

void Particle::update(){
    float a = speed.x * speedNoise.x*gain;
    float b = speed.y * speedNoise.y*gain;
    pos.x += a;
    pos.y += b;
    //    pos += speed;
    
    for(int n=posN-1; 0<n; --n){
        prePos[n] = prePos[n-1];
    }
    prePos[0] = pos;
}

void Particle::setSpeedNoise(){
    speedNoise.set(ofNoise(ofRandom(0, 100.0)), ofNoise(ofRandom(0, 100.0)));
}


void Particle::setSpeedGain(float gain_){
    gain = gain_;
}

void Particle::draw(float rad){
    ofDrawCircle(pos.x, pos.y, rad);
    
//    ofSetColor(color);
//    for(int n=0; n<posN; n++){
//        ofDrawCircle(prePos[n].x, prePos[n].y, rad-n*0.22);
//    }
}
