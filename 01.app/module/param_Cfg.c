#include "includes.h"

ParamCfg paramCfg = {0};

/*
** get Charger Over Temp Limit
*/
uint8 get_ChargerOverTempLimit(void){
	return paramCfg.chargerTemp;
}

/*
** set Charger Over Temp Limit
*/
void set_ChargerOverTmepLimit(uint8 temp){
	paramCfg.chargerTemp = temp;
}

/*
** get Bat Over Temp Limit
*/
uint8 get_BatOverTempLimit(void){
	return paramCfg.batTemp;
}

/*
** set Bat Over Temp Limit
*/
void set_BatOverTempLimit(uint8 temp){
	paramCfg.batTemp = temp;
}

/*
** get Soc Limit
*/
uint8 get_SocLimit(void){
	return paramCfg.soc;
}

/*
** init Soc Limit
*/
void init_SocLimit(void){
	uint8 buf[ELen_SocLimit] = {0};
	uint8 buf_bkp[ELen_SocLimit] = {0};
	
	eeprom_read(EAddr_SocLimit,buf,ELen_SocLimit);
	BKP_ReadBackupRegDat(EAddr_SocLimit, buf_bkp, ELen_SocLimit);

	if(calcSum((uint8 *)&buf[0], ELen_SocLimit -1) == buf[ELen_SocLimit-1]){
		paramCfg.soc = buf[1];
		BKP_WriteBackupDat(EAddr_SocLimit, buf, ELen_SocLimit);
	}else if(calcSum((uint8 *)&buf_bkp[0], ELen_SocLimit -1) == buf_bkp[ELen_SocLimit-1]){
		paramCfg.soc = buf_bkp[1];
		eeprom_write(EAddr_SocLimit, buf_bkp, ELen_SocLimit);
	}else{
		set_SocLimit(95);
	}
}

/*
** set Soc Limit
*/
void set_SocLimit(uint8 soc){
	uint8 buf[ELen_SocLimit] = {0};
	
	paramCfg.soc = soc;

	buf[0] = Param_Cfg_Head;
	buf[1] = soc;
	buf[2] = calcSum((uint8 *)&buf[0], ELen_SocLimit - 1);

	eeprom_write(EAddr_SocLimit,buf,ELen_SocLimit);
	BKP_WriteBackupDat(EAddr_SocLimit, buf, ELen_SocLimit);
}

/*
** get ChgTime Limit
*/
uint16 get_ChgTimeLimit(void){
	return paramCfg.chgTime;
}

/*
** set ChgTime Limit
*/
void set_ChgTimeLimit(uint16 timeLimit){
	paramCfg.chgTime = timeLimit;
}

/*
** init Cfg Param 
*/
void init_CfgParam(void){
	/*
	** set Charger Over Temp Limit
	*/
	 set_ChargerOverTmepLimit(80);
	/*
	** set Bat Over Temp Limit
	*/
	set_BatOverTempLimit(70);
	/*
	** init Soc Limit
	*/
	init_SocLimit();
	/*
	** set ChgTime Limit
	*/
	set_ChgTimeLimit(600);	
}

