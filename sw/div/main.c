// main.c

#include <projectHeader.h>
#include <tmp_1L.h>
#include <main.h>// Contiene fuses y otras cosas.
#include <system.h>// Para la inicialización del sistema.
#include <interrupts.h>
#include <timer_lib.h>
#include <timer_fixed_lib.h>
#include <pulsPinDc_lib_1ms.h>
#include <eeprom_16f_lib.h>

//FGR: NECESARIO PARA REFERENCIAR GENERICAMENTE AL HACER EEPROM_WRITE_CHAR(mem_address[i],tmp_1L.mem[MEM_COUNTER]);
const char mem_address[CANT_MEM]=
	{
	EEADDR_COUNTER_LIM,
	EEADDR_T_PUL_S
	};

char estado_salida=0;
t_temporizador tmp_1L;

void tmp_1L_init(void)
	{
	tmp_1L.state=STATE_IDLE;//FGR: POR LO QUE HE PROBADO, NO ES INICIALIZADO, POR LO QUE LO HAGO MANUALMENTE
	tmp_1L.counter=0;//FGR: POR LO QUE HE PROBADO, NO ES INICIALIZADO, POR LO QUE LO HAGO MANUALMENTE

	//FGR: INICIALIZACION DE SETEOS EEPROM DEL TEMPORIZADOR
	EEPROM_READ_CHAR(EEADDR_COUNTER_LIM,tmp_1L.mem[MEM_COUNTER_LIM]);
	EEPROM_READ_CHAR(EEADDR_T_PUL_S,tmp_1L.mem[MEM_T_PUL_S]);

	timerDelayConstant[TMR_1L_PUL]=tmp_1L.mem[MEM_T_PUL_S]*4;
	}

void main(void)
	{
	systemInit();
	tmp_1L_init();
   while(1)
	{
	if(tmp_1L.state==STATE_IDLE)
		{
	      if(PULSPIN_EVENT_ID(PULS_FN))
			{
			tmp_1L.state=STATE_START_SET_UP;
			tmp_1L.aux_n_blink=5;//FGR: INDICA INICIO SET-UP CON 5 PARPADEOS
			tmp_1L.aux_n_setting=CANT_MEM;//FGR: CANTIDAD DE SETEOS QUE VOY A CONFIGURAR (0 A N-1). EMPIEZA A INGRESAR DEL ULTIMO AL PRIMERO
			TMR_FIXED_START(TMR_FIXED_BLINK_OFF);
			}

		if(PULSPIN_EVENT_ID(SIGNAL_FN) && ++tmp_1L.counter==tmp_1L.mem[MEM_COUNTER_LIM])
			{
			tmp_1L.counter=0;
			TMR_START(TMR_1L_PUL);
			LED=1;
			RELAY=1;
			}
		
		if(TMR_TIMEOUT(TMR_1L_PUL))
			{
			LED=0;
			RELAY=0;
			}
		}

	if(tmp_1L.state==STATE_START_SET_UP)
		{
		if(TMR_FIXED_TIMEOUT(TMR_FIXED_BLINK_ON))
			{
			LED=0;
			tmp_1L.aux_n_blink--;
			if(tmp_1L.aux_n_blink==0)
				{
				tmp_1L.state=STATE_DIGIT;
				tmp_1L.aux_n_digit=3;//FGR: MORE SIGNIFICANT A MENOS SIGNIFICANT (1 digito = minima cantidad)
				tmp_1L.aux_digit=0;//FGR: CONTADOR PARA INGRESO DEL DIGITO POR PARTE DEL USUARIO
				TMR_FIXED_START(TMR_FIXED_LONG);
				}
			else TMR_FIXED_START(TMR_FIXED_BLINK_OFF);
			}
		if(TMR_FIXED_TIMEOUT(TMR_FIXED_BLINK_OFF))
			{
			LED=1;
			TMR_FIXED_START(TMR_FIXED_BLINK_ON);
			}
		}

	if(tmp_1L.state==STATE_DIGIT)
		{
	      if(PULSPIN_EVENT_ID(PULS_FN))
			{
			TMR_FIXED_START(TMR_FIXED_LONG);//FGR: RESET TIEMPO TIMEOUT INGRESO SETTING
			tmp_1L.aux_digit++;
			}

		if(TMR_FIXED_TIMEOUT(TMR_FIXED_LONG))
			{
			tmp_1L.aux_n_digit--;
			tmp_1L.aux_digits[tmp_1L.aux_n_digit]=tmp_1L.aux_digit;
			if(tmp_1L.aux_n_digit==0)
				{
				tmp_1L.state=STATE_FEEDBACK;
				tmp_1L.aux_n_blink=tmp_1L.aux_digits[2];
				tmp_1L.aux_n_digit=3;//FGR: VA A MOSTRAR, DESDE MORE SIGNIFICANT A LESS SIGNIFICANT
				TMR_FIXED_START(TMR_FIXED_BLINK_OFF);
				}
			else
				{
				tmp_1L.aux_digit=0;
				LED=1;
				TMR_FIXED_START(TMR_FIXED_BLINK_ON);
				TMR_FIXED_START(TMR_FIXED_LONG);
				}
			}
		if(TMR_FIXED_TIMEOUT(TMR_FIXED_BLINK_ON))
			{
			LED=0;
			}
		}

	if(tmp_1L.state==STATE_FEEDBACK)
		{
		if(TMR_FIXED_TIMEOUT(TMR_FIXED_BLINK_ON) || TMR_FIXED_TIMEOUT(TMR_FIXED_BLINK_ON_ZERO))
			{
			LED=0;
			if(tmp_1L.aux_digits[tmp_1L.aux_n_digit-1]!=0) tmp_1L.aux_n_blink--;
			if(tmp_1L.aux_n_blink==0)
				{
				tmp_1L.aux_n_digit--;
				if(tmp_1L.aux_n_digit==0)
					{
					tmp_1L.aux_n_setting--;
					EEPROM_WRITE_CHAR(mem_address[tmp_1L.aux_n_setting],(tmp_1L.aux_digits[2])*100+tmp_1L.aux_digits[1]*10+tmp_1L.aux_digits[0]);
					if(tmp_1L.aux_n_setting==0)
						{
						tmp_1L.state=STATE_IDLE;
						}
					else
						{
						tmp_1L.state=STATE_DIGIT;
						tmp_1L.aux_n_digit=3;//FGR: MORE SIGNIFICANT A MENOS SIGNIFICANT (1 digito = minima cantidad)
						tmp_1L.aux_digit=0;//FGR: CONTADOR PARA INGRESO DEL DIGITO POR PARTE DEL USUARIO
						TMR_FIXED_START(TMR_FIXED_LONG);
						}
					}
				else
					{
					tmp_1L.aux_n_blink=tmp_1L.aux_digits[tmp_1L.aux_n_digit-1];
					TMR_FIXED_START(TMR_FIXED_LONG);
					}
				}
			else TMR_FIXED_START(TMR_FIXED_BLINK_OFF);
			}
		if(TMR_FIXED_TIMEOUT(TMR_FIXED_BLINK_OFF) || TMR_FIXED_TIMEOUT(TMR_FIXED_LONG))
			{
			LED=1;
			if(tmp_1L.aux_digits[tmp_1L.aux_n_digit-1]==0) TMR_FIXED_START(TMR_FIXED_BLINK_ON_ZERO) //FGR: ESTA BIEN AQUI QUE NO TENGA ";" AL FINAL DE LA MACRO
			else TMR_FIXED_START(TMR_FIXED_BLINK_ON);
			}

		}


/*
      if(PULSPIN_EVENT_ID(SIGNAL_FN))
         {
         TMR_START(TMR_1L_PUL);
         RELAY=1;
         LED=1;
         }

      if(TMR_TIMEOUT(TMR_1L_PUL))
         {
         RELAY=0;
         LED=0;
         }
  
	if(PULSPIN_EVENT_ID(PULS_FN))
         {
         TMR_START(TMR_1L_PUL);
         RELAY=1;
         LED=1;
         }
*/
      /*if(TMR_FIXED_TIMEOUT(TMR_FIXED_BLINK_ON))
         {
         RELAY=0;
         LED=0;
         }
*/

      }
   }




