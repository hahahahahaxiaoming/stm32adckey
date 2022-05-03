#ifndef  __STM32F10X_IT_H
#define  __STM32F10X_IT_H
#include "stm32f10x.h" 
#include "adc_key.h"

#ifdef ADC_KEY_EN
extern AdcKeyMsg buttonmsg;
#endif

#define USART1_BUFF_LEN 16							//�����������ֽ��� 16
extern unsigned char Uart1_Buffer[USART1_BUFF_LEN];	//���ջ���
extern unsigned char USART1_RX_FLAG;				//����״̬��� 1���ս���
extern unsigned int USART1_RX_LEN;					//���ճ��ȱ��

#endif
