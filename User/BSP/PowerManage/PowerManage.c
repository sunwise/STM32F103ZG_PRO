#include "PowerManage.h"   



static void                         Powermanage_GPIO_Config                  ( void );



 /**
  * @brief  ���� LED �� GPIO ����
  * @param  ��
  * @retval ��
  */
static void Powermanage_GPIO_Config ( void )
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* ���� LED1 ���� */
	RCC_APB2PeriphClockCmd ( KILL_GPIO_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = KILL_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( KILL_GPIO_PORT, & GPIO_InitStructure );	
}


 /**
  * @brief  LED ��ʼ������
  * @param  ��
  * @retval ��
  */
void Powermanage_Init ( void )
{
  Powermanage_GPIO_Config ();
	
	KILL_HIGH();
	
}



/*********************************************END OF FILE**********************/
