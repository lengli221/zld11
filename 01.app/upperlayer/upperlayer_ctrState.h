#ifndef __UPPERLAYER_CTRSTATE_H_
#define __UPPERLAYER_CTRSTATE_H_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** parse Ctr State
**	@param:
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_CtrState(uint16 rxlen,uint8* rx);

/*
** packect Ctr State
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_CtrState(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** ctr State Logic
*/
void ctr_StateLogic(void);

#endif

