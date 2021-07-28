#ifndef __PARAM_CFG_H_
#define __PARAM_CFG_H_

#include "type.h"

#define Param_Cfg_Head						(uint8)0xAA

#pragma pack(1)
typedef struct{
	/*---------- Ctr Sub Protcol V101 ----------------------*/
	uint8 chargerTemp;/*�����������ֵ*/
	uint8 batTemp;/*��ع�����ֵ*/
	uint8 soc;/*SOC��ֵ*/
	uint16 chgTime;/*���ʱ����ֵ*/
	/*------------------------------------------------------*/
}ParamCfg;
#pragma pack()

/*
** get Charger Over Temp Limit
*/
uint8 get_ChargerOverTempLimit(void);

/*
** set Charger Over Temp Limit
*/
void set_ChargerOverTmepLimit(uint8 temp);

/*
** get Bat Over Temp Limit
*/
uint8 get_BatOverTempLimit(void);

/*
** set Bat Over Temp Limit
*/
void set_BatOverTempLimit(uint8 temp);

/*
** get Soc Limit
*/
uint8 get_SocLimit(void);

/*
** set Soc Limit
*/
void set_SocLimit(uint8 soc);

/*
** get ChgTime Limit
*/
uint16 get_ChgTimeLimit(void);

/*
** set ChgTime Limit
*/
void set_ChgTimeLimit(uint16 timeLimit);

/*
** init Cfg Param 
*/
void init_CfgParam(void);

#endif

