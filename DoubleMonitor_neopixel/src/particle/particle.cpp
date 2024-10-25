#include "particle.h"

Particle::Particle(int _dir, int _speed){
		re_dir = _dir;
		re_spe = _speed;
}

void Particle::setup(){
	if(re_dir==10){
		pos = 0;
		speed = re_spe;
	}else if(re_dir==20){
		pos = 6000;
		speed = -re_spe;
	}
}

void Particle::update(){
    pos += speed;
    
    //境界条件を入れるべきか否か（哲学的な話）
    //このパーティクルたちは知覚できているのか
    //神の目が必要だとしたら（知覚できていない）ofAppのほうでやるべき
}

void Particle::draw(){
		
}

int Particle::get_pos(){
		return pos;
}
