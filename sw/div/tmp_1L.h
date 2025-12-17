// tmp_11_xxxv.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __TMP_1L_H
#define __TMP_1L_H

//FGR: ESTADOS PRINCIPALES DE TMP_11_XXXV
enum e_state
	{
	STATE_IDLE,
	STATE_START_SET_UP,
	STATE_DIGIT,
	STATE_FEEDBACK,
	CANT_STATE
	};

//FGR: ESTABLECE EL MENU PRINCIPAL DE SETEOS
enum e_menu_time
	{
	/*03*/ MENU_TIEMPO_PULSO_H,
	/*04*/ MENU_TIEMPO_PULSO_M,
	/*05*/ MENU_TIEMPO_PULSO_S,
	CANT_MENU_TIME
	};

//FGR: TEXTOS DE MENU A MOSTRAR EN DISPLAY
const char *menu_time_text[]=
	{
	"HORAS",/*MENU_TIEMPO_PULSO_H*/
	"MINUtOS",/*MENU_TIEMPO_PULSO_M*/
	"SEGUNDOS"/*MENU_TIEMPO_PULSO_S*/
	};


//FGR: ESTABLECE EL MENU PRINCIPAL DE SETEOS
enum e_menu_config
	{
	/*01*/ MENU_EVENTO_DURANTE_PULSO,
	/*02*/ MENU_MOSTRAR_VISOR_PULSO,
	CANT_MENU_CONFIG
	};

//FGR: TEXTOS DE MENU A MOSTRAR EN DISPLAY
const char *menu_config_text[]=
	{
	"A- ENtRAdA dURANtE EL PROCESO",/*03 MENU_EVENTO_DURANTE_PULSO*/
	"b- PULSO REGRESIvA O tRANSCURRIDO"/*09 MENU_MOSTRAR_VISOR_PULSO*/
	};


//FGR: SETEOS UNO POR UNO (SUBMENU)
enum e_evento_fp_durante_pulso
	{
	FP_DURANTE_PULSO_NADA,
	FP_DURANTE_PULSO_CANCELA_PULSO,
	FP_DURANTE_PULSO_PAUSA_SAL_ON,
	FP_DURANTE_PULSO_PAUSA_SAL_OFF,
	FP_DURANTE_PULSO_REINICIA_PULSO,
	FP_DURANTE_PULSO_SUMA_PULSO,
	CANT_EVENTO_FP_DURANTE_PULSO
	};
const char *evento_fp_durante_pulso_text[]=
	{
	"1- NAdA",/*FP_DURANTE_PULSO_NADA*/
	"2- CANCELA PULSO",/*FP_DURANTE_PULSO_CANCELA_PULSO*/
	"3- PAUSA PULSO SALIdA ON",/*FP_DURANTE_PULSO_PAUSA_PULSO*/
	"4- PAUSA PULSO SALIdA OFF",/*FP_DURANTE_PULSO_SUMA_PULSO*/
	"5- REINICIA PULSO",/*FP_DURANTE_PULSO_REINICIA_PULSO*/
	"6- SUMA PULSO",/*FP_DURANTE_PULSO_SUMA_PULSO*/
	};

//FGR: SETEOS UNO POR UNO (SUBMENU)
enum e_mostrar_visor_pulso
	{
	MOSTRAR_VISOR_PULSO_REGRESIVA,
	MOSTRAR_VISOR_PULSO_TRANSCURRIDO,
	CANT_MOSTRAR_VISOR_PULSO
	};
const char *mostrar_visor_pulso_text[]=
	{
	"1- REGRESIvA",/*MOSTRAR_VISOR_PULSO_REGRESIVA*/
	"2- tRANSCURRIdO"/*MOSTRAR_VISOR_PULSO_TRANSCURRIDO*/
	};

//FGR: BIDIMENSIONAL ARRAY OF SUBMENU
const char **submenu_text[]=
	{
	evento_fp_durante_pulso_text,/*07 MENU_EVENTO_FN_DURANTE_PULSO*/
	mostrar_visor_pulso_text,/*09 MENU_MOSTRAR_VISOR_PULSO*/
	};


#define TMP11_MAX_STRLEN 4

enum e_mem {MEM_COUNTER_LIM,MEM_T_PUL_S,CANT_MEM};

//FGR: ESTRUCTURA (OJO ESTA ESTRUCTURA, SI NO COMPILA POR "no space for _isr temps" PUEDE HACER QUE COMPILE AGRANDAR EL ESPACIO OCUPADO EN MEMORIA, ME HA OCURRIDO)
typedef struct
	{
	unsigned char mem[CANT_MEM];
	unsigned char counter;
	unsigned char state;
	unsigned char aux_n_blink;
	unsigned char aux_n_setting;//FGR: SETEOS EN MEMORIA
	unsigned char aux_n_digit;//FGR: N DÍGITOS A RECIBIR/RECIBIENDO (1=MINIMO)
	unsigned char aux_digit;//FGR: COUNTER DIGITO
	unsigned char aux_digits[3];//FGR: COUNTER DIGITO ACUMULADO
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
