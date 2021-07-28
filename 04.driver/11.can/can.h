#ifndef __CAN_H_
#define __CAN_H_

/*
**CAN Rx��������δ��������֡��
*/
#define CAN_Rx_MaxNum						(uint8)150
#define CAN_Tx_MaxNum						(uint8)150

/*
** CAN Port����
*/
#define CAN_Port_1								(uint8)0x01
#define CAN_Port_2								(uint8)0x02

/*
**CAN Rx����ṹ��
*/
typedef struct{
	CanRxMsg msg[CAN_Rx_MaxNum];/*CAN Rx������Ϣ*/
	uint16 rx_wptr;/*д�洢λ�ñ��*/
	uint16 rx_rptr;/*���洢λ�ñ��*/
}CAN_Rx_MsgInfo;


/*
** CAN Tx ����ṹ��
*/
typedef struct{
	CanTxMsg msg[CAN_Tx_MaxNum];/*CAN Tx������Ϣ*/
	uint16 wCnt;
	uint16 rCnt;
}CAN_TX_MsgInfo;

/*
**CAN Rx���ݷ���
*/
bool CAN_RecAnalysis(uint8 canPort,CanRxMsg *msg);
/*
**CAN Transmit ����
*/
void CAN_TransmitAnalysis(uint8 canPort,uint8 len,uint8* tx,uint8 dst,uint8 funId);
/*
**CAN1��ʼ��
*/
void CAN_Cfg_Init(void);

#endif

