#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_ 

#define GPIO_APB_ADDRESS    0x40004000
#define GPIO_AHB_ADDRESS    0x40058000

#define ANALOG_PIN_MASK     0x01 
typedef enum __regPin
{
    REG_PIN0 = 0    ,
    REG_PIN1        ,
    REG_PIN2        ,
    REG_PIN3        ,
    REG_PIN4        ,
    REG_PIN5        ,
    REG_PIN6        
}enu_regPin_t;

typedef enum __IRQIndex  
{
    GPIO_IRQ_PORTA = 0  ,
    GPIO_IRQ_PORTB      ,
    GPIO_IRQ_PORTC      ,
    GPIO_IRQ_PORTD      ,
    GPIO_IRQ_PORTE      ,
    GPIO_IRQ_PORTF = 30   

}enu_IRQIndex_t;
   

typedef enum __gpioRegOffset
{
    GPIODATA            = 0x3FC,
    GPIODIR             = 0x400,
    GPIOIS              = 0x404,
    GPIOIBE             = 0x408,
    GPIOIEV             = 0x40C,
    GPIOIM              = 0x410,
    GPIORIS             = 0x414,
    GPIOMIS             = 0x418,
    GPIOICR             = 0x41C, 
    GPIOAFSEL           = 0x420,
    GPIODR2R            = 0x500,
    GPIODR4R            = 0x504, 
    GPIODR8R            = 0x508,
    GPIOODR             = 0x50C, 
    GPIOPUR             = 0x510, 
    GPIOPDR             = 0x514, 
    GPIOSLR             = 0x518, 
    GPIODEN             = 0x51C,  
    GPIOLOCK            = 0x520, 
    GPIOCR              = 0x524, 
    GPIOAMSEL           = 0x528, 
    GPIOPCTL            = 0x52C, 
    GPIOADCCTL          = 0x530, 
    GPIODMACTL          = 0x534, 
    GPIOPeriphID4       = 0xFD0, 
    GPIOPeriphID5       = 0xFD4, 
    GPIOPeriphID6       = 0xFD8, 
    GPIOPeriphID7       = 0xFDC, 
    GPIOPeriphID0       = 0xFE0,
    GPIOPeriphID1       = 0xFE4,
    GPIOPeriphID2       = 0xFE8,
    GPIOPeriphID3       = 0xFEC
    
}enu_gpioRegOffset_t;

#define  RCGCGPIO_REG      (*((volatile uint32_t*) 0x400FE608))





#ifdef  APB_BUS
#define GPIO_PORT_OFFSET(_portIndex_) ((_portIndex_ < GPIO_PORTE)?((GPIO_APB_ADDRESS)+(_portIndex_ * 0x1000)):((GPIO_APB_ADDRESS) + ((_portIndex_ - GPIO_PORTE) * (0x1000)) + (0x20000)))
#else    
#define GPIO_PORT_OFFSET(_portIndex_) ((GPIO_APB_ADDRESS)+(_portIndex_ * 0x1000))
#endif 




#define ACCESS_REG(_port_ , _reg_) 	   *((volatile uint32_t*)((GPIO_PORT_OFFSET(_port_)) + (_reg_)))


#endif // !GPIO_PRIVATE_H_