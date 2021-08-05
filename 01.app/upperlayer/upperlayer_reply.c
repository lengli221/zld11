#include "includes.h"

static int32 upperLayerReply_TaskStk[512] = {0};

/*上层协议之发送命令*/
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
**上层协议之回复接口函数表格
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
** 上层协议之封装回复帧接口函数
*/
void ul_PackectReplyFun(UpperLayerFrame *ulFreame,uint8* item,uint8*tx){
	uint8 len = 0;

	/*帧头*/
	tx[len] = UpperLayerFrame_Head;
	len += sizeof(uint8);

	/*帧数据长度计算逻辑*/
	ulFreame->msgFrameLen = sizeof(UpperLayerFrame) + ulFreame->msgHead.dataLen;

	/*帧长度*/
	memcpy((uint8*)&tx[len],(uint8*)&ulFreame->msgFrameLen,sizeof(uint16));
	len += sizeof(uint16);

	/*消息头*/
	memcpy((uint8*)&tx[len],(uint8*)&ulFreame->msgHead.id,sizeof(MsgHead));
	len += sizeof(MsgHead);

	/*消息内容项*/
	memcpy((uint8*)&tx[len],(uint8*)&item[0],ulFreame->msgHead.dataLen);
	len += ulFreame->msgHead.dataLen;

	/*校验*/
	tx[len] = calcBcc((uint8 *)&tx[0], len);
	len += sizeof(uint8);

	/*帧尾*/
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
					ulFrameTmp.msgHead.addr = smCmd.deviceAddr;/*设备地址参阅协议总线部分说明*/
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
		** 更新看门狗寄存器--喂狗
		*/
		watchdogUpdate();
			
		Sleep(10);		
	}
}

/*
**提供系统软件创建上层协议回复接口函数
*/
void UpperLayerReply_Init(void){
	Thread_create(SM_UpperLayerReply_Task, 0, 
		(int32 *)&upperLayerReply_TaskStk[512-1], UpperLayerReplyTask_Prio);
}
