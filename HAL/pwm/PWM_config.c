#include "PWM_config.h"

str_pwmCFG_t str_g_pwmCFG = {
    .enu_pwmPortNumber = PWM_PORTF,
    .enu_pwmPinNumber = PWM_PIN3,
    .enu_pwmTimer = PWM_TM0,
    .uint16_a_pwmFreq = 1000,
    .uint8_a_pwmDC = 50,
    .uint16_a_Onticks = 0
}; 
