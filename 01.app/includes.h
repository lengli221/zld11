#ifndef __INCLUDES_H_
#define __INCLUDES_H_

#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <math.h>


#include "ucos_ii.h"

#include "stm32f2xx.h"
#include "stm32f2xx_conf.h"
#include "stm32f2xx_spi.h"

#include "type.h"
#include "queue.h"
#include "common.h"

#include "usart.h"
#include "stm32f207bsp.h"
#include "os_bsp.h"
#include "FM24CL16.h"
#include "gpio.h"
#include "watchdog.h"
#include "rtc.h"
#include "timer.h"
#include "timer5.h"
#include "temp.h"
#include "adc.h"
#include "SPIFlash.h"
#include "backup.h"
#include "can.h"
#include "can_1.h"
#include "can_2.h"
#include "canFilterDesign.h"

#include "main.h"
#include "app_cfg.h"

/*hardware module*/
#include "gpio_runLed.h"

/*param*/
#include "param.h"

/*Addr Allocation*/
#include "eeprom_Addr.h"
#include "flash_Addr.h"

/*App module*/
#include "sysCtrLogic.h"
#include "sysCtrLogic_Output.h"
#include "sysCtrLogic_Input.h"
#include "param_Cfg.h"
#include "sub_Online.h"

/*lowerlayer*/
#include "lowerlayer_reply.h"
#include "lowerlayer_stateInfo.h"
#include "lowerlayer_parse.h"
#include "lowerlayer_Analyze.h"
#include "lowerlayer_cfg.h"
#include "lowerlayer_openDoor.h"
#include "lowerlayer_bms.h"
#include "lowerlayer_chargerInfo.h"

/*upperlayer*/
#include "upperlayer_ctrState.h"
#include "upperlayer_subState.h"
#include "upperlayer_cfg.h"
#include "upperlayer_bms.h"
#include "upperlayer_Parse.h"
#include "upperlayer_reply.h"

#endif

