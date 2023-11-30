#include "../LIB/std_types.h"
#include "../HAL/button/button_interface.h"
#include "../HAL/led/led_interface.h"
#include "../HAL/pwm/PWM_interface.h"
#include "../SERVICES/tmu/tmu_interface.h"
#include "app_interface.h"
#include "app_config.h"
uint8_t uint8_gl_appSequenceCounter = 0;
uint16_t uint16_gl_duty = LED_OFF;
uint16_t uint16_appTime = 0;

void APP_firstPress(void)
{
	uint16_gl_duty = THIRTY_PERCENT_ON;
}
void APP_secondPress(void)
{
	uint16_gl_duty = FIFTY_PERECENT_ON;
}
void APP_thirdPress(void)
{
	uint16_gl_duty = NINTY_PERCENT_ON;
}
void APP_fourthPress(void)
{
	uint16_gl_duty = LED_OFF;
}
void APP_fifthPress(void)
{

}
void (*ptr_func_appSequenceFunctions[])(void) = {APP_firstPress,APP_secondPress,APP_thirdPress,APP_fourthPress,APP_fifthPress};
void APP_sequence(void)
{
    if (uint8_gl_appSequenceCounter < APP_SEQUENCE_COUNT)
    {
        ptr_func_appSequenceFunctions[uint8_gl_appSequenceCounter++]();
    }
    else
    {
        uint8_gl_appSequenceCounter = RESET_COUNTER;
    }
    debounce();
}
void APP_taskHandler(void)
{
	uint16_appTime++;
	if(uint16_gl_duty == RESET_COUNTER)
		LED_off(&st_g_greenLed);
	else if(uint16_appTime == uint16_gl_duty)
		LED_off(&st_g_greenLed);
	if(uint16_appTime == LED_PERIOD  )
	{
		uint16_appTime = RESET_COUNTER;
		if(uint16_gl_duty != LED_OFF)
		LED_on(&st_g_greenLed);
	}
}

enu_appErrorState_t APP_init()
{
    enu_appErrorState_t enu_a_functionRet = APP_SUCCESS;
		BUTTON_init(&st_g_sw1);
    LED_init(&st_g_greenLed);
		//LED_toggle(&st_g_greenLed);
	  TMU_createTask(&st_gl_appTask);
}
enu_appErrorState_t APP_start()
{
    enu_appErrorState_t enu_a_functionRet = APP_SUCCESS;
    if (BUTTON_enable(&st_g_sw1) == BUTTON_SUCCESS)
    {
       TMU_startTask(&st_gl_appTask.uint8_a_taskId,(uint64_t *)&st_gl_appTask.taskInterval);
    }
    else
    {
        enu_a_functionRet = APP_NOT_SUCCESS;
    }
    return enu_a_functionRet;
}
enu_appErrorState_t APP_stop()
{
    enu_appErrorState_t enu_a_functionRet = APP_SUCCESS;
    if (BUTTON_disable(&st_g_sw1) == BUTTON_SUCCESS)
    {
        /*do nothing*/
    }
    else
    {
        enu_a_functionRet = APP_NOT_SUCCESS;
    }
    return enu_a_functionRet;
}

