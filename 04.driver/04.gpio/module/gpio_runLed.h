#ifndef __GPIO_RunLed_H_
#define __GPIO_RunLed_H_

/*�������е�*/
#define Ctr_RunLed_On					(GPIOF->BSRRL = GPIO_Pin_10)
#define Ctr_RunLed_Off					(GPIOF->BSRRH = GPIO_Pin_10)


/*
** �������еƳ�ʼ��
*/
void GPIO_RunLed_InitCfg(void);
/*
** ���е���˸
** @param: time-->��˸Ƶ�ʿ���
*/
void RunLed_Ctr_Ficker(uint32 time);
#endif

