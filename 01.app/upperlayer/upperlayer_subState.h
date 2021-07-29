#ifndef __UPPERLAYER_SUBSTATE_H_
#define __UPPERLAYER_SUBSTATE_H_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** parse Sub State
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_SubState(uint16 rxlen,uint8* rx);

/*
** packect sub State
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_SubState(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** sub State Logic
*/
void sub_StateLogic(void);

#endif

