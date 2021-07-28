#include "includes.h"

static int32 sysCtrlLogic_TaskStk[256] = {0};

/*
** Sys Ctr Logic Task
*/
void SM_SysCtrlLogic_Task(void* p_arg){
	for(;;){

		/*
		** Sys Ctr Logic Input
		*/
		SysCtrLogic_Input();		
		
		/*
		** Sys Ctr Logic Output
		*/
		SysCtrLogic_Output();
	
		/*
		** CAN1 Tx Task
		*/
		CAN1_TxDataTask();
		
		/*
		** ι��
		*/
		watchdogUpdate();
		/*
		** ������ʱ����
		*/
		Sleep(10);
	}
}

/*
** �ṩϵͳ�������ϵͳ���ƽӿں���
*/
void SysCtrlLogic_Init(void){
	Thread_create(SM_SysCtrlLogic_Task, 0, (int32 *)&sysCtrlLogic_TaskStk[256-1], SysCtrlLogic_Prio);
}
