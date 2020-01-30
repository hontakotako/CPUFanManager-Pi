# CPUFanManager-Pi
Simple CPU Fan Manager for raspberry Pi
raspberry Pi用　CPU冷却ファン管理プログラム

■概要
一定時間ごとにraspberry PiのCPU温度を監視し、取得した温度に応じてGPIO12番ピン（※）に接続した冷却ファンの回転を制御します。
GPIOの制御にwiringPiを使用しています。

※提示している番号はraspberry Pi基板上の物理ピン番号です。
　wiringPiで用いるGPIO番号ではないのでご注意ください。

■必要パッケージ
・wiringpi

■コンパイル方法
①githubからファイル一式をダウンロード
②ダウンロードした「CPUFanManager-Pi」ディレクトリへ移動
③make実行
　ディレクトリ内に実行ファイル「cpufm」が生成されれば成功です。

■使い方
ターミナルで「CPUFanManager-Pi」ディレクトリへ移動し、以下のコマンドを入力します。
$./cpufm

停止するときはターミナル上で[Ctrl]+[C]を押下してください。

■動作確認済み環境
・raspberry Pi2 & raspbian buster ( stretchからアップグレード )
　冷却ファン：5V25mm角　DCファン[D02X-05TS1 02]
