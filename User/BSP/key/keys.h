#ifndef __KEYS_H_
#define	__KEYS_H_



#include <includes.h>
#include <os.h>


#define             KEY2_GPIO_CLK                        RCC_APB2Periph_GPIOC
#define             KEY2_GPIO_PORT                       GPIOC
#define             KEY2_GPIO_PIN                        GPIO_Pin_5
#define             KEY2_PortSource                      GPIO_PortSourceGPIOC
#define             KEY2_PINSource                       GPIO_PinSource5
#define             KEY2_EXTI_Line                       EXTI_Line5
#define             KEY2_IRQChannel                      EXTI9_5_IRQn



#define             KEY3_GPIO_CLK                        RCC_APB2Periph_GPIOB
#define             KEY3_GPIO_PORT                       GPIOB
#define             KEY3_GPIO_PIN                        GPIO_Pin_0
#define             KEY3_PortSource                      GPIO_PortSourceGPIOB
#define             KEY3_PINSource                       GPIO_PinSource0
#define             KEY3_EXTI_Line                       EXTI_Line0
#define             KEY3_IRQChannel                      EXTI0_IRQn


#define             KEY4_GPIO_CLK                        RCC_APB2Periph_GPIOB
#define             KEY4_GPIO_PORT                       GPIOB
#define             KEY4_GPIO_PIN                        GPIO_Pin_1
#define             KEY4_PortSource                      GPIO_PortSourceGPIOB
#define             KEY4_PINSource                       GPIO_PinSource1
#define             KEY4_EXTI_Line                       EXTI_Line1
#define             KEY4_IRQChannel                      EXTI1_IRQn


#define             KEY5_GPIO_CLK                        RCC_APB2Periph_GPIOD
#define             KEY5_GPIO_PORT                       GPIOD
#define             KEY5_GPIO_PIN                        GPIO_Pin_3
#define             KEY5_PortSource                      GPIO_PortSourceGPIOD
#define             KEY5_PINSource                       GPIO_PinSource3
#define             KEY5_EXTI_Line                       EXTI_Line3
#define             KEY5_IRQChannel                      EXTI3_IRQn

/*
*********************************************************************************************************
*												  TCB
*********************************************************************************************************
*/
extern OS_TCB	KeyDealTaskTCB;


/*
*********************************************************************************************************
*												 STACKS
*********************************************************************************************************
*/
extern CPU_STK	KeyDealTaskStk[KEY_DEAL_TASK_STK_SIZE];


/*
*********************************************************************************************************
*										  FUNCTION PROTOTYPES
*********************************************************************************************************
*/
extern void KeyDealTask(void * p_arg);


void Keys_Init ( void );
void KEY2_IRQ_DEAL(void);
void KEY3_IRQ_DEAL(void);
void KEY4_IRQ_DEAL(void);
void KEY5_IRQ_DEAL(void);


#endif 
