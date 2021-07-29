#include "includes.h"

/*
** parse bms
**	@param:
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_bms(uint16 rxlen,uint8* rx){

}

/*
** packect bms
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_bms(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num){
	uint16 len = 0;
	static uint16 frameLabel = 0;
	BmsInfo bmsInfoTemp = get_BmsInfo(addr);

	/*
	** data item
	**	1.帧标识
	**	2/仓门地址
	**	3.BMS详细信息
	*/
	frameLabel++;
	memcpy((uint8*)&item[len],(uint8*)&frameLabel,sizeof(uint16));
	len += sizeof(uint16);
	item[len] = addr;
	len += sizeof(uint8);
	memcpy((uint8*)&item[len],(uint8*)&bmsInfoTemp.zone[0],sizeof(BmsInfo));
	len += sizeof(BmsInfo);
	
	/*数据项长度*/
	ulFreame->msgHead.dataLen = len;	
}

/*
** bms Logic
*/
void bms_Logic(void){
	SmCmd cmd = {true,0x84,0,0,0};
	static uint32 circTick = 0;
	static uint8 deviceAddr = 0;
	
	if(TickOut((uint32*)&circTick,1000) == true){
		TickOut((uint32*)&circTick,0);
		for(;deviceAddr < SysCtr_AllDoorNum;deviceAddr++){
			if(get_BatIsOnline(deviceAddr) == true){/*电池在线*/
				cmd.doorAddr = deviceAddr;
				cmd.doorNum = 0;
				setCmd(cmd);
				deviceAddr++;
				break;
			}
		}
	}
	
	if(deviceAddr == SysCtr_AllDoorNum){
		deviceAddr = 0;
	}
}
