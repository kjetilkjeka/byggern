#include <avr/io.h>

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	unsigned int i, werrors, rerrors;
	werrors = 0;
	rerrors = 0;
	unsigned char testvalue;
	printf("Starting SRAM test...\r\n");
	for (i = 0; i < 0x800; i++) {
		testvalue = ~(i % 256);
		ext_ram[i] = testvalue;
		if (ext_ram[i] != testvalue) {
			printf("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			werrors++;
		}
	}
	for (i = 0; i < 0x800; i++) {
		testvalue = ~(i % 256);
		if (ext_ram[i] != testvalue) {
			printf("SRAM error (read phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			rerrors++;
		}
	}
	printf("SRAM test completed with %d errors in write phase and %d errors in read phase\r\n", werrors, rerrors);
}


void SRAM_test2(int place)
{
	volatile char *ext_ram = (char *) 0x1800;
	int errors = 0;
	int sucess = 0;
	for(int k = 0; k < 0xff; k++)
	{
		ext_ram[place] = k;
		
		int temp = ext_ram[place];
		if (temp == k)
		{
			sucess++;
			//printf("Sram sucess");
		} else 
		{
			errors++;
			printf("Sram fuckup writing ext_ram[%d] = %02X (should be %02X)\r\n", place, temp, k);	
		
		}
	}	
	
	if(errors != 0)
		printf("success: %d, errors: %d \r\n", sucess, errors);
	
}		


/*void SRAM_init(void)
{
	MCUCR |= (1<<SRE); // setting SRE mode (wich will allow us to use the external memory interface)
		
	//freeing pin PC4-PC7 (A12-A15) for not for io (don't think this is nececarry?)
	SFIOR &= ~((1<<XMM1)|(1<<XMM0));
	SFIOR |= (1<<XMM2);	
}
*/
