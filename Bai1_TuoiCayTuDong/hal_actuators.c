#include <stdio.h>
#include "hal_actuators.h"


void HAL_Actuators_Init(void)
{
    printf("Actuators initialized\n");
}


void HAL_Pump_TurnOn(void)
{
    printf("BOM BAT\n");
}


void HAL_Pump_TurnOff(void)
{
    printf("BOM TAT\n");
}


void HAL_LED_SetNormal(void)
{
    printf("LED: NORMAL\n");
}


void HAL_LED_SetWatering(void)
{
    printf("LED: WATERING\n");
}


void HAL_LED_SetError(void)
{
    printf("LED: ERROR\n");
}