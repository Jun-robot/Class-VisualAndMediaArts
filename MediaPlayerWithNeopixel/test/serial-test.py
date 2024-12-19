import serial
import struct
from time import sleep

def send( buf ):
	while True:
		if ser.out_waiting == 0: #送信待ちのデータが0になるのを確認
			break
	for b in buf:
		a = struct.pack("B", b) #符号なし8ビットのバイナリ形式にする
		ser.write(a) #1byte送信する
	ser.flush() #全て送信するまで待機

ser = serial.Serial(
	port = "/dev/cu.wchusbserial110",
	baudrate = 115200,
	parity = serial.PARITY_NONE,
	bytesize = serial.EIGHTBITS,
	stopbits = serial.STOPBITS_ONE,
	#timeout = None,
	#xonxoff = 0,
	#rtscts = 0,
)


led_list = [(35, 10, 30) for _ in range(60)]

def convert_led_list_to_array(led_list):
	return [value for rgb in led_list for value in rgb]

while True:
	startbyte=[250] #スタートバイトは250
	send(startbyte)
	send(convert_led_list_to_array(led_list))

	print("a")
	sleep(0.015)

