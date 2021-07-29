#include "includes.h"

SCL_Input scl_Input = {0};

/*
** get Sys Ctr Err
**	@return:
**		SysErr:故障信息
*/
SysErr get_SysCtrErr(void){
	return scl_Input.sysErr;
}

/*
** get Sys Run State
**	@return:
**		uint16:运行状态信息
*/
SysRunState get_SysRunState(void){
	return scl_Input.runState;
}

/*
** get Sys Ctr Is Err -- 一级故障
** @param:
**		true:故障
**		false:正常
*/
bool get_SysCtrIsErr(void){
	return (scl_Input.sysErr.flag !=0 || scl_Input.runState.bits.emer != 0)? true:false;
}

/*
** get Cabinet Temp
**	@return:
**		uint16:柜子温度
*/
uint16 get_CabinetTemp(void){
	return scl_Input.temp;
}

/*
** Sys Ctr Logic Input
*/
void SysCtrLogic_Input(void){

}

