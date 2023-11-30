#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_ 
typedef enum __appErrorState
{
    APP_SUCCESS = 0,
    APP_NOT_SUCCESS ,
    APP_INVALID_STATE
}enu_appErrorState_t;

enu_appErrorState_t APP_init();
enu_appErrorState_t APP_start();
enu_appErrorState_t APP_stop();
#endif