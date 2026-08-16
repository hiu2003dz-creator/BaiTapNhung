#ifndef SENSOR_H
#define SENSOR_H
void Hal_Sensors_Init(void);
float HAL_Sensors_ReadSoilMoisture(void);
float HAL_Sensors_ReadTemperature(void);
#endif
