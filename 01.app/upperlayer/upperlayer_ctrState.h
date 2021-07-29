#ifndef __UPPERLAYER_CTRSTATE_H_
#define __UPPERLAYER_CTRSTATE_H_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** parse Ctr State
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_CtrState(uint16 rxlen,uint8* rx);

/*
** packect Ctr State
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_CtrState(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** ctr State Logic
*/
void ctr_StateLogic(void);

#endif

