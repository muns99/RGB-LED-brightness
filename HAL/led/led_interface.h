#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_ 

typedef enum __ledState 
{
    LED_ON = 0,
    LED_OFF   ,
    INVALID_STATE
}enu_ledState_t;

typedef enum __ledErrorState
{
    LED_SUCCESS  =0      ,
    LED_NOT_SUCCES      ,
    LED_INVALID_STATE   
}enu_ledErrorState_t;

typedef enum __ledPin
{
    LED_PIN0    = 0 ,
    LED_PIN1        ,
    LED_PIN2        ,
    LED_PIN3        ,
    LED_PIN4        ,
    LED_PIN5        ,
    LED_PIN6        ,
    LED_PIN7        
}enu_ledPin_t;

typedef enum __ledPort
{
    LED_PORTA   = 0 ,
    LED_PORTB       ,
    LED_PORTC       ,
    LED_PORTD       ,
    LED_PORTE       ,
    LED_PORTF
}enu_ledPort_t;

typedef struct __led
{
    enu_ledPin_t ledPin;
    enu_ledPort_t ledPort;
    enu_ledState_t ledState;
}st_led_t;

enu_ledErrorState_t LED_init(st_led_t *st_a_led);
enu_ledErrorState_t LED_on(st_led_t *st_a_led);
enu_ledErrorState_t LED_off(st_led_t *st_a_led);
enu_ledErrorState_t LED_toggle(st_led_t *st_a_led);

#endif