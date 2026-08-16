#ifndef SPWS_CONTROLLER_H
#define SPWS_CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>

#include "config.h"

void SPWS_Controller_Run(const Sensor *sensor,const SystemSetting_t *settings,SystemState_t *state,
                         bool modeButtonPressed,
                         bool manualButtonPressed,
                         uint32_t currentTime_s);

#endif