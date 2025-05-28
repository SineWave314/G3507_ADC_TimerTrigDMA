#if 0
#include "ADC.h"

volatile uint16_t ADC0_Data = 0;
volatile uint8_t ADC0_DataValid = 0;
volatile uint16_t ADC1_Data[4] = {0};
volatile uint8_t ADC1_DataValid = 0;

/**
 * @brief ADC初始化
 */
void ADC_init(void) {
    NVIC_EnableIRQ(ADC0_INST_INT_IRQN);
    NVIC_EnableIRQ(ADC1_INST_INT_IRQN);
}

/**
 * @brief 启动ADC0
 * @details 使用中断方式, 非阻塞
 */
void ADC0_start(void) {
    ADC0_DataValid = 0;
    DL_ADC12_startConversion(ADC0_INST);
}

/**
 * @brief 获取ADC0数据
 * @param timeout 超时时间(ms)
 * @return ADC0转换数据
 */
uint16_t ADC0_getData(uint32_t timeout) {
    uint32_t startTime = Tick;
    while (!ADC0_DataValid) {
        if (Tick - startTime >= timeout) return 0;
    }
    return ADC0_Data;
}

/**
 * @brief 获取ADC0电压值
 * @param timeout 超时时间(ms)
 * @return ADC0电压值
 */
float ADC0_getVoltage(uint32_t timeout) {
    uint32_t startTime = Tick;
    while (!ADC0_DataValid) {
        if (Tick - startTime >= timeout) return 0;
    }
    return ADC_VAL_TO_VOLTAGE(ADC0_Data);
}

/**
 * @brief 启动ADC1
 * @details 使用中断方式, 非阻塞
 */
void ADC1_start(void) {
    ADC1_DataValid = 0;
    DL_ADC12_startConversion(ADC1_INST);
}

/**
 * @brief 获取ADC1数据
 * @param mem ADC1转换内存序号
 * @param timeout 超时时间(ms)
 * @return ADC1对应内存序号转换数据
 */
uint16_t ADC1_getData(uint8_t mem, uint32_t timeout) {
    uint32_t startTime = Tick;
    while (!ADC0_DataValid) {
        if (Tick - startTime >= timeout) return 0;
    }
    return ADC1_Data[mem];
}

/**
 * @brief 获取ADC1电压值
 * @param mem ADC1转换内存序号
 * @param timeout 超时时间(ms)
 * @return ADC1对应内存序号电压值
 */
float ADC1_getVoltage(uint8_t mem, uint32_t timeout) {
    uint32_t startTime = Tick;
    while (!ADC0_DataValid) {
        if (Tick - startTime >= timeout) return 0;
    }
    return ADC_VAL_TO_VOLTAGE(ADC1_Data[mem]);
}

// ADC0中断回调
void ADC0_mem0ResultLoadedCallback(void) {
    ADC0_Data = DL_ADC12_getMemResult(ADC0_INST, ADC0_ADCMEM_0);
    ADC0_DataValid = 1;
    DL_ADC12_enableConversions(ADC0_INST);
}

// ADC1中断回调
void ADC1_mem3ResultLoadedCallback(void) {
    ADC1_Data[0] = DL_ADC12_getMemResult(ADC1_INST, ADC1_ADCMEM_0);
    ADC1_Data[1] = DL_ADC12_getMemResult(ADC1_INST, ADC1_ADCMEM_1);
    ADC1_Data[2] = DL_ADC12_getMemResult(ADC1_INST, ADC1_ADCMEM_2);
    ADC1_Data[3] = DL_ADC12_getMemResult(ADC1_INST, ADC1_ADCMEM_3);
    ADC1_DataValid = 1;
    DL_ADC12_enableConversions(ADC1_INST);
}
#endif