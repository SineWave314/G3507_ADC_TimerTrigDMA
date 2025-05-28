#include "Tick.h"

volatile uint32_t Tick = 0;

/**
 * @brief 延时(使用SysTick中断计时)
 * @param t 延时时间(ms)
 */
void Tick_delay(uint32_t t) {
    uint32_t tEnd = Tick + t;
    while (Tick < tEnd);
}

// SysTick中断回调(1ms)
void Tick_SysTickCallback(void) {
    Tick++;
    UserTask_tick();
}
