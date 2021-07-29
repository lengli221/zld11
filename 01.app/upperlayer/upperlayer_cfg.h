#ifndef __UPPERLAYER_CFG_H_
#define __UPPERLAYER_CFG_H_

#include "type.h"
#include "upperlayer_Parse.h"

#pragma pack(1)
/*
** Cfg Info
*/
typedef struct{
	uint8 protocol;/*协议号*/
	uint8 softVer;/*软件版本号*/
	uint8 chargerOT;/*充电器过温阈值*/
	uint8 batOT;/*电池过温阈值*/
	uint8 socLimit;/*SOC阈值*/
	uint16 chgTime;/*充电时间阈值*/
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
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_CfgInfo(uint16 rxlen,uint8* rx);

/*
** packect Cfg Flag
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_CfgFlag(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

#endif

