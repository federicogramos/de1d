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
	EEADDR_S2,
	EEADDR_M2,
	EEADDR_H2,
	EEADDR_S,
	EEADDR_M,
	EEADDR_H
	};

t_temporizador tmp_1L;

void tmp_1L_init(void)
	{
	tmp_1L.state=STATE_IDLE;//FGR: POR LO QUE HE PROBADO, NO ES INICIALIZADO, POR LO QUE LO HAGO MANUALMENTE
	//tmp_1L.counter=0;//FGR: POR LO QUE HE PROBADO, NO ES INICIALIZADO, POR LO QUE LO HAGO MANUALMENTE

	//FGR: INICIALIZACION DE SETEOS EEPROM DEL TEMPORIZADOR
	EEPROM_READ_CHAR(EEADDR_H,tmp_1L.mem[MEM_PUL_H]);
	EEPROM_READ_CHAR(EEADDR_M,tmp_1L.mem[MEM_PUL_M]);
	EEPROM_READ_CHAR(EEADDR_S,tmp_1L.mem[MEM_PUL_S]);

	//timerDelayConstant[TMR_1L_PUL]=tmp_1L.mem[MEM_PUL_H]*60*60*4+tmp_1L.mem[MEM_PUL_M]*60*4+tmp_1L.mem[MEM_PUL_S]*4;
    timerDelayConstant[TMR_1L_PUL]=tmp_1L.mem[MEM_PUL_H]*60*60*4+tmp_1L.mem[MEM_PUL_M]*60*4+tmp_1L.mem[MEM_PUL_S]*4;

	//FGR: INICIALIZACION DE SETEOS EEPROM DEL TEMPORIZADOR
	EEPROM_READ_CHAR(EEADDR_H2,tmp_1L.mem[MEM_PUL_H2]);
	EEPROM_READ_CHAR(EEADDR_M2,tmp_1L.mem[MEM_PUL_M2]);
	EEPROM_READ_CHAR(EEADDR_S2,tmp_1L.mem[MEM_PUL_S2]);

	//timerDelayConstant[TMR_1L_OFF]=tmp_1L.mem[MEM_PUL_H2]*60*60*4+tmp_1L.mem[MEM_PUL_M2]*60*4+tmp_1L.mem[MEM_PUL_S2]*4;
    timerDelayConstant[TMR_1L_OFF]=tmp_1L.mem[MEM_PUL_H2]*60*60*4+tmp_1L.mem[MEM_PUL_M2]*60*4+tmp_1L.mem[MEM_PUL_S2]*4;

	}

void main(void)
	{
	systemInit();
	tmp_1L_init();


    //FGR: EMPIEZO EL CICLO DEL PULSO
    TMR_START(TMR_1L_PUL);
	LED=1;
	RELAY=1;

   while(1)
	{
	if(tmp_1L.state==STATE_IDLE)
		{
	      if(PULSPIN_EVENT_ID(PULS_FN))
			{
			LED=0;//APAGA TODO PARA SETUP
			RELAY=0;//APAGA TODO PARA SETUP
			TMR_STOP(TMR_1L_PUL);//APAGA TODO PARA SETUP

			tmp_1L.state=STATE_FEEDBACK;
			tmp_1L.aux_n_blink=5;//FGR: INDICA INICIO SET-UP CON 5 PARPADEOS
			tmp_1L.aux_n_setting=CANT_MEM;//FGR: CANTIDAD DE SETEOS QUE VOY A CONFIGURAR (0 A N-1). EMPIEZA A INGRESAR DEL ULTIMO AL PRIMERO
			TMR_FIXED_START(TMR_FIXED_BLINK_OFF);
			}

	
		if(TMR_TIMEOUT(TMR_1L_PUL))
			{
            TMR_START(TMR_1L_OFF);
			LED=0;
			RELAY=0;
			}
        if(TMR_TIMEOUT(TMR_1L_OFF))
			{
            TMR_START(TMR_1L_PUL);
			LED=1;
			RELAY=1;
			}
		}





	if(tmp_1L.state==STATE_FEEDBACK)
    		{
    		if(TMR_FIXED_TIMEOUT(TMR_FIXED_BLINK_ON))
    			{
    			LED=0;
    			tmp_1L.aux_n_blink--;
    			if(tmp_1L.aux_n_blink==0)
    				{
                    if(tmp_1L.aux_n_setting==0)//FGR: TERMINÓ LA CONFIGURACION DEL USUARIO
                        {
                        tmp_1L.state=STATE_IDLE;
    TMR_START(TMR_1L_PUL);
	LED=1;
	RELAY=1;
                        }
                    else
                        {
                        tmp_1L.state=STATE_INPUT;
    				    tmp_1L.aux_digit=0;//FGR: CONTADOR PARA INGRESO DEL DIGITO POR PARTE DEL USUARIO
    				    TMR_FIXED_START(TMR_FIXED_LONG);
                        }
    				}
    			else TMR_FIXED_START(TMR_FIXED_BLINK_OFF);
    			}
    		if(TMR_FIXED_TIMEOUT(TMR_FIXED_BLINK_OFF))
    			{
    			LED=1;
    			TMR_FIXED_START(TMR_FIXED_BLINK_ON);
    			}
    		}


    	if(tmp_1L.state==STATE_INPUT)
    		{
            //PARA QUE CUANDO USUARIO APRIETE PULSADOR, VEA QUE ENCIENDE
            if(PULSADOR==0) LED=1;
            else LED=0;
    
            if(PULSPIN_EVENT_ID(PULS_FN))
    		    {
    			TMR_FIXED_START(TMR_FIXED_LONG);//FGR: RESET TIEMPO TIMEOUT INGRESO SETTING
    			tmp_1L.aux_digit++;
    			}
    
    		if(TMR_FIXED_TIMEOUT(TMR_FIXED_LONG)) tmp_1L.state=STATE_SAVE_AND_CONTINUE_OR_REBOOT;
    		}

    	if(tmp_1L.state==STATE_SAVE_AND_CONTINUE_OR_REBOOT)
    		{
   			tmp_1L.state=STATE_FEEDBACK;
   			tmp_1L.aux_n_blink=5;//FGR: INDICA INICIO SET-UP CON 5 PARPADEOS
   			TMR_FIXED_START(TMR_FIXED_BLINK_OFF);

    		tmp_1L.aux_n_setting--;
            EEPROM_WRITE_CHAR(mem_address[tmp_1L.aux_n_setting],tmp_1L.aux_digit);
    
    		if(tmp_1L.aux_n_setting==0)//YA SE QUE TERMINÉ DE INGRESAR SETEOS
    			{
	//FGR: INICIALIZACION DE SETEOS EEPROM DEL TEMPORIZADOR
	EEPROM_READ_CHAR(EEADDR_H,tmp_1L.mem[MEM_PUL_H]);
	EEPROM_READ_CHAR(EEADDR_M,tmp_1L.mem[MEM_PUL_M]);
	EEPROM_READ_CHAR(EEADDR_S,tmp_1L.mem[MEM_PUL_S]);

	//timerDelayConstant[TMR_1L_PUL]=tmp_1L.mem[MEM_PUL_H]*60*60*4+tmp_1L.mem[MEM_PUL_M]*60*4+tmp_1L.mem[MEM_PUL_S]*4;
    timerDelayConstant[TMR_1L_PUL]=tmp_1L.mem[MEM_PUL_H]*60*60*4+tmp_1L.mem[MEM_PUL_M]*60*4+tmp_1L.mem[MEM_PUL_S]*4;

	//FGR: INICIALIZACION DE SETEOS EEPROM DEL TEMPORIZADOR
	EEPROM_READ_CHAR(EEADDR_H2,tmp_1L.mem[MEM_PUL_H2]);
	EEPROM_READ_CHAR(EEADDR_M2,tmp_1L.mem[MEM_PUL_M2]);
	EEPROM_READ_CHAR(EEADDR_S2,tmp_1L.mem[MEM_PUL_S2]);

	//timerDelayConstant[TMR_1L_OFF]=tmp_1L.mem[MEM_PUL_H2]*60*60*4+tmp_1L.mem[MEM_PUL_M2]*60*4+tmp_1L.mem[MEM_PUL_S2]*4;
    timerDelayConstant[TMR_1L_OFF]=tmp_1L.mem[MEM_PUL_H2]*60*60*4+tmp_1L.mem[MEM_PUL_M2]*60*4+tmp_1L.mem[MEM_PUL_S2]*4;




    			}
            }

      }
   }




