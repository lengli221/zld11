#ifndef __UPPERLAYER_OPENDOOR_H_
#define __UPPERLAYER_OPENDOOR_H_

#include "type.h"
#include "upperlayer_Parse.h"

/*
** Open Door Proc
*/
typedef struct{
	bool flag;/*���ֽ��̱�־*/
	uint8 addr;/*���ŵ�ַ*/
	uint8 result;/*������*/
}OpenDoorProc;

/*
** Open Door Reslut 
*/
typedef struct{
	bool flag;/*�ϱ����*/
	/*
	** -2:�ֿ�ʧ��
	**	0:���ֳɹ�
	**	1:�ֿ�δ��Ӧָ��
	**	2:���Ź���
	**	3.�ֿ�ִ�п��ֶ�������
	*/
	int8 result;
}OpenDoorResult;

/*
** parse open Door
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_openDoor(uint16 rxlen,uint8* rx);

/*
** packect open Door
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_openDoor(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** open Door Proc
*/
void open_DoorProc(void);

/*
** parse open Door Result
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_openDoorResult(uint16 rxlen,uint8* rx);

/*
** packect open Door Result
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_openDoorResult(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num);

/*
** open Door Result Proc 
*/
void open_DoorResultProc(void);

#endif

