#ifndef __UPPERLAYER_PARSE_H_
#define __UPPERLAYER_PARSE_H_

#include "type.h"

/*
** 帧头帧尾
*/
#define UpperLayerFrame_Head										(uint8)0x68
#define UpperLayerFrame_End											(uint8)0x16

/*
** 帧长度合法性限制	
*/
#define FrameLenIsLegal_Min											(uint16)0x0009
#define FrameLenIsLegal_Max											(uint16)0x0039

#pragma pack(1)
/*
** 帧格式
*/
typedef struct{
	uint8 id;/*消息id*/
	uint16 dataLen;/*数据长度*/
	uint8 addr;/*从设备地址*/
}MsgHead;

typedef struct{
	uint8 head;/*帧起始符*/
	uint16 msgFrameLen;/*帧长度*/
	MsgHead msgHead;/*消息头*/
	uint8 chkCode;/*校验码*/
	uint8 end;/*帧结束符*/
}UpperLayerFrame;

/*
** 功能函数之解析上层协议
*/
typedef struct{
	uint8 id;/*消息ID*/
	void (*handle)(uint16,uint8*);/*数据项长度,数据项*/
}UpperLayerFunTable;

#pragma pack()

/*
** 提供系统软件创建上层协议解析接口函数
*/
void UpperLayerParse_Init(void);

#endif
