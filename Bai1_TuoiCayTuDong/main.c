#include<stdio.h>
#include<stdint.h>
#include"config.h"
SystemState_t g_State;
SensorData g_Sensor;
SystemSettings_t g_Setting;
// Bơm đang mở 
void TurnPumpOn(void){
    if(g_State.pumpState == PUMP_ON){
        return ;
        g_State.pumpState == PUMP_ON;
        printf("\n MÁY ĐANG BƠM");
    }
}
// Bơm đang tắt
void TurnPumpOff(void){
    if(g_State.pumpState == PUMP_OFF){
        return;
       g_State.pumpState == PUMP_OFF;
       printf("\n DỪNG BƠM");
    }
}
// TRẠNG THÁI LED
void LEDSTATE(void){
    if(g_State.ledState == LED_NORMAL){
        g_State.currentMode == MODE_AUTO;
        printf("LED NORMAL");
    }else{
        g_State.ledState == LED_WATERING;
        g_State.currentMode == MODE_MANUAL;
        printf("LED WARNING");
    }
}
// ĐỌC CẢM BIẾN
void ReadSensor(void){
    if(g_State.currentMode != MODE_AUTO){
        return;
    }
    g_Sensor.soilMoisturePercent = 29,5;
    g_Sensor.airTemperatureCelsius = 21,5;
    printf("NHIỆT ĐỘ , ĐỘ ẨM = %.2f %.2f ",g_Sensor.soilMoisturePercent,g_Sensor.airTemperatureCelsius);
}
// LOGIC BƠM CHẠY
void Run_Logic(void){
    if (g_State.currentMode != MODE_AUTO) 
    return;
    if (g_Sensor.soilMoisturePercent < g_Setting.minMoistureThreshold) {
        printf("[LOGIC] Dat kho (%.1f < %.1f) -> BAT BOM\n", 
               g_Sensor.soilMoisturePercent, g_Setting.minMoistureThreshold);
        TurnPumpOn();
    }
    else if (g_Sensor.soilMoisturePercent > g_Setting.maxMoistureThreshold) {
        printf("[LOGIC] Dat du am (%.1f > %.1f) -> TAT BOM\n", 
               g_Sensor.soilMoisturePercent, g_Setting.maxMoistureThreshold);
        TurnPumpOff();
}
}
// KHỞI TẠO BƠM VÀ CÁC TRẠNG THÁI
void Bơm_Init(){
    // các thông số máy bơm
    g_Setting.manualWateringDuration_s = 30,5;
    g_Setting.maxMoistureThreshold = 80.0;
    g_Setting.maxWateringDuration_s = 60;
    g_Setting.sensorReadInterval_s = 5;
    g_Setting.minMoistureThreshold = 30.0;
    // các chế độ hoạt động của bơm
    g_State.currentMode = MODE_AUTO;
    g_State.ledState = LED_NORMAL;
    g_State.pumpState = PUMP_ON;
    g_State.sensorCheckCounter = 0;
    g_State.wateringTimeCounter = 0;
    printf("=== KHOI TAO HE THONG ===\n");
    printf("Cau hinh: Min %.1f%% - Max %.1f%%\n", 
           g_Setting.minMoistureThreshold, g_Setting.maxMoistureThreshold);
    printf("-------------------------\n");
}
int main(){
    void Bơm_Init();
    printf("\n TEST 1: DO AM THAP (Auto) \n");
    Process_Sensors(); //
    Run_Auto_Logic();  //
    // TEST (MƯA XUỐNG) 
    printf("\n--- TEST 2: DO AM CAO (Sau khi tuoi) ---\n");
    g_Sensor.soilMoisturePercent = 95.0; // Giả lập đất ướt
    Run_Auto_Logic(); // Logic thấy 95.0 > 80.0 -> Sẽ Tắt bơm
    // (CHUYỂN MANUAL)
    printf("\n TEST 3: CHUYEN SANG MANUAL \n");
    g_State.currentMode = MODE_MANUAL;
    printf("Nguoi dung chuyen sang che do MANUAL.\n");
    // Thử chạy logic Auto xem có tác dụng không 
    g_Sensor.soilMoisturePercent = 10.0; // Rất khô
    Run_Auto_Logic(); 
    if (g_State.pumpState == PUMP_OFF) {
        printf("(Dung: Logic Auto khong can thiep khi dang o Manual)\n");
    }
    // Bật bơm thủ công
    printf("\n--- TEST 4: BAT BOM THU CONG ---\n");
    TurnPumpOn();
    return 0;
}       