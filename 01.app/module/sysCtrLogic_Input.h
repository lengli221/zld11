#ifndef __SYSCTRLOGIC_INPUT_H_
#define __SYSCTRLOGIC_INPUT_H_

#pragma pack(1)
/*
** ���ϱ�־
*/
typedef union{
	uint8 flag;
	struct{
		uint8 res:8;
	}bits;
}SysErr;/*����*/

typedef struct{
	SysErr sysErr;
}SCL_Input;
#pragma pack()

/*
** get Sys Ctr Is Err
** @param:
**		true:����
**		false:����
*/
bool get_SysCtrIsErr(void);

/*
** Sys Ctr Logic Input
*/
void SysCtrLogic_Input(void);

#endif

