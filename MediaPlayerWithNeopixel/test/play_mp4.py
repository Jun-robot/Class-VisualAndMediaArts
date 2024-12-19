import cv2

# 動画ファイルのパス
video_path = 'video.mp4'  # ここに動画ファイルのパスを指定

# 動画ファイルを開く
cap = cv2.VideoCapture(video_path)

# 動画が正しく開けたか確認
if not cap.isOpened():
		print("動画を開けませんでした。")
		exit()

# 動画のフレームサイズを取得
frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

# カットする部分の設定
# 下部分をカットするために、例えば 100px をカットするとする
crop_height = frame_height - 100  # 下100ピクセルをカット

# 動画の再生
while True:
		# 1フレームを読み込む
		ret, frame = cap.read()

		# フレームが正常に読み込めなかった場合（動画終了など）
		if not ret:
				print("動画の再生が終了しました。")
				break

		# フレームをカット（下100ピクセルをカット）q
		cropped_frame = frame[0:crop_height, 0:frame_width]
		collor_frame = frame[crop_height:frame_height, 0:frame_width]

		# カットしたフレームをウィンドウに表示
		cv2.imshow('Cropped Video', cropped_frame)
		cv2.imshow('Collor Video', collor_frame)

		pixel = collor_frame[50, 50]  # (50, 50)の位置のピクセルのRGB値を取得
		print(f"Pixel at (50, 50): B={pixel[0]}, G={pixel[1]}, R={pixel[2]}")

		# 'q'キーで動画を停止
		if cv2.waitKey(1) & 0xFF == ord('q'):
				break

# 動画を解放してウィンドウを閉じる
cap.release()
cv2.destroyAllWindows()