#include "includes.h"

CfgInfo cfgInfo = {0};
CfgFlag cfgFlag = {0};

/*
** parse Cfg Info
**	@param:
**		uint16:数据长度
**		uint8*:数据项
*/
void parse_CfgInfo(uint16 rxlen,uint8* rx){
	uint16 index = 0;
	CfgFlag cfgFlagTemp = {0};
	SmCmd cmd = {true,0x83,0,0,0};
	
	/*
	** data item
	**	1.协议号
	**	2.软件版本号
	**	3.充电器过温阈值
	**	3.电池过温阈值
	**	4.SOC过温阈值
	**	5.充电时间阈值
	*/
	if(rx[index] >= 102){
		/*copy data*/
		memcpy((uint8*)&cfgInfo.protocol,(uint8*)&rx[0],sizeof(CfgInfo));
		index += sizeof(CfgInfo);
		
		/*data analyze*/
		if(cfgInfo.chargerOT >= 100 || cfgInfo.chargerOT <= 40){
			cfgFlagTemp.bits.chargerOT = 1;
		}else{
			if(cfgInfo.chargerOT != get_ChargerOverTempLimit()){
				set_ChargerOverTmepLimit(cfgInfo.chargerOT);
			}
		}
		
		if(cfgInfo.batOT >= 100 || cfgInfo.batOT <= 40){
			cfgFlagTemp.bits.batOT = 1;
		}else{
			if(cfgInfo.batOT != get_BatOverTempLimit()){
				set_BatOverTempLimit(cfgInfo.batOT);
			}
		}	

		if(cfgInfo.socLimit >= 100 || cfgInfo.socLimit <= 40){
			cfgFlagTemp.bits.socLimit = 1;
		}else{
			if(cfgInfo.socLimit != get_SocLimit()){
				set_SocLimit(cfgInfo.socLimit);
			}
		}	

		if(cfgInfo.chgTime >= 720 || cfgInfo.chgTime <= 150){
			cfgFlagTemp.bits.chgTime = 1;
		}else{
			if(cfgInfo.chgTime != get_ChgTimeLimit()){
				set_ChgTimeLimit(cfgInfo.chgTime);
			}
		}		
		
		cfgFlag = cfgFlagTemp;
		setCmd(cmd);
	}
}

/*
** packect Cfg Flag
**	@param:
**		UpperLayerFrame:上层协议帧
**		uint8*:数据项
**		uint8:仓门地址
**		uint8:仓门数
*/
void packect_CfgFlag(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num){
	uint8 len = 0;
	
	/*
	** data item
	**	1.是否配置成功
	*/
	memcpy((uint8*)&item[len],(uint8*)&cfgFlag.flag,sizeof(CfgFlag));
	len += sizeof(CfgFlag);
	
	/*数据项长度*/
	ulFreame->msgHead.dataLen = len;		
}
