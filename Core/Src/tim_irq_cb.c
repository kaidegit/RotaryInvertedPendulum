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
    int out1=0;  //角度环输出
    int out2=0;  //位置环输出
    int out=0;   //整体输出
    int time=0;  //计时
    int P_flag=0;  //位置环开启标致

    volatile int Measure;  //测量值

    if (htim->Instance == htim13.Instance) {
        Measure = GetADCValue(&hadc1);
        if ((Measure >= 1800) && (Measure <= 2800)) {  //处于平衡区间

            out1 = PID_calc_A(&Rp_A_PID, get_error(2250, Measure));

            if(P_flag == 0){
               if ((Measure >= 2000) && (Measure <= 2400)){
                      time++;                             //当角度环平衡后开启位置环
               }
               if(time>60){ P_flag = 1; time=0;}                 //开器位置控制 编码器致0
            }

            if(P_flag==1)    //开启位置环time
             {  time++;
                if (time == 5) {  //每隔25ms进行一次找到平衡点
                    out2 = PID_calc_P(&Rp_P_PID , motor_speed);
                    time = 0;
                }
            }

            out=out1-out2;// 正反馈输出
            SetMotorSpeed(out);

        } else {
            SetMotorSpeed(0);
        }
    } else if (htim->Instance == htim14.Instance) {


    }
    HAL_TIM_Base_Start_IT(htim);
}