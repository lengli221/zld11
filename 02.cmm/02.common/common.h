#ifndef __COMMON_H_
#define __COMMON_H_

#include "type.h"

/*--------------------------------------------校验-------------------------------------------------------*/
/*
** CRC16 校验
**	@param:
**		uint8*:数据项
**		uint16:数据长度
**	@return:
**		uint16:CRC16校验值
*/
uint16 CRC16(uint8 *puchMsg, uint16 usDataLen);

/*
** Discontinuous CRC16
**	Note:
**			数据量大,无法开辟buf直接CRC16校验,则采取拆分方式
**	@param:
**		uint8*:数据项起始地址
**		uint16:数据项长度
**		uint16:CRC校验初始值
**		uint8*:指向CRC校验表格初始位置
*/
uint16 CRC16_Discontinuous(uint8 *puchMsg, uint16 usDataLen,uint16 uchInit,uint8* indexInit);
/*
** calc BCC
**	@param:
**		uint8*:数据项
**		uint16:数据长度
**	@return:
**		uint8:异或校验值
*/
uint8 calcBcc(uint8 *buf,uint16 len);

/*
** calc Sum
**	@param:
**		uint8*:数据项
**		uint16:数据长度
**	@return:
**		uint8:和校验值
*/
uint8 calcSum(uint8 *buf,uint16 len);
/*-------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------任务时间处理----------------------------------------------*/
/*
** TickOut
**	@param:
**		uint32*:时钟节拍数计数器
**		uint32:超时时间阈值
**	@return:
**		bool:true-->超时 false-->未超时
*/
bool TickOut(uint32 *tick,uint32 timeout);
/*
** Sleep
**	@param:
**		uint32:任务调度延时值
*/
void Sleep(uint32 milliSec);
/*-------------------------------------------------------------------------------------------------------*/

#endif

