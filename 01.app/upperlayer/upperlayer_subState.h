#ifndef __UPPERLAYER_SUBSTATE_H_
#define __UPPERLAYER_SUBSTATE_H_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** parse Sub State
**	@param:
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_SubState(uint16 rxlen,uint8* rx);

/*
** packect sub State
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_SubState(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** sub State Logic
*/
void sub_StateLogic(void);

#endif

