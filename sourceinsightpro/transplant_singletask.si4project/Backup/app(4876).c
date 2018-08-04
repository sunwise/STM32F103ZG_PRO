

/*
*********************************************************************************************************
*											   EXAMPLE CODE
*
*						   (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*				All rights reserved.  Protected by international copyright laws.
*				Knowledge of the source code may NOT be used to develop a similar product.
*				Please help us continue to provide the Embedded community with the finest
*				software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*											 EXAMPLE CODE
*
*									  ST Microelectronics STM32
*											   on the
*
*									  Micrium uC-Eval-STM32F107
*										 Evaluation Board
*
* Filename		: app.c
* Version		: V1.00
* Programmer(s) : EHS
*				  DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*											  INCLUDE FILES
*********************************************************************************************************
*/
#include <includes.h>



/*
*********************************************************************************************************
*											 LOCAL DEFINES
*********************************************************************************************************
*/
//定义一个存储区
OS_MEM			INTERNAL_MEM;

//存储区中存储块数量
#define INTERNAL_MEM_NUM		50

//每个存储块大小
//由于一个指针变量占用4字节所以块的大小一定要为4的倍数
//而且必须大于一个指针变量(4字节)占用的空间,否则的话存储块创建不成功
#define INTERNAL_MEMBLOCK_SIZE	25*4  

//存储区的内存池，使用内部RAM
__align(4) CPU_INT08U		Internal_RamMemp[INTERNAL_MEM_NUM][INTERNAL_MEMBLOCK_SIZE];

//定义一个存储区
OS_MEM			EXTERNAL_MEM;

//存储区中存储块数量
#define EXTRENNAL_MEM_NUM		2000

//每个存储块大小
//由于一个指针变量占用4字节所以块的大小一定要为4的倍数
//而且必须大于一个指针变量(4字节)占用的空间,否则的话存储块创建不成功
#define EXTERNAL_MEMBLOCK_SIZE	128*4

//存储区的内存池，使用外部SRAM
__align(32) volatile CPU_INT08U External_RamMemp[EXTRENNAL_MEM_NUM][EXTERNAL_MEMBLOCK_SIZE] __attribute__((at(0X68000000)));


/*
*********************************************************************************************************
*												  TCB
*********************************************************************************************************
*/
static OS_TCB	AppTaskStartTCB;


/*
*********************************************************************************************************
*												 STACKS
*********************************************************************************************************
*/
static CPU_STK	AppTaskStartStk[APP_TASK_START_STK_SIZE];


/*
*********************************************************************************************************
*										  FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static void AppTaskStart(void * p_arg);


/*
*********************************************************************************************************
*												 main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*				main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns	  : none
*********************************************************************************************************
*/
int main(void)
{
	OS_ERR			err;
	CPU_SR     cpu_sr;

	SRAM_Init();

	OSInit(&err);									/* Init uC/OS-III.										*/
	OS_CRITICAL_ENTER();	//进入临界区
	
	OSMemCreate((OS_MEM*	)&INTERNAL_MEM, 					//创建一个存储分区
					(CPU_CHAR*	)"Internal Mem",
					(void*		)&Internal_RamMemp[0][0],
					(OS_MEM_QTY )INTERNAL_MEM_NUM,
					(OS_MEM_SIZE)INTERNAL_MEMBLOCK_SIZE,
					(OS_ERR*	)&err);
	 
		OSMemCreate((OS_MEM*	)&EXTERNAL_MEM, 				//创建一个存储分区
					(CPU_CHAR*	)"External Mem",
					(void*		)&External_RamMemp[0][0],
					(OS_MEM_QTY )EXTRENNAL_MEM_NUM,
					(OS_MEM_SIZE)EXTERNAL_MEMBLOCK_SIZE,
					(OS_ERR*	)&err);

	OS_CRITICAL_EXIT();	//退出临界区
	OSTaskCreate((OS_TCB *) &AppTaskStartTCB,		/* Create the start task								*/
	(CPU_CHAR *) "App Task Start", 
		(OS_TASK_PTR) AppTaskStart, 
		(void *) 0, 
		(OS_PRIO) APP_TASK_START_PRIO, 
		(CPU_STK *) &AppTaskStartStk[0], 
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10, 
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE, 
		(OS_MSG_QTY) 0u, 
		(OS_TICK) 0u, 
		(void *) 0, 
		(OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
		(OS_ERR *) &err);

	OSStart(&err);									/* Start multitasking (i.e. give control to uC/OS-III). */
}


/*
*********************************************************************************************************
*										   STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*				initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg	is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns	  : none
*
* Notes 	  : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*				   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/
CPU_INT16U		count = 0;
CPU_INT16U		count1 = 0;


static void AppTaskStart(void * p_arg)
{
	CPU_INT32U		cpu_clk_freq;
	CPU_INT32U		cnts;
	OS_ERR			err;


	(void)
	p_arg;

	BSP_Init(); 									/* Initialize BSP functions 							*/
	CPU_Init();

	cpu_clk_freq		= BSP_CPU_ClkFreq();		/* Determine SysTick reference freq.					*/
	cnts				= cpu_clk_freq / (CPU_INT32U)
	OSCfg_TickRate_Hz;								/* Determine nbr SysTick increments 					*/
	OS_CPU_SysTickInit(cnts);						/* Init uC/OS periodic time src (SysTick).				*/
	Mem_Init(); 									/* Initialize Memory Management Module					*/

#if OS_CFG_STAT_TASK_EN 			> 0u
	OSStatTaskCPUUsageInit(&err);					/* Compute CPU capacity with no task running			*/
#endif

	CPU_IntDisMeasMaxCurReset();

	OSTaskCreate((OS_TCB *) &KeyDealTaskTCB,		/* Create the start task								*/
	(CPU_CHAR *) "key deal task", 
		(OS_TASK_PTR) KeyDealTask, 
		(void *) 0, 
		(OS_PRIO) KEY_DEAL_TASK_PRIO, 
		(CPU_STK *) &KeyDealTaskStk[0], 
		(CPU_STK_SIZE) KEY_DEAL_TASK_STK_SIZE / 10, 
		(CPU_STK_SIZE) KEY_DEAL_TASK_STK_SIZE, 
		(OS_MSG_QTY) 20u, 
		(OS_TICK) 0u, 
		(void *) 0, 
		(OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
		(OS_ERR *) &err);

	OSTaskCreate((OS_TCB *) &PowerManTaskTCB,		/* Create the start task								*/
	(CPU_CHAR *) "powermanage", 
		(OS_TASK_PTR) PowerManTask, 
		(void *) 0, 
		(OS_PRIO) POWER_MAN_TASK_PRIO, 
		(CPU_STK *) &PowerManTaskStk[0], 
		(CPU_STK_SIZE) POWER_MAN_TASK_STK_SIZE / 10, 
		(CPU_STK_SIZE) POWER_MAN_TASK_STK_SIZE, 
		(OS_MSG_QTY) 0u, 
		(OS_TICK) 0u, 
		(void *) 0, 
		(OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), 
		(OS_ERR *) &err);


	while (DEF_TRUE)
		{ /* Task body, always written as an infinite loop. 	  */

		macLED1_TOGGLE();

		count++;

		OSTimeDly(1000, OS_OPT_TIME_DLY, &err);
		}


}




