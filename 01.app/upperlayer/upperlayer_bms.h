#ifndef __UPPERLAYER_BMS_H_
#define __UPPERLAYER_BMS_H_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** parse bms
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_bms(uint16 rxlen,uint8* rx);

/*
** packect bms
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_bms(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** bms Logic
*/
void bms_Logic(void);

#endif
