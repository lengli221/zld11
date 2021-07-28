#include "includes.h"

/*
** ϵͳ֮�˲����
*/
 SysFilterDesign sysFilterDesign;

/*
** ϵͳ֮ԪĿ���ַ
*/
IdAddr sysIdAddr;

/*
** ϵͳ֮�˲����֮Ŀ���ַ���ݹ�����Ŀ���޶���ֵַ
*/
uint8 SysFilterDesign_DstAddrLimit(void){
	uint8 i=0;
	uint8 ret = 0;
	uint8 param = SysCtr_AllDoorNum - 0x01;
	
	for(i=7;i>0;i--){/*Ŀ���ַ���ʹ��8λ��ַ*/
		if(param&(0x01<<i)){
			ret = (i+1);
			break;
		}	
	}
	return ret;
}

/*
** ϵͳ֮�˲������
*/
void SysFilterDesign_Param(void){
	/*
	** CAN1֮�˲����
	*/
	sysFilterDesign.filterDesign1.id.bits.rtr = 0;/*����֡*/
	sysFilterDesign.filterDesign1.id.bits.ide = 1;/*��չ֡*/
	sysFilterDesign.filterDesign1.id.bits.src = 0x00;/*Դ��ַ--ͨѶС��*/
	sysFilterDesign.filterDesign1.id.bits.dst = SrcAddr_Define;/*Ŀ���ַ--���ư�*/

	/*
	** Դ��ַ�����ڵ�ַ�޶���Χ��
	*/
	sysFilterDesign.filterDesign1.idMask.bits.src = (uint8)(0xFF<<SysFilterDesign_DstAddrLimit());
	/*
	** Ŀ���ַ����ƥ��
	*/
	sysFilterDesign.filterDesign1.idMask.bits.dst = (uint8)0xFF;
}

/*
** ϵͳ֮��ȡ�˲�����
*/
FilterDesign Sys_GetFilterDesign1(void){
	return(sysFilterDesign.filterDesign1);
}

/*
** ϵͳ֮ԴĿ���ַ��ʼ��
*/
void Sys_IdAddrInit(void){
	sysIdAddr.src = SrcAddr_Define;
	sysIdAddr.dst = 0;
}

/*
** ϵͳ֮��ȡԴ,Ŀ���ַ
*/
IdAddr Sys_GetIdAddr(void){
	return(sysIdAddr);
}

/*
** ϵͳ֮�˲���Ƴ�ʼ������
*/
void SysFilterDesign_ParamInit(void){
	memset((uint8*)&sysFilterDesign.filterDesign1.id.id,0x00,sizeof(SysFilterDesign));
	memset((uint8*)&sysIdAddr.src,0x00,sizeof(IdAddr));
	/*
	** ϵͳ֮�˲������
	*/
	SysFilterDesign_Param();
	/*
	** ϵͳ֮ԴĿ���ַ��ʼ��
	*/
	Sys_IdAddrInit();	
}

