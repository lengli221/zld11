#include "includes.h"

LLParse_StateInfo llParse_StateInfo[SysCtr_AllDoorNum] = {0};

/*
** get Protocol Record
*/
uint8 get_ProtocolRecord(uint8 addr){
		return llParse_StateInfo[addr].protocol; 
}

/*
** get Bat Is Online
** 	@param:
**		uint8:仓门地址
**	@return
**		flag:
**			true:电池在线
**			false:电池不在线
*/
bool get_BatIsOnline(uint8 addr){
	return llParse_StateInfo[addr].subState.bits.batOnline == 1?true:false;
}

/*
** get Bat Is Exit Err
**	@param:
**		uint8:仓门地址
**	@return:
**		bool:true-->电池故障false-->电池正常
*/
bool get_BatIsExitErr(uint8 addr){
	return llParse_StateInfo[addr].subState.bits.batErr == 1?true:false;
}

/*
** get Charger Is Online
** 	@param:
**		uint8:仓门地址
**	@return
**		flag:
**			true:充电器在线
**			false:充电器不在线
*/
bool get_ChargerIsOnline(uint8 addr){
	return llParse_StateInfo[addr].subState.bits.chargerOnline == 1?true:false;
}

/*
** get Door State
**	@param:
**		uint8:仓门地址
**	return:
**		00:仓门关01:仓门开02:仓门故障
*/
uint8 get_DoorState(uint8 addr){
	return llParse_StateInfo[addr].doorstate;
}

/*
** get Door Loc
**	@param:
**		uint8:仓门地址
**	return:
**		00:空仓01:充电中02:满仓03:故障
*/
uint8 get_DoorLoc(uint8 addr){
	return  llParse_StateInfo[addr].doorLoc;
}

/*
** get Sub State Info 
**	@param:
**		uint8:仓门地址
**	@return:
**		LLParse_StateInfo:分控状态信息
*/
LLParse_StateInfo get_SubStateInfo(uint8 addr){
	return llParse_StateInfo[addr];
}

/*----------------------------------------------Reply------------------------------------------------------------------------*/
/*
** Fill State Info
*/
static void Fill_StateInfo(uint8* len,uint8* item){
	uint8 txlen = 0;
	uint8 temp = 0;

	/*
	** data Item
	** 	1.Protocol Record
	**	2.Ctr SoftVer
	**	3.Sys Err -- 存在一级告警
	*/
	item[txlen] = Protocol_Record;
	txlen += sizeof(uint8);
	item[txlen] = Ctr_SoftVer;
	txlen += sizeof(uint8);
	item[txlen] = get_SysCtrIsErr() == true?(temp|0x01):(temp&(~0x01));
	txlen += sizeof(uint8);

	/*data Item Len*/
	*len = txlen;
}

/*
** Lowerlayer State Info
*/
void LowerLayer_StateInfo(void){
	static uint32 itick = 0;
	uint8 len = 0;
	uint8 tx[8] = {0};
	
	if(TickOut((uint32 *)&itick, 95) == true){/*任务调度5ms + 95 ms = 100ms*/
		TickOut((uint32 *)&itick, 0);
		/*Fill State Info*/
		Fill_StateInfo((uint8*)&len,(uint8*)&tx[0]);
		/*CAN Transmit*/
		CAN_TransmitAnalysis(CAN_Port_1, len, (uint8 *)&tx[0], DstAddr_BoardCast_Define, LL_FunId_StateInfo_01);
		/*set Sub Online Cnt --broadcast*/
		set_SubOnlineCnt_Broadcast();
	}
}
/*---------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Parse-----------------------------------------------------------------------*/
/*
** Lowerlayer Parse State Info
*/
void Lowerlayer_ParseStateInfo(uint8 rxlen,uint8* item,uint8 addr){
	uint8 len = 0;
	
	/*协议号*/
	llParse_StateInfo[addr].protocol = item[len];
	len += sizeof(uint8);
	if(llParse_StateInfo[addr].protocol >= 102){
		/*软件版本号*/
		llParse_StateInfo[addr].softVer = item[len];
		len += sizeof(uint8);
		/*仓门状态*/
		llParse_StateInfo[addr].doorstate = item[len];
		len += sizeof(uint8);
		/*仓定位*/
		llParse_StateInfo[addr].doorLoc = item[len];
		len += sizeof(uint8);
		/*运行状态*/
		llParse_StateInfo[addr].subState.flag = item[len];
		len += sizeof(uint8);
		/*电池故障标识*/
		llParse_StateInfo[addr].batErrLab = item[len];
		len += sizeof(uint8);
		/*分控故障标识*/
		llParse_StateInfo[addr].subErrLab = item[len];
		len += sizeof(uint8);
		/*充电器故障标识*/
		llParse_StateInfo[addr].chargerErrLab = item[len];
		len += sizeof(uint8);
	}

	/*set Sub Online*/
	set_SubOnline(addr);
}
/*---------------------------------------------------------------------------------------------------------------------------*/
