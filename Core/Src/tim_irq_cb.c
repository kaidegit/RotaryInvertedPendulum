//
// Created by yekai on 2021/7/9.
//

#include "tim_irq_cb.h"
#include "PID.h"
#include "tim.h"
#include "motor.h"
#include "adc.h"
#include "speed.h"
#include "stdbool.h"
#include "stdio.h"
#include "debug_conf.h"
#include "DataScope_DP.h"


const int32_t ADC_MIDDLE = 1854;
const int32_t ADC_MIN = ADC_MIDDLE - 350;
const int32_t ADC_MAX = ADC_MIDDLE + 350;

// 右=2390  立=2275  左=2140

// 杆在左边时，内环pid正，电机逆时针转
// 杆在右边时，内环pid负，电机顺时针转

// 电机逆时针转，编码器数值减
// 电机顺时针转，编码器数值加

// 转一圈大约780个编码器CNT数值，每度大约2个编码器CNT数值

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    /**
     * timer13 -> pid  5ms
     * timer14 -> motor speed
     */
    int out1 = 0;  //角度环输出
    static int out2 = 0;  //位置环输出
    int out = 0;   //整体输出
    static int All_time = 0;  //总计时
    static int P_time = 0;  //位置环计时
    static bool Position_flag = false;  //位置环计算标志

    volatile int Measure;  //测量值

    if (htim->Instance == htim13.Instance) {
        Measure = GetADCValue(&hadc1);

#ifdef ADC_DEBUG
//        printf("%d\r\n", Measure);
#endif
        if ((Measure >= ADC_MIN) && (Measure <= ADC_MAX)) {  //处于平衡区间

            Measure = GetADCValue(&hadc1);
            out1 = PID_calc_A(&Rp_A_PID, get_error(ADC_MIDDLE, Measure));

            P_time++;
            if (P_time > 4) {  //每隔25ms进行一次找到平衡点
                motor_speed = __HAL_TIM_GET_COUNTER(&htim4) - 32768;
                out2 = PID_calc_P(&Rp_P_PID, motor_speed);
                P_time = 0;
            }

            out = out1 - out2;
            SetMotorSpeed(out);

            DataScope_Get_Channel_Data(Measure,1);
            DataScope_Get_Channel_Data(motor_speed,2);

        } else {
            SetMotorSpeed(0);
            Position_flag = false;
            out2 = 0;
            out1 = 0;
            out = 0;
            All_time = 0;
            P_time = 0;
            PID_Clear();
            __HAL_TIM_SET_COUNTER(&htim4, 32768);
        }
    } else if (htim->Instance == htim14.Instance) {


    }
    HAL_TIM_Base_Start_IT(htim);
}

#ifdef OUT_DEBUG
//               printf("motor_speed:%d\r\n",  __HAL_TIM_GET_COUNTER(&htim4));
#endif
//            DataScope_Get_Channel_Data(motor_speed, 2);
//            DataScope_Get_Channel_Data(out2, 1);
#ifdef OUT_DEBUG
//        printf("out1:%d out2:%d out:%d\r\n", out1, out2, out);//  printf("i:%d\r\n",(int)Rp_A_PID.integral);
#endif

