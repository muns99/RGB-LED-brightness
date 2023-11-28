#include "../../UTILITIES/STD_TYPES.h"
#include "../../UTILITIES/BIT_MATH.h"
#include "GPT_private.h"
#include "GPT_interface.h"
#include "GPT_config.h"

#define     TIMER_ADDR(TIMER_NUM)                      ( (TIMER_NUM < GPT_TIMER0_W) ? (TIMER(TIMER_NUM)) : ( TIMER_W( (TIMER_NUM - GPT_TIMER0_W) ) ) )
void (*ptr_func_gl_timerACallBacks[GPT_TIMER_NUM])(void) = {NULL_PTR};
void (*ptr_func_gl_timerBCallBacks[GPT_TIMER_NUM])(void) = {NULL_PTR};

enu_gptError_t GPT_init()
{
	enu_gptError_t enu_a_functionRet = GPT_OK;
   return enu_a_functionRet;
}
enu_gptError_t GPT_initTimer(str_timer_t *str_a_timer)
{
    /*to do*/ 
    //clear  TAEN in and TBEN in GPTMCTL
    //set value to GPTMCTL indicate timer mode
    //
    enu_gptError_t enu_a_functionRet = GPT_OK;
    if (str_a_timer != NULL)
    {  
        if (str_a_timer->timerMode == TIMER_ONE_SHOT || str_a_timer->timerMode == TIMER_PERIODIC )
        {
            if (str_a_timer->timerChannel == TIMER_CH_A || str_a_timer->timerChannel == TIMER_CONC)
            {
				        (str_a_timer->timerId < GPT_TIMER0_W) ? SET_BIT(GPT_RCGCTIMER, str_a_timer->timerId) 
							                                       :  SET_BIT(GPT_RCGCWTIMER, (str_a_timer->timerId - GPT_TIMER0_W)); 
                CLR_BIT(TIMER_ADDR(str_a_timer->timerId)->GPTMCTL,TAEN);
                TIMER_ADDR(str_a_timer->timerId)->GPTMCFG = ONE_SHOT_OR_PERIODIC_MODE_CONFIG;
                TIMER_ADDR(str_a_timer->timerId)->GPTMTAMR &= GPTMTAMR_MASK;
                TIMER_ADDR(str_a_timer->timerId)->GPTMTAMR |= str_a_timer->timerMode;
                //SET_BIT(TIMER_ADDR(str_a_timer->timerId)->GPTMIMR,TATOIM);
                //SET_BIT(TIMER_ADDR(str_a_timer->timerId)->GPTMCTL,TAEN);
                SET_BIT (TIMER_ADDR(str_a_timer->timerId)->GPTMICR,TATOCINT);
            }
            
        }
        //to do reminde options   

    }
    else
    {
        enu_a_functionRet = GPT_WRONG_ARGS;
    }
    return enu_a_functionRet;
}
enu_gptError_t GPT_startTimer(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel)
{
    enu_gptError_t enu_a_functionRet = GPT_OK;
    if( (enu_a_timerID <= GPT_TIMER5_W) && (enu_a_timerChannel <= TIMER_CONC) )
    {
				if(enu_a_timerChannel == TIMER_CH_A || enu_a_timerChannel == TIMER_CONC)
				{
						SET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMCTL, TAEN);
				}
				else
				{
						SET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMCTL, TBEN);
				}
    }
    else
    {
        enu_a_functionRet = GPT_WRONG_ARGS;
    }
    return enu_a_functionRet;
}
enu_gptError_t GPT_stopTimer(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel)
{
    enu_gptError_t enu_a_funcRet = GPT_OK;
    if ((enu_a_timerID <= GPT_TIMER5_W) && (enu_a_timerChannel <= TIMER_CONC))
    {
        if (enu_a_timerChannel == TIMER_CH_A || enu_a_timerChannel == TIMER_CONC)
        {
            CLR_BIT(TIMER_ADDR(enu_a_timerID)->GPTMCTL, TAEN);
        }
        else
        {
            CLR_BIT(TIMER_ADDR(enu_a_timerID)->GPTMCTL, TBEN);
        }
    }
    else
    {
        enu_a_funcRet = GPT_WRONG_ARGS;
    }
    return enu_a_funcRet;
}
enu_gptError_t GPT_loadTimer(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel, uint64_t uint64_a_loadTicks)
{
	enu_gptError_t enu_a_functionRet = GPT_OK;
   return enu_a_functionRet;
}
enu_gptError_t GPT_preloadTimer(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel, enu_timerScale_t enu_a_timerScale, uint64_t uint64_a_preloadValue)
{
    enu_gptError_t enu_a_funcRet = GPT_OK;
    if ((enu_a_timerID <= GPT_TIMER5_W) && (enu_a_timerChannel <= TIMER_CONC) 
         && ( NULL != uint64_a_preloadValue) && (enu_a_timerScale <= TIMER_SECONDS))
    {
        if (enu_a_timerChannel == TIMER_CH_A)
        {
            switch (enu_a_timerScale)
            {
            case TIMER_MICROSECONDS:
                {
                    TIMER_ADDR(enu_a_timerID)->GPTMTAPR = _8BIT_MICRO_PRE;
                    /* assuming tick time is 1 microsecond(50 as prescaler)*/
                    if (GET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMTAMR, TACDIR) == 0)
                    {
                        //downcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = uint64_a_preloadValue; 
                    }
                    else
                    {
                        //upcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = (_16BIT_MAX_TICKS - uint64_a_preloadValue); 
                    }
                    break;
                }
            case TIMER_MILLISECONDS:
                {
                    uint64_t uint16_a_ticks =  ( (uint64_a_preloadValue * F_CPU) / (_8BIT_MILLI_PRE * _MS_FACTOR) );
                    TIMER_ADDR(enu_a_timerID)->GPTMTAPR = _8BIT_MILLI_PRE;
                    if (GET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMTAMR, TACDIR) == 0)
                    {
                        //downcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = uint16_a_ticks; 
                    }
                    else
                    {
                        //upcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = (_16BIT_MAX_TICKS - uint16_a_ticks); 
                    }
                    break;
                }
                           
            case TIMER_SECONDS:
                {
                    enu_a_funcRet = GPT_WRONG_CONFIG;
                    break;
                }           
                default:
                    enu_a_funcRet = GPT_WRONG_ARGS;
                break;
            }
        }
        else if (enu_a_timerChannel == TIMER_CH_B)
        {
            switch (enu_a_timerScale)
            {
            case TIMER_MICROSECONDS:
                {
                    TIMER_ADDR(enu_a_timerID)->GPTMTBPR = _8BIT_MICRO_PRE;
                    /* assuming tick time is 1 microsecond(50 as prescaler)*/
                    if (GET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMTBMR, TACDIR) == 0)
                    {
                        //downcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTBILR = uint64_a_preloadValue; 
                    }
                    else
                    {
                        //upcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTBILR = (_16BIT_MAX_TICKS - uint64_a_preloadValue); 
                    }
                    break;
                }
            case TIMER_MILLISECONDS:
                {
                    uint64_t uint16_a_ticks =  ( (uint64_a_preloadValue * F_CPU) / (_8BIT_MILLI_PRE * _MS_FACTOR) );
                    TIMER_ADDR(enu_a_timerID)->GPTMTBPR = _8BIT_MILLI_PRE;
                    if (GET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMTBMR, TACDIR) == 0)
                    {
                        //downcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTBILR = uint16_a_ticks; 
                    }
                    else
                    {
                        //upcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTBILR = (_16BIT_MAX_TICKS - uint16_a_ticks); 
                    }
                    break;
                }
                           
            case TIMER_SECONDS:
                {
                    enu_a_funcRet = GPT_WRONG_CONFIG;
                    break;
                }           
                default:
                    enu_a_funcRet = GPT_WRONG_ARGS;
                break;
            }
           
        }
        else
        {
            switch (enu_a_timerScale)
            {
            case TIMER_MICROSECONDS:
                {
                    TIMER_ADDR(enu_a_timerID)->GPTMTAPR = _16BIT_MICRO_PRE;
                    /* assuming tick time is 1 microsecond(50 as prescaler)*/
                    if (GET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMTAMR, TACDIR) == 0)
                    {
                        //downcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = uint64_a_preloadValue; 
                    }
                    else
                    {
                        //upcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = (_16BIT_MAX_TICKS - uint64_a_preloadValue); 
                    }
                    break;
                }
            case TIMER_MILLISECONDS:
                {
                    TIMER_ADDR(enu_a_timerID)->GPTMTAPR = _16BIT_MILLI_PRE;
                    /* assuming tick time is 1 millisecond(50000 as prescaler)*/
                    if (GET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMTAMR, TACDIR) == 0)
                    {
                        //downcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = uint64_a_preloadValue; 
                    }
                    else
                    {
                        //upcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = (_16BIT_MAX_TICKS - uint64_a_preloadValue); 
                    }
                    break;
                }
                           
            case TIMER_SECONDS:
                {
                    /* assuming tick time is 1 millisecond(50000 as prescaler)*/
                    uint64_t uint16_a_ticks = (uint64_a_preloadValue * 1000);
                    TIMER_ADDR(enu_a_timerID)->GPTMTAPR = _16BIT_SEC_PRE;
                    if (GET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMTAMR, TACDIR) == 0)
                    {
                        //downcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = uint16_a_ticks; 
                    }
                    else
                    {
                        //upcounting
                        TIMER_ADDR(enu_a_timerID)->GPTMTAILR = (_16BIT_MAX_TICKS - uint16_a_ticks); 
                    }
                    break;
                }           
                default:
                    enu_a_funcRet = GPT_WRONG_ARGS;
                break;
            }
        } 
    }
    else
    {
        enu_a_funcRet = GPT_WRONG_ARGS;
    }
    return enu_a_funcRet;
}
enu_gptError_t GPT_getTimerElapsed(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel, uint64_t* ptr_uint64_a_elapsedTime)
{
	enu_gptError_t enu_a_functionRet = GPT_OK;
   return enu_a_functionRet;
}
enu_gptError_t GPT_getTimerRemaining(enu_timerID_t enu_a_timerID, enu_timerChannel_t enu_a_timerChannel, uint64_t* ptr_uint64_a_remainingTime)
{
    enu_gptError_t enu_a_funcRet = GPT_OK;
    if ((NULL_PTR != ptr_uint64_a_remainingTime) && (enu_a_timerID <= GPT_TIMER5_W) && (enu_a_timerChannel <= TIMER_CONC))
    {
        if ( (enu_a_timerChannel == TIMER_CH_A) || (enu_a_timerChannel == TIMER_CONC) )
        {
            if (GET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMTAMR, TACDIR) == 0)
            {
                *ptr_uint64_a_remainingTime = TIMER_ADDR(enu_a_timerID)->GPTMTAR;
            }
            else
            {
                *ptr_uint64_a_remainingTime = (TIMER_ADDR(enu_a_timerID)->GPTMTAV - TIMER_ADDR(enu_a_timerID)->GPTMTAR);
            }
        }
        else
        {
            if (GET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMTBMR, TBCDIR) == 0)
            {
                *ptr_uint64_a_remainingTime = TIMER_ADDR(enu_a_timerID)->GPTMTBR;
            }
            else
            {
                *ptr_uint64_a_remainingTime = (TIMER_ADDR(enu_a_timerID)->GPTMTBV - TIMER_ADDR(enu_a_timerID)->GPTMTBR);
            }
        }
    }
    else
    {
        enu_a_funcRet = GPT_WRONG_ARGS;
    }
    return enu_a_funcRet;
}
enu_gptError_t GPT_enableTimerInterrupt(enu_timerID_t enu_a_timerID, enu_timerinterrupt_t enu_a_timerinterrupt)
{
    enu_gptError_t enu_a_funcRet = GPT_OK;
    if( (enu_a_timerID <= GPT_TIMER5_W) && (enu_a_timerinterrupt <= GPT_WIDE_WRITE_UPDATE_ERROR) )
    {
        switch(enu_a_timerinterrupt)
        {
            case GPT_TIMER_A_TIME_OUT:
            case GPT_TIMER_A_CAP_MODE_MATCH:
            case GPT_TIMER_A_CAP_MODE_EVENT:
            case GPT_RTC:
            case GPT_TIMER_A_MATCH:
            {
                SET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMIMR, enu_a_timerinterrupt);
							  SET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMICR, enu_a_timerinterrupt);
                break;
            }
            case GPT_TIMER_B_TIME_OUT:
            case GPT_TIMER_B_CAP_MODE_MATCH:
            case GPT_TIMER_B_CAP_MODE_EVENT:
            case GPT_TIMER_B_MATCH:
            {
                SET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMIMR, enu_a_timerinterrupt + RES_BITS);
							  SET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMICR, enu_a_timerinterrupt + RES_BITS);
                break;
            }
            case GPT_WIDE_WRITE_UPDATE_ERROR:
            {
                SET_BIT(TIMER_ADDR(enu_a_timerID)->GPTMIMR, WUEIM);
                break;
            }
            default:
            break;
        }
    }
    else
    {
        enu_a_funcRet = GPT_WRONG_ARGS;
    }
    return enu_a_funcRet;
}
enu_gptError_t GPT_disableTimerInterrupt(enu_timerID_t enu_a_timerID, enu_timerinterrupt_t enu_a_timerinterrupt)
{
    enu_gptError_t enu_a_funcRet = GPT_OK;
    if( (enu_a_timerID <= GPT_TIMER5_W) && (enu_a_timerinterrupt <= GPT_WIDE_WRITE_UPDATE_ERROR) )
    {
        switch(enu_a_timerinterrupt)
        {
            case GPT_TIMER_A_TIME_OUT:
            case GPT_TIMER_A_CAP_MODE_MATCH:
            case GPT_TIMER_A_CAP_MODE_EVENT:
            case GPT_RTC:
            case GPT_TIMER_A_MATCH:
            {
                CLR_BIT(TIMER_ADDR(enu_a_timerID)->GPTMIMR, enu_a_timerinterrupt);
                break;
            }
            case GPT_TIMER_B_TIME_OUT:
            case GPT_TIMER_B_CAP_MODE_MATCH:
            case GPT_TIMER_B_CAP_MODE_EVENT:
            case GPT_TIMER_B_MATCH:
            {
                CLR_BIT(TIMER_ADDR(enu_a_timerID)->GPTMIMR, enu_a_timerinterrupt + RES_BITS);
                break;
            }
            case GPT_WIDE_WRITE_UPDATE_ERROR:
            {
                CLR_BIT(TIMER_ADDR(enu_a_timerID)->GPTMIMR, WUEIM);
                break;
            }
            default:
            break;
        }
    }
    else
    {
        enu_a_funcRet = GPT_WRONG_ARGS;
    }
    return enu_a_funcRet;
}
enu_gptError_t GPT_setTimerCallBack(enu_timerID_t enu_a_timerID ,enu_timerChannel_t enu_a_timerChannel ,void (*ptr_func_CB)(void))
{
    enu_gptError_t enu_a_functioRet = GPT_OK;
    if (enu_a_timerID <= GPT_TIMER5_W)
    {
        if (enu_a_timerID <= GPT_TIMER5_W)
        {
            if (ptr_func_CB != NULL)
            {
                if (enu_a_timerChannel == TIMER_CH_A || enu_a_timerChannel == TIMER_CONC)
                {
                    ptr_func_gl_timerACallBacks[enu_a_timerID] = ptr_func_CB;
                }
                else if (enu_a_timerChannel == TIMER_CH_B)
                {
                    ptr_func_gl_timerBCallBacks[enu_a_timerID] = ptr_func_CB;
                }
                else
                {
                    enu_a_functioRet = GPT_WRONG_ARGS;
                }
            }
            else
            {
                enu_a_functioRet = GPT_WRONG_ARGS;
            }
        }
        else
        {
            //to do for wide timers
        }
    }
    else
    {
        enu_a_functioRet = GPT_WRONG_ARGS;
    }
    return enu_a_functioRet;
}
/**********************TIMER_HANDLERS********************/
void TIMER0A_Handler(void)
{
    if (ptr_func_gl_timerACallBacks[GPT_TIMER0] != NULL)
    {
        ptr_func_gl_timerACallBacks[GPT_TIMER0]();
			SET_BIT(TIMER_ADDR(GPT_TIMER0)->GPTMICR, 0);
    }
    
}
void TIMER1A_Handler(void)
{
    if (ptr_func_gl_timerACallBacks[GPT_TIMER1] != NULL)
    {
        ptr_func_gl_timerACallBacks[GPT_TIMER1]();
			  
    }
}
void TIMER2A_Handler(void)
{
    if (ptr_func_gl_timerACallBacks[GPT_TIMER2] != NULL)
    {
        ptr_func_gl_timerACallBacks[GPT_TIMER2]();
    }
}
void TIMER3A_Handler(void)
{

}
void TIMER4A_Handler(void)
{

}
void TIMER5A_Handler(void)
{

}



void TIMER0B_Handler(void)
{
    if (ptr_func_gl_timerBCallBacks[GPT_TIMER0] != NULL)
    {
        ptr_func_gl_timerBCallBacks[GPT_TIMER0]();
    }
}
void TIMER1B_Handler(void)
{
    if (ptr_func_gl_timerBCallBacks[GPT_TIMER0] != NULL)
    {
        ptr_func_gl_timerBCallBacks[GPT_TIMER0]();
    }
}
void TIMER2B_Handler(void)
{

}
void TIMER3B_Handler(void)
{

}
void TIMER4B_Handler(void)
{

}
void TIMER5B_Handler(void)
{

}
void WTIMER0A_Handler(void)
 {
	 if (ptr_func_gl_timerACallBacks[GPT_TIMER0_W] != NULL)
    {
        ptr_func_gl_timerACallBacks[GPT_TIMER0_W]();
			  SET_BIT(TIMER_ADDR(GPT_TIMER0_W)->GPTMICR, 0);
    }
	 
 }
void WTIMER0B_Handler(void)
{
	 
}
void WTIMER1A_Handler(void)
{
	 
}
void WTIMER1B_Handler(void)
{
	 
}
void WTIMER2A_Handler(void){
	 
}
void WTIMER2B_Handler(void){
	 
}
void WTIMER3A_Handler(void){
	 
}
void WTIMER3B_Handler(void){
	 
}
void WTIMER4A_Handler(void){
	 
}
void WTIMER4B_Handler(void){
	 
}
void WTIMER5A_Handler(void){
	 
}
void WTIMER5B_Handler(void){
	 
}
/*******************************************************/
