//
//  particle.hpp
//  of_GUI
//
//  Created by 齋藤淳平 on 2024/11/08.
//

#ifndef particle_hpp
#define particle_hpp

#include <stdio.h>

//#include "ofApp.h" これは循環参照になる、
#include "ofMain.h"

class Particle{
public:
    Particle(); //constructor
    
    //member
    ofVec2f pos;
    int posN=60;
    ofVec2f prePos[60];
    ofVec2f speed;
    ofVec2f speedNoise;
    ofColor color;
    float gain;
    
    //method
    void setup(int x, int y, float speedX, float speedY);
    void update();
    void setSpeedNoise();
    void setSpeedGain(float _gain);
    void draw(float rad);
    void setColor(ofColor mycolor);
};


#endif /* particle_hpp */
