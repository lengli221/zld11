#ifndef __COMMON_H_
#define __COMMON_H_

#include "type.h"

/*--------------------------------------------У��-------------------------------------------------------*/
/*
** CRC16 У��
**	@param:
**		uint8*:������
**		uint16:���ݳ���
**	@return:
**		uint16:CRC16У��ֵ
*/
uint16 CRC16(uint8 *puchMsg, uint16 usDataLen);

/*
** Discontinuous CRC16
**	Note:
**			��������,�޷�����bufֱ��CRC16У��,���ȡ��ַ�ʽ
**	@param:
**		uint8*:��������ʼ��ַ
**		uint16:�������
**		uint16:CRCУ���ʼֵ
**		uint8*:ָ��CRCУ�����ʼλ��
*/
uint16 CRC16_Discontinuous(uint8 *puchMsg, uint16 usDataLen,uint16 uchInit,uint8* indexInit);
/*
** calc BCC
**	@param:
**		uint8*:������
**		uint16:���ݳ���
**	@return:
**		uint8:���У��ֵ
*/
uint8 calcBcc(uint8 *buf,uint16 len);

/*
** calc Sum
**	@param:
**		uint8*:������
**		uint16:���ݳ���
**	@return:
**		uint8:��У��ֵ
*/
uint8 calcSum(uint8 *buf,uint16 len);
/*-------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------����ʱ�䴦��----------------------------------------------*/
/*
** TickOut
**	@param:
**		uint32*:ʱ�ӽ�����������
**		uint32:��ʱʱ����ֵ
**	@return:
**		bool:true-->��ʱ false-->δ��ʱ
*/
bool TickOut(uint32 *tick,uint32 timeout);
/*
** Sleep
**	@param:
**		uint32:���������ʱֵ
*/
void Sleep(uint32 milliSec);
/*-------------------------------------------------------------------------------------------------------*/

#endif

