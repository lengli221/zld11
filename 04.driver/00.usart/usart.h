#ifndef __USART_H_
#define __USART_H_

#include "type.h"
#include "queue.h"

/*
** ����1�������
*/
#define UART1_BUFLEN_R												1024
#define UART1_BUFLEN_S												256
#define DMA1_BUFLEN         									256 

/*
** ����2 �������
*/
#define UART_BUFLEN_R													1024
#define UART_BUFLEN_S													256
#define DMA_BUFLEN         										256      

/*
** ����3 �������
*/
#define UART3_BUFLEN_R												256
#define UART3_BUFLEN_S												256
#define DMA3_BUFLEN														256

#define USART1_DR_ADDRESS           					((uint32)USART1 + 0x04)
#define USART2_DR_ADDRESS           					((uint32)USART2 + 0x04)
#define USART3_DR_ADDRESS           					((uint32)USART3 + 0x04)
#define UART4Tx_DR_ADDRESS          					((uint32)UART4 + 0x04)

#define BSP_ComType_USART           					(uint8)0x01

#define BSP_ComUsart1													(uint8)0x01/*upperlayer*/
#define BSP_ComUsart2													(uint8)0x02
#define BSP_ComUsart3													(uint8)0x03

#define BSP_COM_NO														0			
#define BSP_COM_EVEN													1			
#define BSP_COM_ODD														2			

#define BSP_COM_STOP1													1
#define BSP_COM_STOP2													2

#define UpperLayer_Rx       									(GPIOG->BSRRH = GPIO_Pin_14)
#define UpperLayer_Tx       									(GPIOG->BSRRL = GPIO_Pin_14)

typedef struct {
  bool  *  Busy;    
  Queue *  TxQueue;   
  Queue *  RxQueue;   
}UartInfo;

void com_write(uint8 *buf, uint16 len);
int16 com_read(uint8 *buf, int16 len);
bool com_open(int8 port, int32 baud_rate, int32 dataBit, int8 parity, int8 stopBit);
void com_init(void);
void Com_Init(void);
void BSP_SmSend(uint8 ucComType,uint8 ucSmNo,void *msgbuf, uint16 *uclen);
void BSP_SmRecv(uint8 ucComType,uint8 ucSmNo,void *msgbuf, uint16 *uclen);
/*
** ���ڳ�ʼ��
*/
void Usart1_Init(void);
/*
** DMA ����
*/
void Usart1_DmaConfig(void);
/*
** ��ʼ��������
*/
void Usart1_BufferInit(void);
/*
** DMA Write
*/
bool Usart1_DmaWrite(uint8 * txBuf,uint32 txNum);
/*
** �ӻ�����������
*/
int Usart1_Rcv(uint8 *rxBuf, int rxNum);

void Usart2_Init(void);
void Usart2_DmaConfig(void);
void Usart2_BufferInit(void);
int Usart2_Rcv(uint8 *rxBuf, int rxNum);
bool Usart2_DmaWrite(uint8 * txBuf,uint32 txNum);
void Usart3_Init(void);
void Usart3_DmaConfig(void);
void Usart3_BufferInit(void);
int Usart3_Rcv(uint8 *rxBuf, int rxNum);
bool Usart3_DmaWrite(uint8 * txBuf,uint32 txNum);
#endif

