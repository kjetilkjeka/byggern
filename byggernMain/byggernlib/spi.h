

#ifndef SPI_H_
#define SPI_H_

void SPI_Init(void);
char SPI_Transmit(char cData);
void SPI_CS(int ss);



#endif