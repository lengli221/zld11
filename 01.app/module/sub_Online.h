#ifndef __SUB_ONLINE_H_
#define __SUB_ONLINE_H_

/*
** sub Online Struct
*/
typedef struct{
	bool flag;/*�ֿ����߱�־:false-->����true-->����*/
	int8 cnt;/*֡�ط�����*/
}SubOnline;

/*
** set Sub Online Cnt --single -point
**	@param:
**		uint8:���ŵ�ַ
*/
void set_SubOnlineCnt(uint8 addr);

/*
** set Sub Online Cnt --broadcast
*/
void set_SubOnlineCnt_Broadcast(void);

/*
** set Sub Online
**	@param:
**		uint8:���ŵ�ַ
*/
void set_SubOnline(uint8 addr);

/*
** get Sub Is Online 
**	@param:
**		uint8:���ŵ�ַ
**	return:
**		bool:false-->�ֿ�����true-->�ֿ�����
*/
bool get_SubIsOnline(uint8 addr);

/*
** runtime Chk Sub Is Online
*/
void runtime_ChkSubIsOnline(void);

#endif

