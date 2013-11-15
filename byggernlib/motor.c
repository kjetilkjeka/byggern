#include "motor.h"
#define F_CPU 8E6
#include <avr/delay.h>
//#include <avr/interrupt.h>



static int16_t min;
static int16_t max;
static int16_t referance;
static int16_t integrator;



void MOTOR_init()
{
	DDRMJ2 = 0x00;
	DDRMJ1 = 0b11111000;
	
	
	PORTMJ1 &= (0xff^(1<<MOTOR_OE));	
	MOTOR_resetCounter();
	
	MOTOR_enable(1);
	
	MOTOR_calibrate();
	MOTOR_setSpeed(0);
	MOTOR_setRef(128);
	
	ICR3 = 40000; // this is 16bit must fix safe initialization
	
	TCCR3B = (1<<WGM32)|(1<<WGM33)|(1<<CS31);
	ETIMSK |= (1<<TICIE3);
	
	
	
	
	printf("motor is initiated\n\r");

}



uint8_t lookup[16] = {
	0x0, 0x8, 0x4, 0xC,
	0x2, 0xA, 0x6, 0xE,
	0x1, 0x9, 0x5, 0xD,
	0x3, 0xB, 0x7, 0xF }; // this table is used in flip;

uint8_t flip( uint8_t n )
{
	return (lookup[n&0x0F] << 4) | lookup[n>>4];
}

int16_t MOTOR_readEncoder()
{
	volatile int16_t value = 0;
	PORTMJ1 &= (0xff^(1<<MOTOR_OE));	// set OE low to enable output
	PORTMJ1 &= (0xff^(1<<MOTOR_SEL));	// set SEL low to get high byte
	_delay_us(20);						// delay 20 microseconds
	value = (flip(PINMJ2)<<8); //<<8	// read MSB
	PORTMJ1 |= (1<<MOTOR_SEL);			// set SEL high to get low byte
	_delay_us(20);						// wait 20 us
	value += flip(PINMJ2);				// read LSB
	//MOTOR_resetCounter();				// toggle reset to reset encoder
	PORTMJ1 |= (1<<MOTOR_OE);			// set OE high to disable output
	return value;
}



void MOTOR_dir(uint8_t dir) // 1 er høyre
{
	
	if(dir)
		PORTMJ1 |= (1<<MOTOR_DIR);
	else
		PORTMJ1 &= (0xff ^ (1<<MOTOR_DIR));
	
	
}

void MOTOR_setSpeed(uint8_t speed)
{
	unsigned char messageBuf[4];
	
	messageBuf[0] = 0b01011110;
	messageBuf[1] = 0b00000000;
	messageBuf[2] = speed;
	
	TWI_Start_Transceiver_With_Data(messageBuf, 3);
}


void MOTOR_enable(uint8_t enable)
{
	
	if(enable)
		PORTMJ1 |= (1<<MOTOR_EN);
	else
		PORTMJ1 &= (0xff^(1<<MOTOR_EN));
	
}



void MOTOR_resetCounter()
{
	
	PORTMJ1 &= (0xff ^ (1<<MOTOR_RST));
	_delay_ms(20);
	PORTMJ1 |= (1<<MOTOR_RST);
	
}


void MOTOR_calibrate()
{
	MOTOR_enable(1);
	MOTOR_dir(1);
	MOTOR_setSpeed(80);
	_delay_ms(5000);
	MOTOR_resetCounter();
	min = MOTOR_readEncoder();
	MOTOR_dir(0);
	_delay_ms(5000);
	max = MOTOR_readEncoder();
	//MOTOR_setRef(max/2);
	printf("min is %d and max is %d, ref is %u \n\r", min, max, referance);
	MOTOR_dir(1);
	_delay_ms(5000);
	MOTOR_dir(0);
	_delay_ms(500);

}


void MOTOR_updateSpeed()
{
	while(TWI_Transceiver_Busy())
		_delay_ms(10);
	
	static int16_t old_error;
	
	int threashold = 255;
	int16_t P = 1;
	int16_t I = 8;
	int16_t D = 0;
	
	int16_t referancePos = referance;
	int16_t pos = MOTOR_getPos();
	
	int16_t error = referancePos - pos;
	
	integrator += old_error;	
	
	int16_t derivator = error - old_error;
	//derivator = 0;
	
	int16_t speed = P*error + integrator/I + derivator*D;
	
		
	//printf("trololol\n\r");
		
	old_error = error;
	
	
	if(speed > threashold)
		speed = threashold;
	
	if(speed < -threashold)
		speed = -threashold;
	
	
	if(speed > 0)
	{
		MOTOR_dir(0);
		MOTOR_setSpeed(speed);
	} else {
		MOTOR_dir(1);
		MOTOR_setSpeed(speed^0xff);
	}
		
}

int16_t MOTOR_getPos() //working
{
	int32_t pos = MOTOR_readEncoder();
	pos*=256;
	pos/=max;
	return (int16_t)pos;
}

void MOTOR_setRef(int16_t newRef)
{
	printf("integrator is %i \n\r", integrator);
	integrator = 0;
	referance = newRef;
	
	
}



int16_t MOTOR_getRef()
{
	return referance;
}
