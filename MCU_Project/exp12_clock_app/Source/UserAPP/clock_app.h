#ifndef __CLOCK_APP_H
#define __CLOCK_APP_H

#include <stdint.h>

typedef enum {
    MODE_NORMAL      = 0,
    MODE_SET_HOUR    = 1,
    MODE_SET_MINUTE  = 2,
    MODE_ALARM_HOUR  = 3,
    MODE_ALARM_MINUTE = 4,
} ClockMode_t;

/* Public API của Application Layer */
void ClockApp_Init(void);
void ClockApp_Task_1ms(void);
void ClockApp_Task_1s(void);

#endif /* __CLOCK_APP_H */