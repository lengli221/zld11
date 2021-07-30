#ifndef __LOWERLAYER_DOORRESULT_H_
#define __LOWERLAYER_DOORRESULT_H_

#include "type.h"

/*
** Door Result 
*/
typedef struct{
	bool flag;/*���*/
	uint8 result;/*���*/
}DoorResult;

/*
** get Door Result Flag
**	@param:
**		uint8:���ŵ�ַ
**	@return:
**		bool:true-->�����ֿ�����ɿ���ָ��ȴ��ϱ���׿
*/
bool get_DoorResultFlag(uint8 addr);

/*
** get Door Result 
**	@param:
**		uint8:���ŵ�ַ
**	@return:
**		uint8:���
*/
uint8 get_DoorResult(uint8 addr);

/*
** set DoorResult
**	@param:
**		uint8:���ŵ�ַ
**		uint8:true-->�����ֿ�����ɿ���ָ��ȴ��ϱ���׿ false-->����
*/
void set_DoorResult(uint8 addr,bool flag,uint8 result);

/*
** Lowerlayer Parse door Result
*/
void Lowerlayer_ParseDoorResult(uint8 rxlen,uint8* item,uint8 addr);

#endif

