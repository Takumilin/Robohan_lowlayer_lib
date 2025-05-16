#ifndef ENCODER_H //インクルードブロック
#define ENCODER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h" // TIM_HandleTypeDefのためのインクルード
//構造体の定義
typedef struct{
float theta;
float omega;
float rps;
} encod;

// initial setting
void encoder_init(TIM_HandleTypeDef* htim);
// main function
void cnt_convert(encod* encod, TIM_HandleTypeDef* htim);
#endif
