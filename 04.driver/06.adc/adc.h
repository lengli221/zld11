#ifndef __ADC_H_
#define __ADC_H_

#define cSampleTimes													1
#define cChannelNum   												6

#define cSampleTimes_3												1
#define cChannelNum_3   												3

#define ADC1_DR_ADDRESS    										((uint32_t)0x4001204C)
#define ADC3_DR_ADDRESS    										((uint32_t)0x4001224C)


/*
** ADC1 ����ͨ��˵��
** 0.1.2-->���ѹ(ABC) 
** 3.�����¶�
*/
#define APhaseVol_AD_1												0
#define Temper1_ADResult   											3
#define Temper2_ADResult  											4

/*
** ADC3 ����ͨ��˵��
** 0.1.2-->�����(ABC)
*/
#define APhaseCur_ADC_3											0

/*
** ADC ��ʼ��
*/
void AD_UseInit(void);
/*
** ADC1 ��ȡADC����AD Value
*/
uint16 ADC_GetADResultAD(uint8 channel);
/*
** ADC3 ��ȡADC����AD Value
*/
uint16 ADC3_GetADResultAD(uint8 ch);
#endif

