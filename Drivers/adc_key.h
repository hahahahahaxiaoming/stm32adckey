#ifndef __ADC_KEY_H__
#define __ADC_KEY_H__
#include "stm32f10x.h"

#define ADC_KEY_EN
#ifdef ADC_KEY_EN

extern uint16_t ADCKEYSCANTIME;		//����ɨ��ʱ��
typedef enum _AdcKeyType
{
	ADC_KEY_UNKOWN_TYPE = 0,
	ADC_KEY_PRESSED,				//����
	ADC_KEY_RELEASED,				//�����ͷ�
	ADC_KEY_LONG_PRESSED,			//����
	ADC_KEY_LONG_PRESS_HOLD,		//һֱ��
	ADC_KEY_LONG_RELEASED,			//�����ͷ�
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

