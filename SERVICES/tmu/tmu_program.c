#include "../../LIB/std_types.h"
#include "../../MCAL/gpt/GPT_interface.h"
#include "tmu_interface.h"
#include "tmu_config.h"
/// @tmu_configuration //////////////////////
extern st_tmu_t st_gl_tmuInstances[TMU_INSTANCES];
/// @tmu_managing_struct //////////////////////
typedef struct __tmuManage
{
    st_tmu_t *tmuInstance;
    st_tmuTask_t   *tmutask;
}st_tmuManage_t;
/// @tmu_manage_center //////////////////////
uint8_t uint8_gl_manageCenterCounter = 0;
st_tmuManage_t st_gl_tmuManage[TMU_INSTANCES];
/// @tmu_API'S_implementation //////////////////////
enu_tmuErrorState_t TMU_createTask(st_tmuTask_t *st_a_taskInstance)
{
    enu_tmuErrorState_t enu_a_functionRet   = TMU_SUCCESS;
    if (uint8_gl_manageCenterCounter < TMU_INSTANCES)
    {
        if (st_a_taskInstance != NULL)
        {
            if (st_a_taskInstance->uint8_a_taskId < TMU_INSTANCES)
            {
                uint8_t uint8_a_firstFreeTmuInstance;
                for ( uint8_a_firstFreeTmuInstance = 0; uint8_a_firstFreeTmuInstance < TMU_INSTANCES; uint8_a_firstFreeTmuInstance++)
                {
                    if (st_gl_tmuInstances[uint8_a_firstFreeTmuInstance].state == TMU_INSTANCE_NOT_INITIALIZED)
                    {
                        uint64_t uint64_a_taskInterval;
                        uint64_a_taskInterval = st_a_taskInstance->enu_a_scale == MICRO?(st_a_taskInstance->taskInterval / 1000):(st_a_taskInstance->enu_a_scale == MILLI?st_a_taskInstance->taskInterval:st_a_taskInstance->taskInterval * 1000); 
                        if (uint64_a_taskInterval <= st_gl_tmuInstances[uint8_a_firstFreeTmuInstance].maxTime)
                        {
                            break;
                        }
                        else
                        {
                        /*do nothing*/
                        }
                        
                    }
                    else
                    {
                        /*do nothing*/
                    }
                }
                st_gl_tmuInstances[uint8_a_firstFreeTmuInstance].timer.timerMode = st_a_taskInstance->enu_a_periodicity;
                enu_a_functionRet = GPT_initTimer(&st_gl_tmuInstances[uint8_a_firstFreeTmuInstance].timer);
                if (enu_a_functionRet == GPT_OK)
                {
                    enu_a_functionRet = GPT_setTimerCallBack(st_gl_tmuInstances[uint8_a_firstFreeTmuInstance].timer.timerId,
                                                             st_gl_tmuInstances[uint8_a_firstFreeTmuInstance].timer.timerChannel,
                                                             st_a_taskInstance->ptr_func_taskCallBack);
                    if (enu_a_functionRet == GPT_OK)
                    {
                        st_gl_tmuInstances[uint8_a_firstFreeTmuInstance].state = TMU_INSTANCE_INITIALIZED;
                        st_gl_tmuManage[uint8_gl_manageCenterCounter].tmuInstance = &st_gl_tmuInstances[uint8_a_firstFreeTmuInstance];
                        st_gl_tmuManage[uint8_gl_manageCenterCounter].tmutask = st_a_taskInstance;
                    }
                    else
                    {
                        enu_a_functionRet = TMU_NOT_SUCCESS;
                    }
                }
                else
                {
                    enu_a_functionRet = TMU_NOT_SUCCESS;
                }
            }
            else
            {
                enu_a_functionRet = TMU_INVALID_TASK_ID;
            }
            
        }
        else
        {
            enu_a_functionRet = TMU_INVALID_STATE;
        }
    }
    else
    {
        enu_a_functionRet = TMU_FULLY_BUSY;
    }
    
    
    return enu_a_functionRet;
}
enu_tmuErrorState_t TMU_startTask(uint8_t *uint8_a_taskId,uint64_t *uint64_a_interval)
{
    enu_tmuErrorState_t enu_a_functionRet = TMU_SUCCESS;
    if (uint8_a_taskId != NULL)
    {
        if (*uint8_a_taskId < TMU_INSTANCES)
        {
            if (uint64_a_interval != NULL)
            {
                uint8_t uint8_a_taskIndex ;
                for (uint8_a_taskIndex = 0; uint8_a_taskIndex <= uint8_gl_manageCenterCounter; uint8_a_taskIndex++)
                {
                    st_tmuTask_t *st_a_tempTaskInstance = st_gl_tmuManage[uint8_a_taskIndex].tmutask;
                    if (st_a_tempTaskInstance->uint8_a_taskId == *uint8_a_taskId)
                    {
                        st_tmu_t *st_a_tmuTempInstance = st_gl_tmuManage[uint8_a_taskIndex].tmuInstance;

                        if (st_a_tmuTempInstance->state == TMU_INSTANCE_INITIALIZED || st_a_tmuTempInstance->state == TMU_INSTANCE_RUNNING)
                        {
                            if(st_a_tmuTempInstance->maxTime >= *uint64_a_interval)
                            {
                                str_timer_t *st_a_tempTimerInstance = &st_a_tmuTempInstance->timer;
                                enu_a_functionRet = GPT_preloadTimer(st_a_tempTimerInstance->timerId,st_a_tempTimerInstance->timerChannel,st_a_tempTaskInstance->enu_a_scale,*uint64_a_interval) == GPT_OK?enu_a_functionRet : TMU_NOT_SUCCESS;
                                enu_a_functionRet = GPT_enableTimerInterrupt(st_a_tempTimerInstance->timerId,st_a_tmuTempInstance->timerInterrupt);
                                enu_a_functionRet = GPT_startTimer(st_a_tempTimerInstance->timerId,st_a_tempTimerInstance->timerChannel);
                                st_a_tmuTempInstance->state = enu_a_functionRet == TMU_SUCCESS?TMU_INSTANCE_RUNNING : st_a_tmuTempInstance->state;
                                
                            }
                            else
                            {
                                /*do nothing*/
                            }
                        }
                        else
                        {
                            enu_a_functionRet = TMU_INVALID_STATE;
                        }

                        break;
                    }
                    else 
                    {
                        /* do nothing */
                    }
                    
                    
                }
            }
            else
            {
                enu_a_functionRet = TMU_INVALID_TASK_ID;
            }
            
        }
        else
        {
            enu_a_functionRet = TMU_INVALID_TASK_ID;
        }
        
        
        
    }
    else
    {
        enu_a_functionRet = TMU_INVALID_TASK_ID;
    }
    return enu_a_functionRet;
}
enu_tmuErrorState_t TMU_stopTask(uint8_t *uint8_a_taskId)
{
    enu_tmuErrorState_t enu_a_functionRet = TMU_SUCCESS;
    if (uint8_a_taskId != NULL)
    {
        if (uint8_a_taskId < TMU_INSTANCES)
        {
            uint8_t uint8_a_taskIndex ;
            for (uint8_a_taskIndex = 0; uint8_a_taskIndex <= uint8_gl_manageCenterCounter; uint8_a_taskIndex++)
            {
                st_tmuTask_t *st_a_tempTaskInstance = st_gl_tmuManage[uint8_a_taskIndex].tmutask;
                if (st_a_tempTaskInstance->uint8_a_taskId == uint8_a_taskId)
                {
                    st_tmu_t *st_a_tmuTempInstance = st_gl_tmuManage[uint8_a_taskIndex].tmuInstance;

                    if (st_a_tmuTempInstance->state == TMU_INSTANCE_RUNNING)
                    {
                        str_timer_t *st_a_tempTimerInstance = &st_a_tmuTempInstance->timer;
                         enu_a_functionRet = GPT_startTimer(st_a_tempTimerInstance->timerId,st_a_tempTimerInstance->timerChannel);
                        enu_a_functionRet = GPT_disableTimerInterrupt(st_a_tempTimerInstance->timerId,st_a_tmuTempInstance->timerInterrupt);
                        st_a_tmuTempInstance->state = enu_a_functionRet == TMU_SUCCESS?TMU_INSTANCE_RUNNING : st_a_tmuTempInstance->state;
                    }
                    else
                    {
                        enu_a_functionRet = TMU_INVALID_STATE;
                    }

                    break;
                }
                else 
                {
                    /* do nothing */
                }
                    
                    
            }
            
        }
        else
        {
            enu_a_functionRet = TMU_INVALID_TASK_ID;
        }
        
        
        
    }
    else
    {
        enu_a_functionRet = TMU_INVALID_TASK_ID;
    }
    return enu_a_functionRet;
}
enu_tmuErrorState_t TMU_modifyTask(uint8_t *uint8_a_taskId ,st_tmuTask_t *st_a_taskInstance)
{

}
