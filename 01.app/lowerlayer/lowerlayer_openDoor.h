#ifndef __LOWERLAYER_OPENDOOR_H_
#define __LOWERLAYER_OPENDOOR_H_

typedef struct{
	bool flag[SysCtr_AllDoorNum];/*���ֱ�־�����Ƿ�ִ�б�־*/
}ExceOpenDoor;

/*
** get Exce Open Door
**	@param:
**		uint8:���ŵ�ַ
**	@return:
**		bool:ִ�б�־
*/
bool get_ExceOpenDoor(uint8 addr);

/*
** set LowerLayer OpenDoor
** @ param:
**		addr:���㿪��
*/
void set_LowerLayerOpenDoor(uint8 addr);

/*
** Lowerlayer Open Door   
*/
void Lowerlayer_ParseOpenDoor(uint8 rxlen,uint8* item,uint8 addr);

#endif

