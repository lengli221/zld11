#ifndef __UPPERLAYER_REPLY_
#define __UPPERLAYER_REPLY_

#include "type.h"
#include "upperlayer_Parse.h"

#pragma pack(1)
/*
** ��������ϵͳ�ṹ����ؽ���--�ϱ��ϲ�Э�鶨��ṹ��
*/
typedef struct{
	bool refresh;/*���±�־*/
	uint8 id;/*��ϢID*/
	uint8 deviceAddr;/*�豸��ַ*/
	uint8 doorAddr;/*���ŵ�ַ*/
	uint8 doorNum;/*����������*/
}SmCmd;

/*
** ���ܺ���֮�ظ��ϲ�Э��
*/
typedef struct{
	uint8 id;/*��ϢID*/
	void (*handle)(UpperLayerFrame*,uint8*,uint8,uint8);/*��Ϣ��ʽ,��������,���ŵ�ַ,������*/
}UpperLayerReplyFunTable;
#pragma pack()

/*set cmd*/
void setCmd(SmCmd cmd);

/*
**�ṩϵͳ��������ϲ�Э��ظ��ӿں���
*/
void UpperLayerReply_Init(void);

#endif
