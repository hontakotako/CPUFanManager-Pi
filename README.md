# CPUFanManager-Pi
Simple CPU Fan Manager for raspberry Pi<br>
raspberry Pi用　CPU冷却ファン管理プログラム<br>

## ■概要
一定時間ごとにraspberry PiのCPU温度を監視し、取得した温度に応じてGPIO12番ピン（※）に接続した冷却ファンの回転を制御します。<br>
GPIOの制御にwiringPiを使用しています。<br>

※提示している番号はraspberry Pi基板上の物理ピン番号です。<br>
　wiringPiで用いるGPIO番号ではないのでご注意ください。<br>

## ■必要パッケージ
-wiringpi<br>

## ■コンパイル方法
1. githubからファイル一式をダウンロード<br>
    git clone https://github.com/hontakotako/CPUFanManager-Pi.git
2. ダウンロードした「CPUFanManager-Pi」ディレクトリへ移動<br>
    cd CPUFanManager-Pi
3. make実行<br>
    make
　ディレクトリ内に実行ファイル「cpufm」が生成されれば成功です。<br>

## ■使い方
ターミナルで「CPUFanManager-Pi」ディレクトリへ移動し、以下のコマンドを入力します。<br>
    $./cpufm

停止するときはターミナル上で'[Ctrl]+[C]'を押下してください。<br>

## ■動作確認済み環境
-raspberry Pi2 & raspbian buster ( stretchからアップグレード )<br>
　冷却ファン：5V25mm角　DCファン[D02X-05TS1 02]<br>
