#include "UserTask.h"

float Fs = 0;
uint16_t ADC0Data[ADC0_DATA_LEN] = {0};

void UserTask_init(void) {
    ADC_init();
    Fs = ADC0_setEventTimer(1E6);
}

void UserTask_loop(void) {
    ADC0_startDMA(ADC0Data, ADC0_DATA_LEN);

    Tick_delay(500);
    if (IS_ADC0_DONE) {
        DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_LED1_PIN);
    }
}

void UserTask_tick(void) {
    
}
