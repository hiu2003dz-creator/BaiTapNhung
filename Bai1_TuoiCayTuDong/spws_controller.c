#include "spws_controller.h"
#include "hal_actuators.h"

#include <stdio.h>

static void TurnPumpOn(SystemState_t *state,
                       uint32_t currentTime_s)
{
    if (state->TrangthaiBom == PUMP_OFF)
    {
        HAL_Pump_TurnOn();

        state->TrangthaiBom = PUMP_ON;
        state->TrangthaiLed = LED_WATERING;
        state->ThoigiandocCB = currentTime_s;

        printf("Bat dau tuoi\n");
    }
}

static void TurnPumpOff(SystemState_t *state)
{
    if (state->TrangthaiBom == PUMP_ON)
    {
        HAL_Pump_TurnOff();

        state->TrangthaiBom = PUMP_OFF;
        state->TrangthaiLed = LED_NORMAL;
        state->ThoigianBom = 0U;

        printf("Ket thuc tuoi\n");
    }
}

static void SPWS_UpdateLed(const SystemState_t *state)
{
    if (state->TrangthaiLed == LED_NORMAL)
    {
        HAL_LED_SetNormal();
    }
    else if (state->TrangthaiLed == LED_WATERING)
    {
        HAL_LED_SetWatering();
    }
    else
    {
        HAL_LED_SetError();
    }
}

static void SPWS_HandleModeButton(SystemState_t *state)
{
    if (state->TrangthaiHT == MODE_AUTO)
    {
        state->TrangthaiHT = MODE_MANUAL;

        TurnPumpOff(state);

        printf("Chuyen sang MODE_MANUAL\n");
    }
    else
    {
        state->TrangthaiHT = MODE_AUTO;

        printf("Chuyen sang MODE_AUTO\n");
    }
}

static void SPWS_RunAutoMode(const Sensor *sensor,
                             const SystemSetting_t *settings,
                             SystemState_t *state,
                             uint32_t currentTime_s)
{
    uint32_t wateringTime_s;

    if (state->TrangthaiBom == PUMP_OFF)
    {
        if (sensor->DoamDat<
            settings->DoamToiThieuDat)
        {
            TurnPumpOn(state, currentTime_s);
        }
    }
    else
    {
        wateringTime_s =
            currentTime_s - state->ThoigianBom;

        if (sensor->DoamDat >
            settings->DoamToiDaDat)
        {
            TurnPumpOff(state);
        }
        else if (wateringTime_s >=
                 settings->ThoiGianTuoiToiDa)
        {
            TurnPumpOff(state);
        }
    }
}

static void SPWS_RunManualMode(
    const SystemSetting_t *settings,
    SystemState_t *state,
    bool manualButtonPressed,
    uint32_t currentTime_s)
{
    uint32_t wateringTime_s;

    if (state->TrangthaiBom == PUMP_OFF)
    {
        if (manualButtonPressed == true)
        {
            TurnPumpOn(state, currentTime_s);
        }
    }
    else
    {
        wateringTime_s =
            currentTime_s - state->ThoigianBom;

        if (wateringTime_s >= settings->ThoiGianTuoiThuCong)
        {
            TurnPumpOff(state);
        }
    }
}

void SPWS_Controller_Run(const Sensor *sensor,
                         const SystemSetting_t *settings,
                         SystemState_t *state,
                         bool modeButtonPressed,
                         bool manualButtonPressed,
                         uint32_t currentTime_s)
{
    if (modeButtonPressed == true)
    {
        SPWS_HandleModeButton(state);
        SPWS_UpdateLed(state);

        return;
    }

    if (state->TrangthaiHT == MODE_AUTO)
    {
        SPWS_RunAutoMode(sensor,
                         settings,
                         state,
                         currentTime_s);
    }
    else
    {
        SPWS_RunManualMode(settings,
                           state,
                           manualButtonPressed,
                           currentTime_s);
    }

    SPWS_UpdateLed(state);
}