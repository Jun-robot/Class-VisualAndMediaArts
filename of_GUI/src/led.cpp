//
//  led.cpp
//  of_GUI
//
//  Created by 齋藤淳平 on 2024/11/08.
//

#include "led.hpp"

LED::LED(){
    
}

void LED::setup(int x, float myspeed){
    pos = x;
    speed = myspeed;
    color.set(0,0,0);
}

void LED::update(){
    pos += speed;
    
    //境界条件を入れるべきか否か（哲学的な話）
    //このパーティクルたちは知覚できているのか
    //神の目が必要だとしたら（知覚できていない）ofAppのほうでやるべき
}

int LED::getPos(){
    return (int)pos;
}
