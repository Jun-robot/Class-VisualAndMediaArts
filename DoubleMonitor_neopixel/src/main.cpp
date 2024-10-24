#include <Arduino.h>
#include <HardwareSerial.h>

#define VERSION 1.00

#include "./ser_ctrl/ser_ctrl.h"
HardwareSerial ctrl(2);
CTRL ser_ctrl(&ctrl);  

// #include "./power/power.h"
// #define VOL_PIN 32 //これ、無線機能のピンとかぶってるから注意
// #define VOL_MAX 12.6
// #define VOL_MIN 11.1
// POWER power(VOL_PIN, VOL_MAX, VOL_MIN);


#include <FastLED.h>
#define DATA_PIN_A 32
#define DATA_PIN_B 13
#define DATA_PIN_C 27 //circuit
#define NUM_LEDS 120
CRGB ledA[NUM_LEDS];
CRGB ledB[NUM_LEDS];
CRGB ledC[40];


void setup() {
	Serial.begin(115200);
	Serial.println("Hello World");
	Serial.println("Version: " + String(VERSION));
	
	FastLED.addLeds<SK6812, DATA_PIN_A, RGB>(ledA, NUM_LEDS);
	FastLED.addLeds<SK6812, DATA_PIN_B, RGB>(ledB, NUM_LEDS);
	FastLED.addLeds<SK6812, DATA_PIN_C, RGB>(ledC, 40);

	ser_ctrl.init();
	pinMode(35, INPUT); //mic
}

void led_set(int tape_n, int num, int H, int S, int V);
void led_set_high(int High, int Hue, int Sat, int Bri);
void led_set_all(int Hue, int Sat, int Bri);
void led_set_star(int High, int Hue, int Sat, int Bri, bool isDown);
void led_set_band(int center, int width, int Hue, int Sat, int Bri);

int t =0;

void loop() {

	t++;
	for(int i=0; i<NUM_LEDS; i++){
		ledA[i] = CHSV((t+i*2)%255, 255, 55);
	}
	FastLED.show();

	//　受信するよ 
	ser_ctrl.read();
	for(int i=7; i<11; i++){
		Serial.print(ser_ctrl.data[i]);
		Serial.print(" ");
	}
	Serial.println();

	delay(30);

}




void led_set(int tape_n, int num, int H, int S, int V){
	bool oddflg = false;
	if(tape_n == 0){
		tape_n = 0;
	}else if(tape_n == 1){
		tape_n = 0;
		oddflg = true;
	}else if(tape_n == 2){
		tape_n = 1;
	}else if(tape_n == 3){
		tape_n = 1;
		oddflg = true;
	}else if(tape_n == 4){
		tape_n = 2;
	}else if(tape_n == 5){
		tape_n = 2;
		oddflg = true;
	}
	if(0<=num && num<=57){
		// if(!oddflg){
		// 		tape_led[tape_n].setPixel_hsv(num,H,S,V);
		// }else{
		// 		tape_led[tape_n].setPixel_hsv(115-num,H,S,V);
		// }
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

