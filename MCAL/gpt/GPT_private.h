#ifndef GPT_PRIVATE_H_
#define GPT_PRIVATE_H_ 


typedef struct __GPT{
uint32_t GPTMCFG; 
uint32_t GPTMTAMR;
uint32_t GPTMTBMR;
uint32_t GPTMCTL; 
uint32_t GPTMSYNC;
uint32_t RES0;
uint32_t GPTMIMR; 
uint32_t GPTMRIS; 
uint32_t GPTMMIS; 
uint32_t GPTMICR; 
uint32_t GPTMTAILR; 
uint32_t GPTMTBILR; 
uint32_t GPTMTAMATCHR; 
uint32_t GPTMTBMATCHR; 
uint32_t GPTMTAPR; 
uint32_t GPTMTBPR;
uint32_t GPTMTAPMR;
uint32_t GPTMTBPMR;
uint32_t GPTMTAR; 
uint32_t GPTMTBR; 
uint32_t GPTMTAV; 
uint32_t GPTMTBV; 
uint32_t GPTMRTCPD; 
uint32_t GPTMTAPS; 
uint32_t GPTMTBPS; 
uint32_t GPTMTAPV; 
uint32_t GPTMTBPV;
uint32_t RES1[981];
uint32_t GPTMPP;
}str_GPT_t;
#ifndef  GPT_RCGCTIMER
#define  GPT_RCGCTIMER         *((volatile uint32_t*)(0x400FE604))
#define  GPT_RCGCWTIMER        *((volatile uint32_t*)(0x400FE65C))
#endif

#define  TIMER_BASE_ADDRESS           (0x40030000UL)
#define  TIMER_W_BASE_ADDRESS         (0x40036000UL)  

#define  TIMER_OFFSET(TIMER_NUM)             (TIMER_BASE_ADDRESS + (TIMER_NUM * 0x1000))
#define  TIMER_W_OFFSET(TIMER_NUM)           ( (TIMER_NUM < 2) ?  ( TIMER_W_BASE_ADDRESS + (TIMER_NUM * 0x1000) ) : (TIMER_W_BASE_ADDRESS + 0x10000 + (TIMER_NUM * 0x1000) ) )

#define  TIMER(TIMER_NUM)                    ((volatile str_GPT_t*)TIMER_OFFSET(TIMER_NUM))
#define  TIMER_W(TIMER_NUM)                  ((volatile str_GPT_t*)TIMER_W_OFFSET(TIMER_NUM))
/*****************************MUNS_SECTION****************************/
//#define TAEN    0
#define TBEN    8
#define ONE_SHOT_OR_PERIODIC_MODE_CONFIG   4
#define TAMIM   4 
#define TATOIM  0 
#define TATOCINT    0
#define GPTMTAMR_MASK   0xFFFFFFFC
#define MICRO_MODE_TIMEOUT_PRESCALER    0x0
#define MILLI_MODE_TIMEOUT_PRESCALER    0x255
#define SECOND_MODE_TIMEOUT_PRESCALER   
#define TIMEOUT_PRELOAD                 65486
#define SECOND_MODE_TIMEOUT_PRELOAD  

/*********************************************************************/

////////////Mahran Anti Magic Numbers Squad////////////////

#define     TAEN                 0
#define     TBEN                 8
#define     TACDIR               4
#define     TBCDIR               4
/*          GPTMIMR bits                       */
#define     CAMIM                1
#define     CAEIM                2
#define     RTCIM                3
#define     RES_BITS             3
#define     TBTOIM               8
#define     CBMIM                9
#define     CBEIM                10
#define     TBMIM                11
#define     WUEIM                16
/////////////////////////////////////////////////
#define     _16BIT_MAX_TICKS                 (0xFFFF)
#define     _32BIT_MAX_TICKS                 (0xFFFFFFFFUL)
#define     _8BIT_MICRO_PRE                  50UL
#define     _8BIT_MILLI_PRE                  255UL
#define     _16BIT_MICRO_PRE                 50UL
#define     _16BIT_MILLI_PRE                 50000UL
#define     _16BIT_SEC_PRE                   50000UL

#define     _16BIT_MICRO_MAX_TIME             (( (_16BIT_MICRO_PRE * _32BIT_MAX_TICKS) / F_CPU) )
#define     _16BIT_MILLI_MAX_TIME             (( (_16BIT_MILLI_PRE * _32BIT_MAX_TICKS) / F_CPU) )
#define     _16BIT_SECOND_MAX_TIME            (( (_16BIT_SEC_PRE * _32BIT_MAX_TICKS) / F_CPU) )
#define     _MS_FACTOR                        1000UL
#define     GPT_TIMER_NUM                     12
#endif
