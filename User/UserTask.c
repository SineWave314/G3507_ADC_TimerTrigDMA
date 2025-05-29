#include "UserTask.h"

float Fs0 = 0;
float Fs1 = 0;
uint16_t ADC0Data[ADC0_DATA_LEN] = {0};
uint16_t ADC1Data[ADC1_DATA_LEN] = {0};
uint16_t ADC1CH0Data[ADC1_CH_DATA_LEN] = {0};
uint16_t ADC1CH1Data[ADC1_CH_DATA_LEN] = {0};

void UserTask_init(void) {
    ADC_init(); // ADC初始化(使能中断)
    Fs0 = ADC0_setEventTimer(1000000); // 设置ADC0采样率1MSa/s
    Fs1 = ADC1_setEventTimer(100000); // 设置ADC1采样率100kSa/s
}

void UserTask_loop(void) {

    // 启动ADC0 定时器触发+DMA模式
    ADC0_startDMA(ADC0Data, ADC0_DATA_LEN);

    Tick_delay(300);
    if (IS_ADC0_DONE) {
        DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_LED1_PIN);
    }

    // 启动ADC1 定时器触发+DMA FIFO模式
    ADC1_startDMAFIFO(ADC1Data, ADC1_DATA_LEN);

    Tick_delay(300);
    if (IS_ADC1_DONE) {

        // 提取各通道数据
        ADC_extractData(&ADC1Data[0], ADC1CH0Data, ADC1_CH_DATA_LEN, 2);
        ADC_extractData(&ADC1Data[1], ADC1CH1Data, ADC1_CH_DATA_LEN, 2);

        DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_LED1_PIN);
    }
    Tick_delay(300);
}

void UserTask_tick(void) {
    
}
