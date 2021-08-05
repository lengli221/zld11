#include "includes.h"

static int32 upperLayerReply_TaskStk[512] = {0};

/*�ϲ�Э��֮��������*/
SmCmd smCmd;

/*set cmd*/
void setCmd(SmCmd cmd){
	uint8 cnt=0;
	
	while(smCmd.id != 0 && cnt < 100){
		cnt++;
		Sleep(10);
	}
	memcpy((uint8*)&smCmd.refresh,(uint8*)&cmd.refresh,sizeof(SmCmd));
}

/*
**�ϲ�Э��֮�ظ��ӿں������
*/
static const UpperLayerReplyFunTable upperLayerReplyFunTable[] = {
	{0x81,packect_CtrState},
	{0x82,packect_SubState},
	{0x83,packect_CfgFlag},
	{0x84,packect_bms},
	{0x85,packect_openDoor},
	{0x86,packect_openDoorResult},
	{0x87,packect_charger}
};
static uint8 upperLayerReplyFunTableNum = sizeof(upperLayerReplyFunTable)/sizeof(UpperLayerReplyFunTable);

/*
** �ϲ�Э��֮��װ�ظ�֡�ӿں���
*/
void ul_PackectReplyFun(UpperLayerFrame *ulFreame,uint8* item,uint8*tx){
	uint8 len = 0;

	/*֡ͷ*/
	tx[len] = UpperLayerFrame_Head;
	len += sizeof(uint8);

	/*֡���ݳ��ȼ����߼�*/
	ulFreame->msgFrameLen = sizeof(UpperLayerFrame) + ulFreame->msgHead.dataLen;

	/*֡����*/
	memcpy((uint8*)&tx[len],(uint8*)&ulFreame->msgFrameLen,sizeof(uint16));
	len += sizeof(uint16);

	/*��Ϣͷ*/
	memcpy((uint8*)&tx[len],(uint8*)&ulFreame->msgHead.id,sizeof(MsgHead));
	len += sizeof(MsgHead);

	/*��Ϣ������*/
	memcpy((uint8*)&tx[len],(uint8*)&item[0],ulFreame->msgHead.dataLen);
	len += ulFreame->msgHead.dataLen;

	/*У��*/
	tx[len] = calcBcc((uint8 *)&tx[0], len);
	len += sizeof(uint8);

	/*֡β*/
	tx[len] = UpperLayerFrame_End;
}

void SM_UpperLayerReply_Task(void* p_arg){
	uint8 txItem[256] = {0};
	uint8 txbuf[256] = {0};
	UpperLayerFrame ulFrameTmp = {0};
	uint8 i = 0;

	Sleep(2);
	
	for(;;){
		
		if(smCmd.refresh == true){
			for(i=0;i<upperLayerReplyFunTableNum;i++){
				if(smCmd.id == upperLayerReplyFunTable[i].id){
					ulFrameTmp.msgHead.id = upperLayerReplyFunTable[i].id;
					ulFrameTmp.msgHead.addr = smCmd.deviceAddr;/*�豸��ַ����Э�����߲���˵��*/
					upperLayerReplyFunTable[i].handle((UpperLayerFrame*)&ulFrameTmp,
						(uint8*)&txItem[0],smCmd.doorAddr,smCmd.doorNum);
					ul_PackectReplyFun((UpperLayerFrame *)&ulFrameTmp, 
						(uint8 *)&txItem[0], (uint8 *)&txbuf[0]);
					BSP_SmSend(BSP_ComType_USART, BSP_ComUsart1, 
						(void *)&txbuf[0], (uint16 *)&ulFrameTmp.msgFrameLen);
					memset((uint8*)&smCmd.refresh,0x00,sizeof(SmCmd));
					break;
				}
			}			
		}	

		/*
		** ctr State Logic
		*/
		ctr_StateLogic();
		
//		/*
//		** sub State Logic
//		*/
//		sub_StateLogic();		
//		
//		/*
//		** bms Logic
//		*/
//		bms_Logic();	

//		/*
//		** charger Logic
//		*/
//		charger_Logic();		
//		
//		/*
//		** open Door Proc
//		*/
//		open_DoorProc();	

//		/*
//		** open Door Result Proc 
//		*/
//		open_DoorResultProc();		
		
		/*
		** CAN1 Tx Task
		*/
		CAN1_TxDataTask();
		
		/*
		** ���¿��Ź��Ĵ���--ι��
		*/
		watchdogUpdate();
			
		Sleep(10);		
	}
}

/*
**�ṩϵͳ��������ϲ�Э��ظ��ӿں���
*/
void UpperLayerReply_Init(void){
	Thread_create(SM_UpperLayerReply_Task, 0, 
		(int32 *)&upperLayerReply_TaskStk[512-1], UpperLayerReplyTask_Prio);
}
