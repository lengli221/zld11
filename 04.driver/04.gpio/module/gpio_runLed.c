#include "includes.h"

/*
** 主控运行灯初始化
*/
void GPIO_RunLed_InitCfg(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*
	** 输出引脚配置
	*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	

	/*
	** PF10--运行闪烁灯
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOF, &GPIO_InitStructure);	

	/*初始化参数*/
	Ctr_RunLed_On;
}

/*
** 运行灯闪烁
** @param: time-->闪烁频率控制
*/
void RunLed_Ctr_Ficker(uint32 time){
	static uint32 itick = 0;
	static bool flag = false;

	if(TickOut((uint32 *)&itick, time) == true){
		TickOut((uint32 *)&itick, 0);
		flag = flag == false?true:false;
		if(flag == true){
			Ctr_RunLed_On;
		}else{
			Ctr_RunLed_Off;
		}
	}
}

