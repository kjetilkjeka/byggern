#include <avr/io.h>
#include <avr/sfr_defs.h>

#ifndef SPI_H_
#define SPI_H_


#if defined (__AVR_ATmega128__)
#define SS DDB0
#define MOSI DDB2
#define MISO DDB3
#define SCK DDB1
#elif defined(__AVR_ATmega162__)
#define SS DDB4
#define MOSI DDB5
#define MISO DDB6
#define SCK DDB7
#elif defined(__AVR_AT90USB1287__)
#define SS DDB0
#define MOSI DDB2
#define MISO DDB3
#define SCK DDB1


#endif


void SPI_Init(void);
char SPI_Transmit(char cData);
void SPI_CS(int ss);



#endif