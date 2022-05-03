//dac1  PA4
#include "dac.h"

void Dac1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE ); //ʹ�� P A ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE ); // ʹ�� DAC ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ������  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); // ��ʼ�� GPIOA
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4); //PA.4 �����
	
	DAC_InitType.DAC_Trigger=DAC_Trigger_None; //��ʹ�ô�������
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;// ��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ; //DAC1 ��������
	DAC_Init(DAC_Channel_1,&DAC_InitType); // ��ʼ�� DAC ͨ�� 1
	
	DAC_Cmd(DAC_Channel_1, ENABLE); // ʹ�� DAC1
	
	DAC_SetChannel1Data(DAC_Align_12b_R, 0); // λ�Ҷ��� ���� DAC ��ʼ ֵ
}
//����ͨ�� 1 �����ѹ
//vol:0~3300 ���� 0~3.3V
void Dac1_Set_Vol(u16 vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp); //12λ�Ҷ��� ���� DAC ֵ
}


