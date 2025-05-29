#ifndef __USER_TASK_H__
#define __USER_TASK_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"
#include "ADC.h"

#define ADC0_DATA_LEN 1024
#define ADC1_DATA_LEN 256
#define ADC1_CH_DATA_LEN (ADC1_DATA_LEN >> 1)

void UserTask_init(void);
void UserTask_loop(void);
void UserTask_tick(void);

#endif /* #ifndef __USER_TASK_H__ */
