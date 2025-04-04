# M5Atom S3R & Arduino Uno R4 Minima - Magnetic Sensor & Servo Control  

## 概要  
M5Atom S3R と Arduino Uno R4 Minima を使用し、磁気センサーのデータをシリアル通信で送信し、サーボモーターを制御するプロジェクトです。  

## 使用ハードウェア  
- M5Atom S3R CAM
- Arduino Uno R4 Minima  
- サーボモーター （追加予定）

## 使用ライブラリ  
- [M5Unified](https://github.com/m5stack/M5Unified)
- [Servo](https://github.com/arduino-libraries/Servo.git)

# 参考
- [servoの動きに関して](https://github.com/RoboTakao/NX22.git)

## インストール & 使い方  
1. 必要なライブラリをインストール  
2. M5Atom S3R にコードを書き込み、磁気センサーのデータを送信  
3. Arduino Uno R4 Minima にコードを書き込み、受信データでサーボモーターを制御 

## コントローラの向き
![コントローラの向き](IMG_2422.jpg)
あれ、、場合によっては違うな、、、

## 今後の予定  
- 新機能の追加  
- コードの最適化  
