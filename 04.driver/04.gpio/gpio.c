#include "includes.h"

/*
** �̼���������
*/
void GPIO_Init_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF , ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG , ENABLE);

	/*�������еƳ�ʼ��*/
	GPIO_RunLed_InitCfg();
}

