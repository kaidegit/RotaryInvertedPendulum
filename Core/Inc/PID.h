//
// Created by JIANG on 2021/7/9.
//

#ifndef ROTARYINVERTEDPENDULUM_PID_H
#define ROTARYINVERTEDPENDULUM_PID_H

typedef struct pid{
    float err;                //误差
    float err_last;            //前一次误差
    float Kp,Ki,Kd;            //PID计数值
    float out;          //输出
    float integral;            //累计误差
}PID_struct;

extern PID_struct Rp_A_PID;
extern PID_struct Rp_P_PID;

void PID_Init(PID_struct *PID,float kp,float ki,float kd);
float PID_calc_A(PID_struct *PID,float e);
float PID_calc_P(PID_struct *PID,float e);
void PID_Clear();
float get_error(int target,int now);

#endif //ROTARYINVERTEDPENDULUM_PID_H
