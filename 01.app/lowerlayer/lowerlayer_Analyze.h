#ifndef __LOWERLAYER_ANALYZE_H_
#define __LOWERLAYER_ANALYZE_H_

typedef struct{
	uint8 funId;/*���ܺ���ID*/
	void (*handle)(uint8,uint8*,uint8);/*1.���ݳ��� 2.������ 3.�豸��ַ*/
}LowerlayerFunTable;

/*
** Lowerlayer Fun Analyze
*/
void Lowerlayer_FunAnalyze(void);

#endif

