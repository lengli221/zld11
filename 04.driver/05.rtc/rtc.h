#ifndef RTCTIME_H
#define RTCTIME_H

#include "stm32f2xx.h"
#include "stm32f2xx_conf.h"
#include "stdio.h"
#include "type.h"

/* 
** TIME STRUCT 
*/
typedef  struct _TIME_INFO_{
    uint32 iYear;
    uint8  ucMonth;
    uint8  ucDay;
    uint8  ucWeek;
    uint8  uchour;
    uint8  ucMin;
    uint8  ucSec;
}Time_Info;  

/* 
** ʱ��ṹ���� 
*/
typedef struct _COMMON_TIME_{
	uint16 iYear;     									
	uint8 ucMonth;    								
	uint8 ucDay;      									
	uint8 ucHour;     								
	uint8 ucMin;      									
	uint8 ucSec;      									
}Common_Time;


/*
** RTC ʱ������
*/
void RTC_Config(void);
/*
** ʱ�ӳ�ʼ��
*/
void rtc_Init(void);
/*
** ����ʱ��
*/
void RTC_Set_time(Common_Time st_Time);
/*
** ��ȡ��ǰʱ��
*/
void GetCurrentTime(Common_Time *curTime);
/*
** ʱ��ת������
*/
uint32 TimeToSeconds(Common_Time cdzTime);
/*
** ��ȡ��ǰ����,��2000����
*/
uint32 GetCurSecond(void);
/*
** ��ȡϵͳ�δ�ʱ�ӽ���
*/
uint32 GetSysTick(void);

#endif

