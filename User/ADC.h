#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"

#define ADC0_EVENT_TIMER TIMER_ADC0_INST // ADC0事件定时器名称
#define ADC0_EVENT_TIMER_CLK 80E6F // ADC0事件定时器时钟频率(Hz)
#define ADC1_EVENT_TIMER TIMER_ADC1_INST // ADC1事件定时器名称
#define ADC1_EVENT_TIMER_CLK 40E6F // ADC1事件定时器时钟频率(Hz)

#define ADC_VREF 3.3F // ADC基准电压
#define ADC_VAL_TO_VOLTAGE(x) ((float)(x) * ADC_VREF / 4096) // ADC值转为电压(V)
#define IS_ADC0_DONE (ADC0_DataValid) // ADC0是否运行完成
#define IS_ADC1_DONE (ADC1_DataValid) // ADC1是否运行完成

typedef enum ADC_Status_t {
    ADC_STA_TIMEOUT,
    ADC_STA_DONE
} ADC_Status_t;

extern volatile uint8_t ADC0_DataValid;
extern volatile uint8_t ADC1_DataValid;

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
 * @brief 设置ADC1事件定时器
 * @param fs 采样率(Sa/s)
 * @return 实际采样率(Sa/s)
 */
float ADC1_setEventTimer(uint32_t fs);

/**
 * @brief 启动ADC0 DMA
 * @note 采样率由 @ref ADC0_setEventTimer 设置
 * @param dst 转换数据目的数组指针
 * @param cnt 采样点数
 */
void ADC0_startDMA(uint16_t* dst, uint16_t cnt);

/**
 * @brief 启动ADC1 DMA FIFO模式
 * @note 采样率由 @ref ADC1_setEventTimer 设置
 * @details 重复序列转换, 2通道, 启用FIFO
 * @param dst 转换数据目的数组指针(数组长度 = cnt * 2)
 * @param cnt 每通道采样点数
 */
void ADC1_startDMAFIFO(uint16_t* dst, uint16_t cnt);

/**
 * @brief 提取ADC序列转换数据
 * @param src 源数组指针(数组长度 = dstLen * step)
 * @param dst 目的数组指针
 * @param dstLen 目的数组长度
 * @param step 步进值
 */
void ADC_extractData(uint16_t* src, uint16_t* dst, int dstLen, int step);

/**
 * @brief 等待ADC0运行完成
 * @param timeout 超时时间(ms)
 * @retval ADC_STA_TIMEOUT: 等待超时
 * @retval ADC_STA_DONE: 运行完成
 */
ADC_Status_t ADC0_waitDone(uint32_t timeout);

/**
 * @brief 等待ADC1运行完成
 * @param timeout 超时时间(ms)
 * @retval ADC_STA_TIMEOUT: 等待超时
 * @retval ADC_STA_DONE: 运行完成
 */
ADC_Status_t ADC1_waitDone(uint32_t timeout);

void ADC0_DMADoneCallback(void);
void ADC1_DMADoneCallback(void);

#endif /* #ifndef __USER_ADC_H__ */
