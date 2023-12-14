#include "../../LIB/std_types.h"
#include "../../MCAL/gpio/gpio_interface.h"
#include "button_config.h"
#include "button_private.h"
#include "button_interface.h"

void getButtonGpioPinStruct(st_button_t *st_a_button,st_gpioPinConfig_t *st_a_buttonPin,enu_buttonErrorState_t *enu_a_functionRet)
{
    st_a_buttonPin->port =  st_a_button->buttonPort;
    st_a_buttonPin->pinNum = st_a_button->buttonPin;
    switch (st_a_button->buttonMode)
    {
        case BUTTON_PULLUP_MODE:
        {
            st_a_buttonPin->pinMode = INPUT_PULL_UP;
            break;
        }
        case BUTTON_PULLDOWN_MODE:
        {
           st_a_buttonPin->pinMode = INPUT_PULL_DOWN;
            break;
        }
        case BUTTON_INTERRUPT_RISING_EDGE_MODE:
        {
            st_a_buttonPin->pinMode = INTERRUPT_RISING_EDGE;
            break;
        }
        case BUTTON_INTERRUPT_FALLING_EDGE_MODE:
        {
            st_a_buttonPin->pinMode = INTERRUPT_FALLING_EDGE;
            break;
        }
        case BUTTON_INTERRUPT_BOTH_EDGES_MODE:
        {
            st_a_buttonPin->pinMode = INTERRUPT_BOTH_EDGES;
            break;
        }
        default:
        {
            enu_a_functionRet = BUTTON_INVALID_STATE;
            break;
        }
    }
    return enu_a_functionRet;
        
}

enu_buttonErrorState_t BUTTON_init(st_button_t *st_a_button)
{
    enu_buttonErrorState_t enu_a_functionRet = BUTTON_SUCCESS;
    st_gpioPinConfig_t st_a_buttonPin;
    if (st_a_button != NULL)
    {
        getButtonGpioPinStruct(st_a_button,&st_a_buttonPin,&enu_a_functionRet);
        if (enu_a_functionRet == BUTTON_SUCCESS)
        {
            if (st_a_button ->buttonHandler != NULL)
            {
                enu_a_functionRet = GPIO_initPin(&st_a_buttonPin);
            }
            else
            {
                enu_a_functionRet = BUTTON_INVALID_STATE;
            }
            
            
        }
        else
        {
            enu_a_functionRet = BUTTON_INVALID_STATE;
        }
        
    }
    else
    {
        enu_a_functionRet = BUTTON_INVALID_STATE;
    }
    return enu_a_functionRet;
}


enu_buttonErrorState_t BUTTON_getButtonState(st_button_t *st_a_button,uint8_t *uint8_a_buttonState)
{
    enu_buttonErrorState_t enu_a_functionRet = BUTTON_SUCCESS;
    st_gpioPinConfig_t st_a_buttonPin ;
    if (st_a_button != NULL)
    {
        if (uint8_a_buttonState != NULL)
        {
            getButtonGpioPinStruct(st_a_button,&st_a_buttonPin,&enu_a_functionRet);
            if (enu_a_functionRet == BUTTON_SUCCESS)
            {
                enu_a_functionRet = GPIO_getPinValue(st_a_button->buttonPort,st_a_button->buttonPin,uint8_a_buttonState); 
            }
            else
            {
                enu_a_functionRet = BUTTON_INVALID_STATE;
            }
            
        }
        else
        {
            enu_a_functionRet = BUTTON_INVALID_STATE;
        }     
    }
    else
    {
        enu_a_functionRet = BUTTON_INVALID_STATE;
    }
    return enu_a_functionRet;
}
enu_buttonErrorState_t BUTTON_enable(st_button_t *st_a_button)
{
    enu_buttonErrorState_t enu_a_functionRet = BUTTON_SUCCESS;
    if (st_a_button != NULL)
    {
    
        enu_a_functionRet = GPIO_enableInterrupt(st_a_button->buttonPort,st_a_button->buttonPin,st_a_button->buttonHandler); 
        if (enu_a_functionRet != GPIO_SUCCESS)
        {
            enu_a_functionRet = BUTTON_NOT_SUCCESS;
        }
        else
        {
            /*do nothing*/
        }
       
    }
    else
    {
        enu_a_functionRet = BUTTON_INVALID_STATE;
    }
    return enu_a_functionRet;
}
enu_buttonErrorState_t BUTTON_disable(st_button_t *st_a_button)
{
    enu_buttonErrorState_t enu_a_functionRet = BUTTON_SUCCESS;
    if (st_a_button != NULL)
    {
    
        enu_a_functionRet = GPIO_disableInterrupt(st_a_button->buttonPort,st_a_button->buttonPin); 
        if (enu_a_functionRet != GPIO_SUCCESS)
        {
            enu_a_functionRet = BUTTON_NOT_SUCCESS;
        }
        else
        {
            /*do nothing*/
        }
    
    }
    else
    {
        enu_a_functionRet = BUTTON_INVALID_STATE;
    }
    return enu_a_functionRet;
}
enu_buttonErrorState_t BUTTON_deInit(st_button_t *st_a_button)
{

}