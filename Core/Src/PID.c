//
// Created by JIANG on 2021/7/9.
//
#include "PID.h"

PID_struct Rp_PID;

float get_error(int target, int now) {
    float error;
    error = target - now;
    return error;
}


void PID_Init(PID_struct *PID, float kp, float ki, float kd)//  pid参数设置
{
    PID->err = 0;    //PID误差
    PID->err_last = 0;   //上一次误差
    PID->integral = 0;  //累计误差
    PID->Kp = kp;
    PID->Ki = ki;
    PID->Kd = kd;
    PID->out = 0;
}

float PID_calc(PID_struct *PID, float e)  //PID计算
{
    PID->err = e;
    PID->integral += PID->err;
    if (PID->integral >= 1000)
        PID->integral = 1000;
    if (PID->integral <= -1000)
        PID->integral = -1000;
    if (PID->err >= -5 && PID->err <= 5)
        PID->integral = 0;
    PID->out = PID->Kp * PID->err +
               PID->Ki * PID->integral +
               PID->Kd * (PID->err - PID->err_last);
    PID->err_last = PID->err;
    return PID->out;
}

//float PID_calc_z_y(PID_struct *PID,float e)   //PID计算
//{
//    PID->err =e;
//    PID->integral += PID->err;
//
//    PID->out = PID->Kp * PID->err +
//               PID->Ki * PID->integral +
//               PID->Kd *( PID->err - PID->err_last );
//    PID->err_last = PID->err;
//    return PID->out;
//}