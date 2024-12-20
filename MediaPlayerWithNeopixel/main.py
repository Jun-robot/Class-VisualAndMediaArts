import serial
import struct
from time import sleep
import cv2

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

led_list = [(0, 0, 0) for _ in range(60)]
def convert_led_list_to_array(led_list):
	return [value for rgb in led_list for value in rgb]

video_path = 'video2.mp4'  # ここに動画ファイルのパスを指定
cap = cv2.VideoCapture(video_path)
if not cap.isOpened():
	print("動画を開けませんでした。")
	exit()

cv2.namedWindow("CroppedVideo", cv2.WND_PROP_FULLSCREEN)
# cv2.setWindowProperty("CroppedVideo",cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_FULLSCREEN)

frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

while True:
		# 1フレームを読み込む
	ret, frame = cap.read()

	# フレームが正常に読み込めなかった場合（動画終了など）
	if not ret:
			print("動画の再生が終了しました。")
			break

	# フレームをカット（下100ピクセルをカット）q
	cropped_frame = frame[0:820, 0:frame_width]
	collor_frame = frame[820+1:frame_height, 0:frame_width]

	# カットしたフレームをウィンドウに表示
	cv2.imshow('CroppedVideo', cropped_frame)
	cv2.imshow('CollorVideo', collor_frame)


	for i in range(60):
		led_list[i] = collor_frame[10, 10+i*15]
		print(f"0={led_list[0]}, 1={led_list[1]}, 2={led_list[2]}")

	# 'q'キーで動画を停止
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break


	startbyte=[250] #スタートバイトは250
	send(startbyte)

	send_array = convert_led_list_to_array(led_list)
	for i in range(180):
		if send_array[i]<6:
			send_array[i]=0
	send(send_array)

	# sleep(0.015)

# 動画を解放してウィンドウを閉じる
cap.release()
cv2.destroyAllWindows()
