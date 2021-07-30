#include "includes.h"

OpenDoorProc openDoorProc[SysCtr_AllDoorNum] = {0};
OpenDoorResult openDoorResult[SysCtr_AllDoorNum] = {0};

/*
** parse open Door
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_openDoor(uint16 rxlen,uint8* rx){
	uint16 index = 0;
	uint8 addr = 0;
	SmCmd cmd = {true,0x85,0,0,0};
	
	/*
	** data item
	** 1.���ŵ�ַ
	*/
	addr = rx[index];
	index += sizeof(uint8);
	if(addr < SysCtr_AllDoorNum){/*����Addr�Ϸ���*/
		/*result:0x02--������æ 0x01--ִ����*/
		openDoorProc[addr].result = 
			(openDoorProc[addr].flag == true || openDoorResult[addr].flag == true)?0x02:0x01;
		/*�����ж�����:��һ�ν���ϱ��ɹ�,��������һ�ο���*/
		if(openDoorResult[addr].flag == false){
			openDoorProc[addr].flag = true;
		}
		openDoorProc[addr].addr = addr;
		cmd.doorAddr = addr;
		setCmd(cmd);
	}
}

/*
** packect open Door
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_openDoor(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num){
	uint16 len = 0;
	BmsInfo bmsInfoTemp = get_BmsInfo(addr);
	
	/*
	** data item
	**	1.���ŵ�ַ
	**	2.ָ����
	**	3.����Ƿ�����
	**	4.SN LEN
	**	5.SN
	*/
	item[len] = addr;
	len += sizeof(uint8);
	item[len] = openDoorProc[addr].result;
	len += sizeof(uint8);
	/*0x01--�������,0x00--��ز�����*/
	item[len] = get_BatIsOnline(addr) == true?0x01:00;
	len += sizeof(uint8);
	if(get_BatIsOnline(addr) == true){
		item[len] = (uint8)bmsInfoTemp.Field.id.idLen;
		len += sizeof(uint8);
		memcpy((uint8*)&item[len],(uint8*)&bmsInfoTemp.Field.id.id[0],
			(uint8)bmsInfoTemp.Field.id.idLen);
		len += (uint8)bmsInfoTemp.Field.id.idLen;
	}
	
	/*�������*/
	ulFreame->msgHead.dataLen = len;		
}

/*
** open Door Proc
*/
void open_DoorProc(void){
	uint8 i = 0;
	static uint8 step[SysCtr_AllDoorNum] = {0};
	static uint32 itick[SysCtr_AllDoorNum] = {0};
	static uint32 itick1[SysCtr_AllDoorNum] = {0};
	static uint8 repCnt[SysCtr_AllDoorNum] = {0};
	
	for(i=0;i<SysCtr_AllDoorNum;i++){
		if(openDoorProc[i].flag == true){
			switch(step[i]){
				case 0:
					set_LowerLayerOpenDoor(openDoorProc[i].addr);
					step[i]++;
					break;
				case 1:
					if(TickOut((uint32*)&itick[i],200) == false){
						/*���200ms�ڿ���ָ��,�ֿ��Ƿ�ظ�,δ���ջظ�,�ط�*/
						if(get_ExceOpenDoor(i) == true){
							TickOut((uint32*)&itick1[i],0);
							step[i]++;/*�ȴ��������*/
						}
					}else{
						if(++repCnt[i] >= 5){
							repCnt[i] = 0;
							openDoorResult[i].flag = true;
							openDoorResult[i].result = 1;/*�ֿ�δ��Ӧָ��*/
							/*�忪�ֽ��̱��,�����ϴ��������*/
							openDoorProc[i].flag = false;
							/*��lowerlayer�����־*/
							set_DoorResult(i,false,0);
						}						
						step[i] = 0;
					}
					break;
				case 2:
					/*�忪�ֽ��̱��,�����ϴ��������*/
					openDoorProc[i].flag = false;					
					break;					
			}
		}else{
			step[i] = 0;
			repCnt[i] = 0;
		}
		
		/*����Ƿ���λ�ϱ����*/
		if(get_SubIsOnline(i) == true){/*�ֿ�����*/
			openDoorResult[i].flag = true;
			openDoorResult[i].result = -2;
			/*��lowerlayer�����־*/
			set_DoorResult(i,false,0);			
		}else if(get_DoorResultFlag(i) == true){
			openDoorResult[i].flag = true;
			openDoorResult[i].result = get_DoorResult(i);
			/*��lowerlayer�����־*/
			set_DoorResult(i,false,0);
		}else{
			if(TickOut((uint32*)&itick1[i],3000) == true){
				openDoorResult[i].flag = true;
				openDoorResult[i].result = 3;/*�ֿ�ִ�п��ֶ�����ʱ*/
				/*��lowerlayer�����־*/
				set_DoorResult(i,false,0);
			}
		}
		
		/*ι��*/
		watchdogUpdate();
	}
}

/*
** parse open Door Result
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_openDoorResult(uint16 rxlen,uint8* rx){
	uint16 len = 0;
	uint8 addr = 0;
	
	/*data item*/
	addr = rx[len];
	len += sizeof(uint8);
	
	/*��upperlayer�����־*/
	openDoorResult[addr].flag = false;
}

/*
** packect open Door Result
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_openDoorResult(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num){
	uint16 len = 0;
	LLParse_StateInfo subStateInfoTemp = get_SubStateInfo(addr);
	BmsInfo bmsInfoTemp = get_BmsInfo(addr);
	
	/*
	** data Item
	**	1.���ŵ�ַ
	**	2.״̬��
	**	3.���
	**	4.�ֿ�״̬��Ϣ
	**	5.����Ƿ�����
	**	6.sn len
	**	7.sn
	*/
	item[len] = addr;
	len += sizeof(uint8);
	item[len] = 0x02;
	len += sizeof(uint8);
	item[len] = openDoorResult[addr].result;
	len += sizeof(uint8);
	memcpy((uint8*)&item[len],(uint8*)&subStateInfoTemp.protocol,sizeof(LLParse_StateInfo));
	len += sizeof(LLParse_StateInfo);
	/*0x01--�������,0x00--��ز�����*/
	item[len] = get_BatIsOnline(addr) == true?0x01:00;
	len += sizeof(uint8);
	if(get_BatIsOnline(addr) == true){
		item[len] = (uint8)bmsInfoTemp.Field.id.idLen;
		len += sizeof(uint8);
		memcpy((uint8*)&item[len],(uint8*)&bmsInfoTemp.Field.id.id[0],
			(uint8)bmsInfoTemp.Field.id.idLen);
		len += (uint8)bmsInfoTemp.Field.id.idLen;
	}	
}

/*
** open Door Result Proc 
*/
void open_DoorResultProc(void){
	static uint32 itick[SysCtr_AllDoorNum] = {0};
	uint8 i = 0;
	static uint8 step[SysCtr_AllDoorNum] = {0};
	SmCmd cmd = {true,0x86,0,0,0};
	
	for(i=0;i<SysCtr_AllDoorNum;){
		if(openDoorResult[i].flag == true){
			switch(step[i]){
				case 0:
					TickOut((uint32*)&itick,0);
					cmd.doorAddr = i;
					setCmd(cmd);
					step[i]++;
					break;
				case 1:
					if(TickOut((uint32*)&itick,500) == true){
						step[i] = 0;
					}
					break;
			}
		}else{
			step[i] = 0;
		}
		
		/*ι��*/
		watchdogUpdate();
	}
}
