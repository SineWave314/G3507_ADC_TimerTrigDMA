//#ifndef __ADC_H__
#if 0
#define __ADC_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"

#define ADC_VREF 3.3F // ADC基准电压
// ADC值转为电压(V)
#define ADC_VAL_TO_VOLTAGE(x) ((float)(x) * ADC_VREF / 4096)

/**
 * @brief ADC初始化
 */
void ADC_init(void);

/**
 * @brief 启动ADC0
 * @details 使用中断方式, 非阻塞
 */
void ADC0_start(void);

/**
 * @brief 获取ADC0数据
 * @param timeout 超时时间(ms)
 * @return ADC0转换数据
 */
uint16_t ADC0_getData(uint32_t timeout);

/**
 * @brief 获取ADC0电压值
 * @param timeout 超时时间(ms)
 * @return ADC0电压值
 */
float ADC0_getVoltage(uint32_t timeout);

/**
 * @brief 启动ADC1
 * @details 使用中断方式, 非阻塞
 */
void ADC1_start(void);

/**
 * @brief 获取ADC1数据
 * @param mem ADC1转换内存序号
 * @param timeout 超时时间(ms)
 * @return ADC1对应内存序号转换数据
 */
uint16_t ADC1_getData(uint8_t mem, uint32_t timeout);

/**
 * @brief 获取ADC1电压值
 * @param mem ADC1转换内存序号
 * @param timeout 超时时间(ms)
 * @return ADC1对应内存序号电压值
 */
float ADC1_getVoltage(uint8_t mem, uint32_t timeout);

void ADC0_mem0ResultLoadedCallback(void);
void ADC1_mem3ResultLoadedCallback(void);

#endif /* #ifndef __USER_ADC_H__ */
