#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"

#define EVENT_TIMER_CLK 40E6F // ADC事件定时器时钟频率(Hz)
#define ADC0_EVENT_TIMER TIMER_ADC0_INST // ADC0事件定时器名称

#define ADC_VREF 3.3F // ADC基准电压
#define ADC_VAL_TO_VOLTAGE(x) ((float)(x) * ADC_VREF / 4096) // ADC值转为电压(V)
#define IS_ADC0_DONE (ADC0_DataValid) // ADC0是否运行完成

typedef enum ADC_Status_t {
    ADC_STA_TIMEOUT,
    ADC_STA_DONE
} ADC_Status_t;

extern volatile uint8_t ADC0_DataValid;

/**
 * @brief ADC初始化
 */
void ADC_init(void);

/**
 * @brief 设置ADC0事件定时器
 * @param fs 采样率(Sa/s)
 * @return 实际采样率(Sa/s)
 */
float ADC0_setEventTimer(uint32_t fs);

/**
 * @brief 启动ADC0 DMA
 * @note 采样率由 @ref ADC0_setEventTimer 设置
 * @param dst 转换数据目的数组指针
 * @param cnt 采样点数
 */
void ADC0_startDMA(uint16_t* dst, uint16_t cnt);

/**
 * @brief 等待ADC0运行完成
 * @param timeout 超时时间(ms)
 * @retval ADC_STA_TIMEOUT: 等待超时
 * @retval ADC_STA_DONE: 运行完成
 */
ADC_Status_t ADC0_waitDone(uint32_t timeout);

void ADC0_DMADoneCallback(void);

#endif /* #ifndef __USER_ADC_H__ */
