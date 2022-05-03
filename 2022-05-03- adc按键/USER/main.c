#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "timer.h"
#include "adc.h"
#include "adc_key.h"
#include "dac.h"

int main(void)
{
	char result[5];
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	uart1_init(115200);
	//TIM1_Int_Init(10-1, 7200-1);//1ms
	Dac1_Init();
	AdcKeyInit();
	
	while(1)
	{
		if(USART1_RX_FLAG)
		{
			USART1_RX_FLAG = 0;
			//printf("data:%s\r\n", Uart1_Buffer);
			strncpy(result, (char *)Uart1_Buffer, USART1_RX_LEN-2);
			//printf("number:%d\r\n", atoi((char *)result));
			Dac1_Set_Vol(atoi((char *)result));
			//printf("adc get:%d\r\n",Get_Adc_Average(ADC_Channel_0,10));
			//printf("adckey get:%d\r\n",GetAdcKeyIndex());
		}
		if(buttonmsg.index != 11)
			printf("adc_key: %d,%d\r\n", buttonmsg.index, buttonmsg.type);
		
		delay_ms(10);
	}
}
