// timerInt_delays.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __TIMER_FIXED_DELAYS_H
#define __TIMER_FIXED_DELAYS_H

// DEFINICION DE TIEMPOS POR PARTE DEL USUARIO
const type_timerFixedSize timerFixedDelayConstant[CANT_FIXED_TIMERS]=
	{
	20,//TMR_FIXED_LONG
	4, //TMR_FIXED_BLINK_ON
	1, //TMR_FIXED_BLINK_ON_ZERO
	5  //TMR_FIXED_BLINK_OFF
	};
#endif//__TIMER_DELAYS_H