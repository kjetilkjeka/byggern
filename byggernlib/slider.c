#include "command.h"

void SLIDER_init()
{
	touch_init(30, 30, 30, 30);
	
	
}

void SLIDER_poll()
{
	// only send if it has changed
	static unsigned char ls_old;
	static unsigned char rs_old;
	static unsigned char lb_old;
	static unsigned char rb_old;
	
	unsigned char ls;
	unsigned char rs;
	unsigned char lb;
	unsigned char rb;
	touch_measure(&ls, &rs, &lb, &rb);
	
	if(ls_old != ls)
	{
		COMMAND_setServo(ls*4);
		ls_old = ls;
		
	}
	if(rs_old != rs)
	{
		COMMAND_setMotor(rs - (unsigned char)30);
		rs_old = rs;	
		
	}
	if(lb_old != lb)
	{
		
	}
	if(rb_old != rb)
	{
		
	}
	
	
}