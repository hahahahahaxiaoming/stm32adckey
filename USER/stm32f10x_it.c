#include "stm32f10x_it.h"
#include "delay.h"
#include "stdio.h"
#include "string.h"
#include "timer.h"
#include "adc_key.h"

#ifdef ADC_KEY_EN
AdcKeyMsg buttonmsg;
static uint16_t index = 0;
#endif
#ifdef USER_TIME
uint32_t timems = 0;	
#endif

void TIM1_UP_IRQHandler(void)   //TIM1�ж�
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		//printf("time1");

		//-----------------------------------
		#ifdef USER_TIME
		timems++;
		#endif
		
		//-----------------------------------
		#ifdef ADC_KEY_EN
		index++;
		if(index == ADCKEYSCANTIME)
		{
			index = 0;
			buttonmsg = AdcKeyScan();
		}
		#endif
		
	}
}

void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		printf("time2");
	}
}

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		printf("time3");
	}
}

unsigned char Uart1_Buffer[USART1_BUFF_LEN];	//���ջ���
unsigned char USART1_RX_FLAG = 0;				//����״̬��� 1���ܽ���
unsigned int USART1_RX_LEN = 0;	

void USART1_IRQHandler(void)
{
	static int Uart1_Rx=0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�
	{
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
		if(Uart1_Rx == 0)
		{
			memset(Uart1_Buffer, 0, sizeof (Uart1_Buffer));//������պ���
		}
		Uart1_Buffer[Uart1_Rx] = USART_ReceiveData(USART1);     //���մ���1���ݵ�buff������
		Uart1_Rx++; 
     		 
		if(Uart1_Buffer[Uart1_Rx-1] == 0x0a)    //������յ�β��ʶ�ǻ��з�
		{
			USART1_RX_LEN = Uart1_Rx;
			Uart1_Rx = 0;
			USART1_RX_FLAG = 1;	
		}
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //�����ж�
	{
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}
}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //�����ж�
	{
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}
}
