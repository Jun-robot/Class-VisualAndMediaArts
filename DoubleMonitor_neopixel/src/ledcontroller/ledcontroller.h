#ifndef ledcontroller_hpp
#define ledcontroller_hpp

#include <Arduino.h>
#include <FastLED.h>

class LEDController {
public:
	LEDController(int pinA, int pinB, int pinC, int num_leds) {
		DATA_PIN_A = pinA;
		DATA_PIN_B = pinB;
		DATA_PIN_C = pinC;
		NUM_LEDS = num_leds;
	}

	void init() {
		FastLED.addLeds<SK6812, DATA_PIN_A, RGB>(ledA, NUM_LEDS);
		FastLED.addLeds<SK6812, DATA_PIN_B, RGB>(ledB, NUM_LEDS);
		FastLED.addLeds<SK6812, DATA_PIN_C, RGB>(ledC, 40);
		FastLED.clear();
		FastLED.show();
	}

	void set(int tape_n, int num, int H, int S, int V) {
		num %= 60;
		if (tape_n == 0) {
			ledA[num] = CHSV(H, S, V);
			ledA[119 - num] = CHSV(H, S, V);
		} else if (tape_n == 1) {
			ledB[num] = CHSV(H, S, V);
			ledB[119 - num] = CHSV(H, S, V);
		}
	}

	void setAll(int Hue, int Sat, int Bri) {
		for (int tape_num = 0; tape_num < 2; tape_num++) {
			for (int led_num = 0; led_num < 60; led_num++) {
				set(tape_num, led_num, Hue, Sat, Bri);
			}
		}
	}

	void show() {
		FastLED.show();
	}

private:
	int DATA_PIN_A;
	int DATA_PIN_B;
	int DATA_PIN_C;
	int NUM_LEDS;
	
	CRGB ledA[60];
	CRGB ledB[60];
	CRGB ledC[40];
};


#endif