#ifndef TMU_H_
#define TMU_H_
/// @tmu_error_state //////////////////////
typedef enum __tmuErrorState
{
    TMU_SUCCESS = 0     ,
    TMU_NOT_SUCCESS     ,
    TMU_INVALID_TASK_ID ,
    TMU_FULLY_BUSY      ,
    TMU_INVALID_STATE
}enu_tmuErrorState_t;
/// @tmu_periodicity //////////////////////
typedef enum __periodicity
{
    TMU_ONE_SHOT    = 1 ,
    TMU_PRIODIC         
}enu_periodicity_t;
/// @tmu_mode //////////////////////
typedef enum __tmuMode
{
    NORMAL  = 0
    //to do all options
}enu_tmuMode_t;
/// @tmu_time_scale //////////////////////
typedef enum __tmuTimeScale
{
    MICRO   = 0 ,
    MILLI       ,
    SECOND
}enu_tmuTimeScale_t;
/// @tmu_task_instance //////////////////////
typedef struct __tmuTask
{
    enu_tmuMode_t enu_a_mode; 
    enu_periodicity_t enu_a_periodicity ;
    enu_tmuTimeScale_t enu_a_scale;
    uint64_t taskInterval;
    void(*ptr_func_taskCallBack)(void);
    uint8_t uint8_a_taskId;
}st_tmuTask_t;
/// @tmu_API's //////////////////////
enu_tmuErrorState_t TMU_createTask(st_tmuTask_t *st_a_taskInstance);
enu_tmuErrorState_t TMU_startTask(uint8_t *uint8_a_taskId,uint64_t *uint64_a_interval);
enu_tmuErrorState_t TMU_stopTask(uint8_t *uint8_a_taskId);
enu_tmuErrorState_t TMU_modifyTask(uint8_t *uint8_a_taskId ,st_tmuTask_t *st_a_taskInstance);
#endif // !TMU_H_
