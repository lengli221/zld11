#ifndef __LOWERLAYER_STATEINFO_H_
#define __LOWERLAYER_STATEINFO_H_

#include "type.h"

#pragma pack(1)
typedef union{
	uint8 flag;
	struct{
		/*---------- Ctr Sub Protcol V101 ----------------------*/
		uint8 batOnline:1;/*�������*/
		uint8 batErr:1;/*��ع���*/
		uint8 selfChkErr:1;/*�Լ����*/
		uint8 chargerOnline:1;/*���������*/
		uint8 chargerErr;/*���������*/
		uint8 res:5;/*Ԥ��*/
		/*------------------------------------------------------*/
	}bits;
}Sub_RunState;
typedef struct{
	/*---------- Ctr Sub Protcol V101 ----------------------*/
	uint8 protocol;/*Э���*/
	uint8 softVer;/*����汾��*/
	uint8 doorstate;/*����״̬00:���Ź�01:���ſ�02:���Ź���*/
	uint8 doorLoc;/*�ֶ�λ00:�ղ�01:�����02:����03:����*/
	Sub_RunState subState;/*�ֿ�����״̬*/
	uint8 batErrLab;/*��ع��ϱ�ʶ*/
	uint8 subErrLab;/*�ֿع��ϱ�ʶ*/
	uint8 chargerErrLab;/*���������*/
	/*------------------------------------------------------*/
}LLParse_StateInfo;
#pragma pack()

/*
** get Protocol Record
*/
uint8 get_ProtocolRecord(uint8 addr);
/*
** get Bat Is Online
** 	@param:
**		uint8:���ŵ�ַ
**	@return
**		flag:
**			true:�������
**			false:��ز�����
*/
bool get_BatIsOnline(uint8 addr);

/*
** get Bat Is Exit Err
**	@param:
**		uint8:���ŵ�ַ
**	@return:
**		bool:true-->��ع���false-->�������
*/
bool get_BatIsExitErr(uint8 addr);

/*
** get Charger Is Online
** 	@param:
**		uint8:���ŵ�ַ
**	@return
**		flag:
**			true:���������
**			false:�����������
*/
bool get_ChargerIsOnline(uint8 addr);

/*
** get Door State
**	@param:
**		uint8:���ŵ�ַ
**	return:
**		00:���Ź�01:���ſ�02:���Ź���
*/
uint8 get_DoorState(uint8 addr);

/*
** get Door Loc
**	@param:
**		uint8:���ŵ�ַ
**	return:
**		00:�ղ�01:�����02:����03:����
*/
uint8 get_DoorLoc(uint8 addr);

/*
** Lowerlayer State Info
*/
void LowerLayer_StateInfo(void);

/*
** Lowerlayer Parse State Info
*/
void Lowerlayer_ParseStateInfo(uint8 rxlen,uint8* item,uint8 addr);
#endif

