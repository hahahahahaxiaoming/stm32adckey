#ifndef __USART_H
#define __USART_H	
#include "stm32f10x.h" 

void uart1_init(u32 bound);
void uart2_Init(u32 bound);
void uart3_Init(u32 bound);

void MyUSART_SendStr(USART_TypeDef * USARTx,u8 *str);
void MyUSART_SendByte(USART_TypeDef * USARTx, uint8_t data);
void MyUSART_SendHalfWord(USART_TypeDef * USARTx, uint16_t data);
void MyUSART_SendWord(USART_TypeDef * USARTx, uint32_t data);
#endif
