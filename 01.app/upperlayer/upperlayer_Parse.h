#ifndef __UPPERLAYER_PARSE_H_
#define __UPPERLAYER_PARSE_H_

#include "type.h"

/*
** ֡ͷ֡β
*/
#define UpperLayerFrame_Head										(uint8)0x68
#define UpperLayerFrame_End											(uint8)0x16

/*
** ֡���ȺϷ�������	
*/
#define FrameLenIsLegal_Min											(uint16)0x0009
#define FrameLenIsLegal_Max											(uint16)0x0039

#pragma pack(1)
/*
** ֡��ʽ
*/
typedef struct{
	uint8 id;/*��Ϣid*/
	uint16 dataLen;/*���ݳ���*/
	uint8 addr;/*���豸��ַ*/
}MsgHead;

typedef struct{
	uint8 head;/*֡��ʼ��*/
	uint16 msgFrameLen;/*֡����*/
	MsgHead msgHead;/*��Ϣͷ*/
	uint8 chkCode;/*У����*/
	uint8 end;/*֡������*/
}UpperLayerFrame;

/*
** ���ܺ���֮�����ϲ�Э��
*/
typedef struct{
	uint8 id;/*��ϢID*/
	void (*handle)(uint16,uint8*);/*�������,������*/
}UpperLayerFunTable;

#pragma pack()

/*
** �ṩϵͳ��������ϲ�Э������ӿں���
*/
void UpperLayerParse_Init(void);

#endif
