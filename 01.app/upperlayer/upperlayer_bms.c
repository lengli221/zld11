#include "includes.h"

/*
** parse bms
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_bms(uint16 rxlen,uint8* rx){

}

/*
** packect bms
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_bms(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num){
	uint16 len = 0;
	static uint16 frameLabel = 0;
	BmsInfo bmsInfoTemp = get_BmsInfo(addr);

	/*
	** data item
	**	1.֡��ʶ
	**	2/���ŵ�ַ
	**	3.BMS��ϸ��Ϣ
	*/
	frameLabel++;
	memcpy((uint8*)&item[len],(uint8*)&frameLabel,sizeof(uint16));
	len += sizeof(uint16);
	item[len] = addr;
	len += sizeof(uint8);
	memcpy((uint8*)&item[len],(uint8*)&bmsInfoTemp.zone[0],sizeof(BmsInfo));
	len += sizeof(BmsInfo);
	
	/*�������*/
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
			if(get_BatIsOnline(deviceAddr) == true){/*�������*/
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
