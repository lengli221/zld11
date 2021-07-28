#ifndef __LOWERLAYER_CFG_H_
#define __LOWERLAYER_CFG_H_

#include "type.h"

#pragma pack(1)
typedef union{
	uint8 flag;
	struct{
		uint8 chargerOT:1;/*充电器过温配置超限*/
		uint8 batOT:1;/*电池过温配置超限*/
		uint8 socO:1;/*SOC配置超限*/
		uint8 chargerTimeO:1;/*充电时间配置超限*/
		uint8 res:4;/*保留*/
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
