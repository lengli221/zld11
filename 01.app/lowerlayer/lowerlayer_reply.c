#include "includes.h"

static int32 lowerLayerReply_TaskStk[512] = {0};

/*
** 下层协议之回复任务函数接口
*/
void SM_LowerLayerReply_Task(void* p_arg){
	
	Sleep(2000);/*等待分控运行稳定再行交互*/
	
	for(;;){
		/*
		** Lowerlayer State Info
		*/
		LowerLayer_StateInfo();		

		/*
		** LowerLayer Cfg
		*/
		LowerLayer_Cfg();

		/*
		** Lowerlayer Bms
		*/
		Lowerlayer_Bms();
		
		/*
		** Lowerlayer Charger
		*/
		Lowerlayer_Charger();

		/*
		** runtime Chk Sub Is Online
		*/
	 	runtime_ChkSubIsOnline();

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
		Sleep(5);
	}
}

/*
** 提供系统软件创建下层协议查询接口函数
*/
void LowerLayerReply_Init(void){
	Thread_create(SM_LowerLayerReply_Task, 0, 
		(int32 *)&lowerLayerReply_TaskStk[512-1], LowerLayerReplyTask_Prio);
}
