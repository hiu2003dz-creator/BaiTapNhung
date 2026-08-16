#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H

/* Khởi tạo các thiết bị đầu ra */
void HAL_Actuators_Init(void);


/* Điều khiển bơm */
void HAL_Pump_TurnOn(void);
void HAL_Pump_TurnOff(void);


/* Điều khiển LED */
void HAL_LED_SetNormal(void);
void HAL_LED_SetWatering(void);
void HAL_LED_SetError(void);

#endif