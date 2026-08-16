#include "hal_sensor.h"
#include<stdio.h>
void Hal_Sensors_Init(void){
    printf("Khoi tao cam bien");
}
float HAL_Sensors_ReadSoilMoisture(void){
    return 20.0f;
}
float HAL_Sensors_ReadTemperature(void){
    return 65.0f;
}