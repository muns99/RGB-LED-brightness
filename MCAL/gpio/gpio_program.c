#include "../../LIB/std_types.h"
#include "../../LIB/bit_math.h"
#include "gpio_interface.h"
#include "gpio_private.h"
#include "gpio_config.h"

#include "TM4C123.h"
#include "core_cm4.h" 

IRQn_Type enu_gl_gpioPortsIrq[]={GPIOA_IRQn,GPIOB_IRQn,GPIOC_IRQn,GPIOD_IRQn,GPIOE_IRQn,GPIOF_IRQn};
const st_gpioConfig_t st_gl_cst_gpioConfig;
void (*ptr_func_gl_gpioPortsHandlers[GPIO_PORTS][PORT_PINS])(void)={NULL};
void (*ptr_func_gl_pinInitializationFunctions[])(st_gpioPinConfig_t *st_a_pin) =   {digitalInputPinInit,
                                                                                    digitalOutput2maPinInit,
                                                                                    digitalOutput4maPinInit,
                                                                                    digitalOutput8maPinInit,
                                                                                    analogInputPinInit,
                                                                                    inputPullUpPinInit,
                                                                                    inputPullDownPinInit,
                                                                                    interruptRisingEdgePinInit,
                                                                                    interruptFallingEdgePinInit,
                                                                                    interruptBothEdgesPinInit
                                                                                    }; 

void digitalInputPinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
}
void digitalOutput2maPinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODR2R),st_a_pin->pinNum);   //set pin drive
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
}
void digitalOutput4maPinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODR4R),st_a_pin->pinNum);   //set pin drive
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
}
void digitalOutput8maPinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODR8R),st_a_pin->pinNum);   //set pin drive
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
}
void analogInputPinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
    ACCESS_REG(st_a_pin->port,GPIODEN) = ANALOG_PIN_MASK ;           //set pin as analog
}
void inputPullUpPinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIOPUR),st_a_pin->pinNum);   //enable pull-up
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
}
void inputPullDownPinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIOPDR),st_a_pin->pinNum);   //enable pull-down
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
}
void interruptFallingEdgePinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);    //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum);  //set pin type GPIO or alternative
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIOPUR),st_a_pin->pinNum);   //enable pull-up
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);    //set pin as a digital pin
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);     //mask the port interrupt
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIS),st_a_pin->pinNum);     //configure port for edge or level detection
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);    //clear the condition
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);    //configure the port for one edge detection
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);    //configure the pin for falling edge
    
}
void interruptRisingEdgePinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);    //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum);  //set pin type GPIO or alternative
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);     //mask the port interrupt
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIS),st_a_pin->pinNum);     //configure port for edge or level detection
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);    //configure the port for edge detection
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);    //configure the pin for rising edge
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);    //set pin as a digital pin
}
void interruptBothEdgesPinInit(st_gpioPinConfig_t *st_a_pin)
{
    SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);    //set pin direction
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum);  //set pin type GPIO or alternative
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);     //mask the port interrupt
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIS),st_a_pin->pinNum);     //configure port for edge or level detection
    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);    //clear the condition
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);    //configure the pin for both edges detection
    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);    //set pin as a digital pin
}





enu_systemErrorState_t  GPIO_init()
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    uint8_t uint8_a_portIterator;
    for(uint8_a_portIterator = GPIO_PORTA ; uint8_a_portIterator < GPIO_PORTS ; uint8_a_portIterator++)
    {
        enu_a_functionRet = GPIO_initPort(&st_gl_cst_gpioConfig.gpioPorts[uint8_a_portIterator]);
        if (enu_a_functionRet != GPIO_SUCCESS)
        {
            break;
        }
        else
        {
            /*do nothing*/
        }
        
    }
    return enu_a_functionRet;
}




enu_systemErrorState_t  GPIO_initPort(st_gpioPortConfig_t *st_a_port)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    uint8_t uint8_a_pinIterator;
    if(st_a_port != NULL)
    {
        if (st_a_port->portNum < INVALID_PORT)
        {
            SET_BIT(RCGCGPIO_REG,st_a_port->portNum);

            for(uint8_a_pinIterator = 0 ; uint8_a_pinIterator < PORT_PINS ; uint8_a_pinIterator++)
            {
                enu_a_functionRet = GPIO_initPin(&(st_a_port->portPins[uint8_a_pinIterator]));
                if (enu_a_functionRet != GPIO_SUCCESS)
                {
                    break;
                }
                else
                {
                    /*do nothing*/
                }

            }
            
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE;
        }
    }
    else
    {
        enu_a_functionRet = GPIO_INVALID_STATE;
    }
        
    return enu_a_functionRet;
}


enu_systemErrorState_t  GPIO_initPin(st_gpioPinConfig_t *st_a_pin)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (st_a_pin != NULL)
    {
        if (st_a_pin->port < INVALID_PORT)
        {
            if (st_a_pin->pinNum < INVALID_PIN)
            {
                if ((st_a_pin->port == GPIO_PORTE && st_a_pin->pinNum < GPIO_PIN6) || (st_a_pin->port == GPIO_PORTF && st_a_pin->pinNum < GPIO_PIN5))
                {
                    if (st_a_pin->pinMode < INVALID_PIN_MODE)
                    {
                        ptr_func_gl_pinInitializationFunctions[st_a_pin->pinMode](st_a_pin);
                    }
                    else
                    {
                        enu_a_functionRet = GPIO_INVALID_STATE; 
                    }
                }
                else
                {
                    enu_a_functionRet = GPIO_INVALID_STATE; 
                }
            }
            else
            {
                enu_a_functionRet = GPIO_INVALID_STATE; 
            }
            
        }
        else
        {
           enu_a_functionRet = GPIO_INVALID_STATE; 
        }
        
    }
    else
    {
        enu_a_functionRet = GPIO_INVALID_STATE;
    }
    return enu_a_functionRet;
}



enu_systemErrorState_t  GPIO_setPinValue(enu_gpioPort_t enu_a_port,enu_pin_t enu_a_pin ,enu_pinLogic_t enu_a_value)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    
    if (enu_a_port < INVALID_PORT)
    {
        if (GET_BIT(RCGCGPIO_REG,enu_a_port) == GPIO_HIGH)   //check if the port was init 
        {
            if (enu_a_pin < INVALID_PIN)
            {
                if (GET_BIT(ACCESS_REG(enu_a_port,GPIODIR),enu_a_pin) == GPIO_PIN_OUTPUT) //check if the is output or not
                {
                    if (enu_a_value < INVALID_PIN_LOGIC)    
                    {
                        if (enu_a_value == GPIO_LOW)
                        {
                            CLR_BIT(ACCESS_REG(enu_a_port,GPIODATA),enu_a_pin);
                        }
                        else
                        {
                            SET_BIT(ACCESS_REG(enu_a_port,GPIODATA),enu_a_pin);
                        }
                        
                    }
                    else
                    {
                        enu_a_functionRet = GPIO_INVALID_STATE; 
                    }
                }
                else
                {
                    enu_a_functionRet = GPIO_INVALID_STATE; 
                }
                
            }
            else
            {
                enu_a_functionRet = GPIO_NOT_SUCCESS;
            }
            
        }
        else
        {
            enu_a_functionRet = GPIO_UN_INITIALIZED_PIN;
        }
  
    }
    else
    {
        enu_a_functionRet = GPIO_UN_INITIALIZED_PIN;
    }

    return enu_a_functionRet;
}
enu_systemErrorState_t  GPIO_getPinValue(enu_gpioPort_t enu_a_port, enu_pin_t enu_a_pin , uint8_t *uint8_a_value)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (enu_a_port < INVALID_PORT)
    {
        if (enu_a_pin < INVALID_PIN)
        {
            if (GET_BIT(RCGCGPIO_REG,enu_a_port) == GPIO_HIGH)   //check for port init
            {
                if (uint8_a_value != NULL)
                {
                    if (GET_BIT(ACCESS_REG(enu_a_port,GPIODATA),enu_a_pin) == GPIO_LOW)
                    {
                        *uint8_a_value = GPIO_LOW;
                    }
                    else
                    {
                        *uint8_a_value = GPIO_HIGH;
                    }
                    
                }
                else
                {
                    enu_a_functionRet = GPIO_NOT_SUCCESS;
                }
                
            }
            else
            {
                enu_a_functionRet = GPIO_UN_INITIALIZED_PIN;
            }
            
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE; 
        }
        
    }
    else
    {
       enu_a_functionRet = GPIO_INVALID_STATE; 
    }
    return enu_a_functionRet;
}

enu_systemErrorState_t  GPIO_togglePin(enu_gpioPort_t enu_a_port, enu_pin_t enu_a_pin)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (enu_a_port < INVALID_PORT)
    {
        if (GET_BIT(RCGCGPIO_REG,enu_a_port) == GPIO_HIGH)
        {
            if (enu_a_pin < INVALID_PIN)
            {
                TOG_BIT(ACCESS_REG(enu_a_port,GPIODATA),enu_a_pin);  
            }
            else
            {
                enu_a_functionRet = GPIO_UN_INITIALIZED_PIN;
            }
            
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE; 
        }
        
    }
    else
    {
       enu_a_functionRet = GPIO_INVALID_STATE; 
    }
    return enu_a_functionRet;
}

enu_systemErrorState_t  GPIO_enableInterrupt(enu_gpioPort_t enu_a_port, enu_pin_t enu_a_pin,void(*ptr_func_pinInterruptCallack)(void))
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (enu_a_port < INVALID_PORT)
    {
      if (enu_a_pin <INVALID_PIN)
        {
            if (ptr_func_pinInterruptCallack != NULL)
            {
                ptr_func_gl_gpioPortsHandlers[enu_a_port][enu_a_pin] = ptr_func_pinInterruptCallack;
                SET_BIT(ACCESS_REG(enu_a_port,GPIOIM),enu_a_pin);
                NVIC_EnableIRQ(enu_gl_gpioPortsIrq[enu_a_port]);
                __enable_irq();
            }
            else
            {
                enu_a_functionRet = GPIO_INVALID_STATE;
            }      
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE;
        }   
    }
    else
    {
         enu_a_functionRet = GPIO_INVALID_STATE;
    }
    return enu_a_functionRet;
}

enu_systemErrorState_t  GPIO_disableInterrupt(enu_gpioPort_t enu_a_port, enu_pin_t enu_a_pin)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (enu_a_port < INVALID_PORT)
    {
      if (enu_a_pin <INVALID_PIN)
        {
            ptr_func_gl_gpioPortsHandlers[enu_a_port][enu_a_pin] = NULL;
            CLR_BIT(ACCESS_REG(enu_a_port,GPIOIM),enu_a_pin);
            NVIC_DisableIRQ(enu_gl_gpioPortsIrq[enu_a_port]);        
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE;
        }   
    }
    else
    {
        enu_a_functionRet = GPIO_INVALID_STATE;
    }
    return enu_a_functionRet;
}

enu_systemErrorState_t  GPIO_configurePinInterrupt(enu_gpioPort_t enu_a_port, enu_pin_t enu_a_pin , enu_gpioPinInterruptMode_t enu_a_interruptMode)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (enu_a_port < INVALID_PORT)
    {
        if (enu_a_pin < INVALID_PIN)
        {
            if (enu_a_interruptMode < INVALID_INTERRUPT_MODE)
            {
               
                CLR_BIT(ACCESS_REG(enu_a_port,GPIOIM),enu_a_pin);
                CLR_BIT(ACCESS_REG(enu_a_port,GPIOIS),enu_a_pin);
                CLR_BIT(ACCESS_REG(enu_a_port,GPIORIS),enu_a_pin);
                if (enu_a_interruptMode == GPIO_PIN_BOTH_EDGES)
                {
                    SET_BIT(ACCESS_REG(enu_a_port,GPIOIBE),enu_a_pin);
                }
                else
                {
                    CLR_BIT(ACCESS_REG(enu_a_port,GPIOIBE),enu_a_pin);
                    if (enu_a_interruptMode == GPIO_PIN_RISING_EDGE)
                    {
                        SET_BIT(ACCESS_REG(enu_a_port,GPIOIEV),enu_a_pin);
                    }
                    else if (enu_a_interruptMode == GPIO_PIN_FALLING_EDGE)
                    {
                        CLR_BIT(ACCESS_REG(enu_a_port,GPIOIEV),enu_a_pin);
                    }
                }     
            }
            else
            {
                enu_a_functionRet = GPIO_INVALID_STATE;
            }
                
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE;
        }
    }
    else
    {
        enu_a_functionRet = GPIO_INVALID_STATE;
    }
    return enu_a_functionRet;
}

enu_systemErrorState_t GPIO_setPinCallBackFunction(enu_gpioPort_t enu_a_port , enu_pin_t enu_a_pin,void(*ptr_func_a_interruptCallBack)(void))
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (enu_a_port < INVALID_PORT)
    {
        if (enu_a_pin < INVALID_PIN)
        {
            if (ptr_func_a_interruptCallBack != NULL)
            {
                ptr_func_gl_gpioPortsHandlers[enu_a_port][enu_a_pin] = ptr_func_a_interruptCallBack;
            }
            else
            {
                enu_a_functionRet = GPIO_INVALID_STATE;
            }
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE;
        }
    }
    else
    {
        enu_a_functionRet = GPIO_INVALID_STATE;
    }
    return enu_a_functionRet;
                
}



void GPIOA_Handler(void)
{
    uint8_t uint8_a_pinIndex;
    for (uint8_a_pinIndex = GPIO_PIN0; uint8_a_pinIndex < PORT_PINS; uint8_a_pinIndex++)
    {
        if (GET_BIT(ACCESS_REG(GPIO_PORTA,GPIORIS),uint8_a_pinIndex) == GPIO_HIGH)
        {
            if (ptr_func_gl_gpioPortsHandlers[GPIO_PORTA][uint8_a_pinIndex] != NULL)
            {
                ptr_func_gl_gpioPortsHandlers[GPIO_PORTA][uint8_a_pinIndex]();
                SET_BIT(ACCESS_REG(GPIO_PORTA,GPIOICR),uint8_a_pinIndex);
            } 
        }
    }
 
}
void GPIOB_Handler(void)
{
    uint8_t uint8_a_pinIndex;
    for (uint8_a_pinIndex = GPIO_PIN0; uint8_a_pinIndex < PORT_PINS; uint8_a_pinIndex++)
    {
        if (GET_BIT(ACCESS_REG(GPIO_PORTB,GPIORIS),uint8_a_pinIndex) == GPIO_HIGH)
        {
            if (ptr_func_gl_gpioPortsHandlers[GPIO_PORTB][uint8_a_pinIndex] != NULL)
            {
                ptr_func_gl_gpioPortsHandlers[GPIO_PORTB][uint8_a_pinIndex]();
                SET_BIT(ACCESS_REG(GPIO_PORTB,GPIOICR),uint8_a_pinIndex);
            } 
        }
    }
 
}
void GPIOC_Handler(void)
{
    uint8_t uint8_a_pinIndex;
    for (uint8_a_pinIndex = GPIO_PIN0; uint8_a_pinIndex < PORT_PINS; uint8_a_pinIndex++)
    {
        if (GET_BIT(ACCESS_REG(GPIO_PORTC,GPIORIS),uint8_a_pinIndex) == GPIO_HIGH)
        {
            if (ptr_func_gl_gpioPortsHandlers[GPIO_PORTC][uint8_a_pinIndex] != NULL)
            {
                ptr_func_gl_gpioPortsHandlers[GPIO_PORTC][uint8_a_pinIndex]();
                SET_BIT(ACCESS_REG(GPIO_PORTC,GPIOICR),uint8_a_pinIndex);
            } 
        }
    }
 
}
void GPIOD_Handler(void)
{
    uint8_t uint8_a_pinIndex;
    for (uint8_a_pinIndex = GPIO_PIN0; uint8_a_pinIndex < PORT_PINS; uint8_a_pinIndex++)
    {
        if (GET_BIT(ACCESS_REG(GPIO_PORTD,GPIORIS),uint8_a_pinIndex) == GPIO_HIGH)
        {
            if (ptr_func_gl_gpioPortsHandlers[GPIO_PORTD][uint8_a_pinIndex] != NULL)
            {
                ptr_func_gl_gpioPortsHandlers[GPIO_PORTD][uint8_a_pinIndex]();
                SET_BIT(ACCESS_REG(GPIO_PORTD,GPIOICR),uint8_a_pinIndex);
            } 
        }
    }
 
}
void GPIOE_Handler(void)
{
    uint8_t uint8_a_pinIndex;
    for (uint8_a_pinIndex = GPIO_PIN0; uint8_a_pinIndex < GPIO_PIN6; uint8_a_pinIndex++)
    {
        if (GET_BIT(ACCESS_REG(GPIO_PORTE,GPIORIS),uint8_a_pinIndex) == GPIO_HIGH)
        {
            if (ptr_func_gl_gpioPortsHandlers[GPIO_PORTE][uint8_a_pinIndex] != NULL)
            {
                ptr_func_gl_gpioPortsHandlers[GPIO_PORTE][uint8_a_pinIndex]();
                SET_BIT(ACCESS_REG(GPIO_PORTE,GPIOICR),uint8_a_pinIndex);
            } 
        }
    }
 
}
void GPIOF_Handler(void)
{
    uint8_t uint8_a_pinIndex;
    for (uint8_a_pinIndex = GPIO_PIN0; uint8_a_pinIndex < GPIO_PIN5; uint8_a_pinIndex++)
    {
        if (GET_BIT(ACCESS_REG(GPIO_PORTF,GPIORIS),uint8_a_pinIndex) == GPIO_HIGH)
        {
            if (ptr_func_gl_gpioPortsHandlers[GPIO_PORTF][uint8_a_pinIndex] != NULL)
            {
                ptr_func_gl_gpioPortsHandlers[GPIO_PORTF][uint8_a_pinIndex]();
                SET_BIT(ACCESS_REG(GPIO_PORTF,GPIOICR),uint8_a_pinIndex);
            } 
        }
    }
 
}