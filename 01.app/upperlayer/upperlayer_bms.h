#ifndef __UPPERLAYER_BMS_H_
#define __UPPERLAYER_BMS_H_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** parse bms
**	@param:
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_bms(uint16 rxlen,uint8* rx);

/*
** packect bms
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_bms(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** bms Logic
*/
void bms_Logic(void);

#endif
