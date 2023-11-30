#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_ 
void APP_sequence(void);
void APP_taskHandler(void);
#define TASK_REPEAT	1 //
#define TASK_ID				0
st_tmuTask_t st_gl_appTask =
{
    NORMAL,
    TMU_PRIODIC,
    MILLI,
    TASK_REPEAT,//in miilies
    APP_taskHandler,
		TASK_ID//task id
};
st_button_t st_g_sw1 = {
    .buttonPort = BUTTON_PORTF,
    .buttonPin  = BUTTON_PIN4,
    .buttonMode = BUTTON_INTERRUPT_FALLING_EDGE_MODE,
    .buttonHandler = APP_sequence
};

st_led_t st_g_greenLed = {
    .ledPort = LED_PORTF,
    .ledPin  = LED_PIN3,
    .ledState= LED_OFF
};
#define LED_PERIOD				500			
#define THIRTY_PERCENT_ON	150
#define FIFTY_PERECENT_ON	250
#define NINTY_PERCENT_ON	450
#define LED_OFF						0
#define APP_SEQUENCE_COUNT	4
#define RESET_COUNTER			0
#endif