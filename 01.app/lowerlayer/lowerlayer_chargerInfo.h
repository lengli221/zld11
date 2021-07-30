#ifndef __LOWERLAYER_CHARGERINFO_H_
#define __LOWERLAYER_CHARGERINFO_H_

#include "type.h"

#pragma pack(1)
/*
** Charger Set
*/
typedef struct{
	uint16 vol;/*设置电压--0.1*/
	int16 cur;/*设置电流--0.01*/
	uint16 onoff;/*设置开关机--0:关机 1:开机*/
}ChargerSet;

/*
** Charger Err
*/
typedef union{
	uint16 flag;
	struct{
		uint16 outputVolH:1;/*输出电压高*/
		uint16 outVolAvgH:1;/*输出电压平均值高*/
		uint16 batVolH:1;/*电池电压高*/
		uint16 batVolAvgH:1;/*电池电压平均值高*/
		uint16 batVolAvgL:1;/*电池电压平均值低*/
		uint16 batAT:1;/*电池反接*/
		uint16 batVolAb:1;/*电池电压异常*/
		uint16 outputOC:1;/*输出过流*/
		uint16 outputCurAvgH:1;/*输出电流平均值高*/
		uint16 chargerH:1;/*充电器温度过高*/
		uint16 res:6;
	}bits;
}ChargerErr;

/*
** Charger Get
*/
typedef struct{
	uint16 chgCur;/*充电电流*/
	uint16 batVol;/*电池电压*/
	uint16 outputVol;/*输出电压*/
	ChargerErr err;/*故障信息*/
	uint16 state;/*状态信息*/
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
**		uint8:仓门地址
**	@return:
**		ChargerInfo:充电器详细信息
*/
ChargerInfo get_ChargerInfo(uint8 addr);

/*
** Lowerlayer Charger
*/
void Lowerlayer_Charger(void);

/*
** Lowerlayer Parse Charger
**	@param:
**		uint8:数据项长度
**		uint8*:数据项
**		uint8:仓位地址
*/
void Lowerlayer_ParseCharger(uint8 rxlen,uint8* item,uint8 addr);

#endif

