#include "ADC.h"

volatile uint8_t ADC0_DataValid = 0;

/**
 * @brief ADC初始化
 */
void ADC_init(void) {
    NVIC_EnableIRQ(ADC0_INST_INT_IRQN);
}

/**
 * @brief 设置ADC0事件定时器
 * @param fs 采样率(Sa/s)
 * @return 实际采样率(Sa/s)
 */
float ADC0_setEventTimer(uint32_t fs) {
    uint32_t loadVal;
    loadVal = (uint32_t)(EVENT_TIMER_CLK / (float)fs - 0.5F);
    DL_TimerG_setLoadValue(ADC0_EVENT_TIMER, loadVal);
    return (EVENT_TIMER_CLK / (float)(loadVal + 1));
}

/**
 * @brief 启动ADC0 DMA
 * @note 采样率由 @ref ADC0_setEventTimer 设置
 * @param dst 转换数据目的数组指针
 * @param cnt 采样点数
 */
void ADC0_startDMA(uint16_t* dst, uint16_t cnt) {
    ADC0_DataValid = 0;

    // 配置ADC DMA
    DL_DMA_disableChannel(DMA, DMA_ADC0_CHAN_ID);
    DL_DMA_setSrcAddr(DMA, DMA_ADC0_CHAN_ID, DL_ADC12_getMemResultAddress(ADC0_INST, ADC0_ADCMEM_0));
    DL_DMA_setDestAddr(DMA, DMA_ADC0_CHAN_ID, (uint32_t)dst);
    DL_DMA_setTransferSize(DMA, DMA_ADC0_CHAN_ID, cnt);
    DL_DMA_enableChannel(DMA, DMA_ADC0_CHAN_ID);

    // 使能ADC
    DL_ADC12_enableConversions(ADC0_INST);
    delay_cycles(800);

    // 启动事件定时器
    DL_TimerG_startCounter(ADC0_EVENT_TIMER);
}

/**
 * @brief 等待ADC0运行完成
 * @param timeout 超时时间(ms)
 * @retval ADC_STA_TIMEOUT: 等待超时
 * @retval ADC_STA_DONE: 运行完成
 */
ADC_Status_t ADC0_waitDone(uint32_t timeout) {
    uint32_t startTime = Tick;
    while (!IS_ADC0_DONE) {
        if (Tick - startTime >= timeout) return ADC_STA_TIMEOUT;
    }
    return ADC_STA_DONE;
}

// ADC0中断回调
void ADC0_DMADoneCallback(void) {
    DL_TimerG_stopCounter(ADC0_EVENT_TIMER);
    DL_ADC12_disableConversions(ADC0_INST);
    ADC0_DataValid = 1;
}
