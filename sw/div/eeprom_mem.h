////////////////////////////////////////////////////////////////////////////////
// MAPA DE MEMORIA DE EEPROM                                                  //
////////////////////////////////////////////////////////////////////////////////

//FGR: INICIALIZACION DE EEPROM
__EEPROM_DATA(
	0x03,//EEADDR_COUNTER_LIM
	0x05,//EEADDR_T_PUL_S
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00 //EEADDR_
	);
__EEPROM_DATA(
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x05 //EEADDR_
	);
__EEPROM_DATA(
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//EEADDR_
	0x00,//
	0x00,//
	0x00,//
	0x00,//
	0x00 //
	);

//FGR: RESERVA DE EEPROM
enum e_eeprom
	{
	EEADDR_COUNTER_LIM,
	EEADDR_T_PUL_S=EEADDR_COUNTER_LIM+sizeof(char)
	};
