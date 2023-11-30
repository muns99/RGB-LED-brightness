#include "../../MCAL/gpt/GPT_interface.h"
#include "tmu_config.h"
/// @tmu_instances //////////////////////
st_tmu_t st_gl_tmuInstances[TMU_INSTANCES] = {
    {
        .timer.timerId = GPT_TIMER0_W,
        .timer.timerChannel = TIMER_CONC,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_A_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER0_W,
        .timer.timerChannel = TIMER_CH_B,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_B_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER1_W,
        .timer.timerChannel = TIMER_CH_A,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_A_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER1_W,
        .timer.timerChannel = TIMER_CH_B,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_B_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER2_W,
        .timer.timerChannel = TIMER_CH_A,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_A_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER2_W,
        .timer.timerChannel = TIMER_CH_B,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_B_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER3_W,
        .timer.timerChannel = TIMER_CH_A,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_A_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER4_W,
        .timer.timerChannel = TIMER_CH_B,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_B_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER4_W,
        .timer.timerChannel = TIMER_CH_A,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_A_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER4_W,
        .timer.timerChannel = TIMER_CH_B,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_B_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER5_W,
        .timer.timerChannel = TIMER_CH_A,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_A_TIME_OUT
    },
    {
        .timer.timerId = GPT_TIMER5_W,
        .timer.timerChannel = TIMER_CH_B,
        .maxTime    = MAX_TIME ,  //miili seconds
        .timerInterrupt = GPT_TIMER_B_TIME_OUT
    }
};