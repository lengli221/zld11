#include "includes.h"

static int32 lowerLayerParse_TaskStk[512] = {0};

/*
** �²�Э��֮�����������ӿ�
*/
void SM_LowerLayerParse_Task(void* p_arg){
	
	Sleep(2000);/*�ȴ��ֿ������ȶ����н���*/
	
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
** �ṩϵͳ��������²�Э������ӿں���
*/
void LowerLayerParse_Init(void){
	Thread_create(SM_LowerLayerParse_Task, 0,
		(int32 *)&lowerLayerParse_TaskStk[512-1], (int8)LowerLayerParseTask_Prio);
}
