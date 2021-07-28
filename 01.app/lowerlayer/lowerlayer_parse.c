#include "includes.h"

static int32 lowerLayerParse_TaskStk[512] = {0};

/*
** 下层协议之解析任务函数接口
*/
void SM_LowerLayerParse_Task(void* p_arg){
	
	Sleep(2000);/*等待分控运行稳定再行交互*/
	
	for(;;){
		/*
		** Lowerlayer Fun Analyze
		*/
		Lowerlayer_FunAnalyze();
		
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
** 提供系统软件创建下层协议解析接口函数
*/
void LowerLayerParse_Init(void){
	Thread_create(SM_LowerLayerParse_Task, 0,
		(int32 *)&lowerLayerParse_TaskStk[512-1], (int8)LowerLayerParseTask_Prio);
}
