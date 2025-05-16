#include "encoder.h"
// define PI
const float PI = 3.1415;
	float CNT_current;
	float CNT_old;
	float TIM_current;
	float speriod;
	float TIM_old;
	float oldtheta;


//initial setting
void encoder_init(TIM_HandleTypeDef* htim){
	HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL );
	__HAL_TIM_SET_COUNTER(htim,4294967295/2);
}

// from CNT to Member
void cnt_convert(encod* encod, TIM_HandleTypeDef* htim){
	// Get Proccess TIM
	float MAXCNT = 8092;
	CNT_current = __HAL_TIM_GET_COUNTER(htim)-4294967295/2;

	// main function
	// from CNT to THETA
	encod -> theta = 360.0*(CNT_current/MAXCNT);

	// from CNT to OMEGA
	TIM_current = HAL_GetTick();
    if(TIM_current-TIM_old >= 1){
	speriod = (TIM_current - TIM_old);

	encod -> omega = //((encod -> theta - oldtheta)*1000);
			(360.0*((CNT_current - CNT_old)/MAXCNT))*1000;

	// from CNT to RPS
	encod -> rps = //(((encod -> theta - oldtheta)/360)*1000);
	((CNT_current - CNT_old)/MAXCNT)*1000;

	CNT_old = __HAL_TIM_GET_COUNTER(htim)-4294967295/2;
	TIM_old = HAL_GetTick();
	oldtheta=encod -> theta;
    }

}
