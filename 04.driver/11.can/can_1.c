#include "includes.h"
/*
**CAN1 Rx�洢����֮��������
*/
static CAN_Rx_MsgInfo can1RxMsgInfo;

/*
** CAN1 Tx���ʹ洢����
*/
static CAN_TX_MsgInfo can1TxMsgInfo;

/*
**CAN1 ������ʼ������
*/
static void CAN1_ParamInit(void){
	memset((uint8*)&can1RxMsgInfo.msg[0].StdId,0x00,sizeof(CAN_Rx_MsgInfo));
} 

/*
**CAN1 ʱ�� ���� ����
*/
void CAN1_Configure(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	/*
	**��������ʱ�� ���Ź���ģʽ����ʼ������
	*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	/*
	** �������Ÿ��� ��ȷ207��105 ����ʱ�Ӻ����Ÿ��õ����� ����������������
	*/
	GPIO_PinAFConfig((GPIO_TypeDef *)GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
	GPIO_PinAFConfig((GPIO_TypeDef *)GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//CAN_Rx | CAN_Tx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init((GPIO_TypeDef *)GPIOD, (GPIO_InitTypeDef *)&GPIO_InitStructure);

	/*
	**CAN1�Ĵ���Ĭ�ϳ�ʼ��
	*/
	CAN_DeInit((CAN_TypeDef *)CAN1);

	/*
	**CAN1����ʱ��ʹ��
	*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
}

/*
**CAN1�˲�������
*/
void CAN1_Cfg_Filter(void){
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	FilterDesign filterDesginTmp = Sys_GetFilterDesign1();
	/*
	**CAN����������Ĵ���CAN_FxRi ����:���ڹ��������ԭ��? ʹ�ö���������ҵ���߼�
	*/
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	/*
	**��ʶ������ 
	**1)--1.����Ϊģʽ 2.��ʶ���б�ģʽ
	**2)--���������λ���ģʽ����
	*/
  	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  	CAN_FilterInitStructure.CAN_FilterIdHigh = (uint16)(filterDesginTmp.id.id>>16);
  	CAN_FilterInitStructure.CAN_FilterIdLow = (uint16)(filterDesginTmp.id.id&0x0000FFFF);
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (uint16)(filterDesginTmp.idMask.id>>16);
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow = (uint16)(filterDesginTmp.idMask.id&0x0000FFFF);	
	/*
	**CAN������FIFO�����Ĵ���CAN_FFA1R
	*/
  	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	/*
	**CAN���˼���Ĵ��� CAN_FA1R
	*/
  	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit((CAN_FilterInitTypeDef *)&CAN_FilterInitStructure);
}

/*
**CAN1 �������� ���������� �ж�����
*/
void CAN1_BaudRate(void){
	CAN_InitTypeDef CAN_InitStructure;
	uint8 ret = 0;

	CAN_StructInit((CAN_InitTypeDef *)&CAN_InitStructure);
	/*
	**CAN1��ʼ��
	**1.CAN1ʱ�䴥��ͨ��ģʽ
	**2.�Զ����߹���--���߻ָ�+CAN�����ȶ��Է���
	**3.˯��ģʽ--�Զ����Ѵ�����
	**4.��ֹ�����Զ��ش�ģʽ--DISABLE:�ش�--1.(����)�����Ƿ���ڹ�ϵ 2.��������Ƿ񴥷�
	**5.����FIFO����ģʽ(Receive FIFO locked mode)--DISABLE:���Ǳ������±���
	**6.����FIFO���ȼ� (Transmit FIFO priority)--DISABLE:���ȼ���ʶ������
	**7.CAN����ģʽ
	*/
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = ENABLE/*DISABLE*/;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

	/*
	**CAN1������ = 1MBps
	** The maximum allowed frequency of the low-speed APB1 domain is 30 MHz
	*/
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	#if CAN1_BaudRateParam == CAN1_BaudRateParam_1M
		CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
		CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
		CAN_InitStructure.CAN_Prescaler = 2;
	#elif CAN1_BaudRateParam == CAN1_BaudRateParam_500K
		CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
		CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
		CAN_InitStructure.CAN_Prescaler = 5;
	#elif CAN1_BaudRateParam == CAN1_BaudRateParam_250K
		CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
		CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
		CAN_InitStructure.CAN_Prescaler = 10;	
	#elif CAN1_BaudRateParam == CAN1_BaudRateParam_50K		
		CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
		CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
		CAN_InitStructure.CAN_Prescaler = 50;	
	#elif CAN1_BaudRateParam == CAN1_BaudRateParam_100K		
		CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
		CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
		CAN_InitStructure.CAN_Prescaler = 25;	
	#elif CAN1_BaudRateParam == CAN1_BaudRateParam_125K		
		CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
		CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
		CAN_InitStructure.CAN_Prescaler = 20;			
	#endif
	
	ret = CAN_Init((CAN_TypeDef *)CAN1, (CAN_InitTypeDef *)&CAN_InitStructure);

	switch(ret){
		case CAN_InitStatus_Failed:
			
			break;
		case CAN_InitStatus_Success:
			
			break;
	}

	/*
	**CAN�ж�����
	**FIFO 0��Ϣ�Һ��ж�ʹ�� (FIFO message pending interrupt enable)
	** Note:
			1.Once a message has been stored in the FIFO, the FMP[1:0] bits are updated and an
				interrupt request is generated if the FMPIE bit in the CAN_IER register is set.
	*/
	CAN_ITConfig((CAN_TypeDef *)CAN1, CAN_IT_FMP0, ENABLE);
}

/*
**CAN�жϳ�ʼ��
*/
void CAN1_NVIC_Init(void){
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init((NVIC_InitTypeDef *)&NVIC_InitStructure);
}

/*
**CAN1�����жϺ���
*/
void CAN1_RX0_IRQHandler(void){
	CanRxMsg RxMessage = {0};
	uint16 i = can1RxMsgInfo.rx_wptr;

	/*
	**��λֵ���ڲ�ȷ����
	*/
	memset((uint8*)&RxMessage.StdId,0x00,sizeof(CanRxMsg));

	if(CAN_GetITStatus((CAN_TypeDef *)CAN1, CAN_IT_FMP0) != RESET){
		CAN_Receive((CAN_TypeDef *)CAN1, CAN_FIFO0, (CanRxMsg *)&RxMessage);	
		can1RxMsgInfo.msg[i] = RxMessage;
		can1RxMsgInfo.rx_wptr++;
		if(can1RxMsgInfo.rx_wptr==CAN_Rx_MaxNum){
			can1RxMsgInfo.rx_wptr = 0;
		}
		
		/*
		**�������жϱ�־������Ϊ������Ӧ��־:CAN_IT_FMP0
		**���۷���:
		*/
		CAN_ClearITPendingBit((CAN_TypeDef *)CAN1, CAN_IT_FMP0);
	}
}

/*
** CAN1 Rx���ݻ�ȡ
*/
bool CAN1_GetMsgInfo(CanRxMsg *msg){
	bool ret = false;
	uint16 i=0;

	if(can1RxMsgInfo.rx_rptr == can1RxMsgInfo.rx_wptr){
		ret = false;
	}else{
		i = can1RxMsgInfo.rx_rptr;
		*msg = can1RxMsgInfo.msg[i];
		/*
		**��洢������CAN��Ӧ�洢��CAN��������
		*/
		memset((uint8*)&can1RxMsgInfo.msg[i].StdId,0x00,sizeof(CanRxMsg));
		can1RxMsgInfo.rx_rptr++;
		if(can1RxMsgInfo.rx_rptr == CAN_Rx_MaxNum){
			can1RxMsgInfo.rx_rptr = 0;
		}
		ret = true;
	}

	return ret;
}

/*
**����CAN ��������
*/
#if Debug_CAN1_TxFun == 1
void DEBUG_CAN1_TxFun(void){
	CanTxMsg TxMessage = {0};
	uint8 ret = CAN_TxStatus_NoMailBox;
	IdAddr idAddrTmp = Sys_GetIdAddr();

	/*
	**��λֵ���ڲ�ȷ����
	*/
	memset((uint8*)&TxMessage.StdId,0x00,sizeof(CanTxMsg));

	/*
	**����
	**:1.����ʱ��� Ϊ�ιٷ�δ�ṩʱ�������λϵͳ����
	*/
	TxMessage.StdId = 0;/*Standard identifier*/
	TxMessage.ExtId |= (uint32)((idAddrTmp.dst<<8) | idAddrTmp.src);/*Extended identifier*/
	/*
	**Identifier extension
	**Note:This bit defines the identifier type of message in the mailbox.
	*/
	TxMessage.IDE = CAN_Id_Extended;
	TxMessage.RTR = CAN_RTR_Data;/*Data Frame*/
	/*
	**Data length code
	**Note:This field defines the number of data bytes a data frame contains or a remote frame request
	*/
	TxMessage.DLC = 4;
	/*
	**Data Item
	*/
	TxMessage.Data[0] = 0x92;
	TxMessage.Data[1] = 0x93;
	TxMessage.Data[2] = 0x02;
	TxMessage.Data[3] = 0x21;
	
	ret = CAN_Transmit((CAN_TypeDef *)CAN1, (CanTxMsg *)&TxMessage);

	switch(ret){
		case CAN_TxStatus_NoMailBox:
			
			break;
		default:
			
			break;
	}
}
#endif

/*
**CAN1 Transmit���ݺ�������
*/
void CAN1_TransmitData(uint8 len, uint8* tx,uint8 dst,uint8 funId){
	CanTxMsg TxMessage = {0};
	uint8 ret = CAN_TxStatus_NoMailBox;
	IdAddr idAddrTmp = Sys_GetIdAddr();

	/*
	**��λֵ���ڲ�ȷ����
	*/
	memset((uint8*)&TxMessage.StdId,0x00,sizeof(CanTxMsg));

	/*
	**����
	**:1.����ʱ��� Ϊ�ιٷ�δ�ṩʱ�������λϵͳ����
	*/
	TxMessage.StdId = 0;/*Standard identifier*/
	TxMessage.ExtId |= (uint32)((funId<<16) | (dst<<8) | idAddrTmp.src);/*Extended identifier*/
	/*
	**Identifier extension
	**Note:This bit defines the identifier type of message in the mailbox.
	*/
	TxMessage.IDE = CAN_Id_Extended;
	TxMessage.RTR = CAN_RTR_Data;/*Data Frame*/
	/*
	**Data length code
	**Note:This field defines the number of data bytes a data frame contains or a remote frame request
	*/
	TxMessage.DLC = len;
	/*
	**Data Item
	*/
	memcpy((uint8*)&TxMessage.Data[0],(uint8*)&tx[0],len);

	/*
	** Note:
		1.���ҿ��������ٽ������������䷢�͵�����:
			Transmission handling:Once the mailbox has left empty state, the software no longer has write access to the mailbox registers
	*/
	/*ret = CAN_Transmit((CAN_TypeDef *)CAN1, (CanTxMsg *)&TxMessage);*/

	/*
	** �Ż��߼� ��ָֹ����� ģ���ж��������
	*/
	if(dst < 24 || dst == DstAddr_BoardCast_Define){
		can1TxMsgInfo.msg[can1TxMsgInfo.wCnt++] = TxMessage;
		if(can1TxMsgInfo.wCnt== CAN_Tx_MaxNum){
			can1TxMsgInfo.wCnt= 0;
		}
	}
	
	switch(ret){
		case CAN_TxStatus_NoMailBox:
			
			break;
		default:
			
			break;
	}
}


/*
** CAN1 Tx Task
*/
void CAN1_TxDataTask(void){
	CanTxMsg TxMessage = {0};
	uint16 i = 0;
	uint8 ret = CAN_TxStatus_NoMailBox; 
	uint8 circ = 0;
	static uint32 itick = 0;
	static uint8 itickCnt = 0;

	TickOut((uint32 *)&itick, 0x00);

	for(circ = 0;circ < 3;/*circ++*/){
		if(can1TxMsgInfo.rCnt != can1TxMsgInfo.wCnt){
			i = can1TxMsgInfo.rCnt;		
			TxMessage = can1TxMsgInfo.msg[i];
			ret = CAN_Transmit((CAN_TypeDef *)CAN1, (CanTxMsg *)&TxMessage);/*��ַ0-23����CAN1 �㲥��ַ ����*/
			if(ret != CAN_TxStatus_NoMailBox){
				can1TxMsgInfo.rCnt++;
				if(can1TxMsgInfo.rCnt == CAN_Tx_MaxNum){
					can1TxMsgInfo.rCnt = 0;
				}
				circ++;
				itickCnt = 0;/*ƥ�������Ч*/
			}else{
				if(itickCnt>=5){/*ƥ�����ʧЧ*/
					itickCnt = 5;
					break;
				}
				Sleep(2);
				if(TickOut((uint32 *)&itick, 1000) == true){
					itickCnt++;
					break;
				}
			}
			/*
			** ���¿��Ź��Ĵ���--ι��
			*/
			watchdogUpdate();
		}else{
			break;
		}
	}
}

/*
**CAN1��ʼ������
*/
void CAN1_Cfg_Init(void){
	/*
	**CAN1 ������ʼ������
	*/
	CAN1_ParamInit();
	/*
	**CAN1 ʱ�� ���� ����
	*/
	CAN1_Configure();
	/*
	**CAN1�˲�������
	*/
	CAN1_Cfg_Filter();
	/*
	**CAN1 �������� ���������� �ж�����
	*/
	CAN1_BaudRate();	
}

