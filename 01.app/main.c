/**
**bin�ļ�����˵��*****************************
**1.Run User Programs After Build/Rebuild
	��ѡ Run #1:E:\00.ApplicationSoftware\00.keil\01.Install\ARM\ARMCC\bin\fromelf.exe --bin --output ./02.Output/chenfu.bin F:\00.CurrentSourceCode\01.ChangeCabinet\05.Okay\02.Project\00.prj\project\keil\output\chenfu.axf
**2.Read/Only Memory Areas
			Start		 	Size
	IROM1: 0x8040000   	0x5FFFF
**3.Create Exectable
	�������������ѡ
	Debug Information
	Create HEX File
	Browse Information
**4.�޸��ļ�system_stm32f2xx.c
	#define VECT_TAB_OFFSET  0x40000
***/

#include "includes.h"

int stk[1024] = {0}; 

void hard_init(void){	
	BspCPUClkFreq();
	BspInit();
}

void Thread(void *p){	
	/*
	** �ṩϵͳ�������ϵͳ���ƽӿں���
	*/
	SysCtrlLogic_Init();

	/*
	** �ṩϵͳ��������²�Э���ѯ�ӿں���
	*/
	LowerLayerReply_Init();	

	/*
	** �ṩϵͳ��������²�Э������ӿں���
	*/
	LowerLayerParse_Init();
	
	while(1){
		/*ι��*/
		watchdogUpdate();
		Sleep(50);
	}
}

int main()
{
	#if OS_CRITICAL_METHOD == 3u           		
		OS_CPU_SR  cpu_sr = 0u;
	#endif
	OS_ENTER_CRITICAL();
	
	hard_init();
	os_init();

	Thread_create(Thread,0,&stk[1024 - 1],MainTask_Prio);

	OS_EXIT_CRITICAL();

	Thread_start();

	while(1)
	{
		Sleep(10);
	}
}

void App_TaskIdleHook(void)
{

}

