#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "func.h"
#include "smb.h"

struct i2c_device
{
	BYTE addr;
	BYTE data;
};

WORD SMB_base;
BYTE bus,dev,func;
int smb_type;
int device_qty;
int pre_sld;
int current_sld;

struct i2c_device devs[20];

void main(void)
{
	WORD vendor;
	
	if(Search_Device(0x0c,0x05,0x05,&vendor,&bus,&dev,&func)==0) //SMBus
	{
		printf("Can NOT found System Management Bus(SMBus) controller\n");
		return;
	}
	
	if(vendor == 0x10DE)
	{//NVidia
		smb_type = 0;
	}
	else if(vendor == 0x8086)
	{//Intel
		smb_type = 1;
	}
	else
	{
		printf("This tool support NVidia & Intel SMBus ONLY\n");
		return;
	}
	
	GUI();
	
}

void GUI(void)
{
	int ch1,ch2;
	
	clrscr();
	HideCursor();
	
	Block(0,0,79,24,B_BLUE);
	
	gotoxy(0,0);
	color_printf(B_BROWN | F_BLUE,"                              DOSSMB.EXE Rev:v1.0                                        ");
	
	gotoxy(1,1);
	color_printf(B_BROWN | F_WHITE," Device#  Device address   1'st data in device                                 ");
	Block(1,2,78,22,B_WHITE);
	
	tool_bar(0);
	
	gotoxy(0,24);
	color_printf(B_BROWN | F_BLUE,"                                                                         Intra  ");
	
	pre_sld = 0;
	current_sld = 0; //第一個預選
	
	detect_device(); //偵測有幾個裝置
	
	//show all i2c devices
	show_device();
	
	//Device 1 is selected(default)
	draw_select();
	
	
	while(1)
	{
		if(kbhit() != 0)
		{
			ch1 = getch();
			switch(ch1)
			{
				case 0:	//特殊功能鍵
					ch2 = getch();
					switch(ch2)
					{
						case 0x50: //下箭頭
							if(current_sld < 20)
							{
								if(current_sld < (device_qty-1)) //小於總裝置數才可以下移
								{
									pre_sld = current_sld;
									current_sld ++;
								}
							}
							break;
						
						case 0x48: //上箭頭
							if(current_sld > 0)
							{
								pre_sld = current_sld;
								current_sld--;
							}
							break;

						case 0x44: // F10 Exit
							clrscr();
							ShowCursor();
							return;
					}
					draw_select();
					break;
					
				case 13://Enter(使用者選擇裝置)
					tool_bar(1);
					Get_Content();
					
					//選擇完，回復未選擇前顯示
					pre_sld = current_sld;
					Block(1,2,78,22,B_WHITE);
					show_device();
					draw_select();
					tool_bar(0);
					break;
			}//end of switch(ch1)
		}//end of if(kbhit())
	}
}

void detect_device(void)
{
	BYTE addr,data;
	
	device_qty = 0;
	memset(devs,0,sizeof(devs));
	
	for(addr = 0xA0; addr < 0xAF; addr+=2)
	{
		if(smb_type == 0)
		{//NVidia
			data = read_nv_slave_data(addr,0);
		}
		else
		{
			data = read_it_slave_data(addr,0);
		}
		if(data != 0xff)
		{
			//	printf("Found %02X at %02X\n",data,addr);
			devs[device_qty].addr = addr;
			devs[device_qty].data = data;
			device_qty++;
		}
	}
}

void Get_Content(void)
{
	int ch1,ch2;
	
	Block(1,2,78,22,B_WHITE);
	
	//顯示被選擇的裝置資料
	Block(1,2,78,2,B_MAGENTA);
		
	gotoxy(4,2);
	color_printf(B_MAGENTA | F_LIGHT_WHITE,"%d             %2Xh       %02Xh",current_sld,devs[current_sld].addr,devs[current_sld].data);
	
	//畫出橫的數字
	gotoxy(1,3);
	color_printf(B_BROWN | F_WHITE,"   x:  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F            ASCII code   ");
	
	Col_NO(); // 垂直數字
	
	//讀取並顯示資料
	read_spd();
	
	while(1)
	{
		if(kbhit() != 0)
		{
			ch1 = getch();
			if(ch1 == 0) //特殊功能鍵
			{
				ch2 = getch();
				
				switch(ch2)
				{
					case 0x44: // F10 Exit
						clrscr();
						ShowCursor();
						quit(0);
				}
			}
			else if(ch1 == 27) //ESC
			{
				HideCursor();
				return;
			}
		}
	}
}

void read_spd(void)
{
	int i;
	BYTE addr,data,x,y,tmp;
	

	x = 0;
	y = 0;
	
	addr = devs[current_sld].addr;
	for(i = 0; i < 128; i++)
	{
		if(smb_type == 0)
		{//NVidia
			data = read_nv_slave_data(addr,(BYTE)i);
		}
		else
		{
			data = read_it_slave_data(addr,(BYTE)i);
		}
		
		tmp = x * 3+7;
		gotoxy(tmp,(BYTE)(4+y));
		color_printf(B_WHITE | F_BLACK,"%02X",data);
		
		//ASCII code
		gotoxy((BYTE)(63+x),(BYTE)(y+4));
		if(data >= 0x20 && data <= 0x7e)
		{//如果是一般的字元
			color_printf(B_WHITE | F_BLACK,"%c",data);
		}
		else
		{//特殊字元，用.表示
			color_printf(B_WHITE | F_BLACK,".");
		}
		
		x++;
		if(x == 16)
		{
			x=0;
			y++;
		}
	}
	
}

BYTE read_nv_slave_data(BYTE slave_address, BYTE offset)
{
	BYTE temp,tmp;//protocol,
	int timeout = 0;

	// for Nvidia
	write_io_byte((SMB_base+NVIDIA_SMB_STS),NVIDIA_SMB_STS_STATUS);

	//I2C_SMBUS_BYTE_DATA:
	write_io_byte((SMB_base+NVIDIA_SMB_CMD),offset);
	
	write_io_byte((SMB_base+NVIDIA_SMB_ADDR),(BYTE)(slave_address|0x01));

	write_io_byte((SMB_base+NVIDIA_SMB_PRTCL),0x07);

	do{
		Delay_1us(10);
		temp = read_io_byte(SMB_base+NVIDIA_SMB_STS);

	} while (((temp & NVIDIA_SMB_STS_DONE) == 0) && (timeout++ < MAX_TIMEOUT));

	if(timeout > MAX_TIMEOUT)
	{
		return 0xff;
	}
	tmp = read_io_byte(SMB_base+NVIDIA_SMB_DATA);

	return tmp;
}

BYTE read_it_slave_data(BYTE slave_address, BYTE offset)
{
	BYTE temp;
	int timeout=0;
	
	//clear all status bits
	write_io_byte((SMBHSTSTS | SMB_base),0x1E);
	
	// write the offset
	write_io_byte((SMBHSTCMD | SMB_base),(BYTE)offset);
	
	// write the slave address 
	write_io_byte((SMBHSTADD | SMB_base),(BYTE)(slave_address|1));
	
	//Read byte protocol and Start
	write_io_byte((SMBHSTCNT | SMB_base),0x48);
	
	while(1)
	{
		Delay_1us(10);
		temp = read_io_byte(SMB_base | SMBHSTSTS);
		//if((temp & 0x1E) == 0x1E)
		if((temp & 0x42)==0x42)
		{
			break;
		}
		timeout++;
		
		if(timeout > MAX_TIMEOUT)
		{
			return 0xff;
		}
	}
		
	if((temp & 0x1c)==0)
	{//ok
		return read_io_byte((SMBHSTDAT0|SMB_base));
	}
	return 0xff;	
}

BOOL Search_Device( BYTE Classtype,BYTE Subclass1,BYTE Subclass2,WORD *vd,BYTE *Bus, BYTE *Dev, BYTE *Func )
{
	WORD i,j,k;
	BYTE gclass,tp,gsclass;
	WORD vendor,dvc;
	
	for(i = 0; i < 256; i++)
	{
		for(j = 0; j < 32; j++)
		{
			for(k = 0; k < 8; k++)
			{
				if(k == 0)
				{
					tp = read_pci_byte(i,j,k,0x0e) & 0x80;
				}
				vendor = read_pci_word(i,j,k,0x0);
				if(vendor != 0xffff)//If vendor is valid
				{
					dvc = read_pci_word(i,j,k,0x2);
					gclass = read_pci_byte(i,j,k,0x0B);
					if(gclass == Classtype)//If find device
					{
						gsclass = read_pci_byte(i,j,k,0x0A);
						if(gsclass == Subclass1 || gsclass == Subclass2)
						{//Log Bus, Device, Func
							*Bus = (BYTE)i;
							*Dev = (BYTE)j;
							*Func = (BYTE)k;
							*vd = vendor;
							if(vendor == 0x10de)
							{
								if(dvc == 0x52)
								{
									SMB_base = (read_pci_word(bus,dev,func,0x50) & 0xfffe);
								}
							}
							else if(vendor == 0x8086)
							{
								SMB_base = (read_pci_word(bus,dev,func,0x20)& 0xfffe);
							}
							else
							{
								return 0;
							}
							
							return 1;
						}
					}
				}//end of if(vendor != 0xffff)
				if(k == 0 && tp != 0x80)
				{
					break;
				}
			}//end of for(k = 0; k < 8; k++)
		}//end of for(j = 0; j < 32; j++)
	}//end of for(i = 0; i < 256; i++)
	return 0;
}

void Delay_1us( WORD usecs )
{
	WORD ticks=(WORD) (0.596590*(++usecs));
	
	if (ticks==0)
		return;
	
	_asm {
	mov  cx,ticks
	mov  bx,02h
waittrig:
	in   al,41h
	and  al,02h
	cmp  al,bl
	jz   waittrig
	xor  bl,02h
	loop waittrig
	}
}

void Block( BYTE sx,BYTE sy,BYTE ex,BYTE ey,BYTE color )
{
	BYTE x,y;
	
	for(y = sy; y <= ey; y++)
	{
		for(x = sx; x <= ex; x++)
		{
			gotoxy(x,y);
			color_char(' ', color);
		}
	}
}

void Col_NO(void)
{//畫垂直的數字
	int i;
	
	//畫出直的數字
	for(i = 0; i < 8; i++)
	{
		gotoxy(1,(BYTE)(4+i));
		color_printf(B_BROWN | F_WHITE,"  %dx ",i);
	}
}

void tool_bar(int sld)
{
	gotoxy(1,23);
	
	if(sld==0)
	{
		color_printf(B_BLUE | F_LIGHT_WHITE," Enter:View             :Move      F10:Exit                                    ");
		gotoxy(23,23);
		WriteChar(0x18);//
		gotoxy(24,23);
		WriteChar(0x19);//
	}
	else
	{
		color_printf(B_BLUE | F_LIGHT_WHITE,"                            ESC:Return  F10:Exit                         ");
	
	}
}

void show_device(void)
{
	int i,j;
	
	j = 0;
	for(i = 0; i < device_qty; i++)
	{
		gotoxy(4,(BYTE)(2+j));
		color_printf(B_WHITE | F_BLACK,"%d             %2Xh       %02Xh",i,devs[i].addr,devs[i].data);
		j++;
	}
}

void draw_select(void)
{

	if(pre_sld != current_sld)
	{//還原前一個被選到的
		Block(1,(BYTE)(pre_sld+2),78,(BYTE)(pre_sld+2),B_WHITE);
		
		gotoxy(4,(BYTE)(2+pre_sld));
		color_printf(B_WHITE | F_BLACK,"%d             %2Xh       %02Xh",pre_sld,devs[pre_sld].addr,devs[pre_sld].data);
	}
	
	Block(1,(BYTE)(current_sld+2),78,(BYTE)(current_sld+2),B_MAGENTA);

	gotoxy(4,(BYTE)(2+current_sld));
	color_printf(B_MAGENTA | F_WHITE,"%d             %2Xh       %02Xh",current_sld,devs[current_sld].addr,devs[current_sld].data);

}

void quit( int errorlevel )
{//結束程式
	printf("Error level = %d",errorlevel);
	if(errorlevel != 0)
	{
		puts("\a");
	}
	exit(errorlevel);
}
