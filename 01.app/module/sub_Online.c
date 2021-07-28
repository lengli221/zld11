#include "includes.h"

SubOnline subOnline[SysCtr_AllDoorNum] = {0};

/*
** set Sub Online Cnt --single -point
**	@param:
**		uint8:���ŵ�ַ
*/
void set_SubOnlineCnt(uint8 addr){
	subOnline[addr].cnt++;
}

/*
** set Sub Online Cnt --broadcast
*/
void set_SubOnlineCnt_Broadcast(void){
	uint8 i = 0;

	for(i=0;i<SysCtr_AllDoorNum;i++){
		set_SubOnlineCnt(i);
	}
}

/*
** set Sub Online 
**	@param:
**		uint8:���ŵ�ַ
*/
void set_SubOnline(uint8 addr){
	subOnline[addr].cnt = 0;
	subOnline[addr].flag = false;
}

/*
** get Sub Is Online 
**	@param:
**		uint8:���ŵ�ַ
**	return:
**		bool:false-->�ֿ�����true-->�ֿ�����
*/
bool get_SubIsOnline(uint8 addr){
	return subOnline[addr].flag;
}

/*
** runtime Chk Sub Is Online
*/
void runtime_ChkSubIsOnline(void){
	uint8 i = 0;

	for(i=0;i<SysCtr_AllDoorNum;i++){
		if(subOnline[i].cnt >= 10){
			subOnline[i].cnt = 10;
			subOnline[i].flag = true;/*�ֿ�����*/
		}
	}
}

