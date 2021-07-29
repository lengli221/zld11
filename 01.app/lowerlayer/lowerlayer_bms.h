#ifndef __LOWERLAYER_BMS_H_
#define __LOWERLAYER_BMS_H_

#include "type.h"

#pragma pack(1)

/*
** Bms Id
*/
typedef struct{
	uint16 idLen;/*id����--�������ID�������ֵ��*/
	uint8 id[28];/*ID*/	
}BmsId;

/*
** Bms Item
*/
typedef struct{
	uint16 batVol;/*��ذ�ʵ���ܵ�ѹ--0.01*/
	uint16 batCoreNum;/*��о����*/
	uint16 soc;/*soc*/
	uint16 surplueCap;/*ʣ������--0.01 AH*/
	uint16 soh;/*soh*/
	int16 chgCur;/*������--0.01*/
	uint16 envTemp;/*�����¶�*/
	uint16 batCoreTemp;/*��о�¶�*/
	uint16 mosTemp;/*MOS���¶�*/
	uint16 batCoreVol[20];/*��оx��ѹ--0.001*/
	uint16 reqChgCur;/*���������--0.01*/
	uint16 maxChgVol;/*��߳���ѹ--0.01*/
	uint16 chgIsPermit;/*�������/��ֹ--0xAA55:������ ���������������*/	
}BmsItem;

/*
** Bms Err Detail
*/
typedef union{
	uint16 flag;
	struct{
		uint16 res0:1;/*����*/
		uint16 batCoreDiffPressP:1;/*��оѹ����󱣻�*/
		uint16 chgOCP:1;/*����������*/
		uint16 disOCP:1;/*�ŵ��������*/
		uint16 shortP:1;/*��·����*/
		uint16 chgHTP:1;/*�����±���*/
		uint16 disHTP:1;/*�ŵ���±���*/
		uint16 chgLTP:1;/*�����±���*/
		uint16 disLTP:1;/*�ŵ���±���*/
		uint16 chgMosE:1;/*���MOS��*/
		uint16 disMosE:1;/*�ŵ�Mos��*/
		uint16 innerComE:1;/*�ڲ�ͨѶ�쳣*/
		uint16 oChgVP:4;/*�����ѹ����1-4*/
	}bits;
}BmsErrDetail;

/*
** Bms Err
*/
typedef struct{
	BmsErrDetail errDetail;
	uint8 err[5];/*�����ѹ����5-20,���ŵ�ѹ����1-20*/ 
}BmsErr;

typedef union{
	struct{
		BmsId id;/*���ID��Ϣ*/
		BmsItem item;/*bms��������Ϣ*/
		BmsErr err;/*��ع�����Ϣ*/
	}Field;
	uint8 zone[101]; 
}BmsInfo;
#pragma pack()

/*
** get Bms Vol
**	@param:
**		uint8:���ŵ�ַ
**	@return:
**		uint16:vol--kenya:0.01V
*/
uint16 get_BmsVol(uint8 doorId);

/*
** get Bms Cur
** 	@param:
**		uint8:���ŵ�ַ
**	@return:
**		int16:cur--kenya:0.01A
*/
int16 get_BmsCur(uint8 doorId);

/*
** get Bms Soc
** 	@param:
**		uint8:���ŵ�ַ
**	@return:
**		uint8:soc
*/
uint8 get_BmsSoc(uint8 doorId);

/*
** get Bms Info
**	@param:
**		uint8:���ŵ�ַ
**	@return:
**		BmsInfo:bms��Ϣ
*/
BmsInfo get_BmsInfo(uint8 addr);

/*
** Lowerlayer Bms
*/
void Lowerlayer_Bms(void);

/*
** Lowerlayer Parse Bms
*/
void Lowerlayer_ParseBms(uint8 rxlen,uint8* item,uint8 addr);

#endif

