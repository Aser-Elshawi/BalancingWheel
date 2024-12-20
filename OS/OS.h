/*
 * OS.h
 *
 *  Created on: Jun 29, 2021
 *      Author: 
 */

#ifndef OS_H_
#define OS_H_

#ifdef __cplusplus
extern "C" {
#endif
// Congfig //
#define TASK_MAX 6

// Config END //
#define RUN  1
#define RUNNING 2
#define IDLE  0
#ifndef NULL
#define NULL (void*)0
#endif

typedef enum OS_State_e{
    OS_TASK_CREATED,
    OS_MAX_TASK_REACHED
}OS_State_t;


void OS_Init(void);
typedef void(*taskPtr_t)(void);
void delay(uint32_t time_ms);
void OS_handlerCallBack(void);
OS_State_t OS_CreateNewTask(taskPtr_t task, uint32_t TASK_TIME);
void OS_ServeOS(void);
void PLL_Init(void);
#ifdef __cplusplus
}
#endif

#endif /* OS_H_ */

