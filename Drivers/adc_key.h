#ifndef __ADC_KEY_H__
#define __ADC_KEY_H__
#include "stm32f10x.h"

#define ADC_KEY_EN
#ifdef ADC_KEY_EN

extern uint16_t ADCKEYSCANTIME;		//按键扫描时间
typedef enum _AdcKeyType
{
	ADC_KEY_UNKOWN_TYPE = 0,
	ADC_KEY_PRESSED,				//按下
	ADC_KEY_RELEASED,				//按下释放
	ADC_KEY_LONG_PRESSED,			//长按
	ADC_KEY_LONG_PRESS_HOLD,		//一直按
	ADC_KEY_LONG_RELEASED,			//长按释放
}AdcKeyType;

typedef struct _AdcKeyMsg
{
    uint16_t index;
    uint16_t type;
}AdcKeyMsg;

uint8_t GetAdcKeyIndex(void);

AdcKeyMsg AdcKeyScan(void);

void AdcKeyInit(void);
#endif

#endif

