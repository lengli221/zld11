#ifndef __CAN2_H_
#define __CAN2_H_

/*
**CAN�жϳ�ʼ��
*/
void CAN2_NVIC_Init(void);
/*
** CAN2 Rx���ݻ�ȡ
*/
bool CAN2_GetMsgInfo(CanRxMsg *msg);
/*
**CAN2��ʼ������
*/
void CAN2_Cfg_Init(void);

#endif

