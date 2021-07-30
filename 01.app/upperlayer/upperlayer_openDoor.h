#ifndef __UPPERLAYER_OPENDOOR_H_
#define __UPPERLAYER_OPENDOOR_H_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** Open Door Proc
*/
typedef struct{
	bool flag;/*开仓进程标志*/
	uint8 addr;/*仓门地址*/
	uint8 result;/*命令结果*/
}OpenDoorProc;

/*
** Open Door Reslut 
*/
typedef struct{
	bool flag;/*上报标记*/
	/*
	** -2:分控失联
	**	0:开仓成功
	**	1:分控未响应指令
	**	2:仓门故障
	**	3.分控执行开仓动作操作
	*/
	int8 result;
}OpenDoorResult;

/*
** parse open Door
**	@param:
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_openDoor(uint16 rxlen,uint8* rx);

/*
** packect open Door
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_openDoor(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** open Door Proc
*/
void open_DoorProc(void);

/*
** parse open Door Result
**	@param:
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_openDoorResult(uint16 rxlen,uint8* rx);

/*
** packect open Door Result
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_openDoorResult(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** open Door Result Proc 
*/
void open_DoorResultProc(void);

#endif

