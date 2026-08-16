#ifndef CONFIG_H
#define CONFIG_H
#include<stdio.h>
#define DO_AM_TOI_THIEU_DAT       30.0f
#define DO_AM_TOI_DA_DAT          70.0f

#define THOI_GIAN_TUOI_TOI_DA     20
#define CHU_KY_DOC_CAM_BIEN         5
#define THOI_GIAN_TUOI_THU_CONG    10
typedef enum{
    MODE_MANUAL,
    MODE_AUTO
}SystemMode_t;
// Tranng thái của hệ thống
typedef enum{
    PUMP_OFF,
    PUMP_ON
}PumpState_t;
//Bơm
typedef enum{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOILSTURE_ALERT,
    LED_ERROR,
}LedState_t;
// LED
typedef struct{
    float DoamDat;
    float NhietDo;
}Sensor;
// cảm biến
typedef struct{
    float DoamToiThieuDat;
    float DoamToiDaDat;
    unsigned int ThoiGianTuoiToiDa;
    unsigned int ChuKyDocCamBien;
    unsigned int ThoiGianTuoiThuCong;
}SystemSetting_t;
// cấu hình cho mặc định đầu vào cho hệ thống
typedef struct {
    SystemMode_t TrangthaiHT;
    PumpState_t TrangthaiBom;
    LedState_t   TrangthaiLed;
    unsigned int ThoigianBom;
    unsigned int ThoigiandocCB;
}SystemState_t;
// quản lý hệ thống 
#endif