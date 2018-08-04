
#include "PowerManage.h"   



static void Powermanage_GPIO_Config(void);



/**
 * @brief  ���� LED �� GPIO ����
 * @param  ��
 * @retval ��
 */
static void Powermanage_GPIO_Config(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* ���� LED1 ���� */
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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE); //使能ADC1通道时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能DMA传输


	RCC_ADCCLKConfig(RCC_PCLK2_Div8);				//设置ADC分频因子8 72M/8=9,ADC最大时钟不能超过14M

	/* PC0 作为模拟通道输入引脚 ->ADC_IN10 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ADC初始化*/
	ADC_DeInit(ADC1);								//将外设 ADC1 的全部寄存器重设为缺省值

	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //外部触发转换关闭
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 4; 		//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure); 			//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

	/* ADC1 regular channel11 configuration */
	//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
	//ADC1,ADC通道x,规则采样顺序值为y,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_239Cycles5);

	// 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
	ADC_DMACmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);							//使能指定的ADC1

	/* Enable ADC1 reset calibaration register */
	ADC_ResetCalibration(ADC1); 					//复位指定的ADC1的校准寄存器

	/* Check the end of ADC1 reset calibration register */
	while (ADC_GetResetCalibrationStatus(ADC1))
		; //获取ADC1复位校准寄存器的状态,设置状态则等待

	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1); 					//开始指定ADC1的校准状态

	/* Check the end of ADC1 calibration */
	while (ADC_GetCalibrationStatus(ADC1))
		; //获取指定ADC1的校准程序,设置状态则等待


}

CPU_INT16U AD_Value[4];

/*配置DMA*/
void DMA_Configuration(void)
{
	/* ADC1  DMA1 Channel Config */
	DMA_InitTypeDef DMA_InitStructure;

	DMA_DeInit(DMA1_Channel1);						//将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32) &ADC1->DR; //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32) &AD_Value; //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //内存作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = 4;		//DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	//根据DMA_InitStruct中指定的参数初始化DMA的通道

}



/**
 * @brief  LED ��ʼ������
 * @param  ��
 * @retval ��
 */
void Powermanage_Init(void)
{
	Powermanage_GPIO_Config();

	KILL_HIGH();

	AllAdcInit();
	
	DMA_Configuration();

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    DMA_Cmd(DMA1_Channel1, ENABLE);         //启动DMA通道
}



/*********************************************END OF FILE**********************/
