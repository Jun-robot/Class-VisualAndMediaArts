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

i=0
while True:
	startbyte=[250] #スタートバイトは250
	send(startbyte)
	i+=1
	mylist = list(range(180))

	mylist[0]=(30+i)%60
	mylist[1]=(42+i)%60
	mylist[2]=(53+i)%60
	mylist[3]=(21+i)%60
	send(mylist)
	# sleep(0.016)
	print("a")
	sleep(0.015)

