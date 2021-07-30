#include "includes.h"

DoorResult doorResult[SysCtr_AllDoorNum] = {0};

/*
** get Door Result Flag
**	@param:
**		uint8:仓门地址
**	@return:
**		bool:true-->表明分控已完成开仓指令等待上报安卓
*/
bool get_DoorResultFlag(uint8 addr){
	return doorResult[addr].flag;
}

/*
** get Door Result 
**	@param:
**		uint8:仓门地址
**	@return:
**		uint8:结果
*/
uint8 get_DoorResult(uint8 addr){
	return doorResult[addr].result;
}

/*
** set DoorResult
**	@param:
**		uint8:仓门地址
**		uint8:true-->表明分控已完成开仓指令等待上报安卓 false-->空闲
*/
void set_DoorResult(uint8 addr,bool flag,uint8 result){
	doorResult[addr].flag = flag;
	doorResult[addr].result = result;
}

/*-----------------------------------------------Parse-----------------------------------------------------------------------*/
/*
** Lowerlayer Parse door Result
*/
void Lowerlayer_ParseDoorResult(uint8 rxlen,uint8* item,uint8 addr){
	uint8 len =0;
	uint8 txlen = 1;
	uint8 tx[8] = {0x01};
	
	/*
	** data item
	**	1.开仓结果
	*/
	set_DoorResult(addr,true,item[len]);
	len += sizeof(uint8);
	/*CAN Transmit*/
	CAN_TransmitAnalysis(CAN_Port_1, txlen, (uint8 *)&tx[0], DstAddr_BoardCast_Define, LL_FunId_DoorResult_04);	
}
/*---------------------------------------------------------------------------------------------------------------------------*/
