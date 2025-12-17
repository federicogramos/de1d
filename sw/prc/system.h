// system.h

#define INPUT 1
#define OUTPUT 0

// PINES Y ORDEN EN EL QUE LOS VOY A UTILIZAR
#define PULSADOR GPIO5
#define RELAY GPIO2
#define SIGNAL GPIO3
#define LED GPIO4

#define AUX_A GPIO1
#define AUX_B GPIO0

// DATA DIRECTION REGISTERS
#define DDR_PULSADOR TRISIO5
#define DDR_RELAY TRISIO2
#define DDR_SIGNAL TRISIO3
#define DDR_LED TRISIO4

#define DDR_AUX_A TRISIO1
#define DDR_AUX_B TRISIO0

#define INIT_DDR() {                \
                   DDR_RELAY=OUTPUT;\
                   DDR_LED=OUTPUT;\
                   }

#define INIT_PORTS() {       \
                     RELAY=0;\
                     LED=0;\
                     }

void systemInit(void);



// VARIABLES EXTERNAS
#define DISABLE_COMPARATOR() {     \
                             CM0=1;\
                             CM1=1;\
                             CM2=1;\
                             }

#define DISABLE_AD() {      \
                     ANS0=0;\
                     ANS1=0;\
                     ANS2=0;\
                     ANS3=0;\
                     }
// Si no se va a usar el A/D, esta función se debe invocar, ya que por defecto,
// luego del reset, los puertos de entrada comienzan como entradas analógicas
// para ser usadas con el A/D, lo cual deshabilita que funcionen como entradas/
// salidas digitales.

#define ENABLE_AD() {         \
                     ANS0=1;  \
                     ANS1=1;  \
                     ANS2=0;  \
                     ANS3=0;  \
                              \
                     ADCS0=1; \
                     ADCS1=0; \
                     ADCS2=0; \
                              \
                     ADFM=0;  \
                              \
                     ADON=1;  \
                     }




#define PIC12F683_8MHZ() {        \
                          IRCF0=1;\
                          IRCF1=1;\
                          IRCF2=1;\
                          }





