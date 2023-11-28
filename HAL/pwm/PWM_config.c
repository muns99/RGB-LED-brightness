#include "PWM_config.h"

str_pwmCFG_t str_g_pwmCFG = {
    .enu_pwmPortNumber = PWM_PORTC,
    .enu_pwmPinNumber = PWM_PIN6,
    .enu_pwmTimer = PWM_TM0,
    .uint16_a_pwmFreq = 5000,
    .uint8_a_pwmDC = 50,
    .uint16_a_Onticks = 0
}; 