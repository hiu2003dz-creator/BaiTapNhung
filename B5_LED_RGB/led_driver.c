#include "led_driver.h"
#include<stdlib.h>
static uint32_t total_led_pixal = 0;
static uint32_t *led_buffer = NULL;
int led_init(size_t num_pixel){
    if(num_pixel == 0){
      return -1;
    }
    led_buffer = (uint32_t*)calloc(num_pixel,sizeof(uint32_t)); // ham calloc cấp phát động nên trả về con trỏ nên phải ép kiểu
    if(led_buffer == NULL){
        return -1 ;
    }else{
        total_led_pixal = num_pixel;
    }
}
void led_shutdown(void){
    if(led_buffer != NULL){
        free(led_buffer);
        // lệnh  return này nếu không cho led_buffer = NULL thì nó vẫn sẽ lưu địa chỉ
        led_buffer = NULL;
        total_led_pixal = 0;
    }
}
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b){
    if(led_buffer == NULL || index > total_led_pixal){
        return;
    }
    uint32_t color = ((uint32_t) g << 16 | (uint32_t) r << 8 | b );
    index = led_buffer[color];
}
void led_fill(uint8_t r, uint8_t g, uint8_t b){
    if(led_buffer == NULL){
        return;
    }
    uint32_t color = ((uint32_t)g << 16 | (uint32_t)r << 8 | (uint32_t)b);
    for(size_t i = 0 ; i < total_led_pixal ; i++){
        led_buffer[i] = color;
    } 
}
void led_clear(void) {
    led_fill(0, 0, 0); 
}
const uint32_t* led_get_buffer(void) {
    return led_buffer; 
}
size_t led_get_pixel_count(void) {
    return total_led_pixal;
}