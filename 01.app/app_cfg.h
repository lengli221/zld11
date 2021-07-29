#ifndef OS_APP_CFG_H_
#define OS_APP_CFG_H_

#include "type.h"

/*
** Protocol Record
** Ctr_SoftVer	
*/
#define Protocol_Record														(uint8)102
#define Ctr_SoftVer																(uint8)101

/*
** 仓门数
*/
#define SysCtr_AllDoorNum													(uint8)0x08

/*
**任务优先级别处理
*/
#define MainTask_Prio															(int8)10

#define LowerLayerParseTask_Prio									(int8)4
#define LowerLayerReplyTask_Prio									(int8)5
#define UpperLayerParseTask_Prio									(int8)6
#define UpperLayerReplyTask_Prio									(int8)7
#define SysCtrlLogic_Prio													(int8)8

#endif

