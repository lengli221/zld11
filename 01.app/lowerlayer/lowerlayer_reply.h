#ifndef __LOWERLAYER_REPLY_H_
#define __LOWERLAYER_REPLY_H_

#define LL_FunId_StateInfo_01					(uint8)0x01/*状态信息*/
#define LL_FunId_Cfg_02								(uint8)0x02/*配置信息*/
#define LL_FunId_OpenDoor_03					(uint8)0x03/*开仓动作*/
#define LL_FunId_BmsInfo_80						(uint8)0x80/*Bms信息*/
#define LL_FunId_ChargerInfo_81				(uint8)0x81/*充电器信息*/


/*
** 提供系统软件创建下层协议查询接口函数
*/
void LowerLayerReply_Init(void);

#endif
