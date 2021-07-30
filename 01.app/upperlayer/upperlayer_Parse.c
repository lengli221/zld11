#include "includes.h"

static int32 upperLayerParse_TaskStk[1024] = {0};

/*
**校验数据帧数据长度数据是否合法
*/
bool ChkFrameDataLenIsOk(uint16 frameLen){
	bool ret = false;

	if(frameLen>=FrameLenIsLegal_Min && frameLen<=FrameLenIsLegal_Max){
		ret = true;
		
	}
	return ret;
}

/*
**校验设备地址
*/
bool ChkDeviceAddrIsOk(uint8 addr){
	bool ret = true;

	return ret;
}

/*
** 执行函数表格
*/
static const UpperLayerFunTable upperLayerFunTabel[] = {
	{0x01,parse_CtrState},
	{0x02,parse_SubState},
	{0x03,parse_CfgInfo},
	{0x04,parse_bms},
	{0x05,parse_openDoor},
	{0x06,parse_openDoorResult},
	{0x07,parse_charger}
};
static uint8 upperLayerFunTabelNum = sizeof(upperLayerFunTabel)/sizeof(UpperLayerFunTable);

/*
**上层协议帧执行函数处理分析
*/
void UpperLayerExecuteFun(MsgHead msgHead,uint8*msgItem){
	uint8 i=0;
	for(i=0;i<upperLayerFunTabelNum;i++){
		if(msgHead.id == upperLayerFunTabel[i].id){
			upperLayerFunTabel[i].handle(msgHead.dataLen,(uint8*)msgItem);
			break;
		}
	}
}

/*
**解析数据帧多帧,粘帧,异常帧处理
*/
void ParseUpperLayerFrame(uint8* rxbuf,uint16* rxlen){
	/*临时变量*/
	UpperLayerFrame ulFrameTmp = {0};
	/*
	**异常帧,粘帧处理变量
	*/
	uint8 *ptrbuf = rxbuf;	
	uint16 updataLen = *rxlen;
	uint16 frameLen = 0;
	uint16 msgLen=0;
	uint16 saveDataLen = *rxlen;

	for(;updataLen>=(uint16)(sizeof(ulFrameTmp.head)+sizeof(ulFrameTmp.msgFrameLen));){
		memcpy((uint8*)&frameLen,(uint8*)&ptrbuf[1] ,sizeof(uint16));
		if(ptrbuf[0] == UpperLayerFrame_Head&&ChkFrameDataLenIsOk(frameLen)){
			if(updataLen>=frameLen){
				if(calcBcc((uint8 *)&ptrbuf[0], (uint16)frameLen-2) == ptrbuf[frameLen-2] 
					&& ptrbuf[frameLen-1] == UpperLayerFrame_End){
					memcpy((uint8*)&ulFrameTmp.head,(uint8*)&ptrbuf[0],sizeof(ulFrameTmp.head)+sizeof(ulFrameTmp.msgFrameLen)+sizeof(MsgHead));
					memcpy((uint8*)&msgLen,(uint8*)&ulFrameTmp.msgHead.dataLen,sizeof(uint16));
					ulFrameTmp.chkCode = ptrbuf[frameLen-2];
					if(ChkDeviceAddrIsOk((uint8)ulFrameTmp.msgHead.addr)){
						UpperLayerExecuteFun(ulFrameTmp.msgHead, 
							(uint8 *)(ptrbuf+sizeof(ulFrameTmp.head)+sizeof(ulFrameTmp.msgFrameLen)+sizeof(ulFrameTmp.msgHead)));
						memset((uint8*)&ulFrameTmp.head,0x00,sizeof(ulFrameTmp));
					}
					ptrbuf += frameLen;
					updataLen -= frameLen;
					frameLen = 0;					
				}
				else{
					ptrbuf++;
					updataLen--;
					frameLen = 0;
				}
			}
			else{
				break;
			}
		}
		else{
			ptrbuf++;
			updataLen--;
			frameLen = 0;
		}
	}
	memcpy((uint8*)&rxbuf[0],(uint8*)&ptrbuf[0],updataLen);
	*rxlen = updataLen;
	memset((uint8*)rxbuf+updataLen,0x00,saveDataLen-updataLen);
}

void SM_UpperLayerParse_Task(void* p_arg){
	uint8 ucRxBuf[1024];
	uint8 *rxptr;
	uint16 ucLen = 0;
	uint16 ucRecvLen = 0;
	
	Sleep(4000);/*收集分控信息,再响应安卓信息*/
	
	for(;;){
		
		ucRecvLen = 0;
		BSP_SmRecv(BSP_ComType_USART,BSP_ComUsart1,ucRxBuf + ucLen,&ucRecvLen);
		ucLen += ucRecvLen;
		if(ucLen >( sizeof(ucRxBuf)))
		{
			ucLen = 0;
		}
		
		if(ucRecvLen == 0 && ucLen != 0)
		{
			rxptr = ucRxBuf;
			ucRecvLen = ucLen;
			ParseUpperLayerFrame((uint8 *)rxptr, (uint16 *)&ucRecvLen);
			ucLen = ucRecvLen;
		}			
	
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
** 提供系统软件创建上层协议解析接口函数
*/
void UpperLayerParse_Init(void){
	Thread_create(SM_UpperLayerParse_Task, 0,
		(int32 *)&upperLayerParse_TaskStk[1024-1], (int8)UpperLayerParseTask_Prio);
}
