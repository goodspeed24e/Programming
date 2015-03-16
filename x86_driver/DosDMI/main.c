#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "func.h"
#include "main.h"

int GetProcessorString(WORD no);

void main(void)
{
	int ch,sta;
	
	memset(tp_Addrs,0,sizeof(tp_Addrs));
	
	HideCursor();
	
	//進入大真實模式
	into_PT_mode();
	
	Load_String();
	FindEntry();
	ShowTtile();
	ShowHotKey(0);

	ShowTypes();
	while(1)
	{
		ch = getch();
		if(ch == 27)
		{
			clrscr();
			ShowCursor();
			break;
		}
		else if(ch == 'T' || ch == 't')
		{//使用者輸入想要看的type
			InputType();
			goto display;
				
		}
		else if(ch == 0)
		{
			gotoxy(0,24);
			color_printf(B_BROWN | F_WHITE,"                                                                                ");
			ch = getch();
			if(ch == 0x48)
			{//上
				goto display;
			}
			else if(ch == 0x50)
			{//下
				goto display;
			}
			else if(ch == 0x49)
			{//pg up
				Dec_ID();
				goto display;
			}
			else if(ch == 0x51)
			{//pg dn
				Inc_ID();
				
display:
				ShowTtile();
				ShowHotKey(0);
				sta = ShowTypes();
				if(sta)
				{
					goto display;
				}
			}
		}
	}
	//離開大真實模示
	into_RL_mode();
	
}

void ShowTtile(void)
{
	int i,len,start;
	char buf[81],title[80];
	
	clrscr();
	memset(title,0,sizeof(title));
	if(tp_Addrs[type_sld][0]==0)
	{
		sprintf(title,"DOSDMI - %s",TableName[0]);
	}
	else if(tp_Addrs[type_sld][0] != 32)
	{
		if(tp_Addrs[type_sld][0] == 128)
		{
			strcpy(title,"DOSDMI - type: 127 End-of-Table");
		}
		else if(tp_Addrs[type_sld][0] == 127)
		{
			sprintf(title,"DOSDMI - type: %ld %s",tp_Addrs[type_sld][0]-1,TableName[41]);
		}
		else if(tp_Addrs[type_sld][0] >= 1 && tp_Addrs[type_sld][0] <= 40)
		{
			sprintf(title,"DOSDMI - type: %ld %s",tp_Addrs[type_sld][0]-1,TableName[tp_Addrs[type_sld][0]]);
		}
		else
		{
			sprintf(title,"DOSDMI - OEM type: %ld",tp_Addrs[type_sld][0]-1);
		}
	}
	
	memset(buf,0,sizeof(buf));
	memset(buf,0x20,sizeof(buf)-1);
	len = strlen(title);
	start = 40-(len / 2);
	if((len%2) != 0)
	{
		start--;
	}
	for(i = 0; i < len; i++)
	{
		buf[start+i] = title[i];
	}
	
	gotoxy(0,0);
	color_printf(B_BLUE | F_YELLOW,"%s",buf);
	gotoxy(0,1);
}

void ShowHotKey(int sld)
{
	BYTE x,y;
	
	x = getx();
	y = gety();
	
	gotoxy(0,23);
	switch(sld)
	{
		case 0:
			color_printf(B_BROWN | F_WHITE," ESC:Quit  PgUp:Pre-type  PgDown:Next-type                 'T':Input Type       ");
			break;
		case 1:
			color_printf(B_BROWN | F_WHITE," ESC:Quit  PgUp:Pre-type  PgDown:Next-type    :more info.  'T':Input Type       ");
			gotoxy(44,23);
			WriteChar(0x18);
			gotoxy(45,23);
			WriteChar(0x19);
			break;
	}
	
	gotoxy(x,y);
}

void Inc_ID(void)
{
	if(type_sld == (tp_cnt-1))
	{
		type_sld = 0;
	}
	else
	{
		type_sld++;
	}
}

void Dec_ID(void)
{
	if(type_sld==0)
	{
		type_sld = tp_cnt-1;
	}
	else
	{
		type_sld--;
	}
}

int CheckPosi(int more)
{
	int ch,flag=0;
	
	if(gety() == 22 || more != 0)
	{
		color_printf(B_GRAY | F_LIGHT_BLUE,"  .....Press SPACE to show more.....");
		while(1)
		{
			ch = getch();
			if(ch==0)
			{
				ch = getch();
				if(ch == 0x48)
				{//上
					flag = 2;
					break;
				}
				else if(ch == 0x50)
				{//下
					flag = 3;
					break;
				}
				else if(ch == 0x49)
				{//pg up
					Dec_ID();
					flag = 4;
					return flag;
				}
				else if(ch == 0x51)
				{//pg dn
					Inc_ID();
					flag = 5;
					return flag;
				}
			}
			else if(ch == 27)
			{
				return 1;
			}
			else if(ch == 'T' || ch == 't')
			{//使用者輸入想要看的type
				if(InputType()==0)
				{
					return 5;
				}
			}
			else if(ch == ' ')
			{
				break;
			}
		}
		ShowTtile();
		ShowHotKey(1);
	}
	return flag;
}

int ShowTypes(void)
{
	int sta=0,val;
	
	EntryAddr = tp_Addrs[type_sld][1];
	//data_buf, data_len
	val = (int)(tp_Addrs[type_sld][0]);
	val--;
	switch(val)
	{
		case -1:
			ReportEntry();
			break;
		case 0:
			sta = ReportTp0();
			break;
		case 1:
			sta = ReportTp1();
			break;
		case 2:
			sta = ReportTp2();
			break;
		case 3:
			sta = ReportTp3();
			break;
		case 4:
			sta = ReportTp4();
			break;
		case 5:
			sta = ReportTp5();
			break;
		case 6:
			sta = ReportTp6();
			break;
		case 7:
			sta = ReportTp7();
			break;
		case 8:
			sta = ReportTp8();
			break;
		case 9:
			sta = ReportTp9();
			break;
		case 10:
			sta = ReportTp10();
			break;
		case 11:
			sta = ReportTp11();
			break;
		case 12:
			sta = ReportTp12();
			break;
		case 13:
			sta = ReportTp13();
			break;
		case 14:
			sta = ReportTp14();
			break;
		case 15:
			sta = ReportTp15();
			break;
		case 16:
			sta = ReportTp16();
			break;
		case 17:
			sta = ReportTp17();
			break;
		case 18:
			sta = ReportTp18();
			break;
		case 19:
			sta = ReportTp19();
			break;
		case 20:
			sta = ReportTp20();
			break;
		case 21:
			sta = ReportTp21();
			break;
		case 22:
			sta = ReportTp22();
			break;
		case 23:
			sta = ReportTp23();
			break;
		case 24:
			sta = ReportTp24();
			break;
		case 25:
			sta = ReportTp25();
			break;
		case 26:
			sta = ReportTp26();
			break;
		case 27:
			sta = ReportTp27();
			break;
		case 28:
			sta = ReportTp28();
			break;
		case 29:
			sta = ReportTp29();
			break;
		case 30:
			sta = ReportTp30();
			break;
		case 32:
			sta = ReportTp32();
			break;
		case 33:
			sta = ReportTp33();
			break;
		case 34:
			sta = ReportTp34();
			break;
		case 35:
			sta = ReportTp35();
			break;
		case 36:
			sta = ReportTp36();
			break;
		case 37:
			sta = ReportTp37();
			break;
		case 38:
			sta = ReportTp38();
			break;
		case 39:
			sta = ReportTp39();
			break;
		case 126:
			ReportTp126();
			break;
		case 127:
			ReportEnd();
			break;
		default:
			ReportOEM();
			break;
	}
	return sta;
}

void ReportEntry(void)
{
	WORD dd;
	
	Read_Entry();
	
	printf(" Anchor String                 : ");
	color_printf(F_CYAN,"%c%c%c%c\n",data_buf[0],data_buf[1],data_buf[2],data_buf[3]);
	printf(" Entry Point Structure Checksum: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[4]);
	printf(" Entry Point Length            : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
	printf(" SMBIOS version                : ");
	color_printf(F_CYAN,"%d.%d\n",data_buf[6],data_buf[7]);
	printf(" Maximum Structure Size        : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[9],data_buf[8]);
	printf(" Entry Point Revision          : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0xa]);
	printf(" Formatted Area                : ");
	color_printf(F_CYAN,"0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",data_buf[0xb],data_buf[0xc],data_buf[0xd],data_buf[0xe],data_buf[0xf]);
	printf(" Intermediate anchor string    : ");
	color_printf(F_CYAN,"%c%c%c%c%c\n",data_buf[0x10],data_buf[0x11],data_buf[0x12],data_buf[0x13],data_buf[0x14]);
	printf(" Intermediate Checksum         : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0x15]);
	
	printf(" Structure Table Length        : ");
	dd = data_buf[0x17];
	dd<<=8;
	dd |= data_buf[0x16];
	color_printf(F_CYAN,"%d(0x%02X%02X)\n",dd,data_buf[0x17],data_buf[0x16]);
	
	printf(" Structure Table Address       : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0x1b],data_buf[0x1a],data_buf[0x19],data_buf[0x18]);
	
	dd = data_buf[0x1d];
	dd<<=8;
	dd |= data_buf[0x1c];
	
	printf(" Number of SMBIOS Structure    : ");
	color_printf(F_CYAN,"%d(0x%02X%02X)\n",dd,data_buf[0x1d],data_buf[0x1c]);
	printf(" SMBIOS BCD Revision           : ");
	color_printf(F_CYAN,"%d.%d(0x%02X)",(BYTE)(data_buf[0x1e]>>4),data_buf[0x1e] & 0x0F,data_buf[0x1e]);
}

int ReportTp0(void)
{
	int j,k,flag;
	DWORD dd;
	
	if(FindTable(0) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 0");
		return 0;
	}

	printf("Type                         : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                       : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                       : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("BIOS Vendor                  : ");
	GetAttachedString(SMB_string,data_buf[4]); //讀取字串
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("BIOS Version                 : ");
	GetAttachedString(SMB_string,data_buf[5]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[5]);
	
	printf("BIOS Starting Address Segment: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[7],data_buf[6]);
	
	printf("BIOS Release Date            : ");
	GetAttachedString(SMB_string,data_buf[8]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[8]);
	
	printf("BIOS ROM Size                : ");
	color_printf(F_CYAN,"%ldKB (0x%02X)\n",(data_buf[9]+1)*64,data_buf[9]);
	
	printf("BIOS Characteristics         : ");
	color_printf(F_CYAN,"%02X %02X %02X %02X %02X %02X %02X %02X [HEX];MSB->LSB\n",data_buf[0x11],data_buf[0x10],data_buf[0xf],data_buf[0xe],data_buf[0xd],data_buf[0xc],data_buf[0xb],data_buf[0xa]);
	
	for(k = 0; k < 2; k++)
	{
		dd = data_buf[0xa+k*4];
		for(j = 3; j >= 0; j--)
		{
			dd <<= 8;
			dd |= data_buf[0xa+j+k*4];
		}
	
		for(j = 0; j < 32; j++)
		{
			if((dd & 0x1) == 0x1)
			{
				color_printf(F_CYAN," bit%d: %s\n",j+k*32,GetString(0,1,j+k*32));
				flag = CheckPosi(0);
				if(flag == 1)
				{//ESC
					return 0;
				}
				else if(flag >= 4 || flag == 2)
				{//上或page up/down
					return flag;
				}
			}
			dd >>= 1;
		}
	}
	
	if(data_buf[1] >= 0x13)
	{
		printf("BIOS Characteristics Extension Byte 1: ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x12]);
		
		dd = data_buf[0x12];

		for(j = 0; j < 8; j++)
		{
			if((dd & 0x1) == 0x1)
			{
				color_printf(F_CYAN," bit%d: %s\n",j,GetString(0,2,j));
				flag = CheckPosi(0);
				if(flag == 1)
				{//ESC
					return 0;
				}
				else if(flag >= 4 || flag == 2)
				{//上或page up/down
					return flag;
				}
			}
			dd >>= 1;
		}
		
	}
	
	if(data_buf[1] >= 0x14)
	{
		printf("BIOS Characteristics Extension Byte 2: ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x13]);
		dd = data_buf[0x13];
	
		for(j = 0; j < 8; j++)
		{
			if((dd & 0x1) == 0x1)
			{
				color_printf(F_CYAN," bit%d: %s\n",j,GetString(0,3,j));
				flag = CheckPosi(0);
				if(flag == 1)
				{//ESC
					return 0;
				}
				else if(flag >= 4 || flag == 2)
				{//上或page up/down
					return flag;
				}
			}
			dd >>= 1;
		}
		
	}
	
	if(data_buf[1] >= 0x15)
	{
		printf("System BIOS Release                  : ");
		color_printf(F_CYAN,"%d.%d\n",data_buf[0x14],data_buf[0x15]);
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上下或page up/down
			return flag;
		}
	}
	return 0;
}

int ReportTp1(void)
{
	if(FindTable(1) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 1");
		return 0;
	}
	
	printf("Type         : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length       : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle       : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Manufacturer : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Product Name : ");
	GetAttachedString(SMB_string,data_buf[5]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[5]);
	
	printf("Version      : ");
	GetAttachedString(SMB_string,data_buf[6]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[6]);
	
	printf("Serial Number: ");
	GetAttachedString(SMB_string,data_buf[7]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[7]);
	
	printf("UUID         : ");
	color_printf(F_CYAN,"%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X [HEX]\n",data_buf[8],data_buf[9],data_buf[10],data_buf[11],data_buf[12],data_buf[13],data_buf[14],data_buf[15],data_buf[16],data_buf[17],data_buf[18],data_buf[19],data_buf[20],data_buf[21],data_buf[22],data_buf[23]);
	
	printf("Wake-up Type : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(1,1,data_buf[0x18]),data_buf[0x18]);
		
	if(smb_ver >= 2.4)
	{
		printf("SKU Number   : ");
		GetAttachedString(SMB_string,data_buf[0x19]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x19]);

		printf("Family       : ");
		GetAttachedString(SMB_string,data_buf[0x1a]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x1a]);
	}
		
	return 0;
}

int ReportTp2(void)
{
	int j,flag;
	WORD dd;
	
	if(FindTable(2) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 2");
		return 0;
	}
	
	printf("Type               : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length             : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle             : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Manufacturer       : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Product Name       : ");
	GetAttachedString(SMB_string,data_buf[5]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[5]);
	
	printf("Version            : ");
	GetAttachedString(SMB_string,data_buf[6]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[6]);
	
	printf("Serial Number      : ");
	GetAttachedString(SMB_string,data_buf[7]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[7]);
	
	printf("Asset Tag          : ");
	GetAttachedString(SMB_string,data_buf[8]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[8]);
	
	printf("Feature Flags      : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[9]);
	
	dd = data_buf[9];
	for(j = 0; j < 5; j++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN," bit%d: %s\n",j,GetString(2,1,j));
			flag = CheckPosi(0);
			if(flag == 1)
			{//ESC
				return 0;
			}
			else if(flag >= 4 || flag == 2)
			{//上下或page up/down
				return flag;
			}
		}
		dd >>= 1;
	}
	
	if(data_buf[1] >= 0x0a)
	{
		printf("Location in Chassis: ");
		GetAttachedString(SMB_string,data_buf[0xa]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0xa]);
	}

	if(data_buf[1] >= 0x0b)
	{
		printf("Chassis Handle     : ");
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xc],data_buf[0xb]);
	}
	
	if(data_buf[1] >= 0x0d)
	{
		printf("Board Type         : ");
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(2,2,data_buf[0xd]),data_buf[0xd]);
	}
	
	if(data_buf[1] >= 0x0e)
	{
		printf("Number of Contained Object Handles:");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0xe]);
	}
	
	for(j = 0; j < data_buf[0xe]; j++)
	{
		color_printf(F_CYAN," Contained Object Handle(%d) - ",j+1);
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x10+j*2],data_buf[0xf+j*2]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 2)
		{//上下或page up/down
			return flag;
		}
	}
		
	return 0;
}

int ReportTp3(void)
{
	int j,k,flag;
	
	if(FindTable(3) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 3");
		return 0;
	}
	
	printf("Type              : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length            : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle            : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Manufacturer      : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Type              : ");
	if((data_buf[5] & 0x80) == 0x80)
	{
		color_printf(F_CYAN,"Chassis lock present(0x%02X)\n",data_buf[5]);
	}
	else
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(3,1,data_buf[5]),data_buf[5]);
	}
	
	printf("Version           : ");
	GetAttachedString(SMB_string,data_buf[6]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[6]);
	
	printf("Serial Number     : ");
	GetAttachedString(SMB_string,data_buf[7]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[7]);
	
	printf("Asset Tag Number  : ");
	GetAttachedString(SMB_string,data_buf[8]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[8]);
	
	if(smb_ver >= 2.1)
	{
		printf("Boot-up State     : ");
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(3,2,data_buf[9]),data_buf[9]);
		
		printf("Power Supply State: ");
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(3,2,data_buf[0xa]),data_buf[0xa]);
	
		printf("Thermal State     : ");
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(3,2,data_buf[0xb]),data_buf[0xb]);
	
		printf("Security State    : ");
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(3,3,data_buf[0xc]),data_buf[0xc]);
	}
	
	if(smb_ver >= 2.3)
	{
		printf("OEM-defined                    : ");
		color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0x10],data_buf[0xf],data_buf[0xe],data_buf[0xd]);
	
		printf("Height                         : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x11]);
	
		printf("Number of Power Cords          : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x12]);
	
		printf("Contained Element Count        : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x13]);
	
		printf("Contained Element Record Length: ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x14]);
	
		for(j = 0; j < data_buf[0x13]; j++)
		{
			for(k = 0; k < data_buf[0x14]; k++)
			{
				printf("Contained Elements(%d) - ",((j*255)+k)+1);
				color_printf(F_CYAN,"0x%02X\n",data_buf[0x15+j*data_buf[0x14]+k]);
		
				flag = CheckPosi(0);
				if(flag == 1)
				{//ESC
					return 0;
				}
				else if(flag >= 2)
				{//上下或page up/down
					return flag;
				}
			}
		}
	}
	
	return 0;
}

int ReportTp4(void)
{
	int j,flag;
	WORD dd;
	
	if(FindTable(4) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 4");
		return 0;
	}
	
	printf("Type                  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Socket Designation    : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Processor Type        : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(4,1,data_buf[5]),data_buf[5]);
	
	printf("Processor family      : ");
	j = GetProcessorString(data_buf[6]);
	
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(4,2,j),data_buf[6]);
	
	printf("Processor Manufacturer: ");
	GetAttachedString(SMB_string,data_buf[7]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[7]);
	
	printf("Processor ID          : ");
	color_printf(F_CYAN," %02X %02X %02X %02X %02X %02X %02X %02X [HEX]; MSB->LSB\n",data_buf[8],data_buf[9],data_buf[0xa],data_buf[0xb],data_buf[0xc],data_buf[0xd],data_buf[0xe],data_buf[0xf]);
	
	printf("Processor Version     : ");
	GetAttachedString(SMB_string,data_buf[0x10]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x10]);

	printf("Voltage               : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0x11]);
	
	dd = data_buf[0x11];
	for(j = 0; j < 4; j++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN," bit%d: %s\n",j,GetString(4,3,j));
		}
		dd >>= 1;
	}
		
	printf("External Clock        : ");
	dd = data_buf[0x13];
	dd <<= 8;
	dd |= data_buf[0x12];
	color_printf(F_CYAN,"%dMhz (0x%02X%02X)\n",dd,data_buf[0x13],data_buf[0x12]);
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	printf("Max Speed             : ");
	dd = data_buf[0x15];
	dd <<= 8;
	dd |= data_buf[0x14];
	color_printf(F_CYAN,"%dMHz (0x%02X%02X)\n",dd,data_buf[0x15],data_buf[0x14]);
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	printf("Current Speed         : ");
	dd = data_buf[0x17];
	dd <<= 8;
	dd |= data_buf[0x16];
	color_printf(F_CYAN,"%dMHz (0x%02X%02X)\n",dd,data_buf[0x17],data_buf[0x16]);
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	printf("Status                : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0x18]);
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	color_printf(F_CYAN," bit7: Reserved\n");
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
		
	dd = data_buf[0x18] & 0x40;
	if(dd == 0x40)
	{
		color_printf(F_CYAN," bit6: CPU Socked Populated\n");
	}
	else
	{
		color_printf(F_CYAN," bit6: CPU Socked Unopulated\n");
	}
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	color_printf(F_CYAN," bit5-3: Reserved\n");
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	dd = data_buf[0x18] & 0x07;
	switch(dd)
	{
		case 0:
			color_printf(F_CYAN," bit2-0: CPU Status - Unknown\n");
			break;
		case 1:
			color_printf(F_CYAN," bit2-0: CPU Status - CPU Enable\n");
			break;
		case 2:
			color_printf(F_CYAN," bit2-0: CPU Status - CPU Disabled by User via BIOS Setup\n");
			break;
		case 3:
			color_printf(F_CYAN," bit2-0: CPU Status - CPU Disabled by BIOS(POST Error)\n");
			break;
		case 4:
			color_printf(F_CYAN," bit2-0: CPU Status - CPU is Idle, waiting to be enabled\n");
			break;
		case 5:
		case 6:
			color_printf(F_CYAN," bit2-0: CPU Status - Reserved\n");
			break;
		case 7:
			color_printf(F_CYAN," bit2-0: CPU Status - Other\n");
			break;
	}
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	printf("Processor Upgrade     : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(4,4,data_buf[0x19]),data_buf[0x19]);
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	if(smb_ver >= 2.1)
	{
		printf("L1 Cache Handle       : ");
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x1b],data_buf[0x1a]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上下或page up/down
			return flag;
		}
	
		printf("L2 Cache Handle       : ");
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x1d],data_buf[0x1c]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上下或page up/down
			return flag;
		}
		
		printf("L3 Cache Handle       : ");
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x1f],data_buf[0x1e]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上下或page up/down
			return flag;
		}
	}
	
	if(smb_ver >= 2.3)
	{
		printf("Serial Number         : ");
		GetAttachedString(SMB_string,data_buf[0x20]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x20]);
	
		printf("Asset Tag             : ");
		GetAttachedString(SMB_string,data_buf[0x21]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x21]);
	
		printf("Part Number           : ");
		GetAttachedString(SMB_string,data_buf[0x22]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x22]);
	}
	
	if(smb_ver >= 2.5)
	{
		printf("Core Count               : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x23]);
	
		printf("Core Enable              : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x24]);
	
		printf("Thread Count             : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x25]);
	
		printf("Processor Characteristics: ");
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x27],data_buf[0x26]);
		
		dd = data_buf[0x27];
		dd <<= 8;
		dd |= data_buf[0x26];
		for(j = 0; j < 3; j++)
		{
			if((dd & 0x1) == 0x1)
			{
				color_printf(F_CYAN," bit%d: %s\n",j,GetString(4,5,j));
				
				flag = CheckPosi(0);
				if(flag == 1)
				{//ESC
					return 0;
				}
				else if(flag >= 4 || flag == 2)
				{//上下或page up/down
					return flag;
				}
	
			}
			dd >>= 1;
		}
	}
	
	if(smb_ver >= 2.6)
	{
		printf("Processor Family 2   : ");
		dd = data_buf[0x29];
		dd <<= 8;
		dd |= data_buf[0x28];
		j = GetProcessorString(dd);
		color_printf(F_CYAN,"%s (0x%02X%02X)\n",GetString(4,2,j),data_buf[0x29],data_buf[0x28]);
		//buf[26]=1;
		//WriteStrToMemory(buf);
	}
	
	return 0;
}

int ReportTp5(void)
{
	int i,j,flag;
	WORD dd;
	
	if(FindTable(5) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 5");
		return 0;
	}
	
	printf("Type                       : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                     : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                     : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Error Detecting Method     : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(5,1,data_buf[4]),data_buf[4]);
	
	printf("Error Correcting Capability:\n");
	dd = data_buf[5];
	for(i = 0; i < 5; i++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN," %s (0x%02X)\n",GetString(5,2,i),data_buf[5]);
		}
		dd >>= 1;
	}
	
	printf("Support Interleave         : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[6]);
	
	dd = data_buf[6];
	for(j = 0; j < 7; j++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN," %s\n",GetString(5,3,j+1));
		}
		dd >>= 1;
	}
	
	printf("Current Interleave         : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(5,3,data_buf[7]),data_buf[7]);
	
	printf("Maximum Memory Module Size : ");
	color_printf(F_CYAN,"%02X\n",data_buf[8]);
	
	printf("Supported Speeds             :\n");
	dd = data_buf[9];
	for(i = 0; i < 5; i++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN," %s (0x%02X%02X)\n",GetString(5,4,i),data_buf[0xa],data_buf[9]);
		}
		dd >>= 1;
	}

	printf("Supported Memory Type      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xc],data_buf[0xb]);
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	flag = 0;
	printf("Memory Module Voltage      : ");
	if((data_buf[0xd] & 0x7) == 1)
	{
		color_printf(F_CYAN,"5V (0x%02X)\n",data_buf[0xd]);
		flag = 1;
	}
	else if((data_buf[0xd] & 0x7) == 2)
	{
		color_printf(F_CYAN,"3.3V (0x%02X)\n",data_buf[0xd]);
		flag = 1;
	}
	else if((data_buf[0xd] & 0x7) == 4)
	{
		color_printf(F_CYAN,"2.9V (0x%02X)\n",data_buf[0xd]);
		flag = 1;
	}
	
	if(flag==0)
	{
		color_printf(F_CYAN,"(0x%02X)\n",data_buf[0xd]);
	}
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	printf("Number of Associated Memory Slots: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0xe]);
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	for(j = 0; j < data_buf[0xe] ;j++)
	{
		printf("Memory Module Configuration Handles(%d) - ",j+1);
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x10+j*2],data_buf[0xf+j*2]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上下或page up/down
			return flag;
		}
	}
	
	//if(data_buf[1] >= (16+2*data_buf[0xe]))
	if(smb_ver >= 2.1)
	{
		printf("Enabled Error Correcting Capabilities: ");
		
		color_printf(F_CYAN,"(0x%02X)\n",data_buf[15+2*data_buf[0xe]]);
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上下或page up/down
			return flag;
		}
		
		dd = data_buf[15+2*data_buf[0xe]];
		for(i = 0; i < 6; i++)
		{
			if((dd & 0x1) == 0x1)
			{
				color_printf(F_CYAN," %s\n",GetString(5,2,i));
			}
			dd >>= 1;
		}
	}
	return 0;
}

int ReportTp6(void)
{
	int i,flag;
	WORD dd;
	char buf[30];
	
	if(FindTable(6) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 6");
		return 0;
	}
	
	printf("Type               : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length             : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle             : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Socket Designation : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Bank Connections   : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
	
	printf("Current Speed      : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[6]);
	
	flag = 0;
	printf("Current Memory Type: ");
	dd = data_buf[8];
	dd <<= 8;
	dd |= data_buf[7];
	for(i = 0; i < 11; i++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN,"%s (0x%04X)\n",GetString(6,1,i),dd);
			flag = 1;
			break;
		}
		dd >>= 1;
	}
	
	if(flag==0)
	{
		color_printf(F_CYAN,"(0x%04X)\n",dd);
	}
	
	printf("Installed Size     : ");
	if((data_buf[9] & 0x80) == 0x80)
	{
		strcpy(buf,"double-bank");
	}
	else
	{
		strcpy(buf,"single-bank");
	}
	dd = data_buf[9] & 0x7F;
	switch(dd)
	{
		case 0x7D:
			color_printf(F_CYAN,"%s (0x%02X) - %s\n",GetString(6,2,0),data_buf[9],buf);
			break;
		case 0x7E:
			color_printf(F_CYAN,"%s (0x%02X) - %s\n",GetString(6,2,1),data_buf[9],buf);
			break;
		case 0x7F:
			color_printf(F_CYAN,"%s (0x%02X) - %s\n",GetString(6,2,2),data_buf[9],buf);
			break;
		default:
			color_printf(F_CYAN,"Size 0x%02X - %s\n",data_buf[9],buf);
			break;
	}
	
	
	printf("Enabled Size       : ");
	if((data_buf[0xa] & 0x80) == 0x80)
	{
		strcpy(buf,"double-bank");
	}
	else
	{
		strcpy(buf,"single-bank");
	}
	dd = data_buf[0xa] & 0x7F;
	switch(dd)
	{
		case 0x7D:
			color_printf(F_CYAN,"%s (0x%02X) - %s\n",GetString(6,2,0),data_buf[0xa],buf);
			break;
		case 0x7E:
			color_printf(F_CYAN,"%s (0x%02X) - %s\n",GetString(6,2,1),data_buf[0xa],buf);
			break;
		case 0x7F:
			color_printf(F_CYAN,"%s (0x%02X) - %s\n",GetString(6,2,2),data_buf[0xa],buf);
			break;
		default:
			color_printf(F_CYAN,"Size 0x%02X - %s\n",data_buf[0xa],buf);
			break;
	}

	printf("Error Status       : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0xb]);
		
	if((data_buf[0xb] & 0x4) == 0x4)
	{
		color_printf(F_CYAN," Error status information obtained from event log\n");
	}
		
	if((data_buf[0xb] & 0x2) == 0x2)
	{
		color_printf(F_CYAN," Correctable errors received from module\n");
	}
		
	if((data_buf[0xb] & 0x1) == 0x1)
	{
		color_printf(F_CYAN," Uncorrectable errors received from module\n");
	}
	return 0;
}

int ReportTp7(void)
{
	int i,flag;
	WORD dd;
	
	if(FindTable(7) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 7");
		return 0;
	}
	
	printf("Type                 : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length               : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle               : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Socket Designation   : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Cache Configuration  : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[6],data_buf[5]);
	
	if((data_buf[6] & 0x3)==0)
	{
		color_printf(F_CYAN," bit9-8: Operational Mode - Write through\n");
	}
	else if(data_buf[6]==0x1)
	{
		color_printf(F_CYAN," bit9-8: Operational Mode - Write Back\n");
	}
	else if(data_buf[6]==0x2)
	{
		color_printf(F_CYAN," bit9-8: Operational Mode - Varies with Memory Adress\n");
	}
	else
	{
		color_printf(F_CYAN," bit9-8: Operational Mode - Unknown\n");
	}
		
	if((data_buf[5] & 0x80)==0)
	{
		color_printf(F_CYAN," bit7: Disable\n");
	}
	else
	{
		color_printf(F_CYAN," bit7: Enable\n");
	}
		
	if((data_buf[5] & 0x60)==0)
	{
		color_printf(F_CYAN," bit6-5: Location - Internal\n");
	}
	else if((data_buf[5] & 0x60)==0x20)
	{
		color_printf(F_CYAN," bit6-5: Location - External\n");
	}
	else if((data_buf[5] & 0x60)==0x40)
	{
		color_printf(F_CYAN," bit6-5: Location - Resvered\n");
	}
	else
	{
		color_printf(F_CYAN," bit6-5: Location - Unknown\n");
	}
	
	color_printf(F_CYAN," bit4: Reserved\n");
		
	if((data_buf[5] & 0x8)==0)
	{
		color_printf(F_CYAN," bit3: Cache Socketed - Not Socketed\n");
	}
	else
	{
		color_printf(F_CYAN," bit3: Cache Socketed - Socketed\n");
	}
		
	color_printf(F_CYAN," bit2-0: Cache Level\n");
	
	printf("Maximum Cache Size   : ");
	dd = data_buf[8];
	dd <<= 8;
	dd |= data_buf[7];
	if((data_buf[8] & 0x80) == 0x80)
	{
		color_printf(F_CYAN,"64K granularity - 0x%04X in granularity\n",dd&0x7fff);
	}
	else
	{
		color_printf(F_CYAN,"1K granularity - 0x%04X in granularity\n",dd&0x7fff);
	}
	
	printf("Installed Size       : ");
	dd = data_buf[0xa];
	dd <<= 8;
	dd |= data_buf[9];
	if((data_buf[0xa] & 0x80) == 0x80)
	{
		color_printf(F_CYAN,"64K granularity - 0x%04X in granularity\n",dd&0x7fff);
	}
	else
	{
		color_printf(F_CYAN,"1K granularity - 0x%04X in granularity\n",dd&0x7fff);
	}
	
	printf("Supported SRAM Type  : ");
	dd = data_buf[0xb];
	for(i = 0; i < 7; i++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN,"%s (0x%02X%02X)\n",GetString(7,1,i),data_buf[0xc],data_buf[0xb]);
			
			flag = CheckPosi(0);
			if(flag == 1)
			{//ESC
				return 0;
			}
			else if(flag >= 4 || flag == 2)
			{//上下或page up/down
				return flag;
			}
		}
		dd >>= 1;
	}
	
	printf("Current SRAM Type    : ");
	dd = data_buf[0xd];
	for(i = 0; i < 7; i++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN,"%s (0x%02X%02X)\n",GetString(7,1,i),data_buf[0xe],data_buf[0xd]);
			break;
		}
		dd >>= 1;
	}
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上下或page up/down
		return flag;
	}
	
	
	if(smb_ver >= 2.1)
	{
		printf("Cache Speed          : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0xf]);

		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上下或page up/down
			return flag;
		}

		printf("Error Correction Type: ");
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(7,2,data_buf[0x10]),data_buf[0x10]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上下或page up/down
			return flag;
		}
		
		printf("System Cache Type    : ");
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(7,3,data_buf[0x11]),data_buf[0x11]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上下或page up/down
			return flag;
		}
		
		printf("Associativity        : ");
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(7,4,data_buf[0x12]),data_buf[0x12]);
	}
	return 0;
}

int ReportTp8(void)
{
	if(FindTable(8) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 8");
		return 0;
	}
	
	printf("Type                         : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                       : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                       : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Internal Reference Designator: ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Internal Connector Type      : ");
	if(data_buf[5] <= 0x22)
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(8,1,data_buf[5]),data_buf[5]);
	}
	else if(data_buf[5] >= 0xA0 && data_buf[5] <= 0xA4)
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(8,1,data_buf[5]-126),data_buf[5]);
	}
	else
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(8,1,39),data_buf[5]);
	}
	
	printf("External Reference Designator: ");
	GetAttachedString(SMB_string,data_buf[6]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[6]);
	
	printf("External Connector Type      : ");
	if(data_buf[7] <= 0x22)
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(8,1,data_buf[7]),data_buf[7]);
	}
	else if(data_buf[7] >= 0xA0 && data_buf[7] <= 0xA4)
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(8,1,data_buf[7]-126),data_buf[7]);
	}
	else
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(8,1,39),data_buf[7]);
	}
	
	printf("Port Type                    : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[8]);
	if(data_buf[8] <= 0x22)
	{
		color_printf(F_CYAN," %s\n",GetString(8,2,data_buf[8]));
	}
	else if(data_buf[8] >= 0xA0 && data_buf[8] <= 0xA1)
	{
		color_printf(F_CYAN," %s\n",GetString(8,2,data_buf[8]-127));
	}
	else
	{
		color_printf(F_CYAN," %s\n",GetString(8,2,35));
	}
	
	return 0;
}

int ReportTp9(void)
{
	int j;
	WORD dd;
	
	if(FindTable(9) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 9");
		return 0;
	}
	
	printf("Type                 : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length               : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle               : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Slot Designation     : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Slot Type            : ");
	if(data_buf[5] <= 0x13)
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(9,1,data_buf[5]),data_buf[5]);
	}
	else
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(9,1,data_buf[5]-140),data_buf[5]);
	}
	
	printf("Slot Data Bus Width  : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(9,2,data_buf[6]),data_buf[6]);
	
	printf("Current Usage        : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(9,3,data_buf[7]),data_buf[7]);
	
	printf("Slot Length          : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(9,4,data_buf[8]),data_buf[8]);
	
	printf("Slot ID              : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xa],data_buf[9]);
	
	printf("Slot Characteristics1: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0xb]);
		
	dd = data_buf[0xb];
	for(j = 0; j < 8; j++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN," bit%d: %s\n",j,GetString(9,5,j));
		}
		dd >>= 1;
	}
	
	if(smb_ver >= 2.1)
	{
		printf("Slot Characteristics2: ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0xc]);
		
		dd = data_buf[0xc];
		for(j = 0; j < 3; j++)
		{
			if((dd & 0x1) == 0x1)
			{
				color_printf(F_CYAN," bit%d: %s\n",j,GetString(9,6,j));
			}
			dd >>= 1;
		}
	}
	
	if(smb_ver >= 2.6)
	{
		
		printf("Segment Group Number  : ");
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xe],data_buf[0xd]);
		
		printf("Bus Number            : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0xf]);
		
		printf("Device/Function Number: ");
		color_printf(F_CYAN,"Device:0x%02X Function:0x%X (0x%02X)\n",data_buf[0x10] >> 2,data_buf[0x10] & 0x3, data_buf[0x10]);
		
	}
	
	return 0;
}

int ReportTp10(void)
{
	int i,cnt;
	
	if(FindTable(10) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 10");
		return 0;
	}
	
	printf("Type  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length: ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	cnt = (data_buf[1]-4)/2;
	for(i = 0; i < cnt; i++)
	{
		printf("Device %d Type - ",i+1);
		if((data_buf[4+i] & 0x80) == 0x80)
		{
			color_printf(F_CYAN,"%s (0x%02X)- Device Enable\n",GetString(10,1,data_buf[4+i] & 0x7f),data_buf[4+i]);
		}
		else
		{
			color_printf(F_CYAN,"%s (0x%02X)- Device Disable\n",GetString(10,1,data_buf[4+i] & 0x7f),data_buf[4+i]);
		}
		
		printf("Device %d String - ",i+1);
		GetAttachedString(SMB_string,i+1);
		color_printf(F_CYAN,"%s\n",SMB_string);
	}
	
	return 0;
}

int ReportTp11(void)
{
	int j;
	
	if(FindTable(11) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 11");
		return 0;
	}
	
	printf("Type  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length: ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Count : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[4]);
	for(j = 0; j < data_buf[4]; j++)
	{
		printf("String %d Type - ",j+1);
		GetAttachedString(SMB_string,(j+1));
		color_printf(F_CYAN,"%s\n",SMB_string);
	}
	
	return 0;
}

int ReportTp12(void)
{
	int i;
	
	if(FindTable(12) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 12");
		return 0;
	}
	
	printf("Type  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length: ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Count : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[4]);
	
	for(i = 0; i < data_buf[4]; i++)
	{
		printf("String %d Type - ",i+1);
		GetAttachedString(SMB_string,(i+1));
		color_printf(F_CYAN,"%s\n",SMB_string);

	}
	
	return 0;
}

int ReportTp13(void)
{
	int s;
	
	if(FindTable(13) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 13");
		return 0;
	}
	
	printf("Type            : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length          : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle          : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Installable Language: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[4]);
	
	if(smb_ver >= 2.1)
	{
		printf("Flags           : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
		s = 6;
	}
	else
	{
		s = 5;
	}
	
	
	printf("Reserved        : ");
	color_printf(F_CYAN,"%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X [HEX]; MSB -> LSB\n",data_buf[s+14],data_buf[s+13],data_buf[s+12],data_buf[s+11],data_buf[s+10],data_buf[s+9],data_buf[s+8],data_buf[s+7],data_buf[s+6],data_buf[s+5],data_buf[s+4],data_buf[s+3],data_buf[s+2],data_buf[s+1],data_buf[s]);
	
	printf("Current Language: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[s+15]);
	
	return 0;
}

int ReportTp14(void)
{
	if(FindTable(14) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 14");
		return 0;
	}
	
	printf("Type       : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length     : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle     : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Group Name : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Item Type  : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
	
	printf("Item Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[7],data_buf[6]);
	
	return 0;
}

int ReportTp15(void)
{
	int i,j,flag,k;
	
	if(FindTable(15) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 15");
		return 0;
	}
	
	printf("Type                   : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                 : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                 : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Log Area Length        : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[5],data_buf[4]);
	
	printf("Log Header Start Offset: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[7],data_buf[6]);
	
	printf("Log Data Start offset  : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[9],data_buf[8]);
	
	printf("Access Method          :\n");
	if(data_buf[0xa]==0)
	{
		color_printf(F_CYAN," 1 8-bit index port, 1 8-bit data port (0x%02X)\n",data_buf[0xa]);
	}
	else if(data_buf[0xa]==1)
	{
		color_printf(F_CYAN," 2 8-bit index port, 1 8-bit data port (0x%02X)\n",data_buf[0xa]);
	}
	else if(data_buf[0xa]==2)
	{
		color_printf(F_CYAN," 1 16-bit index port, 1 8-bit data port (0x%02X)\n",data_buf[0xa]);
	}
	else if(data_buf[0xa]==3)
	{
		color_printf(F_CYAN," Memory-mapped physical 32-bbit address (0x%02X)\n",data_buf[0xa]);
	}
	else if(data_buf[0xa]==4)
	{
		color_printf(F_CYAN," Available via General-Purpose NonVolatile Data functions (0x%02X)\n",data_buf[0xa]);
	}
	else if(data_buf[0xa]>=5 && data_buf[0xa]<=0x7f)
	{
		color_printf(F_CYAN," Available for future as signment via specification (0x%02X)\n",data_buf[0xa]);
	}
	else
	{
		color_printf(F_CYAN," BIOS Vendor/OEM-specific (0x%02X)\n",data_buf[0xa]);
	}
	
	printf("Log Status             : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0xb]);
	
	if((data_buf[0xb] & 0x1) == 0x1)
	{
		color_printf(F_CYAN," bit0: Log area vaild\n");
	}
	
	if((data_buf[0xb] & 0x2) == 0x2)
	{
		color_printf(F_CYAN," bit1: Log area full\n");
	}
	
	printf("Log Change Token       : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0xf],data_buf[0xe],data_buf[0xd],data_buf[0xc]);
	
	printf("Access Method Address  : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0x13],data_buf[0x12],data_buf[0x11],data_buf[0x10]);
	
	if(smb_ver >= 2.1)
	{
		printf("Log Header Format      : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x14]);
		if(data_buf[0x14]==0)
		{
			color_printf(F_CYAN," No header\n");
		}
		else if(data_buf[0x14] == 1)
		{
			color_printf(F_CYAN," Type 1 log header\n");
		}
		else if(data_buf[0x14] >= 2 && data_buf[0x14] <= 0x7f)
		{
			color_printf(F_CYAN," Available for future assignment via SMBIOS spce\n");
		}
		else
		{
			color_printf(F_CYAN," BIOS Vendor or OEM-specific format\n");
		}
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上或page up/down
			return flag;
		}
		
		printf("Number of Supported Log Type Descriptors:");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x15]);
	
		printf("Length of each Log Type Descriptor: ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x16]);
	
		k = 1;
		for(i = 0; i < data_buf[0x15]; i++)
		{
			for(j = 0; j < data_buf[0x16]; j++)
			{
				printf("Event Log %d:\n",k);
				
				flag = CheckPosi(0);
				if(flag == 1)
				{//ESC
					return 0;
				}
				else if(flag >= 4 || flag == 2)
				{//上或page up/down
					return flag;
				}
				
				if(data_buf[0x17+k*2] <= 0x17)
				{
					color_printf(F_CYAN," Log Type:%s (0x%02X)\n",GetString(15,1,data_buf[0x17+k*2]),data_buf[0x17+k*2]);
				}
				else if(data_buf[0x17+k*2] >= 0x18 && data_buf[0x17+k*2] <= 0x7F)
				{
					color_printf(F_CYAN," Log Type:Unused (0x%02X)\n",data_buf[0x17+k*2]);
				}
				else if(data_buf[0x17+k*2] == 0xff)
				{
					color_printf(F_CYAN," Log Type:End-of-log (0x%02X)\n",data_buf[0x17+k*2]);
				}
				else
				{
					color_printf(F_CYAN," Log Type:Available for system and OEM specific assignments (0x%02X)\n",data_buf[0x17+k*2]);
				}
				
				flag = CheckPosi(0);
				if(flag == 1)
				{//ESC
					return 0;
				}
				else if(flag >= 4 || flag == 2)
				{//上或page up/down
					return flag;
				}
				
				if(data_buf[0x18+k*2] <= 6)
				{
					color_printf(F_CYAN," Variable format Type: %s (0x%02X)\n",GetString(15,2,data_buf[0x18+k*2]),data_buf[0x18+k*2]);
				}
				else if(data_buf[0x18+k*2] >= 7 && data_buf[0x18+k*2] <= 0x7f)
				{
					color_printf(F_CYAN," Variable format Type: Unused (0x%02X)\n",data_buf[0x18+k*2]);
				}
				else
				{
					color_printf(F_CYAN," Variable format Type: OEM assigned (0x%02X)\n",data_buf[0x18+k*2]);
				}
				k++;
				
				flag = CheckPosi(0);
				if(flag == 1)
				{//ESC
					return 0;
				}
				else if(flag >= 4 || flag == 2)
				{//上或page up/down
					return flag;
				}
				
			}
		}
	}
	
	return 0;
}

int ReportTp16(void)
{
	if(FindTable(16) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 16");
		return 0;
	}
	
	printf("Type                           : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                         : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                         : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Location                       : ");
	if(data_buf[4] <=0xA)
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(16,1,data_buf[4]),data_buf[4]);
	}
	else
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(16,1,data_buf[4]-148),data_buf[4]);
	}
	
	printf("Use                            : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(16,2,data_buf[5]),data_buf[5]);
	
	printf("Memory Error Correction        : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(16,3,data_buf[6]),data_buf[6]);
	
	printf("Maximum Capacity               : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0xa],data_buf[9],data_buf[8],data_buf[7]);
	
	printf("Memory Error Information Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xc],data_buf[0xb]);
	
	printf("Number of Memory Device        : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xe],data_buf[0xd]);
	
	return 0;
}

int ReportTp17(void)
{
	int j,flag;
	WORD dd;
	
	if(FindTable(17) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 17");
		return 0;
	}
	
	printf("Type          : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length        : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle        : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[3],data_buf[2]);
	
	printf("Physical Memory Array Handle   : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[5],data_buf[4]);
	
	printf("Memory Error Information Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[7],data_buf[6]);
	
	printf("Total Width   : ");
	dd = data_buf[9];
	dd <<= 8;
	dd |= data_buf[8];
	color_printf(F_CYAN,"0x%04X(%u-bits)\n",dd,dd);
	
	printf("Data Width    : ");
	dd = data_buf[0xb];
	dd <<= 8;
	dd |= data_buf[0xa];
	color_printf(F_CYAN,"0x%04X(%u-bits)\n",dd,dd);
	
	printf("Size          : ");
	dd = data_buf[0xd];
	dd <<= 8;
	dd |= data_buf[0xc];
	color_printf(F_CYAN,"0x%04X(%s)\n",dd,CalSize(dd));
	
	printf("Form Factor   : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(17,1,data_buf[0xe]),data_buf[0xe]);
	
	printf("Device Set    : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0xf]);
	
	printf("Device Locator: ");
	GetAttachedString(SMB_string,data_buf[0x10]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x10]);
	
	printf("Bank Locator  : ");
	GetAttachedString(SMB_string,data_buf[0x11]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x11]);
	
	printf("Memory Type   : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(17,2,data_buf[0x12]),data_buf[0x12]);
	
	flag = 0;
	printf("Type Detail   : ");
	dd = data_buf[0x14];
	dd <<= 8;
	dd |= data_buf[0x13];
	for(j = 0; j < 13; j++)
	{
		if((dd & 0x1) == 0x1)
		{
			color_printf(F_CYAN,"%s (0x%02X%02X)\n",GetString(17,3,j),data_buf[0x14],data_buf[0x13]);
			flag = 1;
			break;
		}
		dd >>= 1;
	}
	
	if(flag==0)
	{
		color_printf(F_CYAN,"(0x%02X%02X)\n",data_buf[0x14],data_buf[0x13]);
	}
	
	if(smb_ver >= 2.3)
	{
		printf("Speed         : ");
		dd = data_buf[0x16];
		dd <<= 8;
		dd |= data_buf[0x15];
		color_printf(F_CYAN,"0x%04X(%dMHz)\n",dd,dd);
		
		printf("Manufacturer  : ");
		GetAttachedString(SMB_string,data_buf[0x17]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x17]);
		
		printf("Serial Number : ");
		GetAttachedString(SMB_string,data_buf[0x18]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x18]);
		
		printf("Asset Tag     : ");
		GetAttachedString(SMB_string,data_buf[0x19]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x19]);
		
		printf("Part Number   : ");
		GetAttachedString(SMB_string,data_buf[0x1a]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x1a]);
		
	}
	
	if(smb_ver >= 2.6)
	{
		printf("Attributes    : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x1b]);
	}
	return 0;
}

int ReportTp18(void)
{
	if(FindTable(18) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 18");
		return 0;
	}
	
	printf("Type                : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length              : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle              : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Error Type          : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(18,1,data_buf[4]),data_buf[4]);
	
	printf("Error Granularity   : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(18,2,data_buf[5]),data_buf[5]);
	
	printf("Error Operation     : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(18,3,data_buf[6]),data_buf[6]);
	
	printf("Vendor Syndrome     : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0xa],data_buf[9],data_buf[8],data_buf[7]);
	
	printf("Memory Array Error Address: ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0xe],data_buf[0xd],data_buf[0xc],data_buf[0xb]);
	
	printf("Device Error Address: ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0x12],data_buf[0x11],data_buf[0x10],data_buf[0xf]);
	
	printf("Error Resolution    : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0x16],data_buf[0x15],data_buf[0x14],data_buf[0x13]);
	
	return 0;
}

int ReportTp19(void)
{
	if(FindTable(19) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 19");
		return 0;
	}
	
	printf("Type               : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length             : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle             : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Starting Address   : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[7],data_buf[6],data_buf[5],data_buf[4]);
	
	printf("Ending Address     : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0xb],data_buf[0xa],data_buf[9],data_buf[8]);
	
	printf("Memory Array Hnadle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xd],data_buf[0xc]);
	
	printf("Partition Width    : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0xe]);
	
	return 0;
}

int ReportTp20(void)
{
	
	if(FindTable(20) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 20");
		return 0;
	}
	
	printf("Type                  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Starting Address      : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[7],data_buf[6],data_buf[5],data_buf[4]);
	
	printf("Ending Address        : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0xb],data_buf[0xa],data_buf[9],data_buf[8]);
	
	printf("Memory Device Hnadle  : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xd],data_buf[0xc]);
	
	printf("Memory Array Mapped Address Hnadle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xf],data_buf[0xe]);
	
	printf("Partition Row Position: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0x10]);
	
	printf("Interleave Position   : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0x11]);
	
	printf("Interleaved Data Depth: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0x12]);
	
	return 0;
}

int ReportTp21(void)
{
	if(FindTable(21) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 21");
		return 0;
	}
	
	printf("Type             : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length           : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle           : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Type             : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(21,1,data_buf[4]),data_buf[4]);
	
	printf("Interface        : ");
	if(data_buf[5] <= 8)
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(21,2,data_buf[5]),data_buf[5]);
	}
	else
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(21,2,data_buf[5]-150),data_buf[5]);
	}
	
	printf("Number of Buttons: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[6]);
	
	return 0;
}

int ReportTp22(void)
{
	WORD dd;
	
	if(FindTable(22) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 22");
		return 0;
	}
	
	printf("Type               : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length             : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle             : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Location           : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Manufacturer       : ");
	GetAttachedString(SMB_string,data_buf[5]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[5]);
	
	printf("Mamufacture Date   : ");
	GetAttachedString(SMB_string,data_buf[6]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[6]);
	
	printf("Serial Number      : ");
	GetAttachedString(SMB_string,data_buf[7]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[7]);
	
	printf("Device Name        : ");
	GetAttachedString(SMB_string,data_buf[8]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[8]);
	
	printf("Device Chemistry   : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(22,1,data_buf[9]),data_buf[9]);
	
	printf("Device Capacity    : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xb],data_buf[0xa]);
	
	printf("Design Voltage     : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xd],data_buf[0xc]);
	
	printf("SBDS Version Number: ");
	GetAttachedString(SMB_string,data_buf[0xe]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0xe]);
	
	printf("Maximum Error in Battery Data: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[0xf]);
	
	if(smb_ver >= 2.2)
	{
		printf("SBDS Serial Number   : ");
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x11],data_buf[0x10]);
	
		dd = data_buf[0x13];
		dd <<= 8;
		dd |= data_buf[0x12];
		printf("SBDS Manufacture Date: ");
		color_printf(F_CYAN,"%d/%d/%d (0x%04X)\n",1980+((dd&0xFE00)>>9),(dd&0x1E0)>>5,(dd&0x1F),dd);
		
		printf("SBDS Device Chemistry: ");
		GetAttachedString(SMB_string,data_buf[0x14]);
		color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0x14]);
	
		printf("Design Capacity      : ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[0x15]);
		
		printf("OEM-specific         : ");
		color_printf(F_CYAN,"0x%08lX\n",data_buf[0x16]);
	}
	return 0;
}

int ReportTp23(void)
{
	if(FindTable(23) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 23");
		return 0;
	}
	
	printf("Type          : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length        : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle        : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Capabilities  : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[4]);
	
	color_printf(F_CYAN," Bits 7-6: Reserved\n");
	
	if((data_buf[4] & 0x20) == 0x20)
	{
		color_printf(F_CYAN," System contains a watchdog timer\n");
	}
	else
	{
		color_printf(F_CYAN," System does not contain a watchdog timer\n");
	}
	
	switch((data_buf[4] & 0x18))
	{
		case 0x00:
			color_printf(F_CYAN," Boot Option on Limit - Reserved\n");
			break;
		case 0x08:
			color_printf(F_CYAN," Boot Option on Limit - Operating system\n");
			break;
		case 0x10:
			color_printf(F_CYAN," Boot Option on Limit - System utilities\n");
			break;
		case 0x18:
			color_printf(F_CYAN," Boot Option on Limit - Do not reboot\n");
			break;
	}
	
	switch((data_buf[4] & 0x6))
	{
		case 0x00:
			color_printf(F_CYAN," Boot Option - Reserved\n");
			break;
		case 0x02:
			color_printf(F_CYAN," Boot Option - Operating system\n");
			break;
		case 0x04:
			color_printf(F_CYAN," Boot Option - System utilities\n");
			break;
		case 0x6:
			color_printf(F_CYAN," Boot Option - Do not reboot\n");
			break;
	}
	
	if((data_buf[4] & 0x01) == 0x1)
	{
		color_printf(F_CYAN," The system reset is enabled by the user\n");
	}
	else
	{
		color_printf(F_CYAN," The system reset is not enabled by the user\n");
	}
	
	printf("Reset Count   : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[6],data_buf[5]);
	
	printf("Reset Limit   : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[8],data_buf[7]);
	
	printf("Timer Interval: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xa],data_buf[9]);
	
	printf("Timeout       : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xc],data_buf[0xb]);
	
	return 0;
}

int ReportTp24(void)
{
	if(FindTable(24) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 24");
		return 0;
	}
	
	printf("Type  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length: ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Hardware Security Setting: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[4]);
	
	switch((data_buf[4] & 0xc0))
	{
		case 0x00:
			color_printf(F_CYAN," Power-on Password Status - Disabled\n");
			break;
		case 0x40:
			color_printf(F_CYAN," Power-on Password Status - Enabled\n");
			break;
		case 0x80:
			color_printf(F_CYAN," Power-on Password Status - Not Implemented\n");
			break;
		case 0xc0:
			color_printf(F_CYAN," Power-on Password Status - Unknown\n");
			break;
	}
	
	switch((data_buf[4] & 0x30))
	{
		case 0x00:
			color_printf(F_CYAN," Keyboard Password Status - Disabled\n");
			break;
		case 0x10:
			color_printf(F_CYAN,"Keyboard Password Status - Enabled\n");
			break;
		case 0x20:
			color_printf(F_CYAN,"Keyboard Password Status - Not Implemented\n");
			break;
		case 0x40:
			color_printf(F_CYAN,"Keyboard Password Status - Unknown\n");
			break;
	}
	
	switch((data_buf[4] & 0x0c))
	{
		case 0x00:
			color_printf(F_CYAN," Administrator Password Status - Disabled\n");
			break;
		case 0x04:
			color_printf(F_CYAN," Administrator Password Status - Enabled\n");
			break;
		case 0x08:
			color_printf(F_CYAN," Administrator Password Status - Not Implemented\n");
			break;
		case 0x0c:
			color_printf(F_CYAN," Administrator Password Status - Unknown\n");
			break;
	}
	
	switch((data_buf[4] & 0x03))
	{
		case 0x00:
			color_printf(F_CYAN," Front Panel Reset Status - Disabled\n");
			break;
		case 0x01:
			color_printf(F_CYAN," Front Panel Reset Status - Enabled\n");
			break;
		case 0x02:
			color_printf(F_CYAN," Front Panel Reset Status - Not Implemented\n");
			break;
		case 0x03:
			color_printf(F_CYAN," Front Panel Reset Status - Unknown\n");
			break;
	}
	
	return 0;
}

int ReportTp25(void)
{
	if(FindTable(25) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 25");
		return 0;
	}
	
	printf("Type  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length: ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Next Scheduled Power-on Month       : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[4]);
	
	printf("Next Scheduled Power-on Day of Month: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
	
	printf("Next Scheduled Power-on Hour        : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[6]);
	
	printf("Next Scheduled Power-on Minute      : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[7]);
	
	printf("Next Scheduled Power-on Second      : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[8]);
	
	return 0;
}

int ReportTp26(void)
{
	WORD dd;
	
	if(FindTable(26) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 26");
		return 0;
	}
	
	printf("Type               : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length             : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle             : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Description        : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Location and Status: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
		
	dd = (data_buf[5] & 0xe0) >> 5;
	color_printf(F_CYAN," Status: %s\n",GetString(26,1,dd));
		
	dd = (data_buf[5] & 0x1f)+5;
	color_printf(F_CYAN," Location: %s\n",GetString(26,1,dd));
	
	printf("Maximum Value      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[7],data_buf[6]);
	
	printf("Minimum Value      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[9],data_buf[8]);
	
	printf("Resolution         : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xb],data_buf[0xa]);
	
	printf("Tolerance          : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xd],data_buf[0xc]);
	
	printf("Accuracy           : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xf],data_buf[0xe]);
	
	printf("OEM-defined        : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0x13],data_buf[0x12],data_buf[0x11],data_buf[0x10]);
	
	printf("Nominal Value      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x15],data_buf[0x14]);
	
	return 0;
}

int ReportTp27(void)
{
	WORD dd;
	
	if(FindTable(27) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 27");
		return 0;
	}
	
	printf("Type                    : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                  : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                  : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Temperature Probe Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[5],data_buf[4]);
	
	printf("Device Type and Status  : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[6]);
		
	dd = (data_buf[6] & 0xe0) >> 5;
	color_printf(F_CYAN," Status: %s\n",GetString(27,1,dd));
		
	dd = (data_buf[6] & 0x1f)+5;
	color_printf(F_CYAN," Device Type: %s\n",GetString(27,1,dd));
		
	printf("Cooling Unit Group      : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[7]);
	
	printf("OEM-define              : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0xb],data_buf[0xa],data_buf[9],data_buf[8]);
	
	printf("Nominal Speed           : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xd],data_buf[0xc]);
	
	return 0;
}

int ReportTp28(void)
{
	WORD dd;
	
	if(FindTable(28) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 28");
		return 0;
	}
	
	printf("Type               : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length             : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle             : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Description        : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Location and Status: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
		
	dd = (data_buf[5] & 0xe0) >> 5;
	color_printf(F_CYAN," Status: %s\n",GetString(28,1,dd));
		
	dd = (data_buf[5] & 0x1f)+5;
	color_printf(F_CYAN," Location: %s\n",GetString(28,1,dd));
	
	printf("Maximum Value      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[7],data_buf[6]);
	
	printf("Minimum Value      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[9],data_buf[8]);
	
	printf("Resolution         : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xb],data_buf[0xa]);
	
	printf("Tolerance          : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xd],data_buf[0xc]);
	
	printf("Accuracy           : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xf],data_buf[0xe]);
	
	printf("OEM-defined        : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0x13],data_buf[0x12],data_buf[0x11],data_buf[0x10]);
	
	printf("Nominal Value      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x15],data_buf[0x14]);
	
	return 0;
}

int ReportTp29(void)
{
	WORD dd;
	
	if(FindTable(29) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 29");
		return 0;
	}
	
	printf("Type               : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length             : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle             : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Description        : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Location and Status: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
		
	dd = (data_buf[5] & 0xe0) >> 5;
	color_printf(F_CYAN," Status: %s\n",GetString(29,1,dd));
		
	dd = (data_buf[5] & 0x1f)+5;
	color_printf(F_CYAN," Location: %s\n",GetString(29,1,dd));
		
	printf("Maximum Value      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[7],data_buf[6]);
	
	printf("Minimum Value      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[9],data_buf[8]);
	
	printf("Resolution         : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xb],data_buf[0xa]);
	
	printf("Tolerance          : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xd],data_buf[0xc]);
	
	printf("Accuracy           : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xf],data_buf[0xe]);
	
	printf("OEM-defined        : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0x13],data_buf[0x12],data_buf[0x11],data_buf[0x10]);
	
	printf("Nominal Value      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x15],data_buf[0x14]);
	
	return 0;
}

int ReportTp30(void)
{
	if(FindTable(30) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 30");
		return 0;
	}
	
	printf("Type             : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length           : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle           : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Manufacturer Name: ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Connections      : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
	
	color_printf(F_CYAN," bits 7-2: Reserved\n");
	
	if((data_buf[5] & 0x2) == 0x2)
	{
		color_printf(F_CYAN," Outbound Connection Enabled\n");
	}
	else
	{
		color_printf(F_CYAN," Outbound Connection Disabled\n");
	}
	
	if((data_buf[5] & 0x1) == 0x1)
	{
		color_printf(F_CYAN," Inbound Connection Enabled\n");
	}
	else
	{
		color_printf(F_CYAN," Inbound Connection Disabled\n");
	}
	
	return 0;
}

int ReportTp32(void)
{
	int j,flag;
	
	if(FindTable(32) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 32");
		return 0;
	}
	
	printf("Type    : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length  : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle  : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Reserved: ");
	color_printf(F_CYAN,"%02X %02X %02X %02X %02X %02X [HEX]; MSB -> LSB\n",data_buf[9],data_buf[8],data_buf[7],data_buf[6],data_buf[5],data_buf[4]);
	
	for(j = 0; j < data_buf[1]-10; j++)
	{
		printf("Boot Status(%d) - ",j+1);
		color_printf(F_CYAN,"0x%02X\n",data_buf[0xa+j]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上或page up/down
			return flag;
		}
	}
	
	return 0;
}

int ReportTp33(void)
{
	if(FindTable(33) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 33");
		return 0;
	}
	
	printf("Type                : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length              : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle              : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Error Type          : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[4]);
	
	printf("Error Granularity   : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
	
	printf("Error Operation     : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[6]);
	
	printf("Vendor Syndrome     : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0xa],data_buf[9],data_buf[8],data_buf[7]);
	
	printf("Memory Array Error Address: ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X%02X%02X%02X%02X\n",data_buf[0x12],data_buf[0x11],data_buf[0x10],data_buf[0xf],data_buf[0xe],data_buf[0xd],data_buf[0xc],data_buf[0xb]);
	
	printf("Device Error Address: ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X%02X%02X%02X%02X\n",data_buf[0x1a],data_buf[0x19],data_buf[0x18],data_buf[0x17],data_buf[0x16],data_buf[0x15],data_buf[0x14],data_buf[0x13]);
	
	printf("Error Resolution    : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[0x1e],data_buf[0x1d],data_buf[0x1c],data_buf[0x1b]);
	
	return 0;
}

int ReportTp34(void)
{
	if(FindTable(34) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 34");
		return 0;
	}
	
	printf("Type        : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length      : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle      : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Description : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Type        : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(34,1,data_buf[5]),data_buf[5]);
	
	printf("Address     : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X\n",data_buf[9],data_buf[8],data_buf[7],data_buf[6]);
	
	printf("Address Type: ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(34,2,data_buf[0xa]),data_buf[0xa]);
	
	return 0;
}

int ReportTp35(void)
{
	if(FindTable(35) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 35");
		return 0;
	}
	
	printf("Type                    : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                  : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                  : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Description             : ");
	GetAttachedString(SMB_string,data_buf[4]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[4]);
	
	printf("Management Device Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[6],data_buf[5]);
	
	printf("Component Handle        : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[8],data_buf[7]);
	
	printf("Threshold Handle        : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xa],data_buf[9]);
	
	return 0;
}

int ReportTp36(void)
{
	if(FindTable(36) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 36");
		return 0;
	}
	
	printf("Type  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length: ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Lower Threshold - Non-critical   : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[5],data_buf[4]);
	
	printf("Upper Threshold - Non-critical   : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[7],data_buf[6]);
	
	printf("Lower Threshold - Critical       : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[9],data_buf[8]);
	
	printf("Upper Threshold - Critical       : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xb],data_buf[0xa]);
	
	printf("Lower Threshold - Non-recoverable: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xd],data_buf[0xc]);
	
	printf("Upper Threshold - Non-recoverable: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xf],data_buf[0xe]);
	
	return 0;
}

int ReportTp37(void)
{
	int i,j,flag;
	
	if(FindTable(37) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 37");
		return 0;
	}
	
	printf("Type                : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length              : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle              : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Channel Type        : ");
	color_printf(F_CYAN,"%s (0x%02X)\n",GetString(37,1,data_buf[4]),data_buf[4]);
	
	printf("Maximum Channel Load: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
	
	printf("Memory Device Count : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[6]);
	
	printf("Memory Device Load  : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[7]);
	
	printf("Memory Device Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[9],data_buf[8]);
	
	i = (data_buf[6]-1)*3;
	for(j = 0; j < i; j+=3)
	{
		printf("Memory Device Load: ");
		color_printf(F_CYAN,"0x%02X\n",data_buf[7+j]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上或page up/down
			return flag;
		}
		
		printf("Memory Device Handle: ");
		color_printf(F_CYAN,"0x%02X%02X\n",data_buf[7+2+j],data_buf[7+1+j]);
		
		flag = CheckPosi(0);
		if(flag == 1)
		{//ESC
			return 0;
		}
		else if(flag >= 4 || flag == 2)
		{//上或page up/down
			return flag;
		}
	}
	
	return 0;
}

int ReportTp38(void)
{
	if(FindTable(38) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 38");
		return 0;
	}
	
	printf("Type                       : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length                     : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle                     : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Interface Type             : ");
	if(data_buf[4] <= 3)
	{
		color_printf(F_CYAN,"%s (0x%02X)\n",GetString(38,1,data_buf[4]),data_buf[4]);
	}
	else
	{
		color_printf(F_CYAN,"Reserved (0x%02X)\n",data_buf[4]);
	}
	
	printf("IPMI Specification Revision: ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[5]);
	
	printf("I2C Slave Address          : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[6]);
	
	printf("NV Storage Device Address  : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[7]);
	
	printf("Base Address               : ");
	color_printf(F_CYAN,"0x%02X%02X%02X%02X%02X%02X%02X%02X\n",data_buf[0xf],data_buf[0xe],data_buf[0xd],data_buf[0xc],data_buf[0xb],data_buf[0xa],data_buf[9],data_buf[8]);
	
	return 0;
}

int ReportTp39(void)
{
	int flag;
	WORD dd;
	
	if(FindTable(39) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 39");
		return 0;
	}
	
	printf("Type              : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length            : ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle            : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Power Unit Group  : ");
	color_printf(F_CYAN,"0x%02\n",data_buf[4]);
	
	printf("Location          : ");
	GetAttachedString(SMB_string,data_buf[5]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[5]);
	
	printf("Device Name       : ");
	GetAttachedString(SMB_string,data_buf[6]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[6]);
	
	printf("Manufacturer      : ");
	GetAttachedString(SMB_string,data_buf[7]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[7]);
	
	printf("Serial Number     : ");
	GetAttachedString(SMB_string,data_buf[8]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[8]);
	
	printf("Asset Tag Number  : ");
	GetAttachedString(SMB_string,data_buf[9]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[9]);
	
	printf("Model Part Number : ");
	GetAttachedString(SMB_string,data_buf[0xa]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0xa]);
	
	printf("Revision Level    : ");
	GetAttachedString(SMB_string,data_buf[0xb]);
	color_printf(F_CYAN,"%s (0x%02X)\n",SMB_string,data_buf[0xb]);
	
	printf("Max Power Capacity: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xd],data_buf[0xc]);
	
	printf("Power Supply Characteristics: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0xf],data_buf[0xe]);
	
	dd = data_buf[0xf];
	dd<<= 8;
	dd |= data_buf[0xe];
	dd &= 0x3C00;
	dd >>=10;
	if(dd <= 8)
	{
		color_printf(F_CYAN," bit13-10: DMTF Power Supply Type - %s\n",GetString(39,1,dd-1));
	}
	else
	{
		color_printf(F_CYAN," bit13-10: DMTF Power Supply Type - Reserved\n");
	}
	
	dd = data_buf[0xf];
	dd<<= 8;
	dd |= data_buf[0xe];
	dd &= 0x380;
	dd >>=7;
	if(dd <= 5)
	{
		color_printf(F_CYAN," bit9-7: Status - %s\n",GetString(39,2,dd-1));
	}
	else
	{
		color_printf(F_CYAN," bit9-7: Status - ??\n");
	}
	
	dd = (data_buf[0xe] & 0x78)>>3;
	if(dd <= 6)
	{
		color_printf(F_CYAN," bit6-3: DMTF Input Voltage Range Switching - %s\n",GetString(39,3,dd-1));
	}
	else
	{
		color_printf(F_CYAN," bit6-3: Status - ??\n");
	}
	
	if((data_buf[0xe] & 0x4) == 0x4)
	{
		color_printf(F_CYAN," bit2: Power supply is unplugged from wall\n");
	}
	else
	{
		color_printf(F_CYAN," bit2: Power supply is plugged from wall\n");
	}
	
	if((data_buf[0xe] & 0x2) == 0x2)
	{
		color_printf(F_CYAN," bit2: Power supply is present\n");
	}
	else
	{
		color_printf(F_CYAN," bit2: Power supply is not present\n");
	}
	
	if((data_buf[0xe] & 0x1) == 0x1)
	{
		color_printf(F_CYAN," bit2: Power supply is hot replaceable\n");
	}
	else
	{
		color_printf(F_CYAN," bit2: Power supply is not replaceable\n");
	}
	
	printf("Input Voltage Probe Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x11],data_buf[0x10]);
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上或page up/down
		return flag;
	}
	
	printf("Cooling Device Handle     : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x13],data_buf[0x12]);
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上或page up/down
		return flag;
	}
	
	printf("Input Current Probe Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[0x15],data_buf[0x14]);
	
	flag = CheckPosi(0);
	if(flag == 1)
	{//ESC
		return 0;
	}
	else if(flag >= 4 || flag == 2)
	{//上或page up/down
		return flag;
	}
	
	return 0;
}

void ReportTp126(void)
{
	if(FindTable(126) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 126");
		return;
	}
	
	printf("Type  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length: ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
}

void ReportEnd(void)
{
	if(FindTable(127) == -1)
	{
		color_printf(B_RED | F_LIGHT_WHITE,"Your system did NOT provide Type 127");
		return;
	}
	
	printf("Type  : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length: ");
	color_printf(F_CYAN,"0x%02X",data_buf[1]);
	color_printf(F_RED," %s\n",length_err? "(Type Length Fail)" : "");
	
	printf("Handle: ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
}

void ReportOEM(void)
{
	int i;
	
	FindTable(-1);
	
	gotoxy(0,1);
	printf("Type   : ");
	color_printf(F_CYAN,"%d\n",data_buf[0]);
	
	printf("Length : ");
	color_printf(F_CYAN,"0x%02X\n",data_buf[1]);
	
	printf("Handle : ");
	color_printf(F_CYAN,"0x%02X%02X\n",data_buf[3],data_buf[2]);
	
	printf("Data   : \n");
	for( i = 4; i < data_len; i++)
	{
		color_printf(F_CYAN," %02X",data_buf[i]);
	}
	
}

int InputType(void)
{
	char buf[20];
	int cnt,ch,i;
	
	gotoxy(0,24);
	color_printf(B_BROWN | F_WHITE,"Please input type you want:                                                     ");
	gotoxy(27,24);
	ShowCursor();
	memset(buf,0,sizeof(buf));
	cnt = 0;
	while(1)
	{
		ch = getch();
		if(ch == 27)
		{
			gotoxy(0,24);
			color_printf(B_BLACK | F_WHITE,"                                                                                ");
			break;
		}
		else if(ch == 13)
		{
			HideCursor();
			//找尋type
			if(buf[0] == 'e' || buf[0] == 'E')
			{
				type_sld = 0;
				HideCursor();
				return 0;
			}
			else
			{
				cnt = atoi(buf);
				if(cnt >= 0 && cnt <= 39)
				{
					if(cnt != 31)
					{
						for(i = 0; i < tp_cnt; i++)
						{
							if(tp_Addrs[i][0] == (DWORD)(cnt+1))
							{
								type_sld = i;
								HideCursor();
								return 0;
							}
						}
					}
					else
					{
						goto input_err;
					}
				}
				else if(cnt == 127 || cnt == 126)
				{
					//type_id = cnt;
					for(i = 0; i < tp_cnt; i++)
					{
						if(tp_Addrs[i][0] == (DWORD)(cnt)+1)
						{
							type_sld = i;
							HideCursor();
							return 0;
						}
					}
				}
				else
				{
input_err:
					gotoxy(0,24);
					color_printf(B_BROWN | F_WHITE,"Input value out of range: E, 0~30, 32~39, 126, 127 only                        ");
				}
				break;
			}
		}
		else if(ch == 8)
		{
			cnt--;
			buf[cnt] = '\0';
			printf("\b \b");
		}
		else if(ch >= '0' && ch <= '9')
		{
			if(cnt <= 3)
			{
				buf[cnt] = (char)ch;
				cnt++;
				printf("%c",ch);
			}
		}
	}
	HideCursor();
	return 1;
}



int FindTable(int sld)
{
	WORD data16;
	BYTE data8;
	int i,len,flag=0;
	
	data16 = read_mem_word(EntryAddr);
	
	if(sld != -1)
	{//要進行type篩選
		if((BYTE)sld != (BYTE)data16)
		{//不是想要的
			return -1;
		}
	}
	
	if((BYTE)data16 >= 40) //end or OEM type
	{
		flag = 1;
	}
	
	data_len = 0;
	memset(data_buf,0,sizeof(data_buf));
	
	//得到這個type的總大小
	len = (int)((BYTE)(data16 >> 8));
	
	//讀取資料
	for(i = 0; i < len; i++)
	{
		data8 = read_mem_byte(EntryAddr);
		data_buf[data_len] = data8;
		data_len++;
		EntryAddr++;
	}
	
	//判斷長度對不對
	length_err=0;
	switch(sld)
	{
		case 1:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4)
			{
				if(len < 0x1b)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0x19)
				{
					length_err=1;
				}
			}
			break;
		case 3:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3)
			{
				if(len < 0x16)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0xd)
				{
					length_err=1;
				}
			}
			break;
		case 4:
			if(smb_ver == 2.6)
			{
				if(len < 0x29)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.5)
			{
				if(len < 0x27)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.4 || smb_ver == 2.3)
			{
				if(len < 0x23)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0x20)
				{
					length_err=1;
				}
			}
			break;
		case 5:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len <= (0xf+2*data_buf[0xe]))
				{
					length_err=1;
				}
			}
			break;
		case 7:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0xf)
				{
					length_err=1;
				}
			}
			break;
		case 9:
			if(smb_ver == 2.6)
			{
				if(len < 0x11)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0xd)
				{
					length_err=1;
				}
			}
			break;
		case 13:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x16)
				{
					length_err=1;
				}
			}
			break;
		case 15:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x15)
				{
					length_err=1;
				}
			}
			break;
		case 16:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0xf)
				{
					length_err=1;
				}
			}
			break;
		case 17:
			if(smb_ver == 2.6)
			{
				if(len < 0x1c)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3)
			{
				if(len < 0x1b)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0x16)
				{
					length_err=1;
				}
			}
			break;
		case 18:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x14)
				{
					length_err=1;
				}
			}
			break;
		case 19:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0xf)
				{
					length_err=1;
				}
			}
			break;
		case 20:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x13)
				{
					length_err=1;
				}
			}
			break;
		case 21:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x7)
				{
					length_err=1;
				}
			}
			break;
		case 22:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.2)
			{
				if(len < 0x1a)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0x10)
				{
					length_err=1;
				}
			}
			break;
	}
	
	return flag;
}

void GetAttachedString(char *str,int sw)
{
	int cnt;
	char data;
	
	if(sw==0)
	{//沒有字串
		strcpy(str,"null\0");
		return;
	}
	
	//從sw來決定抓第幾個str
	if(sw != 1)
	{
		cnt = 1;
		while(1)
		{
			data = read_mem_byte(EntryAddr);
			if(!data)
			{
				cnt++;
				if(cnt == sw)
				{
					EntryAddr++;
					break;
				}
			}
			EntryAddr++;
		}
	}
	
	cnt = 0;
	memset(str,0,sizeof(str));
	while(1)
	{
		//	sprintf(bb,"get data @: %08lX",SMB_addr);
		//	AfxMessageBox(bb);
		data = read_mem_byte(EntryAddr);
		str[cnt] = data;
		if(data==0)
		{
			//EntryAddr++; //移到下一個字串起點
			return;
		}
		EntryAddr++;
		cnt++;
	}
}

void Read_Entry(void)
{
	int i;
	BYTE data8;
	
	data_len = 0;
	memset(data_buf,0,sizeof(data_buf));
	for(i = 0; i <= 0x1E; i++)
	{
		data8 = read_mem_byte(EntryAddr+i);
		data_buf[data_len] = data8;
		data_len++;
	}
}

int FindEntry(void)
{
	DWORD data32,min;
	int i,j,len;
	char bb[10];

	//找出SMBIOS entry point
	for(EntryAddr = 0xf0000; EntryAddr < 0xfffff; EntryAddr+=4)
	{
		data32 = read_mem_dword(EntryAddr);
		if(data32==0x5F4d535F) //顛倒的_SM_
		{
			tp_Addrs[0][0] = 0;
			tp_Addrs[0][1] = EntryAddr;
			
			Read_Entry();
			
			EntryAddr = 0;
			for(i = 0; i < 4; i++)
			{
				EntryAddr <<= 8;
				EntryAddr |= data_buf[27-i];
			}
			
			sprintf(bb,"%d",data_buf[6]);
			smb_ver = (float)atof(bb);
			sprintf(bb,"0.%d",data_buf[7]);
			smb_ver += (float)atof(bb);
				
			//找出各個type的entry address
			tp_cnt = 1;
			while(1)
			{
				data32 = read_mem_dword(EntryAddr);
				tp_Addrs[tp_cnt][0] = (data32 & 0xff)+1; //為了使用string table才多加1
				tp_Addrs[tp_cnt][1] = EntryAddr;
					
				tp_cnt++;
				if(tp_Addrs[tp_cnt-1][0] == 128)
				{
					break;
				}
				len = (int)((BYTE)(data32 >> 8));
				EntryAddr += len;
				Jump_str();
			}
			
			//排序
			for(i = 1; i < tp_cnt; i++)
			{
				min = tp_Addrs[i][0];
				for(j = i; j < tp_cnt; j++)
				{
					if(min > tp_Addrs[j][0])
					{
						tp_Addrs[i][0] = tp_Addrs[j][0];
						tp_Addrs[j][0] = min;
						min = tp_Addrs[i][1];
						tp_Addrs[i][1] = tp_Addrs[j][1];
						tp_Addrs[j][1] = min;
						min = tp_Addrs[i][0];
					}
				}
			}
			
			return 0;
		}
	}
	return 1;
}

void Jump_str(void)
{
	int i;
	BOOL flag;
	BYTE data8;
	
	i = 0;
	flag = 0;
	while(1)
	{
		data8 = read_mem_byte(EntryAddr+i);
		
		if(data8 != 0)
		{
			flag = 0;
		}
		else
		{
			if(flag == 1)
			{//兩個00
				EntryAddr += i+1; //移到00的下一個，下一個應該是另一起點
				return;
			}
			else
			{
				flag = 1;
			}
		}
		i++;
	}
}

char *CalSize(WORD dd)
{
	char buf[100];
	
	if((dd & 0x8000) == 0x8000)
	{
		dd &= 0x7fff;
		sprintf(buf,"%dKB",dd);
	}
	else
	{
		sprintf(buf,"%dMB",dd);
	}
	
	return buf;
}

char *GetString(int tp,int index,int offset)
{
	DWORD addr;
	char buf[100];
	int cnt;
	
	addr = tp_str[tp][index-1];
	if(addr==0)
	{
		return "tb err";
	}
	addr += offset * 100;
	cnt = 0;
	memset(buf,0,sizeof(buf));
	while(1)
	{
		buf[cnt] = read_mem_byte(addr+cnt);
		if(buf[cnt]=='\0')
		{
			break;
		}
		cnt++;
	}
	return buf;
}

void Load_String(void)
{
	FILE *fpp;
	char buf[100],*p,aa[10];
	DWORD addr=0x500000;
	int i,len;
	
	printf("Loading string table to memory...please wait...");
	
	memset(tp_str,0,sizeof(tp_str));
	fpp = fopen("dosdmi.str","rt");
	if(fpp == NULL)
	{
		return;
	}
	
	while(1)
	{
		memset(buf,0,sizeof(buf));
		p = fgets(buf,sizeof(buf),fpp);
		if(p==0)
		{
			break;
		}
		
		len = strlen(buf);
		if(len < 2)
		{
			continue;
		}
		if(strnicmp(buf,"[TP",3)==0)
		{
			memset(aa,0,sizeof(aa));
			for(i = 3; i < len; i++)
			{
				if(buf[i] == '_')
				{
					len = buf[i+4]-0x31; //從1開始
					break;
				}
				aa[i-3] = buf[i];
			}
			i = atoi(aa);
			tp_str[i][len] = addr;
		}
		else
		{
			buf[len-1] = '\0';
			for(i = 0; i < len; i++) //包含結束字元
			{
				write_mem_byte(addr+i,buf[i]);
			}
			addr+= 100;
		}
	}
	fclose(fpp);
}

void quit( int errorlevel )
{//結束程式
	if(errorlevel != 0)
	{
		puts("\a");
	}
	exit(errorlevel);
}

int GetProcessorString(WORD no)
{
	DWORD i;
	int cnt;
	
	cnt = -1;
	for(i = 1; i <= 0xffff; i++)
	{
		if( i < 0x14)
		{
			cnt++;
		}
		else if(i >= 0x18 && i <= 0x27)
		{
			cnt++;
		}
		else if(i >= 0x30 && i <= 0x37)
		{
			cnt++;
		}
		else if(i >= 0x40 && i <= 0x45)
		{
			cnt++;
		}
		else if(i >= 0x50 && i <= 0x58)
		{
			cnt++;
		}
		else if(i >= 0x60 && i <= 0x65)
		{
			cnt++;
		}
		else if(i == 0x70)
		{
			cnt++;
		}
		else if(i >= 0x78 && i <= 0x7A)
		{
			cnt++;
		}
		else if(i == 0x80)
		{
			cnt++;
		}
		else if(i >= 0x82 && i <= 0x89)
		{
			/*if(smb_ver <= 2.5 && i==0x89)
				{}
			else*/
				cnt++;
		}
		else if(i >= 0x90 && i <= 0x96)
		{
			cnt++;
		}
		else if(i == 0xA0)
		{
			cnt++;
		}
		else if(i >= 0xB0 && i <= 0xBF)
		{
			/*if(smb_ver <= 2.5 && (i>=0xBD && i <=0xBF))
				{}
			else*/
				cnt++;
		}
		else if(i >= 0xC8 && i <= 0xCC)
		{
			/*if(smb_ver <= 2.5 && (i>=0xCB && i <=0xCC))
				{}
			else*/
				cnt++;
		}
		else if(i >= 0xD2 && i <= 0xD5)
		{
			//if(smb_ver >= 2.6)
				cnt++;
		}
		else if(i >= 0xFA && i <= 0xFB)
		{
			cnt++;
		}
		else if(i >= 0xFE && i <= 0xFF /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i >= 0x104 && i <= 0x105 /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i >= 0x118 && i <= 0x119 /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i >= 0x12C && i <= 0x12E /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i == 0x140 /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i == 0x15E /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i == 0x1f4 /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i >= 0xFFFE && i <= 0xFFFF /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		
		if(i == (DWORD)no)
		{
			break;
		}
	}
	return cnt;
}
