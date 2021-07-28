#ifndef __SYSCTRLOGIC_INPUT_H_
#define __SYSCTRLOGIC_INPUT_H_

#pragma pack(1)
/*
** 故障标志
*/
typedef union{
	uint8 flag;
	struct{
		uint8 res:8;
	}bits;
}SysErr;/*故障*/

typedef struct{
	SysErr sysErr;
}SCL_Input;
#pragma pack()

/*
** get Sys Ctr Is Err
** @param:
**		true:故障
**		false:正常
*/
bool get_SysCtrIsErr(void);

/*
** Sys Ctr Logic Input
*/
void SysCtrLogic_Input(void);

#endif

