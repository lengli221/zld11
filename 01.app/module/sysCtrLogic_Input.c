#include "includes.h"

SCL_Input scl_Input = {0};

/*
** get Sys Ctr Is Err
** @param:
**		true:¹ÊÕÏ
**		false:Õý³£
*/
bool get_SysCtrIsErr(void){
	return scl_Input.sysErr.flag !=0 ? true:false;
}

/*
** Sys Ctr Logic Input
*/
void SysCtrLogic_Input(void){

}

