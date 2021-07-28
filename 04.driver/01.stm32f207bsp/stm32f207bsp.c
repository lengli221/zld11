#include "includes.h"

/*
** �ж����������
*/
void NVIC_Config(void){
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/*
	** ��ʱ���ж�
	*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =  0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/*
	**CAN�жϳ�ʼ��
	*/
	CAN1_NVIC_Init();

	/*
	** CAN�жϳ�ʼ��
	*/
	CAN2_NVIC_Init();	
}

/*
** �����ݴ���
*/
void HardFault_Handler(void){
	NVIC_SystemReset();
}

/*
** Eeprom��ʼ��
*/
void Eeprom_Init(void){
	FM24_Init();
}

int8 eeprom_write(int32 addr, uint8 *buf, int32 len){
	return FMWrite(buf, addr, len);
}

int8 eeprom_read(int32 addr, uint8 *buf, int32 len){
	return FMRead(buf, addr, len);
}

uint32 BspCPUClkFreq(void)
{
	RCC_ClocksTypeDef  rcc_clocks;
	RCC_GetClocksFreq(&rcc_clocks);
	return ((uint32)rcc_clocks.HCLK_Frequency);
}

void BspInit(void){
	/*�ڲ�FLASH����*/
	FLASH_Lock();
	/*
	** �̼���������
	*/
	GPIO_Init_Config();
	/*
	** RTCʱ�ӳ�ʼ��
	*/	
	rtc_Init();
	/*
	** �ж����������
	*/
	NVIC_Config();
	/*
	** ʹ�ܱ�����ʱ��
	*/
	PWR_BackupInit();
	/*
	** ���Ź���ʼ��
	*/
	watchdogInit();
	/*
	** USARTͨѶ��ʼ��
	*/
	Com_Init();
	/*
	** ϵͳ֮�˲���Ƴ�ʼ������
	*/
	SysFilterDesign_ParamInit();
	/*
	**CAN��ʼ��
	*/
	CAN_Cfg_Init();
	/*
	** Eeprom��ʼ��
	*/
	Eeprom_Init();
	/*
	** ��ʼ��FLASH,�ṩ�ⲿ�ļ�����
	*/
	spi_flash_init();
	/*
	** ADC ��ʼ��
	*/
	AD_UseInit();

	/*
	** init Param
	*/
	init_Param();
}

