#ifndef GPT_INTERFACE_H_
#define GPT_INTERFACE_H_ 
#include "../../UTILITIES/STD_TYPES.h"
#include "GPT_config.h"
typedef enum __gptError{
    GPT_OK = 0,
    GPT_WRONG_ARGS,
    GPT_WRONG_CONFIG,
    GPT_NOK
}enu_gptError_t;
typedef enum __timerID{
    GPT_TIMER0 = 0,
    GPT_TIMER1,
    GPT_TIMER2,
    GPT_TIMER3,
    GPT_TIMER4,
    GPT_TIMER5,
    GPT_TIMER0_W,
    GPT_TIMER1_W,
    GPT_TIMER2_W,
    GPT_TIMER3_W,
    GPT_TIMER4_W,
    GPT_TIMER5_W
} enu_timerID_t;
typedef enum __timerScale{
    TIMER_MICROSECONDS = 0,
    TIMER_MILLISECONDS,
    TIMER_SECONDS
} enu_timerScale_t;
typedef enum __timerChannel{
    TIMER_CH_A = 0,
    TIMER_CH_B    ,
    TIMER_CONC
} enu_timerChannel_t;

typedef enum __timerinterrupt{
    GPT_TIMER_A_TIME_OUT = 0,
    GPT_TIMER_A_CAP_MODE_MATCH,
    GPT_TIMER_A_CAP_MODE_EVENT,
    GPT_RTC,
    GPT_TIMER_A_MATCH,
    GPT_TIMER_B_TIME_OUT,
    GPT_TIMER_B_CAP_MODE_MATCH,
    GPT_TIMER_B_CAP_MODE_EVENT,
    GPT_TIMER_B_MATCH,
    GPT_WIDE_WRITE_UPDATE_ERROR    
} enu_timerinterrupt_t;

typedef enum __timerMode
{
    TIMER_ONE_SHOT  = 1 ,
    TIMER_PERIODIC      ,

}enu_timerMode_t;

typedef struct __timer
{
    enu_timerID_t timerId;
    enu_timerMode_t timerMode;
    enu_timerChannel_t timerChannel;
}str_timer_t;

extern str_gptCFG_t str_gl_cst_gptConfig;


enu_gptError_t GPT_init(void);
enu_gptError_t GPT_initTimer(str_timer_t *str_a_timer);
enu_gptError_t GPT_startTimer(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel);
enu_gptError_t GPT_stopTimer(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel);
enu_gptError_t GPT_loadTimer(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel, uint64_t uint64_a_loadTicks);
enu_gptError_t GPT_preloadTimer(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel, enu_timerScale_t enu_a_timerScale, uint64_t uint64_a_preloadValue);
enu_gptError_t GPT_getTimerElapsed(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel, uint64_t* ptr_uint64_a_elapsedTime);
enu_gptError_t GPT_getTimerRemaining(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel, uint64_t* ptr_uint64_a_remainingTime);
enu_gptError_t GPT_enableTimerInterrupt(enu_timerID_t enu_a_timerID, enu_timerinterrupt_t enu_a_timerinterrupt);
enu_gptError_t GPT_disableTimerInterrupt(enu_timerID_t enu_a_timerID, enu_timerinterrupt_t enu_a_timerinterrupt);
enu_gptError_t GPT_setTimerCallBack(enu_timerID_t enu_a_timerID ,enu_timerChannel_t enu_a_timerChannel ,void (*ptr_func_CB)(void));

#endif
