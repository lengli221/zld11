#include "includes.h"

BmsInfo bmsInfo[SysCtr_AllDoorNum] = {0};

/*
** get Bms Vol
**	@param:
**		uint8:���ŵ�ַ
**	@return:
**		uint16:vol--kenya:0.01V
*/
uint16 get_BmsVol(uint8 doorId){
	return bmsInfo[doorId].Field.item.batVol;
}

/*
** get Bms Cur
** 	@param:
**		uint8:���ŵ�ַ
**	@return:
**		int16:cur--kenya:0.01A
*/
int16 get_BmsCur(uint8 doorId){
	return bmsInfo[doorId].Field.item.chgCur;
}

/*
** get Bms Soc
** 	@param:
**		uint8:���ŵ�ַ
**	@return:
**		uint8:soc
*/
uint8 get_BmsSoc(uint8 doorId){
	return bmsInfo[doorId].Field.item.soc;
}

/*----------------------------------------------Reply------------------------------------------------------------------------*/
/*
** fill Bms
**	@param:
**		uint8:�����ֶ�
**			0x01:��ѯBMS��Ϣ��ʼ
**			0x02:Bms��Ϣ�ֶ�
**			0x03:Bms��Ϣ�������
**		uint8*:�������
**		uint8*:������
*/
void fill_Bms(uint8 field,uint8* len,uint8* item){
	uint8 txlen = 0;	

	/*
	** data Item
	** 	1.Bms Info
	*/
	item[txlen] = field;
	txlen += sizeof(uint8);

	/*data Item Len*/
	*len = txlen;
}

/*
** Lowerlayer Bms
*/
void Lowerlayer_Bms(void){
	static uint8 addr = 0;
	static uint32 itick = 0;
	uint8 len = 0;
	uint8 tx[8] = {0};


	/*�������*/
	if(TickOut((uint32 *)&itick, 100) == true){
		TickOut((uint32 *)&itick, 0);
		for(;addr < SysCtr_AllDoorNum;addr++){
			if(get_BatIsOnline(addr) == true){
				/*fill Bms*/
				fill_Bms(0x01, (uint8 *)&len, (uint8 *)&tx[0]);
				/*CAN Transmit*/
				CAN_TransmitAnalysis(CAN_Port_1, len, (uint8 *)&tx[0], addr, LL_FunId_BmsInfo_80);	
				addr++;
				break;
			}
		}
	}

	if(addr == SysCtr_AllDoorNum){
		addr = 0;
	}
}
/*---------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Parse-----------------------------------------------------------------------*/
/*
** Lowerlayer Parse Bms
*/
void Lowerlayer_ParseBms(uint8 rxlen,uint8* item,uint8 addr){
	uint8 len = 0;	
	uint8 frameLabel = 0;
	uint8 frameLen = 0;
	uint8 txlen = 0;
	uint8 tx[8] = {0};
	static uint32 frameFlag[SysCtr_AllDoorNum] = {0};

	/*frame Label*/
	frameLabel = item[len];
	len += sizeof(uint8);

	/*frame Len*/
	frameLen = item[len];
	len += sizeof(uint8);

	/*data Item*/
	switch(frameLabel){
		case 1:/*���ֽ���*/
			/*fill Bms*/
			fill_Bms(0x02, (uint8 *)&txlen, (uint8 *)&tx[0]);
			/*CAN Transmit*/
			CAN_TransmitAnalysis(CAN_Port_1, txlen, (uint8 *)&tx[0], addr, LL_FunId_BmsInfo_80);			
			break;
		default:/*������*/
			memcpy((uint8*)&bmsInfo[addr].zone[6*(frameLabel-2)],(uint8*)&item[len],frameLen);
			frameFlag[addr] |= (1<<(frameLabel-2));
			if(frameFlag[addr] == 0x0001FFFF){/*֡�����Խ���*/
				frameFlag[addr] = 0;
				/*fill Bms*/
				fill_Bms(0x03, (uint8 *)&txlen, (uint8 *)&tx[0]);
				/*CAN Transmit*/
				CAN_TransmitAnalysis(CAN_Port_1, txlen, (uint8 *)&tx[0], addr, LL_FunId_BmsInfo_80);					
			}
			break;
	}
}
/*---------------------------------------------------------------------------------------------------------------------------*/

