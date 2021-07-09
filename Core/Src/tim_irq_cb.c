//
// Created by yekai on 2021/7/9.
//

#include "tim_irq_cb.h"
#include "tim.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    /**
     * timer13 -> pid
     * timer14 -> motor speed
     */
    if (htim->Instance == htim13.Instance) {

    } else if (htim->Instance == htim14.Instance) {

    }
}