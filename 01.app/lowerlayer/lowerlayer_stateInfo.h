#ifndef __LOWERLAYER_STATEINFO_H_
#define __LOWERLAYER_STATEINFO_H_

#include "type.h"

#pragma pack(1)
typedef union{
	uint8 flag;
	struct{
		/*---------- Ctr Sub Protcol V101 ----------------------*/
		uint8 batOnline:1;/*电池在线*/
		uint8 batErr:1;/*电池故障*/
		uint8 selfChkErr:1;/*自检故障*/
		uint8 chargerOnline:1;/*充电器在线*/
		uint8 chargerErr;/*充电器故障*/
		uint8 res:5;/*预留*/
		/*------------------------------------------------------*/
	}bits;
}Sub_RunState;
typedef struct{
	/*---------- Ctr Sub Protcol V101 ----------------------*/
	uint8 protocol;/*协议号*/
	uint8 softVer;/*软件版本号*/
	uint8 doorstate;/*仓门状态00:仓门关01:仓门开02:仓门故障*/
	uint8 doorLoc;/*仓定位00:空仓01:充电中02:满仓03:故障*/
	Sub_RunState subState;/*分控运行状态*/
	uint8 batErrLab;/*电池故障标识*/
	uint8 subErrLab;/*分控故障标识*/
	uint8 chargerErrLab;/*充电器故障*/
	/*------------------------------------------------------*/
}LLParse_StateInfo;
#pragma pack()

/*
** get Protocol Record
*/
uint8 get_ProtocolRecord(uint8 addr);
/*
** get Bat Is Online
** 	@param:
**		uint8:仓门地址
**	@return
**		flag:
**			true:电池在线
**			false:电池不在线
*/
bool get_BatIsOnline(uint8 addr);

/*
** get Bat Is Exit Err
**	@param:
**		uint8:仓门地址
**	@return:
**		bool:true-->电池故障false-->电池正常
*/
bool get_BatIsExitErr(uint8 addr);

/*
** get Charger Is Online
** 	@param:
**		uint8:仓门地址
**	@return
**		flag:
**			true:充电器在线
**			false:充电器不在线
*/
bool get_ChargerIsOnline(uint8 addr);

/*
** get Door State
**	@param:
**		uint8:仓门地址
**	return:
**		00:仓门关01:仓门开02:仓门故障
*/
uint8 get_DoorState(uint8 addr);

/*
** get Door Loc
**	@param:
**		uint8:仓门地址
**	return:
**		00:空仓01:充电中02:满仓03:故障
*/
uint8 get_DoorLoc(uint8 addr);

/*
** Lowerlayer State Info
*/
void LowerLayer_StateInfo(void);

/*
** Lowerlayer Parse State Info
*/
void Lowerlayer_ParseStateInfo(uint8 rxlen,uint8* item,uint8 addr);
#endif

