#include "includes.h"

/*
** parse Ctr State
**	@param:
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_CtrState(uint16 rxlen,uint8* rx){

}

/*
** packect Ctr State
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_CtrState(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num){
	uint16 len = 0;
	uint16 temp = 0;
	
	/*
	** data item
	**	1.主控协议号
	**	2.主控软件版本号
	**	3.故障信息
	**	4.状态信息
	**	5.柜体温度信息
	*/
	item[len] = Protocol_Record;
	len += sizeof(uint8);
	item[len] = Ctr_SoftVer;
	len += sizeof(uint8);
	temp = get_SysCtrErr().flag;
	memcpy((uint8*)&item[len],(uint8*)&temp,sizeof(uint16));
	len += sizeof(uint8);
	temp = get_SysRunState().flag;
	memcpy((uint8*)&item[len],(uint8*)&temp,sizeof(uint16));
	len += sizeof(uint8);	
	temp = get_CabinetTemp();
	memcpy((uint8*)&item[len],(uint8*)&temp,sizeof(uint16));
	len += sizeof(uint8);		
	
	
	/*数据项长度*/
	ulFreame->msgHead.dataLen = len;	
}

/*
** ctr State Logic
*/
void ctr_StateLogic(void){
	SmCmd cmd = {true,0x81,0,0,0};
	static uint32 collectTick = 0;
	static uint32 circTick = 0;
	SysErr sysErrTemp = {0};
	SysRunState sysRunStateTemp = {0};
	
	if(TickOut((uint32*)&collectTick,1000) == true){
		/*策略:收集1S状态变更上报,超时1S的状态立即上报*/
		if(sysErrTemp.flag != get_SysCtrErr().flag 
			|| sysRunStateTemp.bits.emer != get_SysRunState().bits.emer){
			TickOut((uint32*)&collectTick,0);
			TickOut((uint32*)&circTick,0);
			sysErrTemp.flag = get_SysCtrErr().flag;
			sysRunStateTemp.bits.emer = get_SysRunState().bits.emer;
			setCmd(cmd);
		}else{/*定期5S轮询上报*/
			if(TickOut((uint32*)&circTick,5000) == true){
				TickOut((uint32*)&circTick,0);
				setCmd(cmd);
			}
		}
	}
}
