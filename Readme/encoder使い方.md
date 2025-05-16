# encoder.hおよびencoder.cの使用方法
### 1.ヘッダファイルのインクルード
必ずmain.c内でヘッダファイルをインクルードしよう
```
#include "encoder.h"
```
### 2.ヘッダファイルの説明
```
#ifndef ENCODER_H //インクルードブロック
#define ENCODER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h" // TIM_HandleTypeDefのためのインクルード
//構造体の定義
typedef struct{
float theta; //角度
float omega; //角速度
float rps;  　//1秒あたりの回転数
} encod;

// initial setting
void encoder_init(TIM_HandleTypeDef* htim); //初期化関数
// main function
void cnt_convert(encod* encod, TIM_HandleTypeDef* htim); //エンコーダのカウント値からteheta,omega,rpsを計算
#endif
```
encordの実体の中にtheta，omega，rpsが入る

### 3.cファイルの説明
・初期化関数
```
//initial setting
void encoder_init(TIM_HandleTypeDef* htim){
	HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL );
	__HAL_TIM_SET_COUNTER(htim,4294967295/2);
}
```
使用するタイマのアドレスをぶち込めば初期化を勝手にしてくれます．
`	HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL )`
でエンコーダをスタートさせています．4逓倍モードなのでチャンネルは2つとも使います．
__HAL_TIM_SET_COUNTER(htim,4294967295/2);でタイマの中央値にカウントを設定します．
4294967295という数値はタイマのカウント値の最大値です．この数字は設定できるようにしないと使いにくいです．すみません．
タイマの中央値からカウントをスタートさせる理由はシンプルに逆回転にも対応できるようにです．
使用するタイマのアドレスをぶち込めば初期化を勝手にしてくれます．
・変換関数
```
void cnt_convert(encod* encod, TIM_HandleTypeDef* htim)
```
現在の時刻と過去の時刻のカウント値の差分を取って回転した角度とか角速度とかrpsを勝手に計算してくれます．

**サンプルプログラムはまたアップすると思います．**
