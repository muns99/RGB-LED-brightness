/// @tmu_instances_num //////////////////////
#define TMU_INSTANCES   12
#define MAX_TIME				35000000UL
/// @tmu_instance_state //////////////////////
typedef enum __tmuInstanceState
{
    TMU_INSTANCE_NOT_INITIALIZED    = 0 ,
    TMU_INSTANCE_INITIALIZED            ,
    TMU_INSTANCE_RUNNING                
}enu_tmuInstanceState_t;
/// @tmu_struct //////////////////////
typedef struct __tmu
{
    str_timer_t timer;
    uint64_t maxTime;
    enu_tmuInstanceState_t state;
    enu_timerinterrupt_t timerInterrupt;
}st_tmu_t;;
