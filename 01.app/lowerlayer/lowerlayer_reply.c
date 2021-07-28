#include "includes.h"

static int32 lowerLayerReply_TaskStk[512] = {0};

/*
** �²�Э��֮�ظ��������ӿ�
*/
void SM_LowerLayerReply_Task(void* p_arg){
	
	Sleep(2000);/*�ȴ��ֿ������ȶ����н���*/
	
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
		** ι��
		*/
		watchdogUpdate();
		
		/*
		** ������ʱ����
		*/
		Sleep(5);
	}
}

/*
** �ṩϵͳ��������²�Э���ѯ�ӿں���
*/
void LowerLayerReply_Init(void){
	Thread_create(SM_LowerLayerReply_Task, 0, 
		(int32 *)&lowerLayerReply_TaskStk[512-1], LowerLayerReplyTask_Prio);
}
