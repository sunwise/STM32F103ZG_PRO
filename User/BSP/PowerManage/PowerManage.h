#ifndef __POWERMANAGE_H_
#define	__POWERMANAGE_H_



#include <includes.h>
#include <os.h>


#define             KILL_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             KILL_GPIO_CLK                        RCC_APB2Periph_GPIOE
#define             KILL_GPIO_PORT                       GPIOE
#define             KILL_GPIO_PIN                        GPIO_Pin_4

#define             KILL_LOW()                            GPIO_ResetBits ( KILL_GPIO_PORT, KILL_GPIO_PIN )
#define             KILL_HIGH()                           GPIO_SetBits ( KILL_GPIO_PORT, KILL_GPIO_PIN )


/*
*********************************************************************************************************
*												  TCB
*********************************************************************************************************
*/
extern OS_TCB	PowerManTaskTCB;


/*
*********************************************************************************************************
*												 STACKS
*********************************************************************************************************
*/
extern CPU_STK	PowerManTaskStk[POWER_MAN_TASK_STK_SIZE];


/*
*********************************************************************************************************
*										  FUNCTION PROTOTYPES
*********************************************************************************************************
*/
extern void PowerManTask(void * p_arg);


extern OS_SEM ALLADCCON;

void Powermanage_Init ( void );
void DMA1_Channel1_IRQHandler(void);


 
 
#endif 
