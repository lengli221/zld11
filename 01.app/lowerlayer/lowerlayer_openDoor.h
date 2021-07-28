#ifndef __LOWERLAYER_OPENDOOR_H_
#define __LOWERLAYER_OPENDOOR_H_

typedef struct{
	bool flag[SysCtr_AllDoorNum];/*开仓标志动作是否执行标志*/
}ExceOpenDoor;

/*
** get Exce Open Door
**	@param:
**		uint8:仓门地址
**	@return:
**		bool:执行标志
*/
bool get_ExceOpenDoor(uint8 addr);

/*
** set LowerLayer OpenDoor
** @ param:
**		addr:单点开仓
*/
void set_LowerLayerOpenDoor(uint8 addr);

/*
** Lowerlayer Open Door   
*/
void Lowerlayer_ParseOpenDoor(uint8 rxlen,uint8* item,uint8 addr);

#endif

