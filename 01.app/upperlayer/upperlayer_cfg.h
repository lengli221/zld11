#ifndef __UPPERLAYER_CFG_H_
#define __UPPERLAYER_CFG_H_

#include "type.h"
#include "upperlayer_Parse.h"

#pragma pack(1)
/*
** Cfg Info
*/
typedef struct{
	uint8 protocol;/*Э���*/
	uint8 softVer;/*����汾��*/
	uint8 chargerOT;/*�����������ֵ*/
	uint8 batOT;/*��ع�����ֵ*/
	uint8 socLimit;/*SOC��ֵ*/
	uint16 chgTime;/*���ʱ����ֵ*/
}CfgInfo;

/*
** Cfg Flag
*/
typedef union{
	uint16 flag;
	struct{
		uint16 chargerOT:1;
		uint16 batOT:1;
		uint16 socLimit:1;
		uint16 chgTime:1;
	}bits;
}CfgFlag;
#pragma pack()

/*
** parse Cfg Info
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_CfgInfo(uint16 rxlen,uint8* rx);

/*
** packect Cfg Flag
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_CfgFlag(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

#endif

