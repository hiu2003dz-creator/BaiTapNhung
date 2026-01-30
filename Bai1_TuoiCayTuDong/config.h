#ifndef CONFIG_H
#define CONFIG_H
#include<stdint.h>
// CHẾ ĐỘ HOẠT ĐỘNG MÁY BƠM
typedef enum{
    MODE_AUTO,
    MODE_MANUAL,
}SystemMode_t;
// CHẾ ĐỘ MÁY BƠM
typedef enum{
   PUMP_ON,
   PUMP_OFF,
}PumpState_t;
// TRẠNG THÁI CỦA LED
typedef enum{
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
}LedState_t;
// Cảm biến
typedef struct{
    float soilMoisturePercent;
    float airTemperatureCelsius;
}SensorData;
typedef struct {
    float minMoistureThreshold;         // Ngưỡng độ ẩm tối thiểu để bắt đầu tưới
    float maxMoistureThreshold;         // Ngưỡng độ ẩm tối đa để dừng tưới
    unsigned int maxWateringDuration_s; // Thời gian tưới tối đa (giây)
    unsigned int sensorReadInterval_s;  // Chu kỳ đọc cảm biến (giây)
    unsigned int manualWateringDuration_s; // Thời gian tưới thủ công (giây)
} SystemSettings_t;

// Cấu trúc quản lý trạng thái động của toàn bộ hệ thống
typedef struct {
    SystemMode_t currentMode;
    PumpState_t pumpState;
    LedState_t ledState;
    unsigned int wateringTimeCounter;   // Biến đếm thời gian đang tưới
    unsigned int sensorCheckCounter;    // Biến đếm cho chu kỳ đọc cảm biến
} SystemState_t;
#endif