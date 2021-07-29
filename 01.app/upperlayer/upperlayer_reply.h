#ifndef __UPPERLAYER_REPLY_
#define __UPPERLAYER_REPLY_

#include "type.h"
#include "upperlayer_Parse.h"

#pragma pack(1)
/*
** 操作进程系统结构体相关进程--上报上层协议定义结构体
*/
typedef struct{
	bool refresh;/*更新标志*/
	uint8 id;/*消息ID*/
	uint8 deviceAddr;/*设备地址*/
	uint8 doorAddr;/*仓门地址*/
	uint8 doorNum;/*仓门数据量*/
}SmCmd;

/*
** 功能函数之回复上层协议
*/
typedef struct{
	uint8 id;/*消息ID*/
	void (*handle)(UpperLayerFrame*,uint8*,uint8,uint8);/*消息格式,数据项域,仓门地址,仓门数*/
}UpperLayerReplyFunTable;
#pragma pack()

/*set cmd*/
void setCmd(SmCmd cmd);

/*
**提供系统软件创建上层协议回复接口函数
*/
void UpperLayerReply_Init(void);

#endif
