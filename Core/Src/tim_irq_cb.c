//
// Created by yekai on 2021/7/9.
//

#include "tim_irq_cb.h"
#include "PID.h"
#include "tim.h"
#include "motor.h"
#include "adc.h"
#include "speed.h"

//右=2390  立=2275  左=2140
//逆时针速度正
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    /**
     * timer13 -> pid
     * timer14 -> motor speed
     */
    int out1=0;
    int out2=0;
    int out=0;
    int time=0;


    volatile int Measure;

    if (htim->Instance == htim13.Instance) {
        time++;
        Measure = GetADCValue(&hadc1);
        if ((Measure >= 1800) && (Measure <= 2800)) {
            out1 = PID_calc_A(&Rp_A_PID, get_error(2250, Measure));

            if( time == 5 ) {
                out2 = PID_calc_P(&Rp_P_PID, get_error(2250, motor_speed));
                time = 0;
            }
            out=out1-out2;
            SetMotorSpeed(out);
        } else {
            SetMotorSpeed(0);
        }
    } else if (htim->Instance == htim14.Instance) {


    }
    HAL_TIM_Base_Start_IT(htim);
}