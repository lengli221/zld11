#include "includes.h"

/*
** Lowerlayer Analyze Table
*/
static const LowerlayerFunTable lowerlayerFunTable[] = {
	{LL_FunId_StateInfo_01,Lowerlayer_ParseStateInfo},
	{LL_FunId_Cfg_02,Lowerlayer_ParseCfg},
	{LL_FunId_OpenDoor_03,Lowerlayer_ParseOpenDoor},
	{LL_FunId_DoorResult_04,Lowerlayer_ParseDoorResult},
	{LL_FunId_BmsInfo_80,Lowerlayer_ParseBms},
	{LL_FunId_ChargerInfo_81,Lowerlayer_ParseCharger}
};
static uint8 lowerlayerFunTableNum = sizeof(lowerlayerFunTable)/sizeof(LowerlayerFunTable);

/*
** Lowerlayer Fun Analyze
*/
void Lowerlayer_FunAnalyze(void){
	CanRxMsg rxMsg = {0};
	uint8 funId = 0;
	uint8 i=0;
	uint8 deviceAddr = 0;	

	for(;CAN_RecAnalysis(CAN_Port_1, (CanRxMsg *)&rxMsg) == true;){
		funId = (uint8)((rxMsg.ExtId>>16)&0x000000FF);
		for(i=0;i<lowerlayerFunTableNum;i++){
			if(funId == lowerlayerFunTable[i].funId){
				deviceAddr = (uint8)(rxMsg.ExtId&0x000000FF);		
				/*优化异常设备地址*/
				if(deviceAddr < SysCtr_AllDoorNum){
					lowerlayerFunTable[i].handle(rxMsg.DLC,(uint8*)&rxMsg.Data[0],deviceAddr);
				}
				break;
			}
		}
		/*喂狗*/
		watchdogUpdate();
	}
}

