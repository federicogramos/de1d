// tmp_11_xxxv.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __TMP_1L_H
#define __TMP_1L_H

//FGR: ESTADOS PRINCIPALES DE TMP_11_XXXV
enum e_state
	{
	STATE_IDLE,
	STATE_FEEDBACK,
	STATE_INPUT,
	STATE_SAVE_AND_CONTINUE_OR_REBOOT,
	CANT_STATE
	};

//FGR: SE INVIERTE EL ORDEN QUE EXISTE FISICAMENTE EN MEMORIA PORQUE COMIENZA A INGRESAR EL USUARIO VARIABLE DE LA POSICION EN MEMORIA N-1--> EN ESTE CASO HORAS
enum e_mem {MEM_PUL_S,MEM_PUL_M,MEM_PUL_H,CANT_MEM};

//FGR: SE ENCUENTRA REPETIDA EN EL MAIN
#define CANT_DIGITS 1//FGR: CANTIDAD DIGITOS DE VARIABLES EN MEMORIA (N DIGITOS QUE TENGO QUE INGRESAR EN LA CONFIGURACION PARA CADA VARIABLE)

//FGR: ESTRUCTURA (OJO ESTA ESTRUCTURA, SI NO COMPILA POR "no space for _isr temps" PUEDE HACER QUE COMPILE AGRANDAR EL ESPACIO OCUPADO EN MEMORIA, ME HA OCURRIDO)
typedef struct
	{
	unsigned char mem[CANT_MEM];
	unsigned char state;
	unsigned char aux_n_blink;
	unsigned char aux_n_setting;//FGR: SETEOS EN MEMORIA
	//unsigned char aux_n_digit;//FGR: N DÍGITOS A RECIBIR/RECIBIENDO (1=MINIMO)
	unsigned char aux_digit;//FGR: COUNTER DIGITO
	//unsigned char aux_digits[CANT_DIGITS];//FGR: COUNTER DIGITO ACUMULADO
	}t_temporizador;

//FGR: VARIABLES
extern t_temporizador tmp_1L;
extern char bitTitila;

//FGR: FUNCIONES
void tmp_11_xxxv_test_display(void);
void tmp_11_xxxv_init(void);
void tmp_11_xxxv_driver(void);
void tmp_11_xxxv_action(char new_event);
char tmp_11_xxxv_get_event(void);
short long delay_constant_hhmmss(char hh,char mm,char ss);
void returnToIdle(void);
#endif//__TMP_1L_H
