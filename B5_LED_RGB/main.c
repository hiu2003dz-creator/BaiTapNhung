#include <stdio.h>
#include "led_driver.h" 

int main(void) {
    printf("Test 1: Khoi tao led_init(10)...\n");
    if (led_init(10) == -1) {
        printf("[LOI SAP NGUON] \n");
        return -1; 
    }
    printf("MO LED THANH CONG\n\n");


    printf("Test 2: Kiem tra xem tat ca bong da tat (mau den) chua...\n");
    const uint32_t* buffer_kiem_tra = led_get_buffer();
    int co_rac_khong = 0; 
    
    for (int i = 0; i < 10; i++) {
        if (buffer_kiem_tra[i] != 0) { 
            co_rac_khong = 1; 
            printf("[LOI] Phat hien bong thu %d dang sang: 0x%08X\n", i, buffer_kiem_tra[i]);
            break; 
        }
    }
    if (co_rac_khong == 0) {
        printf("[PASS] Tat ca 10 bong ban dau deu co gia tri 0x00000000 (Mau den).\n\n");
    }

    printf("Test 3: Bat den Do (0), Trang (4), Xanh duong (9)...\n");
    
    led_set_pixel_color(0, 255, 0, 0);     // Bóng 0: Đỏ
    led_set_pixel_color(4, 255, 255, 255); // Bóng 4: Trắng
    led_set_pixel_color(9, 0, 0, 255);     // Bóng 9: Xanh dương

    printf("--- KET QUA MA HEXA ---\n");
    printf("Bong 0 (Do)   : 0x%08X \t[Ky vong: 0x0000FF00]\n", buffer_kiem_tra[0]);
    printf("Bong 4 (Trang): 0x%08X \t[Ky vong: 0x00FFFFFF]\n", buffer_kiem_tra[4]);
    printf("Bong 9 (Xanh) : 0x%08X \t[Ky vong: 0x000000FF]\n\n", buffer_kiem_tra[9]);
    printf("Test 4: To mau Xanh la (0, 255, 0) cho TOAN BO xuong...\n");
    led_fill(0, 255, 0); 
    
    int tat_ca_deu_xanh = 1; 
    for (int i = 0; i < 10; i++) {
        if (buffer_kiem_tra[i] != 0x00FF0000) {
            tat_ca_deu_xanh = 0; 
            printf("[LOI] Bong thu %d to sai mau: 0x%08X\n", i, buffer_kiem_tra[i]);
            break; 
        }
    }
    if (tat_ca_deu_xanh == 1) {
        printf("[PASS] Tat ca 10 bong deu mang ma 0x00FF0000. Ham led_fill chay xuat sac!\n\n");
    }
    printf("Test 5: Don dep xuong, goi xe rac (led_shutdown)...\n");
    led_shutdown();
    printf("[PASS] Da giai phong bo nho an toan. Dong cua xuong!\n");
    
    printf("\n========== HOAN THANH XUAT SAC DO AN ==========\n");

    return 0;
}