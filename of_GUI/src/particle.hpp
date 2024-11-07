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
    ofVec2f speed;
    ofColor color;
    float radius;
    
    //method
    void setup(int x, int y);
    void update();
    void draw();
};


#endif /* particle_hpp */
