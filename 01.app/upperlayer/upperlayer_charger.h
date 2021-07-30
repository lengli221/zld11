#ifndef __UPPERLAYER_CHARGER_
#define __UPPERLAYER_CHARGER_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** parse charger
**	@param:
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_charger(uint16 rxlen,uint8* rx);

/*
** packect charger
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_charger(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** charger Logic
*/
void charger_Logic(void);

#endif

