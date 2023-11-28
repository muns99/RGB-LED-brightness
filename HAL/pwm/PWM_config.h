#ifndef PWM_CONFIG_H
#define PWM_CONFIG_H
#include "../../UTILITIES/STD_TYPES.h"
typedef enum __pwmTimer{
    PWM_TM0 = 0,
    PWM_TM1,
    PWM_TM2,
    PWM_TM3,
    PWM_TM4,
    PWM_TM5
}enu_pwmTimer_t;

typedef enum __pwmPortNumber
{
    PWM_PORTA = 0,
    PWM_PORTB   ,
    PWM_PORTC   ,
    PWM_PORTD   ,
    PWM_PORTE   ,
    PWM_PORTF   ,
    PWM_INVALID_PORT_NUMBER
}enu_pwmPortNumber_t;

typedef enum __pwmPinNumber
{
    PWM_PIN0 = 0,
    PWM_PIN1   ,
    PWM_PIN2   ,
    PWM_PIN3   ,
    PWM_PIN4   ,
    PWM_PIN5   ,
    PWM_PIN6   ,
    PWM_PIN7
}enu_pwmPinNumber_t;

typedef struct __pwmCFG{
    enu_pwmTimer_t enu_pwmTimer;
    uint16_t uint16_a_pwmFreq;
    uint8_t uint8_a_pwmDC;
    enu_pwmPortNumber_t enu_pwmPortNumber;
    enu_pwmPinNumber_t  enu_pwmPinNumber;
    uint16_t uint16_a_Onticks;
}str_pwmCFG_t;


    



#endif