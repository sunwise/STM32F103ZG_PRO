#include "PowerManage.h"   



static void                         Powermanage_GPIO_Config                  ( void );



 /**
  * @brief  配置 LED 的 GPIO 功能
  * @param  无
  * @retval 无
  */
static void Powermanage_GPIO_Config ( void )
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* 配置 LED1 引脚 */
	RCC_APB2PeriphClockCmd ( KILL_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = KILL_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( KILL_GPIO_PORT, & GPIO_InitStructure );	
}


 /**
  * @brief  LED 初始化函数
  * @param  无
  * @retval 无
  */
void Powermanage_Init ( void )
{
  Powermanage_GPIO_Config ();
	
	KILL_HIGH();
	
}



/*********************************************END OF FILE**********************/
