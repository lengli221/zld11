#ifndef __BACKUP_
#define __BACKUP_

/*
** ʹ�ܱ�����ʱ��
*/
void PWR_BackupInit(void);
void BKP_ReadBackupRegDat(uint16_t Addr, uint8_t *Data,uint16_t Len);
void BKP_WriteBackupDat(uint16_t Addr, uint8_t *Data,uint16_t Len);

#endif

