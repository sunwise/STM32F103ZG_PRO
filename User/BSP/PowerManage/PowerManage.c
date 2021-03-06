
#include "PowerManage.h"   


/*
*********************************************************************************************************
*												  TCB
*********************************************************************************************************
*/
OS_TCB	PowerManTaskTCB;


/*
*********************************************************************************************************
*												 STACKS
*********************************************************************************************************
*/
CPU_STK	PowerManTaskStk[POWER_MAN_TASK_STK_SIZE];


/*
*********************************************************************************************************
*										  FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void Powermanage_GPIO_Config(void);
OS_SEM ALLADCCON;
CPU_INT16U		AD_Value[4][4];

/**
 * @brief  配置 LED 的 GPIO 功能
 * @param  无
 * @retval 无
 */
static void Powermanage_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* 配置 LED1 引脚 */
	RCC_APB2PeriphClockCmd(KILL_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KILL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KILL_GPIO_PORT, &GPIO_InitStructure);
}


static void AllAdcInit(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE); //浣胯兘ADC1閫氶亾鏃堕挓
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //浣胯兘DMA浼犺緭


	RCC_ADCCLKConfig(RCC_PCLK2_Div8);				//璁剧疆ADC鍒嗛鍥犲瓙8 72M/8=9,ADC鏈�澶ф椂閽熶笉鑳借秴杩�14M

	/* PC0 浣滀负妯℃嫙閫氶亾杈撳叆寮曡剼 ->ADC_IN10 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//妯℃嫙杈撳叆寮曡剼
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ADC鍒濆鍖�*/
	ADC_DeInit(ADC1);								//灏嗗璁� ADC1 鐨勫叏閮ㄥ瘎瀛樺櫒閲嶈涓虹己鐪佸��

	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC宸ヤ綔妯″紡:ADC1鍜孉DC2宸ヤ綔鍦ㄧ嫭绔嬫ā寮�
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//妯℃暟杞崲宸ヤ綔鍦ㄦ壂鎻忔ā寮�
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //妯℃暟杞崲宸ヤ綔鍦ㄨ繛缁浆鎹㈡ā寮�
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //澶栭儴瑙﹀彂杞崲鍏抽棴
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC鏁版嵁鍙冲榻�
	ADC_InitStructure.ADC_NbrOfChannel = 4; 		//椤哄簭杩涜瑙勫垯杞崲鐨凙DC閫氶亾鐨勬暟鐩�
	ADC_Init(ADC1, &ADC_InitStructure); 			//鏍规嵁ADC_InitStruct涓寚瀹氱殑鍙傛暟鍒濆鍖栧璁続DCx鐨勫瘎瀛樺櫒

	/* ADC1 regular channel11 configuration */
	//璁剧疆鎸囧畾ADC鐨勮鍒欑粍閫氶亾锛岃缃畠浠殑杞寲椤哄簭鍜岄噰鏍锋椂闂�
	//ADC1,ADC閫氶亾x,瑙勫垯閲囨牱椤哄簭鍊间负y,閲囨牱鏃堕棿涓�239.5鍛ㄦ湡
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_239Cycles5);

	// 寮�鍚疉DC鐨凞MA鏀寔锛堣瀹炵幇DMA鍔熻兘锛岃繕闇�鐙珛閰嶇疆DMA閫氶亾绛夊弬鏁帮級
	ADC_DMACmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);							//浣胯兘鎸囧畾鐨凙DC1

	/* Enable ADC1 reset calibaration register */
	ADC_ResetCalibration(ADC1); 					//澶嶄綅鎸囧畾鐨凙DC1鐨勬牎鍑嗗瘎瀛樺櫒

	/* Check the end of ADC1 reset calibration register */
	while (ADC_GetResetCalibrationStatus(ADC1))
		; //鑾峰彇ADC1澶嶄綅鏍″噯瀵勫瓨鍣ㄧ殑鐘舵��,璁剧疆鐘舵�佸垯绛夊緟

	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1); 					//寮�濮嬫寚瀹欰DC1鐨勬牎鍑嗙姸鎬�

	/* Check the end of ADC1 calibration */
	while (ADC_GetCalibrationStatus(ADC1))
		; //鑾峰彇鎸囧畾ADC1鐨勬牎鍑嗙▼搴�,璁剧疆鐘舵�佸垯绛夊緟


}


/*閰嶇疆DMA*/
void DMA_Configuration(void)
{
	/* ADC1  DMA1 Channel Config */
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	DMA_DeInit(DMA1_Channel1);						//灏咲MA鐨勯�氶亾1瀵勫瓨鍣ㄩ噸璁句负缂虹渷鍊�
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32) &ADC1->DR; //DMA澶栬ADC鍩哄湴鍧�
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32) &AD_Value; //DMA鍐呭瓨鍩哄湴鍧�
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //鍐呭瓨浣滀负鏁版嵁浼犺緭鐨勭洰鐨勫湴
	DMA_InitStructure.DMA_BufferSize = 16;			//DMA閫氶亾鐨凞MA缂撳瓨鐨勫ぇ灏�
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //澶栬鍦板潃瀵勫瓨鍣ㄤ笉鍙�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //鍐呭瓨鍦板潃瀵勫瓨鍣ㄩ�掑
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //鏁版嵁瀹藉害涓�16浣�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //鏁版嵁瀹藉害涓�16浣�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //宸ヤ綔鍦ㄥ惊鐜紦瀛樻ā寮�
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA閫氶亾 x鎷ユ湁楂樹紭鍏堢骇 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	//DMA閫氶亾x娌℃湁璁剧疆涓哄唴瀛樺埌鍐呭瓨浼犺緭
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	//鏍规嵁DMA_InitStruct涓寚瀹氱殑鍙傛暟鍒濆鍖朌MA鐨勯�氶亾


	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	DMA_ClearITPendingBit(DMA_IT_TC);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


}



/**
 * @brief  LED 初始化函数
 * @param  无
 * @retval 无
 */
void Powermanage_Init(void)
{
	OS_ERR err;
		
	Powermanage_GPIO_Config();

	KILL_HIGH();

	AllAdcInit();

	DMA_Configuration();

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE); 				//鍚姩DMA閫氶亾

	OSSemCreate(&ALLADCCON,"ADCCON",  0,&err);
}

void PowerManTask(void * p_arg)
{
	OS_ERR err;
	CPU_INT16U  poweradcv;
	CPU_INT16U batteryvoltage;

	(void)
	p_arg;
	

	while (DEF_TRUE)
			{ /* Task body, always written as an infinite loop. 	  */
			OSSemPend(&ALLADCCON, 0, OS_OPT_PEND_BLOCKING, (CPU_TS * )0, &err);
			poweradcv = AD_Value[0][0] + AD_Value[1][0] + AD_Value[2][0] + AD_Value[3][0];
			poweradcv = poweradcv >> 2;
			batteryvoltage = poweradcv / 286;

			if(batteryvoltage < 7)
				{
				KILL_LOW();
				}
			}

}


void DMA1_Channel1_IRQHandler(void)
{
	OS_ERR err;

	OSIntEnter();

	if(DMA_GetITStatus(DMA_IT_TC)==SET)
		{
		DMA_ClearITPendingBit(DMA_IT_TC);
		OSSemPost(&ALLADCCON, OS_OPT_POST_ALL, &err);
		}

	OSIntExit();

}

/*********************************************END OF FILE**********************/
