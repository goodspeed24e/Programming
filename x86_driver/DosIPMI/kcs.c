#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "func.h"
#include "dosipmi.h"


DWORD tm;

int chktmout(void)
{
	// at least maxtime( must include the subroutines execution time in the loop! )
	if (tm > BMC_TIMEOUT)
	{
		return 1;
	}
	else
	{
		delay1ms();
		tm++;
	}
	return 0;
}

int chkBMCbusy(void)
{
	BYTE dd;

	tm=0;
	while(1)
	{
		dd = read_io_byte(KCS_STATUS);
		if(!(dd & ERROR_STATE))
		{//IDLE_STATE
			return 0;
		}
		if(chktmout())
		{
			return 1;
		}
	}
}

int chkBMCibfrdy(void)
{
	BYTE dd;
	
	tm=0;
	while(1)
	{
		dd = read_io_byte(KCS_STATUS);
		
		if(!(dd & 0x02))
		{//IBF ready
			return 0;
		}
		if(chktmout())
		{
			return 1;
		}
	}
}

BYTE IPDATA(void)
{
	BYTE dd;
	
	dd = read_io_byte(KCS_DATA);
	return dd;
}

void OPDATA(BYTE data)
{
	write_io_byte(KCS_DATA,data);
	inp(0x84);
}

void OPCMD(BYTE data)
{
	write_io_byte(KCS_CTRL,data);
	inp(0x84);
}

int chkBMCobfrdy_l(void)
{
	BYTE dd;
	
	tm=0; 
	while(1)
	{
		dd = read_io_byte(KCS_STATUS);
		if(!(dd & 0x01))
		{//OBF ready
			return 0;
		}
		IPDATA();
	 	if(chktmout())
		{
			return 1;
		}
	}
}

int chkBMCobfrdy_h(void)
{
	BYTE dd;
	
	tm=0; 
	while(1)
	{
		dd = read_io_byte(KCS_STATUS);
		if((dd & 0x01))
		{//OBF ready
			return 0;
		}
		IPDATA();
	 	if(chktmout())
		{
			return 1;
		}
	}
}

int chkBMCtxrdy(void)
{
	BYTE dd;

	tm=0;
	while(1)
	{
		dd = read_io_byte(KCS_STATUS);
		if((dd & ERROR_STATE)==WRITE_STATE)
		{//IDLE_STATE
			return 0;
		}
		if(chktmout())
		{
			return 1;
		}
	}
}

int chkBMCrxrdy(void)
{
	BYTE dd;

	tm=0;
	while(1)
	{
		dd = read_io_byte(KCS_STATUS);
		if((dd & ERROR_STATE)==READ_STATE)
		{//READ_STATE
			return 0;
		}
		if(chktmout())
		{
			return 1;
		}
	}
}

int Send2KCS(void)
{
	int n,out_cnt;
	BYTE dd;

	out_cnt = 0;
ErrAgain:
	if(out_cnt >= RETRY_OUT)
	{
		return 1;
	}

	memset(IPMI_response,0,sizeof(IPMI_response));
	
	if(chkBMCibfrdy())
	{
		goto OnErr;
	}
	
	if(chkBMCobfrdy_l())
	{
		goto OnErr;
	}
	
	OPCMD(KCS_WRITE_START);
	
	inp(0x84);
	
	if(chkBMCibfrdy())
	{
		goto OnErr;
	}
	
	if(chkBMCtxrdy())
	{//not write_state
		goto OnErr;
	}
	
	if(chkBMCobfrdy_l())
	{
		goto OnErr;
	}
		
	n = 0;
	while( n < (IPMI_reqlen-1))
	{
		OPDATA(IPMI_request[n]);
		inp(0x84);
		if(chkBMCibfrdy())
		{
			goto OnErr;
		}
		
		if(chkBMCtxrdy())
		{//not write_state
			goto OnErr;
		}
		
		if(chkBMCobfrdy_l())
		{
			goto OnErr;
		}
		
		n++;
	}
	OPCMD(KCS_WRITE_END);
	inp(0x84);
	if(chkBMCibfrdy())
	{
		goto OnErr;
	}
	
	if(chkBMCtxrdy())
	{
		goto OnErr;
	}
	
	if(chkBMCobfrdy_l())
	{
		goto OnErr;
	}
	
	OPDATA(IPMI_request[n]);
	inp(0x84);
	//-------------------------------- response ------------------------------

	IPMI_rsplen=0;
	while(1)
	{
		if(chkBMCibfrdy())
		{
			goto OnErr;
		}
		
		dd = read_io_byte(KCS_STATUS);
		if((dd & ERROR_STATE)==READ_STATE)
		{
			inp(0x84);
			if(chkBMCobfrdy_h())
			{
				goto OnErr;
			}
			
			IPMI_response[IPMI_rsplen] = IPDATA();
			
			if(IPMI_rsplen==MAX_CMD_LEN)
			{
				break;
			}
			
			OPDATA(KCS_READ);
		}
		else
		{
			if(chkBMCbusy())
			{//not IDLE_STATE
				goto OnErr;
			}
			
			if(chkBMCobfrdy_h())
			{
				goto OnErr;
			}
			
			IPDATA();
			if(chkBMCbusy())
			{
				goto OnErr;
			}
			break;
		}
		IPMI_rsplen++;
	}
	
	return 0;
	
OnErr:
	delay1ms();
	inp(0x84);

	inp(0x84);
	out_cnt++;
	goto ErrAgain;
}
