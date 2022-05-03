#ifndef  __STM32F10X_IT_H
#define  __STM32F10X_IT_H
#include "stm32f10x.h" 
#include "adc_key.h"

#ifdef ADC_KEY_EN
extern AdcKeyMsg buttonmsg;
#endif

#define USART1_BUFF_LEN 16							//定义最大接收字节数 16
extern unsigned char Uart1_Buffer[USART1_BUFF_LEN];	//接收缓冲
extern unsigned char USART1_RX_FLAG;				//接收状态标记 1接收结束
extern unsigned int USART1_RX_LEN;					//接收长度标记

#endif
