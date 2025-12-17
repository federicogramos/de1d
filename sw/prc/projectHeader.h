////////////////////////////////////////////////////////////////////////////////
// projectHeader.h                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef __PROJECT_HEADER_H
#define __PROJECT_HEADER_H

#include <htc.h>
// Este include va adentro del .h, solo porque es un include que deben tener
// todos los archivos fuente.

////////////////////////////////////////////////////////////////////////////////
// MACROS DE MANEJO DE BITS                                                   //
////////////////////////////////////////////////////////////////////////////////

#define HIGH_BYTE(x) ((unsigned char)(x>>8))
#define LOW_BYTE(x) ((unsigned char)(x & 0xFF))

#define BIT_SET(var,bitno) ((var) |= 1UL << (bitno))
#define BIT_CLR(var,bitno) ((var) &= ~(1UL << (bitno)))

#define BIT_GETVAL(byte,bitno) ((1UL<<bitno & byte)>>bitno)
// Retorna 0 o 1.

#define BIT_GETVAL_QUICK(byte,bitno) ((1UL<<(bitno)) & (byte))
// Retorna 0 si el bit es 0, !0 en otro caso.

#define BIT_BY_BIT_BYTE(b7,b6,b5,b4,b3,b2,b1,b0) (         \
                                                 b0*1UL<<0|\
                                                 b1*1UL<<1|\
                                                 b2*1UL<<2|\
                                                 b3*1UL<<3|\
                                                 b4*1UL<<4|\
                                                 b5*1UL<<5|\
                                                 b6*1UL<<6|\
                                                 b7*1UL<<7 \
                                                 )
// Para escribir una constante del tipo byte, pero estableciendo bit por bit.

////////////////////////////////////////////////////////////////////////////////
// MACROS PARA MANEJO DE EEPROM                                               //
////////////////////////////////////////////////////////////////////////////////

#define EEPROM_WRITE_INT(addr,n) {                                \
                                 eeprom_write(addr,HIGH_BYTE(n)); \
                                 eeprom_write(addr+1,LOW_BYTE(n));\
                                 }
// EEPROM:  +------------+----------+
// Address: |    0x00    |   0x01   |
//          +------------+----------+
// Data:    |  HIGH BYTE | LOW BYTE |
//          +------------+----------+

#define EEPROM_READ_INT(addr,var) {                           \
                                  var=0x00;                   \
                                  var|=eeprom_read(addr)<<8;  \
                                  var|=eeprom_read(addr+1)<<0;\
                                  }
// La variable que fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con
// "EEPROM_READ_INT" y medida en una variable en RAM.

////////////////////////////////////////////////////////////////////////////////
// MAPA DE MEMORIA DE EEPROM                                                  //
////////////////////////////////////////////////////////////////////////////////

#define EEADDR_CANT_ACTIVACIONES 0
#define EEADDR_B1 1
// Memoria no volatil para cantidad de activaciones del motor.
// Almacena un unsigned int, por eso requiere 2 bytes.

#endif
   // __PROJECT_HEADER_H