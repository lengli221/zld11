#include "includes.h"
/*
**CAN2 Rx�洢����֮��������
*/
static CAN_Rx_MsgInfo can2RxMsgInfo;

/*
**CAN1 ������ʼ������
*/
static void CAN2_ParamInit(void){
	memset((uint8*)&can2RxMsgInfo.msg[0].StdId,0x00,sizeof(CAN_Rx_MsgInfo));
} 

/*
**CAN2 ʱ�� ���� ����
*/
void CAN2_Configure(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	/*
	**��������ʱ�� ���Ź���ģʽ����ʼ������
	*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	/*
	** �������Ÿ��� ��ȷ207��105 ����ʱ�Ӻ����Ÿ��õ����� ����������������
	*/
	GPIO_PinAFConfig((GPIO_TypeDef *)GPIOB, GPIO_PinSource5, GPIO_AF_CAN2);
	GPIO_PinAFConfig((GPIO_TypeDef *)GPIOB, GPIO_PinSource6, GPIO_AF_CAN2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;//CAN_Rx | CAN_Tx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init((GPIO_TypeDef *)GPIOB, (GPIO_InitTypeDef *)&GPIO_InitStructure);

	/*
	**CAN1�Ĵ���Ĭ�ϳ�ʼ��
	*/
	CAN_DeInit((CAN_TypeDef *)CAN2);

	/*
	**CAN1����ʱ��ʹ��
	*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
}

/*
**CAN2�˲�������
*/
void CAN2_Cfg_Filter(void){
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	FilterDesign filterDesginTmp = Sys_GetFilterDesign1();
	/*
	**CAN����������Ĵ���CAN_FxRi ����:���ڹ��������ԭ��? ʹ�ö���������ҵ���߼�
	*/
	CAN_FilterInitStructure.CAN_FilterNumber = 14;
	/*
	**��ʶ������ 
	**1)--1.����Ϊģʽ 2.��ʶ���б�ģʽ
	**2)--���������λ���ģʽ����
	*/
  	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  	CAN_FilterInitStructure.CAN_FilterIdHigh =(uint16)(filterDesginTmp.id.id>>16);
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
**CAN2 �������� ���������� �ж�����
*/
void CAN2_BaudRate(void){
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
	
	ret = CAN_Init((CAN_TypeDef *)CAN2, (CAN_InitTypeDef *)&CAN_InitStructure);

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
	CAN_ITConfig((CAN_TypeDef *)CAN2, CAN_IT_FMP0, ENABLE);
}

/*
** CAN�жϳ�ʼ��
*/
void CAN2_NVIC_Init(void){
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init((NVIC_InitTypeDef *)&NVIC_InitStructure);
}

/*
**CAN1�����жϺ���
*/
void CAN2_RX0_IRQHandler(void){
	CanRxMsg RxMessage = {0};
	uint16 i = can2RxMsgInfo.rx_wptr;

	/*
	**��λֵ���ڲ�ȷ����
	*/
	memset((uint8*)&RxMessage.StdId,0x00,sizeof(CanRxMsg));

	if(CAN_GetITStatus((CAN_TypeDef *)CAN2, CAN_IT_FMP0) != RESET){
		CAN_Receive((CAN_TypeDef *)CAN2, CAN_FIFO0, (CanRxMsg *)&RxMessage);	
		can2RxMsgInfo.msg[i] = RxMessage;
		can2RxMsgInfo.rx_wptr++;
		if(can2RxMsgInfo.rx_wptr==CAN_Rx_MaxNum){
			can2RxMsgInfo.rx_wptr = 0;
		}
		
		/*
		**�������жϱ�־������Ϊ������Ӧ��־:CAN_IT_FMP0
		**���۷���:
		*/
		CAN_ClearITPendingBit((CAN_TypeDef *)CAN2, CAN_IT_FMP0);
	}
}

/*
** CAN2 Rx���ݻ�ȡ
*/
bool CAN2_GetMsgInfo(CanRxMsg *msg){
	bool ret = false;
	uint16 i=0;

	if(can2RxMsgInfo.rx_rptr == can2RxMsgInfo.rx_wptr){
		ret = false;
	}else{
		i = can2RxMsgInfo.rx_rptr;
		*msg = can2RxMsgInfo.msg[i];
		/*
		**��洢������CAN��Ӧ�洢��CAN��������
		*/
		memset((uint8*)&can2RxMsgInfo.msg[i].StdId,0x00,sizeof(CanRxMsg));
		can2RxMsgInfo.rx_rptr++;
		if(can2RxMsgInfo.rx_rptr == CAN_Rx_MaxNum){
			can2RxMsgInfo.rx_rptr = 0;
		}
		ret = true;
	}

	return ret;
}

/*
**CAN2��ʼ������
*/
void CAN2_Cfg_Init(void){
	/*
	**CAN1 ������ʼ������
	*/
	CAN2_ParamInit();
	/*
	**CAN2 ʱ�� ���� ����
	*/
	CAN2_Configure();
	/*
	**CAN2�˲�������
	*/
	CAN2_Cfg_Filter();
	/*
	**CAN2 �������� ���������� �ж�����
	*/
	CAN2_BaudRate();	
}

