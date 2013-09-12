void ADC_init(void)
{

}

#include <avr/io.h>

char ADC_read(int port)
{
	volatile char * ADCvar = 0x1400;
	
	switch (port)
	{
		case 0:
			ADCvar[0] = 0b00000100;
			break;
		case 1:
			ADCvar[0] = 0x05;
			break;
		case 2:
			ADCvar[0] = 0x06;
			break;
		case 3:
			ADCvar[0] = 0x07;
			break;
		default:
			return 0x00;
			break;				
	}
	
	while((PIND & 0b00000100) != 0b00000100);
	char temp = ADCvar[0];
	return temp;
		
}