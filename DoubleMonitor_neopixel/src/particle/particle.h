#ifndef particle_hpp
#define particle_hpp

#include <Arduino.h>

// #include <stdio.h>


class Particle{
public:
    Particle(int _dir, int _speed); //constructor
    
    //member
		int re_dir;
		int re_spe;

    unsigned int pos;
    unsigned int speed;
    
    //method
    void setup();
    void update();
    void draw();
		int get_pos();
};


#endif /* particle_hpp */