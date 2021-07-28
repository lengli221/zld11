#include "includes.h"

ChargerInfo chargerInfo[SysCtr_AllDoorNum] = {0};

/*----------------------------------------------Reply------------------------------------------------------------------------*/
/*
** fill Charger
**	@param:
**		uint8*:数据项长度
**		uint8*:数据项
*/
void fill_Charger(uint8* len,uint8* item){
	uint8 txlen = 0;	
	
	/*data item*/
	item[txlen] = 0x01;
	txlen += sizeof(uint8);
	
	/*data Item Len*/
	*len = txlen;	
}

/*
** Lowerlayer Charger
*/
void Lowerlayer_Charger(void){
	static uint8 addr = 0;
	static uint32 itick = 0;
	uint8 len = 0;
	uint8 tx[8] = {0};

	/*充电器在线*/
	if(TickOut((uint32*)&itick,200) == true){
		TickOut((uint32 *)&itick, 0);
		for(;addr < SysCtr_AllDoorNum;addr++){
			if(get_ChargerIsOnline(addr) == true){
				/*fill Charger*/
				fill_Charger((uint8 *)&len, (uint8 *)&tx[0]);
				/*CAN Transmit*/
				CAN_TransmitAnalysis(CAN_Port_1, len, (uint8 *)&tx[0], addr, LL_FunId_ChargerInfo_81);	
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
** Lowerlayer Parse Charger
**	@param:
**		uint8:数据项长度
**		uint8*:数据项
**		uint8:仓位地址
*/
void Lowerlayer_ParseCharger(uint8 rxlen,uint8* item,uint8 addr){
	uint8 len = 0;	
	uint8 frameLabel = 0;
	uint8 frameLen = 0;

	/*frame Label*/
	frameLabel = item[len];
	len += sizeof(uint8);

	/*frame Len*/
	frameLen = item[len];
	len += sizeof(uint8);
	
	/*数据项*/
	memcpy((uint8*)&chargerInfo[addr].zone[6*(frameLabel-2)],(uint8*)&item[len],frameLen);
}
/*---------------------------------------------------------------------------------------------------------------------------*/

