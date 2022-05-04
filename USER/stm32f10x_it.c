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

void TIM1_UP_IRQHandler(void)   //TIM1中断
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
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

void TIM2_IRQHandler(void)   //TIM2中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		printf("time2");
	}
}

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		printf("time3");
	}
}

unsigned char Uart1_Buffer[USART1_BUFF_LEN];	//接收缓冲
unsigned char USART1_RX_FLAG = 0;				//接收状态标记 1接受结束
unsigned int USART1_RX_LEN = 0;	

void USART1_IRQHandler(void)
{
	static int Uart1_Rx=0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断
	{
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
		if(Uart1_Rx == 0)
		{
			memset(Uart1_Buffer, 0, sizeof (Uart1_Buffer));//数组清空函数
		}
		Uart1_Buffer[Uart1_Rx] = USART_ReceiveData(USART1);     //接收串口1数据到buff缓冲区
		Uart1_Rx++; 
     		 
		if(Uart1_Buffer[Uart1_Rx-1] == 0x0a)    //如果接收到尾标识是换行符
		{
			USART1_RX_LEN = Uart1_Rx;
			Uart1_Rx = 0;
			USART1_RX_FLAG = 1;	
		}
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接收中断
	{
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}
}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收中断
	{
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}
}
