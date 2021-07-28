#include "includes.h"

/*
** �������еƳ�ʼ��
*/
void GPIO_RunLed_InitCfg(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*
	** �����������
	*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	

	/*
	** PF10--������˸��
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOF, &GPIO_InitStructure);	

	/*��ʼ������*/
	Ctr_RunLed_On;
}

/*
** ���е���˸
** @param: time-->��˸Ƶ�ʿ���
*/
void RunLed_Ctr_Ficker(uint32 time){
	static uint32 itick = 0;
	static bool flag = false;

	if(TickOut((uint32 *)&itick, time) == true){
		TickOut((uint32 *)&itick, 0);
		flag = flag == false?true:false;
		if(flag == true){
			Ctr_RunLed_On;
		}else{
			Ctr_RunLed_Off;
		}
	}
}

