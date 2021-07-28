#ifndef __CANFILTERDESIGN_H
#define __CANFILTERDESIGN_H

/*
** Ŀ���ַ֮�㲥��ַ
*/
#define DstAddr_BoardCast_Define										(uint8)0xBB

/*
**Ŀ���ַ֮#Define����
*/
#define SrcAddr_Define												(uint8)0x21

/*
** CAN֮��ʶ���ṹ��
*/
typedef struct{
	uint8 src;/*Դ��ַ*/
	uint8 dst;/*Ŀ���ַ*/
}IdAddr;

/*
**Identifier ��ɲ���
*/
typedef union{
	uint32 id;
	struct{
		uint32 res0:1;
		uint32 rtr:1;
		uint32 ide:1;
		uint32 src:8;
		uint32 dst:8;
		uint32 res1:13;
	}bits;
}IdMakeUp;

/*
**CAN֮�˲���ƽṹ��
*/
typedef struct{
	IdMakeUp id;
	IdMakeUp idMask;
}FilterDesign;

/*
** CAN֮ϵͳ�˲�
*/
typedef struct{
	FilterDesign filterDesign1;/*ϵͳ�˲�֮CAN1*/
}SysFilterDesign;

/*
** ϵͳ֮��ȡ�˲�����
*/
FilterDesign Sys_GetFilterDesign1(void);
/*
** ϵͳ֮��ȡԴ,Ŀ���ַ
*/
IdAddr Sys_GetIdAddr(void);
/*
** ϵͳ֮�˲���Ƴ�ʼ������
*/
void SysFilterDesign_ParamInit(void);

#endif

