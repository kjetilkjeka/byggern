#include <avr/io.h>

void EXTMEM_init(void)
{
	MCUCR |= (1<<SRE); // setting SRE mode (wich will allow us to use the external memory interface)
	
	//freeing pin PC4-PC7 (A12-A15) for not for io (JTAG interface)
	SFIOR &= ~((1<<XMM1)|(1<<XMM0));
	SFIOR |= (1<<XMM2);
}