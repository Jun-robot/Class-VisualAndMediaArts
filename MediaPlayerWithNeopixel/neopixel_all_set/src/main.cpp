#include <Arduino.h>
#include <HardwareSerial.h>

#define VERSION 1.00

#include "./ser_ctrl/ser_ctrl.h"
// HardwareSerial ctrl(1);
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
	Serial.setRxBufferSize(512);
	
	FastLED.addLeds<SK6812, DATA_PIN_A, GRB>(ledA, NUM_LEDS);
	FastLED.addLeds<SK6812, DATA_PIN_B, GRB>(ledB, NUM_LEDS);
	FastLED.addLeds<SK6812, DATA_PIN_C, GRB>(ledC, 40);

	pinMode(35, INPUT); //mic
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);
	delay(1000);
}

void led_set(int tape_n, int num, int H, int S, int V);
void led_set_rgb(int tape_n, int num, int R, int G, int B);
void led_set_all(int Hue, int Sat, int Bri);

void loop() {
	ser_ctrl.read();

	led_set_all(0,0,0);

	for(int i=0; i<60; i++){

		led_set_rgb(0, i, ser_ctrl.data[i*3], ser_ctrl.data[i*3+1], ser_ctrl.data[i*3+2]);

		// if(ser_ctrl.data[i]!=0){
		// 	if(i<2)led_set(0, ser_ctrl.data[i], 0, 0, 255);
		// 	else led_set(1, ser_ctrl.data[i], 0, 0, 255);
		// }
		// if(ser_ctrl.data[i]!=0){
		// 	led_set(0, ser_ctrl.data[i], 0, 0, 255);
		// }
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

void led_set_rgb(int tape_n, int num, int R, int G, int B) {
	num %= 60; // numを60で割った余りにする
	if (tape_n == 0) {
		ledA[num] = CRGB(R, G, B);          // 左側
		ledA[119 - num] = CRGB(R, G, B);   // 対称位置
	} else if (tape_n == 1) {
		ledB[num] = CRGB(R, G, B);         // 左側
		ledB[119 - num] = CRGB(R, G, B);  // 対称位置
	}
}

void led_set_all(int Hue, int Sat, int Bri){
	for(int tape_num=0;tape_num<2;tape_num++){
		for(int led_num=0; led_num<60;led_num++){
			led_set(tape_num, led_num, Hue, Sat, Bri);
		}
	}
}


