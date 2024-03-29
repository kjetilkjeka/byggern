#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef MCP2515_H_
#define MCP2515_H_


#if defined (__AVR_ATmega128__)
#define CANINT_vect INT4_vect
#define CANINT INT4
#elif defined(__AVR_ATmega162__)
#define CANINT_vect INT0_vect
#define CANINT INT0
#elif defined(__AVR_AT90USB1287__)
#define CANINT_vect INT0_vect
#define CANINT INT0
#endif



#define NORMAL_MODE 0x00
#define LOOPBACK_MODE 0b01000000



#define BFPCTRL 0x0c
#define TXRTSCTRL 0x0d
#define CANSTAT 0x0e
#define CANCTRL 0x0f


#define TEC 0x1c
#define REC 0x1d


#define CNF3 0x28
#define CNF2 0x29
#define CNF1 0x2a
#define CANINTE 0x2b
#define CANINTF 0x2c
#define EFLG 0x2d
#define TXB0CTRL 0x30
#define TXB0SIDH 0x31
#define TXB0SIDL 0x32

#define TXB0DLC 0x35
#define TXB0D0 0x36
#define TXB0D1 0x37
#define TXB0D2 0x38
#define TXB0D3 0x39
#define TXB0D4 0x3a
#define TXB0D5 0x3b
#define TXB0D6 0x3c
#define TXB0D7 0x3d
#define TXB1CTRL 0x40
#define TXB1SIDH 0x41
#define TXB1SIDL 0x42


#define TXB1DLC 0x45

#define TXB1D0 0x46
#define TXB1D1 0x47
#define TXB1D2 0x48
#define TXB1D3 0x49
#define TXB1D4 0x4a
#define TXB1D5 0x4b
#define TXB1D6 0x4c
#define TXB1D7 0x4d


#define TXB2CTRL 0x50
#define TXB2SIDH 0x51
#define TXB2SIDL 0x52


#define TXB2DLC 0x55
#define TXB2D0 0x56
#define TXB2D1 0x57
#define TXB2D2 0x58
#define TXB2D3 0x59
#define TXB2D4 0x5a
#define TXB2D5 0x5b
#define TXB2D6 0x5c
#define TXB2D7 0x5d
#define RXB0CTRL 0x60
#define RXB0SIDH 0x61
#define RXB0SIDL 0x62

#define RXB0DLC 0x65
#define RXB0D0 0x66 
#define RXB0D1 0x67
#define RXB0D2 0x68
#define RXB0D3 0x69
#define RXB0D4 0x6a
#define RXB0D5 0x6b
#define RXB0D6 0x6c
#define RXB0D7 0x6d
#define RXB1CTRL 0x70
#define RXB1SIDH 0x71
#define RXB1SIDL 0x72

#define RXB1DLC 0x75
#define RXB1D0 0x76
#define RXB1D1 0x77
#define RXB1D2 0x78
#define RXB1D3 0x79
#define RXB1D4 0x7a
#define RXB1D5 0x7b
#define RXB1D6 0x7c
#define RXB1D7 0x7d

#define TXREQ 3

//for CANINTE 0x2b
#define RX0IE 0
#define RX1IE 1
#define TX0IE 2
#define TX1IE 3
#define TX2IE 4
#define ERRIE 5
#define WAKIE 6
#define MERRE 7

//for CANINTF 0x2c
#define RX0IF 0
#define RX1IF 1
#define TX0IF 2
#define TX1IF 3
#define TX2IF 4
#define ERRIF 5
#define WAKIF 6
#define MERRF 7




void MCP_reset(void);
char MCP_read(char adr);
char MCP_readRxBuffer(int location);
void MCP_write(char adr, char data);
void MCP_loadTxBuffer(int abc);
void MCP_RTS(int nnn);
void MCP_readStatus();
void MCP_rxStatus();
void MCP_bitModify(char adr, char maskByte, char data);


#endif 