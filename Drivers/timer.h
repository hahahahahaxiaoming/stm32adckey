#ifndef __timer_H
#define __timer_H
#include "stm32f10x.h"

void TIM1_Int_Init(u16 arr, u16 psc);
void TIM1_PWM_Init(u16 arr, u16 psc);
void TIM2_Int_Init(u16 arr, u16 psc);
void TIM2_PWM_Init(u16 arr, u16 psc);
void TIM3_Int_Init(u16 arr, u16 psc);
void TIM3_PWM_Init(u16 arr, u16 psc);

//-------------------------------------
#define USER_TIME
#ifdef USER_TIME

// define softtimer structure.
typedef struct	_TIMER
{
	uint32_t	TimeOutVal; 								//time out value
	uint32_t	TickValCache;			  					//soft timer setting value
	uint8_t		IsTimeOut;									//time out flag
} TIMER;

// Set time out value of softtimer.
extern void TimeOutSet(TIMER* timer, uint32_t timeout);
// Check whether time out.
extern uint8_t IsTimeOut(TIMER* timer);

#endif
//-------------------------------------
#endif
