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
void led_set_all(int Hue, int Sat, int Bri);

void loop() {
	ser_ctrl.read();

	led_set_all(200,200,20);

	for(int i=0; i<4; i++){
		if(ser_ctrl.data[i]!=0){
			if(i<2)led_set(0, ser_ctrl.data[i], 0, 0, 255);
			else led_set(1, ser_ctrl.data[i], 0, 0, 255);
		}
	}

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


void led_set_all(int Hue, int Sat, int Bri){
	for(int tape_num=0;tape_num<2;tape_num++){
		for(int led_num=0; led_num<60;led_num++){
			led_set(tape_num, led_num, Hue, Sat, Bri);
		}
	}
}


