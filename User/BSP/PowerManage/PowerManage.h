#ifndef __POWERMANAGE_H_
#define	__POWERMANAGE_H_



#include "stm32f10x.h"

#define             KILL_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             KILL_GPIO_CLK                        RCC_APB2Periph_GPIOE
#define             KILL_GPIO_PORT                       GPIOE
#define             KILL_GPIO_PIN                        GPIO_Pin_4

#define             KILL_LOW()                            GPIO_ResetBits ( KILL_GPIO_PORT, KILL_GPIO_PIN )
#define             KILL_HIGH()                           GPIO_SetBits ( KILL_GPIO_PORT, KILL_GPIO_PIN )

void Powermanage_Init ( void );

 
 
#endif 
