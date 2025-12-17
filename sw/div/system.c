// system.c

#include <projectHeader.h>
#include <system.h>
#include <interrupts.h>
//#include <pulsadorPinFastDc_lib_1ms.h>

void systemInit(void)
   {
   PIC12F683_8MHZ();

   DISABLE_COMPARATOR();// De todos los periféricos que no se usan y existen en el microcontrolador, el único que arranca en un modo que no es convieniente, es el comparador, por lo que al iniciar, se lo pone en la configuración óptima para deshabilitarlo.

   IRQ_TIMER1_SETUP();// Setup interrupt. Timer1 16 bit timer.
   IRQ_TIMER0_SETUP();

   DISABLE_AD();

   GPPU=0;//Habilito pull-ups
   INIT_DDR();// Establece los puertos de entrada/salida.
   INIT_PORTS()

   IRQ_TIMER1_ENABLE();
   IRQ_TIMER0_ENABLE();

   IRQ_PERIPHERAL_ENABLE();// Timer 1 interrupt entra dentro de las "peripheral interrupts", por lo que debo habilitarlas para que funcione.
   IRQ_ENABLE();// Enable all interrupts
   }

