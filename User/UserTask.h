#ifndef __USER_TASK_H__
#define __USER_TASK_H__

#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "Tick.h"
#include "ADC.h"

void UserTask_init(void);
void UserTask_loop(void);
void UserTask_tick(void);

#endif /* #ifndef __USER_TASK_H__ */
