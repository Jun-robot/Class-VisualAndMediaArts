//
//  particle.cpp
//  of_GUI
//
//  Created by 齋藤淳平 on 2024/11/08.
//

#include "particle.hpp"

Particle::Particle(){
    
}

void Particle::setup(int x, int y){
    pos.set(x, y);
    speed.set(ofRandom(-3,3), ofRandom(-3,3));
    color.set(0,0,0);
}

void Particle::update(){
    pos += speed;
    
    //境界条件を入れるべきか否か（哲学的な話）
    //このパーティクルたちは知覚できているのか
    //神の目が必要だとしたら（知覚できていない）ofAppのほうでやるべき
}

void Particle::setColor(ofColor mycolor){
    mycolor.a = 220;
    color.set(mycolor);
}

void Particle::draw(float rad){
    ofDrawCircle(pos.x, pos.y, rad);
}
