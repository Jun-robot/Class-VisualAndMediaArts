//
//  led.hpp
//  of_GUI
//
//  Created by 齋藤淳平 on 2024/11/08.
//

#ifndef led_hpp
#define led_hpp

#include <stdio.h>
//#include "ofApp.h" これは循環参照になる、
#include "ofMain.h"

class LED{
public:
    LED(); //constructor
    
    //member
    float pos;
    float speed;
    ofColor color;
    
    //method
    void setup(int x, float speed);
    void update();
    int getPos();
};
#endif /* led_hpp */
