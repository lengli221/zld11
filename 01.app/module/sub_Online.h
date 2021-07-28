#ifndef __SUB_ONLINE_H_
#define __SUB_ONLINE_H_

/*
** sub Online Struct
*/
typedef struct{
	bool flag;/*分控在线标志:false-->在线true-->离线*/
	int8 cnt;/*帧重发计数*/
}SubOnline;

/*
** set Sub Online Cnt --single -point
**	@param:
**		uint8:仓门地址
*/
void set_SubOnlineCnt(uint8 addr);

/*
** set Sub Online Cnt --broadcast
*/
void set_SubOnlineCnt_Broadcast(void);

/*
** set Sub Online
**	@param:
**		uint8:仓门地址
*/
void set_SubOnline(uint8 addr);

/*
** get Sub Is Online 
**	@param:
**		uint8:仓门地址
**	return:
**		bool:false-->分控在线true-->分控离线
*/
bool get_SubIsOnline(uint8 addr);

/*
** runtime Chk Sub Is Online
*/
void runtime_ChkSubIsOnline(void);

#endif

