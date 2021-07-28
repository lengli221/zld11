/*
**CAN���˵�� ***************************************************************************************
**Note:
*****1.ʱ��:CAN2����ʹ��Ҳ���뿪��CAN1ʱ��--����:1.�����ģ��ʱ�ӻ��ǰ�������ʹ��ʱ��:����
******����:����CAN_FilterInit�͹ٷ��ο��ֲ�RM0008��CAN filter register�Ĵ���������CAN��׼��ַ
**���ò���
*****2.����������
**����:CAN��ؼĴ���������˳��,�Ƿ�Ӱ���߼���ϵ
*****1.Control/Status/Configuration
*****2.Acceptance Filters
*****3.Master/Slave Receive FIFO/1
*****4.Master/Slave Tx Mailboxes
*****************************************************************************************************
*****Զ������:CAN��������˲�����ѡȡ
*****************************************************************************************************
*/
#include "includes.h"


/*
**CAN Rx���ݷ���
*/
bool CAN_RecAnalysis(uint8 canPort,CanRxMsg *msg){
	bool ret=false;

	switch(canPort){
		case CAN_Port_1:
			ret = CAN1_GetMsgInfo((CanRxMsg *)msg);
			break;
		case CAN_Port_2:
			ret = CAN2_GetMsgInfo((CanRxMsg *)msg);
			break;
		default:
			
			break;
	}
	return ret;
}

/*
**CAN Transmit ����
*/
void CAN_TransmitAnalysis(uint8 canPort,uint8 len,uint8* tx,uint8 dst,uint8 funId){
	switch(canPort){
		case CAN_Port_1:
			CAN1_TransmitData(len, (uint8 *)&tx[0],dst,funId);
			break;
		case CAN_Port_2:

			break;
	}
}


/*
**CAN��ʼ��
*/
void CAN_Cfg_Init(void){
	/*
	** CAN1��ʼ������
	*/
	CAN1_Cfg_Init();
	/*
	** CAN2��ʼ������
	*/
	CAN2_Cfg_Init();	
}

