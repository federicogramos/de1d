// interrupts.c

#include <projectHeader.h>
#include <interrupts.h>
#include <system.h>// Necesario porque contiene la definición de los puertos de entrada/salida.
#include <timer_lib.h>
#include <timer_fixed_lib.h>
#include <pulsPinDc_lib_1ms.h>

void interrupt isr(void)
   {
   if(IRQ_TIMER1) isr_timer1();
   if(IRQ_TIMER0) isr_timer0();
   }

void isr_timer1(void)//FGR: 12F683->250ms
	{
	IRQ_TIMER1_SET(IRQ_TIMER1_RESET_VAL);// Reseteo del contador de la interrupción.
	
	timerDriver(TMR_1L_PUL);
	timerFixedDriver(TMR_FIXED_BLINK_ON);
	timerFixedDriver(TMR_FIXED_BLINK_ON_ZERO);
	timerFixedDriver(TMR_FIXED_BLINK_OFF);
	timerFixedDriver(TMR_FIXED_LONG);
	
	IRQ_TIMER1_RESET_FLAG();
	}

void isr_timer0(void)//FGR: 12F683->1ms
	{
	IRQ_TIMER0_SET(IRQ_TIMER0_RESET_VAL);
	
	puls_dc_0_driver();
	puls_dc_1_driver();
	
	IRQ_TIMER0_RESET_FLAG();
	}

