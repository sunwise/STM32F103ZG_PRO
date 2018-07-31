
#include "keys.h"	


/*
*********************************************************************************************************
*												  TCB
*********************************************************************************************************
*/
OS_TCB			KeyDealTaskTCB;


/*
*********************************************************************************************************
*												 STACKS
*********************************************************************************************************
*/
CPU_STK 		KeyDealTaskStk[APP_TASK_START_STK_SIZE];


/*
*********************************************************************************************************
*										  FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void KeyDealTask(void * p_arg);

static void Keys_GPIO_Config(void);



/**
 * @brief  ���� LED �� GPIO ����
 * @param  ��
 * @retval ��
 */
static void Keys_GPIO_Config(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/* */
	RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);

	EXTI_ClearITPendingBit(KEY2_EXTI_Line);
	GPIO_EXTILineConfig(KEY2_PortSource, KEY2_PINSource);
	EXTI_InitStructure.EXTI_Line = KEY2_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //中断方式为上升与下降沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);


	/* */
	RCC_APB2PeriphClockCmd(KEY3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY3_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY3_GPIO_PORT, &GPIO_InitStructure);

	EXTI_ClearITPendingBit(KEY3_EXTI_Line);
	GPIO_EXTILineConfig(KEY3_PortSource, KEY3_PINSource);
	EXTI_InitStructure.EXTI_Line = KEY3_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //中断方式为上升与下降沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* */
	RCC_APB2PeriphClockCmd(KEY4_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY4_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);

	EXTI_ClearITPendingBit(KEY4_EXTI_Line);
	GPIO_EXTILineConfig(KEY4_PortSource, KEY4_PINSource);
	EXTI_InitStructure.EXTI_Line = KEY4_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //中断方式为上升与下降沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* */
	RCC_APB2PeriphClockCmd(KEY5_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY5_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY5_GPIO_PORT, &GPIO_InitStructure);

	EXTI_ClearITPendingBit(KEY5_EXTI_Line);
	GPIO_EXTILineConfig(KEY5_PortSource, KEY5_PINSource);
	EXTI_InitStructure.EXTI_Line = KEY5_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //中断方式为上升与下降沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3); //NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY4_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY5_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


}


/**
 * @brief  LED ��ʼ������
 * @param  ��
 * @retval ��
 */
void Keys_Init(void)
{
	Keys_GPIO_Config();
}


void KeyDeal(char * keyvalue,OS_ERR * p_err)
{
	static OS_TICK 		tickstart[4];
	static OS_TICK 		tickend[4];
	static CPU_INT08U      enternumber[4]={0,0,0,0};
	static CPU_INT08U      pushtime[4];

	switch (keyvalue[0])
		{
		case '2':
			if(enternumber[0])
				{
				tickend[0] = OSTimeGet(p_err);
				if(tickend[0] > tickstart[0])
					{
					pushtime[0] = tickend[0] - tickstart[0];
					}
				else
					{
					pushtime[0] = tickend[0] + (0xFFFFFFFF - tickstart[0]);
					}
				enternumber[0] = 0;
				}
			else
				{
				tickstart[0] = OSTimeGet(p_err);
				enternumber[0] = 1;
				}
			
			break;

		case '3':
			break;

		case '4':
			break;

		case '5':
			break;

		default:
			break;
		}

}


CPU_TS			count11;


void KeyDealTask(void * p_arg)
{
	CPU_TS			ptime;
	OS_MSG_SIZE 	msize;
	OS_ERR			err;
	char *			pMsg;
	

	(void)
	p_arg;

	while (DEF_TRUE)
		{
		pMsg				= OSTaskQPend((OS_TICK) 0, 
			(OS_OPT) OS_OPT_PEND_BLOCKING, 
			(OS_MSG_SIZE *) &msize, 
			(CPU_TS *) &ptime, 
			(OS_ERR *) &err);

		if (err == OS_ERR_NONE)
			{
			KeyDeal(pMsg,&err);
			}
		}

}


void KEY2_IRQ_DEAL(void)
{
	OS_ERR			err;

	OSIntEnter();

	if (EXTI_GetITStatus(KEY2_EXTI_Line) != RESET) //这里为判断相应的中断号是否进入中断，如果有多个中断的话。
		{
		EXTI_ClearITPendingBit(KEY2_EXTI_Line); 	//清中断
		OSTaskQPost((OS_TCB *) & (KeyDealTaskTCB), 
			"2", 
			(OS_MSG_SIZE) sizeof("2"), 
			(OS_OPT) OS_OPT_POST_FIFO, 
			(OS_ERR *) &err);
		}

	OSIntExit();

}


void KEY3_IRQ_DEAL(void)
{
	OS_ERR			err;

	OSIntEnter();

	if (EXTI_GetITStatus(KEY3_EXTI_Line) != RESET) //这里为判断相应的中断号是否进入中断，如果有多个中断的话。
		{
		EXTI_ClearITPendingBit(KEY3_EXTI_Line); 	//清中断
		OSTaskQPost((OS_TCB *) & (KeyDealTaskTCB), 
			"3", 
			(OS_MSG_SIZE) sizeof("3"), 
			(OS_OPT) OS_OPT_POST_FIFO, 
			(OS_ERR *) &err);

		}

	OSIntExit();

}


void KEY4_IRQ_DEAL(void)
{
	OS_ERR			err;

	OSIntEnter();

	if (EXTI_GetITStatus(KEY4_EXTI_Line) != RESET) //这里为判断相应的中断号是否进入中断，如果有多个中断的话。
		{
		EXTI_ClearITPendingBit(KEY4_EXTI_Line); 	//清中断
		OSTaskQPost((OS_TCB *) & (KeyDealTaskTCB), 
			"4", 
			(OS_MSG_SIZE) sizeof("4"), 
			(OS_OPT) OS_OPT_POST_FIFO, 
			(OS_ERR *) &err);

		}

	OSIntExit();

}


void KEY5_IRQ_DEAL(void)
{
	OS_ERR			err;

	OSIntEnter();

	if (EXTI_GetITStatus(KEY5_EXTI_Line) != RESET) //这里为判断相应的中断号是否进入中断，如果有多个中断的话。
		{
		EXTI_ClearITPendingBit(KEY5_EXTI_Line); 	//清中断
		OSTaskQPost((OS_TCB *) & (KeyDealTaskTCB), 
			"5", 
			(OS_MSG_SIZE) sizeof("5"), 
			(OS_OPT) OS_OPT_POST_FIFO, 
			(OS_ERR *) &err);

		}

	OSIntExit();

}




/*********************************************END OF FILE**********************/
