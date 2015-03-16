#include "stdafx.h"
#include "myio.h"
#include "def.h"

extern void Delay_1us(DWORD delay);

// 93C56
void reset_93( void )
{
	write_io_byte(P_DATA,0x0); //SK=0,en=0(E),DI=0
	Delay_1us(100);
}

void clk_93( void )
{// SK __--__
	BYTE data;

	read_io_byte(P_DATA,&data);
	data |= 0x10; //SK=1, en=0(E),DI=x
	write_io_byte(P_DATA,data);
	Delay_1us(IC_93_DELAY);
	
	data &= 0xef; //SK=0, en=0(E),DI=x
	write_io_byte(P_DATA,data);
}

void start_93( void )
{//
	write_io_byte(P_DATA,0x80); //CS=high,en=0(E), DI=0
	Delay_1us(IC_93_DELAY);

	write_io_byte(P_DATA,0x81); //CS=high,en=0(E), DI=1
	Delay_1us(50);
	clk_93();
}


BYTE read_Byte(BYTE addr)
{
	int i;
	BYTE mask;
	BYTE data=0,data8;

	reset_93();

	start_93();
	//op code(10)
	write_io_byte(P_DATA,0x81);
	clk_93();
	write_io_byte(P_DATA,0x80);
	clk_93();

	//addr <<= (8-ic_info.page_mode);
	//送無效的A8
	write_io_byte(P_DATA,0x80);
	clk_93();
	
	//send address out
	for(i = 0; i < 8; i++)
	{
		mask = (BYTE)((addr & 0x80)>>7);
		write_io_byte(P_DATA,(BYTE)(0x80 | mask));
		clk_93();
		addr <<= 1;
	}
	
	//放開DI
	write_io_byte(P_DATA,(BYTE)0x82); //CS=1, en=1(D)
	
	//read data back
	for(i = 0; i < 8; i++)
	{
		read_io_byte(P_STATUS,&data8);
		data8 &= 0x10;
		data8 >>= 4;
		data |= data8;
		clk_93();
		data <<= 1;
	}
	//data |= ((inportb(P_STATUS)&0x20)>>5);
	read_io_byte(P_STATUS,&data8);
	data8 &= 0x10;
	data8 >>= 4;
	data |= data8;

	reset_93();
	return data;
}

void write_Byte(BYTE addr,BYTE data)
{
	int i;
	BYTE mask;
	BYTE da=0;

	write_enable(); //寫入致能

	start_93();

	//op code(01)
	write_io_byte(P_DATA,0x80);
	clk_93();
	write_io_byte(P_DATA,0x81);
	clk_93();

	//addr <<= (8-ic_info.page_mode);
	//送無效的A8
	write_io_byte(P_DATA,0x80);
	clk_93();
	
	for(i = 0; i < 8; i++) //send address out
	{
		mask = (BYTE)((addr & 0x80)>>7);
		write_io_byte(P_DATA,(BYTE)(0x80 | mask));
		clk_93();
		addr <<= 1;
	}
	
	for(i = 0; i < 8; i++) //send data
	{
		da = ((data & 0x80)>>7);
		write_io_byte(P_DATA,(BYTE)(0x80 | (BYTE)da));
		clk_93();
		data <<= 1;
	}
	
	reset_93();

	write_disable();
}

void write_enable(void)
{//寫入致能
	int i;
	BYTE mask;
	BYTE addr=0xc0;

	start_93();
	//op code(00)
	write_io_byte(P_DATA,0x80);
	clk_93();
	write_io_byte(P_DATA,0x80);
	clk_93();
	
	//byte mode是9bit
	for(i = 0; i < 8; i++) //send address out
	{
		mask = (BYTE)((addr & 0x80)>>7);
		write_io_byte(P_DATA,(BYTE)(0x80 | mask));
		clk_93();
		addr <<= 1;
	}
	//最低位元
	write_io_byte(P_DATA,0x80);
	clk_93();
	
	reset_93();
}

void write_disable(void)
{//寫入禁能
	int i;

	start_93();
	//op code(00)
	write_io_byte(P_DATA,0x80);
	clk_93();
	write_io_byte(P_DATA,0x80);
	clk_93();
	
	//byte mode是9bit
	for(i = 0; i < 9; i++) //send address out
	{
		write_io_byte(P_DATA,0x80);
		clk_93();
	}
	reset_93();
}

