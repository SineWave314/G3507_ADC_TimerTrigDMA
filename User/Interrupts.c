#include "Interrupts.h"

// SysTick中断服务函数(1ms)
void SysTick_Handler(void) {
    Tick_SysTickCallback();
}
/*
// ADC0中断服务函数
void ADC0_IRQHandler(void) {
    switch (DL_ADC12_getPendingInterrupt(ADC0_INST)) {
        case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
            ADC0_mem0ResultLoadedCallback();
            break;
        default:
            break;
    }
}

// ADC1中断服务函数
void ADC1_IRQHandler(void) {
    switch (DL_ADC12_getPendingInterrupt(ADC1_INST)) {
        case DL_ADC12_IIDX_MEM3_RESULT_LOADED:
            ADC1_mem3ResultLoadedCallback();
            break;
        default:
            break;
    }
}
*/