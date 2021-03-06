
#include "keys.h"	


/*
*********************************************************************************************************
*												  TCB
*********************************************************************************************************
*/
OS_TCB	KeyDealTaskTCB;


/*
*********************************************************************************************************
*												 STACKS
*********************************************************************************************************
*/
CPU_STK	KeyDealTaskStk[APP_TASK_START_STK_SIZE];


/*
*********************************************************************************************************
*										  FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void KeyDealTask(void * p_arg);

static void Keys_GPIO_Config(void);



/**
 * @brief  配置 LED 的 GPIO 功能
 * @param  无
 * @retval 无
 */
static void Keys_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
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
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //涓柇鏂瑰紡涓轰笂鍗囦笌涓嬮檷娌�
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
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //涓柇鏂瑰紡涓轰笂鍗囦笌涓嬮檷娌�
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
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //涓柇鏂瑰紡涓轰笂鍗囦笌涓嬮檷娌�
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
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //涓柇鏂瑰紡涓轰笂鍗囦笌涓嬮檷娌�
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
 * @brief  LED 初始化函数
 * @param  无
 * @retval 无
 */
void Keys_Init(void)
{
	Keys_GPIO_Config();
}

void KeyDealTask(void * p_arg)
{
	CPU_TS         ptime;
	OS_MSG_SIZE    msize;
	OS_ERR			err;

	(void)
	p_arg;
	while(DEF_TRUE)
		{
		OSTaskQPend(
			(OS_TICK) 0, 
			(OS_OPT) OS_OPT_PEND_BLOCKING, 
			(OS_MSG_SIZE *) &msize, 
			(CPU_TS *) &ptime, 
			(OS_ERR *) &err);
		if(err == OS_ERR_NONE)
			{
			ptime = 0;
			}
		}

}


void KEY2_IRQ_DEAL(void)
{
	OS_ERR			err;
	
	OSIntEnter ();

	if (EXTI_GetITStatus(KEY2_EXTI_Line) != RESET) //杩欓噷涓哄垽鏂浉搴旂殑涓柇鍙锋槸鍚﹁繘鍏ヤ腑鏂紝濡傛灉鏈夊涓腑鏂殑璇濄��
		{
		EXTI_ClearITPendingBit(KEY2_EXTI_Line); 	//娓呬腑鏂�
		OSTaskQPost(
			(OS_TCB *) &(KeyDealTaskTCB), 
			 "1", 
			(OS_MSG_SIZE) sizeof("1"), 
			(OS_OPT) OS_OPT_POST_FIFO, 
			(OS_ERR *) &err);
		}
	OSIntExit ();

}


void KEY3_IRQ_DEAL(void)
{
	OSIntEnter ();

	if (EXTI_GetITStatus(KEY3_EXTI_Line) != RESET) //杩欓噷涓哄垽鏂浉搴旂殑涓柇鍙锋槸鍚﹁繘鍏ヤ腑鏂紝濡傛灉鏈夊涓腑鏂殑璇濄��
		{
		EXTI_ClearITPendingBit(KEY3_EXTI_Line); 	//娓呬腑鏂�

		}
	OSIntExit ();

}


void KEY4_IRQ_DEAL(void)
{
	OSIntEnter ();

	if (EXTI_GetITStatus(KEY4_EXTI_Line) != RESET) //杩欓噷涓哄垽鏂浉搴旂殑涓柇鍙锋槸鍚﹁繘鍏ヤ腑鏂紝濡傛灉鏈夊涓腑鏂殑璇濄��
		{
		EXTI_ClearITPendingBit(KEY4_EXTI_Line); 	//娓呬腑鏂�

		}
	OSIntExit ();

}


void KEY5_IRQ_DEAL(void)
{
	OSIntEnter ();

	if (EXTI_GetITStatus(KEY5_EXTI_Line) != RESET) //杩欓噷涓哄垽鏂浉搴旂殑涓柇鍙锋槸鍚﹁繘鍏ヤ腑鏂紝濡傛灉鏈夊涓腑鏂殑璇濄��
		{
		EXTI_ClearITPendingBit(KEY5_EXTI_Line); 	//娓呬腑鏂�

		}
	OSIntExit ();

}




/*********************************************END OF FILE**********************/
