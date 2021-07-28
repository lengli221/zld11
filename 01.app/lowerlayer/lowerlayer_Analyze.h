#ifndef __LOWERLAYER_ANALYZE_H_
#define __LOWERLAYER_ANALYZE_H_

typedef struct{
	uint8 funId;/*功能函数ID*/
	void (*handle)(uint8,uint8*,uint8);/*1.数据长度 2.数据项 3.设备地址*/
}LowerlayerFunTable;

/*
** Lowerlayer Fun Analyze
*/
void Lowerlayer_FunAnalyze(void);

#endif

