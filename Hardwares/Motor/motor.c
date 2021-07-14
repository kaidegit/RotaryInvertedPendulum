//
// Created by yekai on 2021/7/9.
//

#include "motor.h"
#include "gpio.h"
#include "tim.h"
#include "stdio.h"



const int32_t DEAD_SPEED = 600;
const int32_t SPEED_MAX = 2100 - DEAD_SPEED;

void SetMotorSpeed(int32_t speed) {
    if (speed > SPEED_MAX) {
        speed = SPEED_MAX;
    }
    if (speed < -SPEED_MAX) {
        speed = -SPEED_MAX;
    }
    if (speed == 0) {
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    } else if (speed > 0) {
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, speed + DEAD_SPEED);
#ifdef MOTOR_DEBUG
        printf("%d\r\n", speed + DEAD_SPEED);
#endif
    } else {
        HAL_GPIO_WritePin(MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, -speed + DEAD_SPEED);
        HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
#ifdef MOTOR_DEBUG
        printf("-%d\r\n", -speed + DEAD_SPEED);
#endif
    }
}
