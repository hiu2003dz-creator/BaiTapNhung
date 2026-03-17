#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stddef.h>

// 1. Khởi tạo dải LED với số lượng bóng chỉ định
int led_init(size_t num_pixels);

// 2. Tắt hệ thống, giải phóng bộ nhớ
void led_shutdown(void);

// 3. Đặt màu cho 1 bóng cụ thể (index từ 0)
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);

// 4. Tô cùng 1 màu cho toàn bộ dải LED
void led_fill(uint8_t r, uint8_t g, uint8_t b);

// 5. Tắt toàn bộ LED (màu đen)
void led_clear(void);

// 6. Lấy con trỏ của nhà kho (để test/in ra xem)
const uint32_t* led_get_buffer(void);

// 7. Lấy tổng số bóng LED
size_t led_get_pixel_count(void);

#endif // LED_DRIVER_H