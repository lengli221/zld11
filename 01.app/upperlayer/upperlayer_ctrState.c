#include "includes.h"

/*
** parse Ctr State
**	@param:
**		uint16:���ݳ���
**		uint8*:������
*/
void parse_CtrState(uint16 rxlen,uint8* rx){

}

/*
** packect Ctr State
**	@param:
**		UpperLayerFrame:�ϲ�Э��֡
**		uint8*:������
**		uint8:���ŵ�ַ
**		uint8:������
*/
void packect_CtrState(UpperLayerFrame *ulFreame,uint8* item,uint8 addr,uint8 num){
	uint16 len = 0;
	uint16 temp = 0;
	
	/*
	** data item
	**	1.����Э���
	**	2.��������汾��
	**	3.������Ϣ
	**	4.״̬��Ϣ
	**	5.�����¶���Ϣ
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
	
	
	/*�������*/
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
		/*����:�ռ�1S״̬����ϱ�,��ʱ1S��״̬�����ϱ�*/
		if(sysErrTemp.flag != get_SysCtrErr().flag 
			|| sysRunStateTemp.bits.emer != get_SysRunState().bits.emer){
			TickOut((uint32*)&collectTick,0);
			TickOut((uint32*)&circTick,0);
			sysErrTemp.flag = get_SysCtrErr().flag;
			sysRunStateTemp.bits.emer = get_SysRunState().bits.emer;
			setCmd(cmd);
		}else{/*����5S��ѯ�ϱ�*/
			if(TickOut((uint32*)&circTick,5000) == true){
				TickOut((uint32*)&circTick,0);
				setCmd(cmd);
			}
		}
	}
}
