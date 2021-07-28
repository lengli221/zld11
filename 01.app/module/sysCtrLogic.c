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
		** 喂狗
		*/
		watchdogUpdate();
		/*
		** 任务延时调度
		*/
		Sleep(10);
	}
}

/*
** 提供系统软件创建系统控制接口函数
*/
void SysCtrlLogic_Init(void){
	Thread_create(SM_SysCtrlLogic_Task, 0, (int32 *)&sysCtrlLogic_TaskStk[256-1], SysCtrlLogic_Prio);
}
