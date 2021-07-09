//
// Created by yekai on 2021/7/9.
//

#include "tim_irq_cb.h"
#include "PID.h"
#include "tim.h"
#include "motor.h"

//右=3590  立=3300  左=2830
//逆时针速度正
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    /**
     * timer13 -> pid
     * timer14 -> motor speed
     */
    int out;
    int Measure;
    if (htim->Instance == htim13.Instance) {
        Measure=__HAL_TIM_GET_COUNTER(&htim4);
        out=PID_calc(&Rp_PID,get_error(3300,Measure));
        SetMotorSpeed(out);
    } else if (htim->Instance == htim14.Instance) {

    }
}