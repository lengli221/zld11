#ifndef __SYSCTRLOGIC_INPUT_H_
#define __SYSCTRLOGIC_INPUT_H_

#include "type.h"

#pragma pack(1)
/*
** 故障标志
*/
typedef union{
	uint16 flag;
	struct{
		uint16 smoke:1;/*烟感故障*/
		uint16 res:15;/*保留*/
	}bits;
}SysErr;/*故障*/

/*
** 运行状态信息
*/
typedef union{
	uint16 flag;
	struct{	
		uint16 emer:1;/*急停*/
		uint16 fan:1;/*风扇开*/
		uint16 res:14;/*保留*/
	}bits;
}SysRunState;/*运行状态*/

typedef struct{
	SysErr sysErr;/*故障*/
	SysRunState runState;/*运行*/
	uint8 temp;/*温度*/
}SCL_Input;
#pragma pack()

/*
** get Sys Ctr Err
**	@return:
**		uint16:故障信息
*/
SysErr get_SysCtrErr(void);

/*
** get Sys Run State
**	@return:
**		uint16:运行状态信息
*/
SysRunState get_SysRunState(void);

/*
** get Sys Ctr Is Err -- 一级故障
** @param:
**		true:故障
**		false:正常
*/
bool get_SysCtrIsErr(void);

/*
** get Cabinet Temp
**	@return:
**		uint16:柜子温度
*/
uint16 get_CabinetTemp(void);

/*
** Sys Ctr Logic Input
*/
void SysCtrLogic_Input(void);

#endif

