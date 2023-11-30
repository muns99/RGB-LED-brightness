#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/gpio/GPIO_interface.h"
#include "../../MCAL/gpt/GPT_interface.h"
#include "PWM_private.h"
#include "PWM_config.h"
#include "PWM_interface.h"

extern str_pwmCFG_t str_g_pwmCFG;

enu_pwmError_t  PWM_init(void)
{
    enu_pwmError_t enu_funcRet = PWM_OK;

        if( (str_g_pwmCFG.enu_pwmPinNumber <= PWM_PIN7) && (str_g_pwmCFG.enu_pwmPortNumber <= PWM_PORTF) 
            && (str_g_pwmCFG.enu_pwmTimer <= PWM_TM5) && (str_g_pwmCFG.uint16_a_pwmFreq >= MIN_FREQ) 
            && (str_g_pwmCFG.uint16_a_pwmFreq <= MAX_FREQ) && (str_g_pwmCFG.uint8_a_pwmDC <= MAX_DC) )
            {
                st_gpioPinConfig_t str_a_pwmPin = 
                {
                    .port = str_g_pwmCFG.enu_pwmPortNumber,
                    .pinNum = str_g_pwmCFG.enu_pwmPinNumber,
                    .pinMode = DIGITAL_OUTPUT_2MA
                };
                str_timer_t str_a_pwmTimer = 
                {
                    .timerChannel = TIMER_CH_A,
                    .timerId = str_g_pwmCFG.enu_pwmTimer,
                    .timerMode = TIMER_PERIODIC
                };
                enu_funcRet |= GPIO_initPin(&str_a_pwmPin);
                enu_funcRet |= GPT_initTimer(&str_a_pwmTimer);
                enu_funcRet |= GPT_setTimerCallBack(str_a_pwmTimer.timerId, TIMER_CH_A, PWM_logic);
                enu_funcRet |= GPT_enableTimerInterrupt(str_a_pwmTimer.timerId, GPT_TIMER_A_TIME_OUT);
                str_g_pwmCFG.uint16_a_Onticks = ( (TICK_TIME_FACTOR * str_g_pwmCFG.uint8_a_pwmDC) / (str_g_pwmCFG.uint16_a_pwmFreq * MAX_DC) );
            }
            else
            {
                enu_funcRet = PWM_WRONG_ARGS;
            }
    return enu_funcRet;
}
enu_pwmError_t  PWM_changeDutyCycle(uint8_t uint8_a_newPwmDC)
{
    enu_pwmError_t enu_funcRet = PWM_OK;
    if(uint8_a_newPwmDC <= MAX_DC)
    {
        str_g_pwmCFG.uint8_a_pwmDC = uint8_a_newPwmDC;
        str_g_pwmCFG.uint16_a_Onticks = (( (TICK_TIME_FACTOR / MAX_DC) * str_g_pwmCFG.uint8_a_pwmDC) / str_g_pwmCFG.uint16_a_pwmFreq);

    }
    else
    {
        enu_funcRet = PWM_WRONG_ARGS;
    }
    return enu_funcRet;
}
enu_pwmError_t  PWM_turnOn()
{
    enu_pwmError_t enu_funcRet = PWM_OK;
    enu_funcRet |= GPT_startTimer(str_g_pwmCFG.enu_pwmTimer, TIMER_CH_A);
    return enu_funcRet;
}
enu_pwmError_t  PWM_turnOff()
{
    enu_pwmError_t enu_funcRet = PWM_OK;
	  GPIO_setPinValue(str_g_pwmCFG.enu_pwmPortNumber, str_g_pwmCFG.enu_pwmPinNumber, GPIO_LOW);
    enu_funcRet |= GPT_stopTimer(str_g_pwmCFG.enu_pwmTimer, TIMER_CH_A);
    return enu_funcRet;
}

void PWM_logic(void)
{
    static boolean periodFlag = TRUE;    
    if (periodFlag == TRUE)
    {
        GPT_preloadTimer(str_g_pwmCFG.enu_pwmTimer, TIMER_CH_A, TIMER_MICROSECONDS, str_g_pwmCFG.uint16_a_Onticks);
        GPIO_setPinValue(str_g_pwmCFG.enu_pwmPortNumber, str_g_pwmCFG.enu_pwmPinNumber, GPIO_HIGH);
        periodFlag = FALSE;
    }
    else if(periodFlag == FALSE)
    {
        GPT_preloadTimer(str_g_pwmCFG.enu_pwmTimer, TIMER_CH_A, TIMER_MICROSECONDS, ( (TICK_TIME_FACTOR / str_g_pwmCFG.uint16_a_pwmFreq) - str_g_pwmCFG.uint16_a_Onticks)  );
				//GPIO_togglePin(str_g_pwmCFG.enu_pwmPortNumber, str_g_pwmCFG.enu_pwmPinNumber);
        GPIO_setPinValue(str_g_pwmCFG.enu_pwmPortNumber, str_g_pwmCFG.enu_pwmPinNumber, GPIO_LOW);
        periodFlag = TRUE;
    }
		
}