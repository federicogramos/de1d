////////////////////////////////////////////////////////////////////////////////
// MAPA DE MEMORIA DE EEPROM                                                  //
////////////////////////////////////////////////////////////////////////////////

//FGR: INICIALIZACION DE EEPROM
__EEPROM_DATA(
	0x00,//EEADDR_H
	0x00,//EEADDR_M
	0x05,//EEADDR_S
	0x00,//EEADDR_H2
	0x00,//EEADDR_M2
	0x01,//EEADDR_S2
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
	EEADDR_H,
	EEADDR_M=EEADDR_H+sizeof(char),
	EEADDR_S=EEADDR_M+sizeof(char),
	EEADDR_H2=EEADDR_S+sizeof(char),
	EEADDR_M2=EEADDR_H2+sizeof(char),
	EEADDR_S2=EEADDR_M2+sizeof(char)
	};
