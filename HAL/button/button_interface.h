#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_ 


typedef enum __buttonErrorState
{
    BUTTON_SUCCESS   = 0    ,
    BUTTON_NOT_SUCCESS      ,
    BUTTON_INVALID_STATE    
}enu_buttonErrorState_t;

typedef enum __buttonState
{
    BUTTON_PRESSED  = 0 ,
    BUTTON_UN_PRESSED   ,
    INVALID_BUTTON_STATE
}enu_buttonState_t;

typedef enum __buttonMode
{
    BUTTON_PULLUP_MODE  = 0              ,
    BUTTON_PULLDOWN_MODE                 ,
    BUTTON_INTERRUPT_RISING_EDGE_MODE    ,
    BUTTON_INTERRUPT_FALLING_EDGE_MODE   ,
    BUTTON_INTERRUPT_BOTH_EDGES_MODE     ,
    INVALID_BUTTON_MODE   
}enu_buttonMode_t;

typedef enum __buttonPin
{
    BUTTON_PIN0    = 0 ,
    BUTTON_PIN1        ,
    BUTTON_PIN2        ,
    BUTTON_PIN3        ,
    BUTTON_PIN4        ,
    BUTTON_PIN5        ,
    BUTTON_PIN6        ,
    BUTTON_PIN7        
}enu_buttonPin_t;

typedef enum __buttonPort
{
    BUTTON_PORTA   = 0 ,
    BUTTON_PORTB       ,
    BUTTON_PORTC       ,
    BUTTON_PORTD       ,
    BUTTON_PORTE       ,
    BUTTON_PORTF
}enu_buttonPort_t;

typedef struct __button
{
    enu_buttonPort_t buttonPort ;
    enu_buttonPin_t  buttonPin;
    enu_buttonMode_t buttonMode;
    void (*buttonHandler)(void);
}st_button_t;

enu_buttonErrorState_t BUTTON_init(st_button_t *st_a_button);
enu_buttonErrorState_t BUTTON_getButtonState(st_button_t *st_a_button,uint8_t *uint8_a_buttonState);
enu_buttonErrorState_t BUTTON_enable(st_button_t *st_a_button);
enu_buttonErrorState_t BUTTON_disable(st_button_t *st_a_button);
enu_buttonErrorState_t BUTTON_deInit(st_button_t *st_a_button);



#endif /*BUTTON_INTERFACE_H_*/