//
// Created by yekai on 2021/7/9.
//

#include "tim_irq_cb.h"
#include "PID.h"
#include "tim.h"
#include "motor.h"
#include "adc.h"

//右=3590  立=3300  左=2830
//逆时针速度正
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    /**
     * timer13 -> pid
     * timer14 -> motor speed
     */
    int out;
    volatile int Measure;

    if (htim->Instance == htim13.Instance) {
        Measure=GetADCValue(&hadc1);
        if((Measure >= 2830) && (Measure <= 3300)){
            out=PID_calc(&Rp_PID,get_error(3000,Measure));
            SetMotorSpeed(out);
        }else{
            SetMotorSpeed(0);
        }
    } else if (htim->Instance == htim14.Instance) {

    }
    HAL_TIM_Base_Start_IT(htim);
}