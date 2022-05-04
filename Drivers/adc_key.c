#include "adc_key.h"
#include "adc.h"
#include "timer.h"

/*
 * ******************************************
 * ADC KEY��׼����ֵ�� ���� 10k (3.30V)
 * 0 = 100(0.00V), 1 = 1K(0.30V),  2 = 2.2K(0.59V), 3 = 3.6K(0.87V), 4= 5.6K(1.18V), 5 = 8.2K(1.48V), 
 * 6 = 12K(1.80V), 7 = 18K(2.10V), 8 = 27K(2.40V),  9 = 47K(2.70V),  10=100K(3.00V),
 *
 ********************************************
*/
#ifdef ADC_KEY_EN

#define 	ADC_KEY_SCAN_TIME			10		//����ɨ��ʱ��(ms)
#define 	ADC_KEY_JITTER_TIME			30		//��������ʱ��(ms)
#define 	ADC_KEY_CP_TIME				800 	//������������������һֱ��ʱ��(ms)
#define 	ADC_KEY_CPH_TIME			500		//һֱ���������(ms)
#define	    ADC_KEY_COUNT				11		//��׼adc��������
#define		ADC_KEY_FULL_VAL			4096	//12λadc����

uint16_t ADCKEYSCANTIME = ADC_KEY_SCAN_TIME;

typedef enum _ADC_KEY_STATE
{
	ADC_KEY_STATE_IDLE,
	ADC_KEY_STATE_JITTER,
	ADC_KEY_STATE_PRESS_DOWN,
	ADC_KEY_STATE_CP

} ADC_KEY_STATE;

TIMER			AdcKeyWaitTimer;
TIMER			AdcKeyScanTimer;
ADC_KEY_STATE	AdcKeyState;
static 	uint8_t 	PreKeyIndex = ADC_KEY_COUNT;

void AdcKeyInit(void)
{
	Adc_Init();						//��ʼ��adc1ͨ��0
	TIM1_Int_Init(10-1, 7200-1);	//��ʼ����ʱ�� 1ms 
}

uint8_t GetAdcKeyIndex(void)
{
	uint16_t Val;
	uint8_t	KeyIndex = ADC_KEY_COUNT;

	Val = Get_Adc(ADC_Channel_0);

	KeyIndex = (Val + (ADC_KEY_FULL_VAL / ADC_KEY_COUNT) / 2) * ADC_KEY_COUNT / ADC_KEY_FULL_VAL;

	return KeyIndex;
}


/**
*����������
*���أ��������� �����¼�  
*buttonmsg.index = 0, buttonmsg.type = ADC_KEY_LONG_PRESS_HOLD����˼��1������һֱ����
*buttonmsg.index = 2, buttonmsg.type = ADC_KEY_RELEASED����˼��3���������º��ͷ�
*/
AdcKeyMsg AdcKeyScan(void)
{
	uint8_t				KeyIndex=ADC_KEY_COUNT;
	AdcKeyMsg Msg = {ADC_KEY_COUNT, ADC_KEY_UNKOWN_TYPE};

	KeyIndex = GetAdcKeyIndex();
	
	switch(AdcKeyState)
	{
		case ADC_KEY_STATE_IDLE:
			if(KeyIndex == ADC_KEY_COUNT)
			{
				return Msg;
			}
			PreKeyIndex = KeyIndex;
			TimeOutSet(&AdcKeyWaitTimer, ADC_KEY_JITTER_TIME);
			//APP_DBG("GOTO JITTER!\n");
			AdcKeyState = ADC_KEY_STATE_JITTER;

		case ADC_KEY_STATE_JITTER:
			if(PreKeyIndex != KeyIndex)
			{
				//APP_DBG("GOTO IDLE Because jitter!\n");
				PreKeyIndex = ADC_KEY_COUNT;
				AdcKeyState = ADC_KEY_STATE_IDLE;
			}
			else if(IsTimeOut(&AdcKeyWaitTimer))
			{
				//APP_DBG("GOTO PRESS_DOWN!\n");
				TimeOutSet(&AdcKeyWaitTimer, ADC_KEY_CP_TIME);
				AdcKeyState = ADC_KEY_STATE_PRESS_DOWN;
				Msg.index = PreKeyIndex;
				Msg.type = ADC_KEY_PRESSED;
			}
			break;

		case ADC_KEY_STATE_PRESS_DOWN:
			if(PreKeyIndex != KeyIndex)
			{
				//APP_DBG("key release %d\n", PreKeyIndex);
				AdcKeyState = ADC_KEY_STATE_IDLE;
				Msg.index = PreKeyIndex;
				Msg.type = ADC_KEY_RELEASED;
				PreKeyIndex = ADC_KEY_COUNT;
			}
			else if(IsTimeOut(&AdcKeyWaitTimer))
			{
				//return key cp value
				//APP_DBG("ADC KEY CPS!\n");
				TimeOutSet(&AdcKeyWaitTimer, ADC_KEY_CPH_TIME);
				AdcKeyState = ADC_KEY_STATE_CP;
				Msg.index = PreKeyIndex;
				Msg.type = ADC_KEY_LONG_PRESSED;
			}
			break;

		case ADC_KEY_STATE_CP:
			if(PreKeyIndex != KeyIndex)
			{
				//return key cp value
				//APP_DBG("ADC KEY CPR!\n");
				AdcKeyState = ADC_KEY_STATE_IDLE;
				Msg.index = PreKeyIndex;
				Msg.type  = ADC_KEY_LONG_RELEASED;
				PreKeyIndex = ADC_KEY_COUNT;
			}
			else if(IsTimeOut(&AdcKeyWaitTimer))
			{
				//return key cph value
				//APP_DBG("ADC KEY CPH!\n");
				TimeOutSet(&AdcKeyWaitTimer, ADC_KEY_CPH_TIME);
				Msg.index = PreKeyIndex;
				Msg.type  = ADC_KEY_LONG_PRESS_HOLD;
			}
			break;

		default:
			AdcKeyState = ADC_KEY_STATE_IDLE;
			PreKeyIndex = ADC_KEY_COUNT;
			break;
	}

	return Msg;
}

#endif
