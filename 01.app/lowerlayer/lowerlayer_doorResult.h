#ifndef __LOWERLAYER_DOORRESULT_H_
#define __LOWERLAYER_DOORRESULT_H_

#include "type.h"

/*
** Door Result 
*/
typedef struct{
	bool flag;/*标记*/
	uint8 result;/*结果*/
}DoorResult;

/*
** get Door Result Flag
**	@param:
**		uint8:仓门地址
**	@return:
**		bool:true-->表明分控已完成开仓指令等待上报安卓
*/
bool get_DoorResultFlag(uint8 addr);

/*
** get Door Result 
**	@param:
**		uint8:仓门地址
**	@return:
**		uint8:结果
*/
uint8 get_DoorResult(uint8 addr);

/*
** set DoorResult
**	@param:
**		uint8:仓门地址
**		uint8:true-->表明分控已完成开仓指令等待上报安卓 false-->空闲
*/
void set_DoorResult(uint8 addr,bool flag,uint8 result);

/*
** Lowerlayer Parse door Result
*/
void Lowerlayer_ParseDoorResult(uint8 rxlen,uint8* item,uint8 addr);

#endif

