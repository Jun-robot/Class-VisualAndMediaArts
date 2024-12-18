//
//  particle.cpp
//  oF_fukusyuu
//
//  Created by 齋藤淳平 on 2024/10/11.
//

#include "particle.hpp"

Particle::Particle(){
    
}

void Particle::setup(){
    pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    speed.set(ofRandom(-3,3), ofRandom(-3,3));
    radius = 5;
    color.set(100,100,ofRandom(0,255));
}

void Particle::update(){
    pos += speed;
    
    //境界条件を入れるべきか否か（哲学的な話）
    //このパーティクルたちは知覚できているのか
    //神の目が必要だとしたら（知覚できていない）ofAppのほうでやるべき
}

void Particle::draw(){
    ofDrawCircle(pos.x, pos.y, radius);
}
