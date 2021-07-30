#ifndef __UPPERLAYER_CHARGER_
#define __UPPERLAYER_CHARGER_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** parse charger
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_charger(uint16 rxlen,uint8* rx);

/*
** packect charger
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_charger(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** charger Logic
*/
void charger_Logic(void);

#endif

