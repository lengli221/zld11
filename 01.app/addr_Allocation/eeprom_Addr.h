#ifndef __EEPROM_ADDR_H_
#define __EEPROM_ADDR_H_

/*
** eeprom Addr Allocation
**	1.Soc Limit Addr/Len
*/
#define EAddr_SocLimit					0
#define ELen_SocLimit						(sizeof(uint8) + 2/*head + calcSum*/)

#endif

