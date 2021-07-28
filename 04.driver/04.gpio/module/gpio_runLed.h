#ifndef __GPIO_RunLed_H_
#define __GPIO_RunLed_H_

/*主控运行灯*/
#define Ctr_RunLed_On					(GPIOF->BSRRL = GPIO_Pin_10)
#define Ctr_RunLed_Off					(GPIOF->BSRRH = GPIO_Pin_10)


/*
** 主控运行灯初始化
*/
void GPIO_RunLed_InitCfg(void);
/*
** 运行灯闪烁
** @param: time-->闪烁频率控制
*/
void RunLed_Ctr_Ficker(uint32 time);
#endif

