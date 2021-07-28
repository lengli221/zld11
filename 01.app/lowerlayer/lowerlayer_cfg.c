#include "includes.h"

LLParse_Cfg llParse_Cfg[SysCtr_AllDoorNum] = {0};

/*----------------------------------------------Reply------------------------------------------------------------------------*/
/*
** Fill Cfg
*/
static void Fill_Cfg(uint8* len,uint8* item){
	uint8 txlen = 0;
	uint8 protocol = Protocol_Record;
	uint16 temp = 0;
	
	/*
	** data Item
	**		1.Charger Over Temp
	**		2.Bat Over Temp
	**		3.Soc 
	**		4.Chg Time 
	*/
	if(protocol >= 101){
		item[txlen] = get_ChargerOverTempLimit();
		txlen += sizeof(uint8);
		item[txlen] = get_BatOverTempLimit();
		txlen += sizeof(uint8);
		item[txlen] = get_SocLimit();
		txlen += sizeof(uint8);
		temp = get_ChgTimeLimit();
		memcpy((uint8*)&item[txlen],(uint8*)&temp,sizeof(uint16));
		txlen += sizeof(uint16);
	}
	
	/*data Item Len*/
	*len = txlen;
}

/*
** LowerLayer Cfg
*/
void LowerLayer_Cfg(void){
	static uint32 itick = 0;
	uint8 len = 0;
	uint8 tx[8] = {0};

	if(TickOut((uint32 *)&itick, 195) == true){/*任务调度5ms + 195 ms = 200ms*/
		TickOut((uint32 *)&itick, 0);
		/*Fill Cfg*/
		Fill_Cfg((uint8*)&len,(uint8*)&tx[0]);
		/*CAN Transmit*/
		CAN_TransmitAnalysis(CAN_Port_1, len, (uint8 *)&tx[0], DstAddr_BoardCast_Define, LL_FunId_Cfg_02);		
	}
}
/*---------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Parse-----------------------------------------------------------------------*/
/*
** Lowerlayer Parse Cfg
*/
void Lowerlayer_ParseCfg(uint8 rxlen,uint8* item,uint8 addr){
	uint8 len = 0;
	
	if(get_ProtocolRecord(addr) >= 101){
		/*分析配置原因*/
		llParse_Cfg[addr].flag = item[len];
		len += sizeof(uint8);
	}
}
/*---------------------------------------------------------------------------------------------------------------------------*/
