#include "includes.h"

/*
** ִ�п��ֶ���
*/
ExceOpenDoor exceOpenDoor = {0};
/*----------------------------------------------Exce Open Door----------------------------------------------------------------*/
/*
** set Exce Open Door
** @param:
**		bool:false-->ִ�л���true-->�ѽ��շֿ�ִ�л����־
**		uint8:���ŵ�ַ
*/
void set_ExceOpenDoor(bool flag,uint8 addr){
	exceOpenDoor.flag[addr] = flag;
}

/*
** get Exce Open Door
**	@param:
**		uint8:���ŵ�ַ
**	@return:
**		bool:ִ�б�־
*/
bool get_ExceOpenDoor(uint8 addr){
	return exceOpenDoor.flag[addr];
}
/*---------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------Reply------------------------------------------------------------------------*/
/*
** fill Open Door 
*/
void fill_OpenDoor(uint8* len,uint8* item){
	uint8 txlen = 0;	

	/*
	** data Item
	**	1.Open Door
	*/
	item[txlen] = 0x01;
	txlen += sizeof(uint8);

	/*data Item Len*/
	*len = txlen;
}

/*
** set LowerLayer OpenDoor
** @ param:
**		addr:���㿪��
*/
void set_LowerLayerOpenDoor(uint8 addr){
	uint8 len = 0;
	uint8 tx[8] = {0};
	
	/*����Addr�Ϸ���*/
	if(addr < SysCtr_AllDoorNum){
		/*fill Open Door */
		fill_OpenDoor((uint8*)&len,(uint8*)&tx[0]);
		/*CAN Transmit*/
		CAN_TransmitAnalysis(CAN_Port_1, len, (uint8 *)&tx[0], addr, LL_FunId_OpenDoor_03);	
		/*set Exce Open Door*/
		set_ExceOpenDoor(false, addr);
	}
}
/*---------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Parse-----------------------------------------------------------------------*/
/*
** Lowerlayer Open Door   
*/
void Lowerlayer_ParseOpenDoor(uint8 rxlen,uint8* item,uint8 addr){
	/*set Exce Open Door*/
	set_ExceOpenDoor(true, addr);
}
/*---------------------------------------------------------------------------------------------------------------------------*/
