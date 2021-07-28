#ifndef __LOWERLAYER_CFG_H_
#define __LOWERLAYER_CFG_H_

#include "type.h"

#pragma pack(1)
typedef union{
	uint8 flag;
	struct{
		uint8 chargerOT:1;/*������������ó���*/
		uint8 batOT:1;/*��ع������ó���*/
		uint8 socO:1;/*SOC���ó���*/
		uint8 chargerTimeO:1;/*���ʱ�����ó���*/
		uint8 res:4;/*����*/
	}bits;
}LLParse_Cfg;
#pragma pack()

/*
** LowerLayer Cfg
*/
void LowerLayer_Cfg(void);

/*
** Lowerlayer Parse Cfg
*/
void Lowerlayer_ParseCfg(uint8 rxlen,uint8* item,uint8 addr);

#endif
