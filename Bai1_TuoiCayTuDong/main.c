#include "config.h"
#include "spws_controller.h"
#include "hal_sensor.h"
#include "hal_actuators.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

static uint32_t GetCurrentTime_s(void)
{
    return (uint32_t)time(NULL);
}

int main(void)
{
    
     Sensor sensorData = {
        .DoamDat = 0.0F,
        .NhietDo = 0.0F
    };

    
     SystemSetting_t settings = {
        .DoamToiThieuDat = 30.0F,
        .DoamToiDaDat = 60.0F,
        .ThoiGianTuoiToiDa = 30U,
        .ThoiGianTuoiThuCong = 10U,
        .ChuKyDocCamBien = 2U
    };

    
    SystemState_t systemState = {
        .TrangthaiHT = MODE_AUTO,
        .TrangthaiBom = PUMP_OFF,
        .TrangthaiLed = LED_NORMAL,
        .ThoigianBom = 0U
    };

    uint32_t currentTime_s;
    uint32_t lastSensorReadTime_s;

   
    bool modeButtonPressed = false;
    bool manualButtonPressed = false;

    

    Hal_Sensors_Init();
    HAL_Actuators_Init();

    
    
    HAL_Pump_TurnOff();
    HAL_LED_SetNormal();

    
    
    sensorData.DoamDat =
        HAL_Sensors_ReadSoilMoisture();

    sensorData.NhietDo =
        HAL_Sensors_ReadTemperature();

    
    lastSensorReadTime_s = GetCurrentTime_s();

    printf("=== HE THONG TUOI CAY TU DONG ===\n");
    printf("Che do ban dau: MODE_AUTO\n");
    printf("Bom ban dau: PUMP_OFF\n");

    while (1)
    {
        
        currentTime_s = GetCurrentTime_s();

       
        if ((currentTime_s - lastSensorReadTime_s) >=
            settings.ChuKyDocCamBien)
        {
            sensorData.DoamDat =
                HAL_Sensors_ReadSoilMoisture();

            sensorData.NhietDo =
                HAL_Sensors_ReadTemperature();

            lastSensorReadTime_s = currentTime_s;

            printf("Do am: %.1f %% | Nhiet do: %.1f C\n",
                   sensorData.DoamDat,
                   sensorData.NhietDo);
        }

        
        SPWS_Controller_Run(
            &sensorData,
            &settings,
            &systemState,
            modeButtonPressed,
            manualButtonPressed,
            currentTime_s
        );

        sleep(1);
    }

    return 0;
}