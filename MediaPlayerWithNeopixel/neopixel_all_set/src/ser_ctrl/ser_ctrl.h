#ifndef _H_CTRL_
#define _H_CTRL_

#include <Arduino.h>
#include <HardwareSerial.h>

class CTRL{
	private:
		HardwareSerial* SER;

	public:
		CTRL(HardwareSerial* ptr_serial);

		void init(void);
		void read(void);


		int data_num = 180;
		byte data[180] = {0};

};

#endif