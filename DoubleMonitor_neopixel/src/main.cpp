#include <Arduino.h>
#include <HardwareSerial.h>

#define VERSION 1.00

#include "./ser_ctrl/ser_ctrl.h"
HardwareSerial ctrl(1);
CTRL ser_ctrl(&Serial);  

#include <FastLED.h>
#define DATA_PIN_A 32
#define DATA_PIN_B 33
#define DATA_PIN_C 27 //circuit
#define NUM_LEDS 120
CRGB ledA[NUM_LEDS];
CRGB ledB[NUM_LEDS];
CRGB ledC[40];


void setup() {
	ser_ctrl.init();
	
	FastLED.addLeds<SK6812, DATA_PIN_A, RGB>(ledA, NUM_LEDS);
	FastLED.addLeds<SK6812, DATA_PIN_B, RGB>(ledB, NUM_LEDS);
	FastLED.addLeds<SK6812, DATA_PIN_C, RGB>(ledC, 40);

	pinMode(35, INPUT); //mic
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);
	delay(1000);
}

void led_set(int tape_n, int num, int H, int S, int V);
void led_set_high(int High, int Hue, int Sat, int Bri);
void led_set_all(int Hue, int Sat, int Bri);
void led_set_star(int High, int Hue, int Sat, int Bri, bool isDown);
void led_set_band(int center, int width, int Hue, int Sat, int Bri);

int t=0;
byte mydata = 0;

void loop() {
	ser_ctrl.read();

	t++;
	for(int i=0; i<60; i++){
		led_set(0, i, (t+i*4)%255, 255, 55);
		led_set(1, i, (t+i*4+120)%255, 255, 55);
		// ledA[i] = CHSV(255, 150, 15);
	}

	led_set(0, ser_ctrl.data[0], 0, 0, 255);

	FastLED.show();
	delay(10);
}




void led_set(int tape_n, int num, int H, int S, int V){
	num%=60;
	if(tape_n==0){
		ledA[num] = CHSV(H,S,V);
		ledA[119-num] = CHSV(H,S,V);
	}else if(tape_n==1){
		ledB[num] = CHSV(H,S,V);
		ledB[119-num] = CHSV(H,S,V);
	}
}

void led_set_high(int High, int Hue, int Sat, int Bri){
	for(int num=0;num<58;num++){
		if(num<High){
			for(int tape_num=0; tape_num<6; tape_num++){
				led_set(tape_num, num, Hue, Sat, Bri);
			}
		}
	}
}


void led_set_all(int Hue, int Sat, int Bri){
	for(int tape_num=0;tape_num<6;tape_num++){
		for(int led_num=0; led_num<58;led_num++){
			led_set(tape_num, led_num, Hue, Sat, Bri);
		}
	}
}



void led_set_star(int High, int Hue, int Sat, int Bri, bool isDown){
	if(isDown == 0){
		for(int tape_num=0; tape_num<6; tape_num++){
			led_set(tape_num, High, Hue, Sat, Bri);
			led_set(tape_num, High-1, Hue, Sat*0.7, Bri*0.7);
			led_set(tape_num, High-2, Hue, Sat*0.5, Bri*0.5);
			led_set(tape_num, High-3, Hue, Sat*0.3, Bri*0.3);
			led_set(tape_num, High-4, Hue, Sat*0.1, Bri*0.2);
		}
	}else{
		for(int tape_num=0; tape_num<6; tape_num++){
			led_set(tape_num, High, Hue, Sat, Bri);
			led_set(tape_num, High+1, Hue, Sat*0.7, Bri*0.7);
			led_set(tape_num, High+2, Hue, Sat*0.5, Bri*0.5);
			led_set(tape_num, High+3, Hue, Sat*0.3, Bri*0.3);
			led_set(tape_num, High+4, Hue, Sat*0.1, Bri*0.2);
		}
	}
}


void led_set_band(int center, int width, int Hue, int Sat, int Bri){
	int myfrom = center - width/2;
	int myto = center + width/2;
	for(int tape_num=0; tape_num<6; tape_num++){
		for(int led_num=myfrom; led_num<=myto; led_num++){
			led_set(tape_num, led_num, Hue, Sat, Bri);
		}
	}
}

