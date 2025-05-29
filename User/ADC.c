#include "ADC.h"

volatile uint8_t ADC0_DataValid = 0;
volatile uint8_t ADC1_DataValid = 0;

/**
 * @brief ADC初始化
 */
void ADC_init(void) {
    NVIC_EnableIRQ(ADC0_INST_INT_IRQN);
    NVIC_EnableIRQ(ADC1_INST_INT_IRQN);
}

/**
 * @brief 设置ADC0事件定时器
 * @param fs 采样率(Sa/s)
 * @return 实际采样率(Sa/s)
 */
float ADC0_setEventTimer(uint32_t fs) {
    uint32_t loadVal;
    loadVal = (uint32_t)(ADC0_EVENT_TIMER_CLK / (float)fs - 0.5F);
    DL_TimerG_setLoadValue(ADC0_EVENT_TIMER, loadVal);
    return (ADC0_EVENT_TIMER_CLK / (float)(loadVal + 1));
}

/**
 * @brief 设置ADC1事件定时器
 * @param fs 采样率(Sa/s)
 * @return 实际采样率(Sa/s)
 */
float ADC1_setEventTimer(uint32_t fs) {
    uint32_t loadVal;
    loadVal = (uint32_t)(ADC1_EVENT_TIMER_CLK / (float)fs - 0.5F);
    DL_TimerG_setLoadValue(ADC1_EVENT_TIMER, loadVal);
    return (ADC1_EVENT_TIMER_CLK / (float)(loadVal + 1));
}

/**
 * @brief 启动ADC0 DMA
 * @note 采样率由 @ref ADC0_setEventTimer 设置
 * @details 重复单通道转换, 禁用FIFO
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
 * @brief 启动ADC1 DMA FIFO模式
 * @note 采样率由 @ref ADC1_setEventTimer 设置
 * @details 重复序列转换, 2通道, 启用FIFO
 * @param dst 转换数据目的数组指针(数组长度 = cnt * 2)
 * @param cnt 每通道采样点数
 */
void ADC1_startDMAFIFO(uint16_t* dst, uint16_t cnt) {
    ADC1_DataValid = 0;

    // 配置ADC DMA
    DL_DMA_disableChannel(DMA, DMA_ADC1_CHAN_ID);
    DL_DMA_setSrcAddr(DMA, DMA_ADC1_CHAN_ID, DL_ADC12_getFIFOAddress(ADC1_INST));
    DL_DMA_setDestAddr(DMA, DMA_ADC1_CHAN_ID, (uint32_t)dst);

    // 使用FIFO, 2次16位数据压缩为32位数据
    DL_DMA_setTransferSize(DMA, DMA_ADC1_CHAN_ID, cnt);

    DL_DMA_enableChannel(DMA, DMA_ADC1_CHAN_ID);

    // 使能ADC
    DL_ADC12_enableConversions(ADC1_INST);
    delay_cycles(800);

    // 启动事件定时器
    DL_TimerG_startCounter(ADC1_EVENT_TIMER);
}

/**
 * @brief 提取ADC序列转换数据
 * @param src 源数组指针(数组长度 = dstLen * step)
 * @param dst 目的数组指针
 * @param dstLen 目的数组长度
 * @param step 步进值
 */
void ADC_extractData(uint16_t* src, uint16_t* dst, int dstLen, int step) {
    int i, j;
    for (i = 0, j = 0; i < dstLen; i++, j += step) {
        dst[i] = src[j];
    }
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

/**
 * @brief 等待ADC1运行完成
 * @param timeout 超时时间(ms)
 * @retval ADC_STA_TIMEOUT: 等待超时
 * @retval ADC_STA_DONE: 运行完成
 */
ADC_Status_t ADC1_waitDone(uint32_t timeout) {
    uint32_t startTime = Tick;
    while (!IS_ADC1_DONE) {
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

// ADC1中断回调
void ADC1_DMADoneCallback(void) {
    DL_TimerG_stopCounter(ADC1_EVENT_TIMER);
    DL_ADC12_disableConversions(ADC1_INST);
    ADC1_DataValid = 1;
}
