#ifndef __LOWERLAYER_REPLY_H_
#define __LOWERLAYER_REPLY_H_

#define LL_FunId_StateInfo_01					(uint8)0x01/*״̬��Ϣ*/
#define LL_FunId_Cfg_02								(uint8)0x02/*������Ϣ*/
#define LL_FunId_OpenDoor_03					(uint8)0x03/*���ֶ���*/
#define LL_FunId_BmsInfo_80						(uint8)0x80/*Bms��Ϣ*/
#define LL_FunId_ChargerInfo_81				(uint8)0x81/*�������Ϣ*/


/*
** �ṩϵͳ��������²�Э���ѯ�ӿں���
*/
void LowerLayerReply_Init(void);

#endif
