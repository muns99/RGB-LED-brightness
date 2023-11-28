#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H

typedef enum __pwmError{
    PWM_OK = 0,
    PWM_WRONG_ARGS,
    PWM_WRONG_CONFIG
}enu_pwmError_t;



enu_pwmError_t  PWM_init(void);
enu_pwmError_t  PWM_changeDutyCycle(uint8_t uint8_a_newPwmDC);
enu_pwmError_t  PWM_turnOn(void);
enu_pwmError_t  PWM_turnOff(void);


#endif