#ifndef __LOWERLAYER_CHARGERINFO_H_
#define __LOWERLAYER_CHARGERINFO_H_

#include "type.h"

#pragma pack(1)
/*
** Charger Set
*/
typedef struct{
	uint16 vol;/*���õ�ѹ--0.1*/
	int16 cur;/*���õ���--0.01*/
	uint16 onoff;/*���ÿ��ػ�--0:�ػ� 1:����*/
}ChargerSet;

/*
** Charger Err
*/
typedef union{
	uint16 flag;
	struct{
		uint16 outputVolH:1;/*�����ѹ��*/
		uint16 outVolAvgH:1;/*�����ѹƽ��ֵ��*/
		uint16 batVolH:1;/*��ص�ѹ��*/
		uint16 batVolAvgH:1;/*��ص�ѹƽ��ֵ��*/
		uint16 batVolAvgL:1;/*��ص�ѹƽ��ֵ��*/
		uint16 batAT:1;/*��ط���*/
		uint16 batVolAb:1;/*��ص�ѹ�쳣*/
		uint16 outputOC:1;/*�������*/
		uint16 outputCurAvgH:1;/*�������ƽ��ֵ��*/
		uint16 chargerH:1;/*������¶ȹ���*/
		uint16 res:6;
	}bits;
}ChargerErr;

/*
** Charger Get
*/
typedef struct{
	uint16 chgCur;/*������*/
	uint16 batVol;/*��ص�ѹ*/
	uint16 outputVol;/*�����ѹ*/
	ChargerErr err;/*������Ϣ*/
	uint16 state;/*״̬��Ϣ*/
}ChargerGet;

/*
** Charger Info
*/
typedef union{
	struct{
		ChargerSet set;
		ChargerGet get;
	}Field;
	uint8 zone[16];
}ChargerInfo;
#pragma pack()

/*
** get Charger Info
**	@param:
**		uint8:���ŵ�ַ
**	@return:
**		ChargerInfo:�������ϸ��Ϣ
*/
ChargerInfo get_ChargerInfo(uint8 addr);

/*
** Lowerlayer Charger
*/
void Lowerlayer_Charger(void);

/*
** Lowerlayer Parse Charger
**	@param:
**		uint8:�������
**		uint8*:������
**		uint8:��λ��ַ
*/
void Lowerlayer_ParseCharger(uint8 rxlen,uint8* item,uint8 addr);

#endif

