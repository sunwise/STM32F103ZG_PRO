
#include "keys.h"	



static void Keys_GPIO_Config(void);



/**
 * @brief  ≈‰÷√ LED µƒ GPIO π¶ƒ‹
 * @param  Œﬁ
 * @retval Œﬁ
 */
static void Keys_GPIO_Config(void)
{
	/*∂®“Â“ª∏ˆGPIO_InitTypeDef¿‡–ÕµƒΩ·ππÃÂ*/
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
	EXTI_InitStructure.EXTI_Line= KEY2_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Rising_Falling;   //‰∏≠Êñ≠ÊñπÂºè‰∏∫‰∏äÂçá‰∏é‰∏ãÈôçÊ≤ø
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	

	/* */
	RCC_APB2PeriphClockCmd(KEY3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY3_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY3_GPIO_PORT, &GPIO_InitStructure);

	EXTI_ClearITPendingBit(KEY3_EXTI_Line);
	GPIO_EXTILineConfig(KEY3_PortSource, KEY3_PINSource);
	EXTI_InitStructure.EXTI_Line= KEY3_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Rising_Falling;   //‰∏≠Êñ≠ÊñπÂºè‰∏∫‰∏äÂçá‰∏é‰∏ãÈôçÊ≤ø
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* */
	RCC_APB2PeriphClockCmd(KEY4_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY4_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);

	EXTI_ClearITPendingBit(KEY4_EXTI_Line);
	GPIO_EXTILineConfig(KEY4_PortSource, KEY4_PINSource);
	EXTI_InitStructure.EXTI_Line= KEY4_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Rising_Falling;   //‰∏≠Êñ≠ÊñπÂºè‰∏∫‰∏äÂçá‰∏é‰∏ãÈôçÊ≤ø
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* */
	RCC_APB2PeriphClockCmd(KEY5_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY5_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY5_GPIO_PORT, &GPIO_InitStructure);

	EXTI_ClearITPendingBit(KEY5_EXTI_Line);
	GPIO_EXTILineConfig(KEY5_PortSource, KEY5_PINSource);
	EXTI_InitStructure.EXTI_Line= KEY5_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode= EXTI_Mode_Interrupt; 
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Rising_Falling;   //‰∏≠Êñ≠ÊñπÂºè‰∏∫‰∏äÂçá‰∏é‰∏ãÈôçÊ≤ø
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);   //NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 2;        
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;   
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 2;        
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;   
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);   //NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY4_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 2;        
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;   
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);   //NVIC
	NVIC_InitStructure.NVIC_IRQChannel = KEY5_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1;        
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;   
	NVIC_Init(&NVIC_InitStructure);

	
}


/**
 * @brief  LED ≥ı ºªØ∫Ø ˝
 * @param  Œﬁ
 * @retval Œﬁ
 */
void Keys_Init(void)
{
	Keys_GPIO_Config();
}



/*********************************************END OF FILE**********************/
