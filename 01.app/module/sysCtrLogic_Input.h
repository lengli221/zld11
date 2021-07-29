#ifndef __SYSCTRLOGIC_INPUT_H_
#define __SYSCTRLOGIC_INPUT_H_

#include "type.h"

#pragma pack(1)
/*
** ���ϱ�־
*/
typedef union{
	uint16 flag;
	struct{
		uint16 smoke:1;/*�̸й���*/
		uint16 res:15;/*����*/
	}bits;
}SysErr;/*����*/

/*
** ����״̬��Ϣ
*/
typedef union{
	uint16 flag;
	struct{	
		uint16 emer:1;/*��ͣ*/
		uint16 fan:1;/*���ȿ�*/
		uint16 res:14;/*����*/
	}bits;
}SysRunState;/*����״̬*/

typedef struct{
	SysErr sysErr;/*����*/
	SysRunState runState;/*����*/
	uint8 temp;/*�¶�*/
}SCL_Input;
#pragma pack()

/*
** get Sys Ctr Err
**	@return:
**		uint16:������Ϣ
*/
SysErr get_SysCtrErr(void);

/*
** get Sys Run State
**	@return:
**		uint16:����״̬��Ϣ
*/
SysRunState get_SysRunState(void);

/*
** get Sys Ctr Is Err -- һ������
** @param:
**		true:����
**		false:����
*/
bool get_SysCtrIsErr(void);

/*
** get Cabinet Temp
**	@return:
**		uint16:�����¶�
*/
uint16 get_CabinetTemp(void);

/*
** Sys Ctr Logic Input
*/
void SysCtrLogic_Input(void);

#endif

