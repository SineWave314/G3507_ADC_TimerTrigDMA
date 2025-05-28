#include "UserTask.h"

void UserTask_init(void) {
    
}

void UserTask_loop(void) {
    DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_LED1_PIN);
    Tick_delay(500);
}

void UserTask_tick(void) {
    
}
