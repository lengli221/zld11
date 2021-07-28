#ifndef __CAN_1_H
#define __CAN_1_H

/*
** CANģ��֮����������
*/
#define CAN1_BaudRateParam_1M								1
#define CAN1_BaudRateParam_500K								2
#define CAN1_BaudRateParam_250K								3
#define CAN1_BaudRateParam_50K								4
#define CAN1_BaudRateParam_100K								5
#define CAN1_BaudRateParam_125K								6
#define CAN1_BaudRateParam										CAN1_BaudRateParam_125K	

/*
**CAN�жϳ�ʼ��
*/
void CAN1_NVIC_Init(void);
/*
** CAN1 Tx Task
*/
void CAN1_TxDataTask(void);
/*
**CAN1��ʼ������
*/
void CAN1_Cfg_Init(void);
/*
** CAN1 Rx���ݻ�ȡ
*/
bool CAN1_GetMsgInfo(CanRxMsg *msg);
/*
**����CAN ��������
*/
#if Debug_CAN1_TxFun == 1
void DEBUG_CAN1_TxFun(void);
#endif
/*
**CAN1 Transmit���ݺ�������
*/
void CAN1_TransmitData(uint8 len, uint8* tx,uint8 dst,uint8 funId);

#endif

