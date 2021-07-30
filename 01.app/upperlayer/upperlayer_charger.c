#include "includes.h"

/*
** parse charger
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_charger(uint16 rxlen,uint8* rx){
	
}

/*
** packect charger
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_charger(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num){
	uint16 len = 0;
	static uint16 frameLabel = 0;
	ChargerInfo chargerInfoTemp = get_ChargerInfo(addr);
	
	/*
	** data item
	**	1.֡��ʶ
	**	2/���ŵ�ַ
	**	3.�������ϸ��Ϣ
	*/
	frameLabel++;
	memcpy((uint8*)&item[len],(uint8*)&frameLabel,sizeof(uint16));
	len += sizeof(uint16);
	item[len] = addr;
	len += sizeof(uint8);
	memcpy((uint8*)&item[len],(uint8*)&chargerInfoTemp.zone[0],sizeof(ChargerInfo));
	len += sizeof(ChargerInfo);	
	
	/*�������*/
	ulFreame->msgHead.dataLen = len;		
}

/*
** charger Logic
*/
void charger_Logic(void){
	SmCmd cmd = {true,0x87,0,0,1};
	static uint32 circTick = 0;
	static uint8 deviceAddr = 0;
	
	if(TickOut((uint32*)&circTick,3000) == true){
		TickOut((uint32*)&circTick,0);
		for(;deviceAddr < SysCtr_AllDoorNum;deviceAddr++){
			if(get_ChargerIsOnline(deviceAddr) == true){/*���������*/
				cmd.doorAddr = deviceAddr;
				cmd.doorNum = 1;
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
