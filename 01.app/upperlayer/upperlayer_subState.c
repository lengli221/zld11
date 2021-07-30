#include "includes.h"

/*
** parse Sub State
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_SubState(uint16 rxlen,uint8* rx){
	
}

/*
** packect sub State
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_SubState(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num){
	uint16 len = 0;
	static uint16 frameLabel = 0;
	uint8 index = 0;
	LLParse_StateInfo sub_StateInfo = {0};
	
	/*
	** data item
	**	1.֡��ʶ
	**	2.�ֿز���ƫ�Ƶ�ַ
	**	3.�ֿز������ݽṹ����
	**	4.�ֿ�״̬��Ϣ
	*/
	frameLabel++;
	memcpy((uint8*)&item[len],(uint8*)&frameLabel,sizeof(uint16));
	len += sizeof(uint16);
	item[len] = addr;
	len += sizeof(uint8);
	item[len] = num;
	len += sizeof(uint8);
	for(index=0;index<num;index++){
		sub_StateInfo = get_SubStateInfo(addr+index);
		memcpy((uint8*)&item[len],(uint8*)&sub_StateInfo.protocol,sizeof(LLParse_StateInfo));
		len += sizeof(LLParse_StateInfo);
	}
	
	/*�������*/
	ulFreame->msgHead.dataLen = len;		
}

/*
** sub State Logic
*/
void sub_StateLogic(void){
	SmCmd cmd = {true,0x82,0,0,1};
	static uint32 collectTick[SysCtr_AllDoorNum] = {0};
	static uint32 circTick = 0;
	uint8 i=0;
	static LLParse_StateInfo sub_StateInfoTemp[SysCtr_AllDoorNum] = {0};
	LLParse_StateInfo subStateTemp = {0};
	
	/*״̬���:�����ϱ�*/
	for(i=0;i<SysCtr_AllDoorNum;i++){
		if(TickOut((uint32*)&collectTick[i],1000) == true){
			subStateTemp = get_SubStateInfo(i);
			if(memcmp((uint8*)&sub_StateInfoTemp[i].protocol,
					(uint8*)&subStateTemp.protocol,sizeof(LLParse_StateInfo)) != 0){
				TickOut((uint32*)&collectTick[i],0);
				sub_StateInfoTemp[i] = subStateTemp;
				cmd.doorAddr = i;
				cmd.doorNum = 1;
				setCmd(cmd);
				Sleep(50);/*����:ִ��һ���ַֿ��ϱ�֮�������ʱ50ms*/
			}
		}
	}
	
	/*��ѯ�ϱ�������Ϣ*/
	if(TickOut((uint32*)&circTick,2000) == true){
		TickOut((uint32*)&circTick,0);
		cmd.doorAddr = 0;
		cmd.doorNum = SysCtr_AllDoorNum;
		setCmd(cmd);		
	}
}
