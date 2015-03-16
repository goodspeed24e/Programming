#include <dos.h> 
#include <bios.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <direct.h>
#include "func.h"
#include "pci.h"

BYTE	temp1[20];

BYTE pci_reg[19][16];
char	str[80];//顯示資料用字元陣列

int PCI_cnt=0;//抓到的PCI裝置數

PCI_info get_pci[50];//取得的PCI裝置資訊
BYTE in_bus,in_dev,in_func;

DWORD Pci_E_addr=0;

WORD max_page;

DWORD BDF_num;

SYSTEM_Info sys_info;


void main( void )
{
	clrscr();
	memset(get_pci,'0',sizeof(get_pci));
	GetAllPCI();
	GUI();
}


char *ChangeClass(WORD ClassID)
{
	WORD mclass,sclass;
	
	//memset(str,'\0',sizeof(str));
	
	mclass = ClassID >> 8;
	sclass = ClassID & 0x00ff;
	
	switch(mclass)
	{
		case 0:
			return "(Old Device(PCI 2.0))";
			break;
		case 1:
			if(sclass == 0)
			{
				return "(SCSI Bus Controller)";
			}
			else if(sclass == 1)
			{
				return "(IDE Controller)";
			}
			else if(sclass == 2)
			{
				return "(Floppy Controller)";
			}
			else if(sclass == 3)
			{
				return "(IPI Controller)";
			}
			else if(sclass == 4)
			{
				return "(RAID Controller)";
			}
			else
			{
				return "(Another Controller)";
			}
			break;
		case 2:
			if(sclass == 0)
			{
				return "(Ethernet Network)";
			}
			else if(sclass == 1)
			{
				return "(Token Ring)";
			}
			else if(sclass == 2)
			{
				return "(FDDI Controller)";
			}
			else if(sclass == 3)
			{
				return "(ATM Controller)";
			}
			else if(sclass == 4)
			{
				return "(ISDN Controller)";
			}
			else
			{
				return "(Other network)";
			}
			break;
		case 3:
			if(sclass == 0)
			{
				return "(VGA Graphics)";
			}
			else if(sclass == 1)
			{
				return "(XGA Graphics)";
			}
			else if(sclass == 2)
			{
				return "(3D Graphics)";
			}
			else
			{
				return "(Other Graphics)";
			}
			break;
		case 4:
			if(sclass == 0)
			{
				return "(Video Multimedia)";
			}
			else if(sclass == 1)
			{
				return "(Audeo Multimedia)";
			}
			else if(sclass == 2)
			{
				return "(Phone Multimedia)";
			}
			else
			{
				return "(Other Multimedia)";
			}
			break;
		case 6:
			if(sclass == 0)
			{
				return "(Host to PCI Bridge)";
			}
			else if(sclass == 1)
			{
				return "(PCI to ISA Bridge)";
			}
			else if(sclass == 2)
			{
				return "(PCI to EISA Bridge)";
			}
			else if(sclass == 3)
			{
				return "(PCI to Micro Channel Bridge)";
			}
			else if(sclass == 4)
			{
				return "(PCI to PCI Bridge)";
			}
			else if(sclass == 5)
			{
				return "(PCI to PCMCIA Bridge)";
			}
			else if(sclass == 6)
			{
				return "(PCI to NuBus Bridge)";
			}
			else if(sclass == 7)
			{
				return "(PCI to CardBus Bridge)";
			}
			else if(sclass == 8)
			{
				return "(RACEway Bridge)";
			}
			else
			{
				return "(Other Bridge)";
			}
			break;
			
		case 12:
			if(sclass == 0)
			{
				return "(IEEE 1394)";
			}
			else if(sclass == 1)
			{
				return "(ACCESS.bus)";
			}
			else if(sclass == 2)
			{
				return "(Serial Storage Architecture)";
			}
			else if(sclass == 3)
			{
				return "(Universal Serial Bus[USB])";
			}
			else if(sclass == 4)
			{
				return "(Fiber Channel)";
			}
			else if(sclass == 5)
			{
				return "(System Management Bus)";
			}
			break;
		
		default:
			return "(Unknow/Reserved)";
	}
}

char *ChangeVendor(WORD Vendor)
{
	//memset(temp1,'\0',sizeof(temp1));
	
	switch(Vendor)
	{
		case 0x10de:
			return "(Nvidia)";
			break;
			
		case 0x11C0:
			return "(HP)";
			break;
			
		case 0x1170:
			return "(Inventec)";
			break;
			
		case 0x0e11:
			return "(Compaq)";
			break;
			
		case 0x1000:
			return "(Symbios)";
			break;
			
		case 0x1002:
			return "(ATI)";
			break;
			
		case 0x1005:
			return "(Advance)";
			break;
			
		case 0x100A:
			return "(Phoenix)";
			break;
			
		case 0x1011:
			return "(Digital)";
			break;
			
		case 0x1013:
			return "(Cirrus)";
			break;
			
		case 0x1014:
			return "(IBM)";
			break;
			
		case 0x101A:
		case 0x11C1:
			return "(AT&T)";
			break;
			
		case 0x1022:
			return "(AMD)";
			break;
		case 0x103C:
			return "(HP)";
			break;
			
		case 0x1077:
			return "(QLogic)";
			break;
			
		case 0x1023:
			return "(Trident)";
			break;
			
		case 0x1025:
			return "(Acer)";
			break;
			
		case 0x102A:
			return "(LSI)";
			break;
			
		case 0x1050:
			return "(Winbond)";
			break;
			
		case 0x1057:
			return "(Motorola)";
			break;
			
		case 0x10B7:
			return "(3COM)";
			break;
			
		case 0x1102:
			return "(Creative)";
			break;
			
		case 0x1166:
			return "(ServerWorks)";
			break;
			
		case 0x14e4:
			return "(BROADCOM)";
			break;
		
		case 0x4005:
			return "(Avance)";
			break;
			
		case 0x8086:
			return "(Intel)";
			break;
			
		case 0x9004:
		case 0x9005:
			return "(Adaptec)";
			break;
		
		case 0x1106:
			return "(VIA)";
			break;
		
		case 0x1186:
			return "(D-Link)";
			break;
	}
}

void GetAllPCI( void )
{//取得所有的PCI
	WORD i,j,k;
	WORD Vendor;//製造廠商
	WORD Device;//裝置
	WORD ClassID;//
	DWORD tmp;
	BYTE tp;
	BYTE FW,mm;
	WORD pp;
	
	PCI_cnt = 0;
	for(i = 0; i < 256; i++)
	{
		for(j = 0; j < 32; j++)
		{
			for(k = 0; k < 8; k++)
			{
				Vendor = read_pci_word(i,j,k,0x00);
				
				if(k == 0)
				{//如果是第一次，判斷是否為單一功能裝置
					tp = (read_pci_byte(i,j,k,0x0e)) & 0x80;
				}
				if(Vendor != 0xffff)
				{
					Device = read_pci_word(i,j,k,0x02);
					ClassID = read_pci_word(i,j,k,0x0a);
					FW = read_pci_byte(i,j,k,0x08);
					get_pci[PCI_cnt].Vendor = Vendor;
					get_pci[PCI_cnt].Device = Device;
					get_pci[PCI_cnt].ClassID = ClassID;
					get_pci[PCI_cnt].FW = FW;
					tmp = 0;
					tmp = i;
					tmp <<= 16;
					tmp |= (j << 8);
					tmp |= k;
					get_pci[PCI_cnt].PCINO = tmp;
					
					get_pci[PCI_cnt].IRQ = read_pci_byte(i,j,k,0x3c);
					
					get_pci[PCI_cnt].PciE = 0;
					if(((read_pci_byte(i,j,k,0x6)>>4) & 0x01)==0x01)
					{
						mm = read_pci_byte(i,j,k,0x34) & 0xfc;
						while(mm)
						{
							pp = read_pci_word(i,j,k,mm);
							mm = (unsigned char)((pp >> 8) & 0xff);
							if( (pp & 0x00ff) == 0x10)
							{
								get_pci[PCI_cnt].PciE = 1;
								break;
							}
						}
					}
					PCI_cnt++;
				}
				if(k == 0 && tp != 0x80)
				{//單一功能裝置
					break;
				}
			}
		}
	}
}


/******************************************************************************************
傳入值：errorlevel
傳回值：無

*******************************************************************************************/
void quit( int errorlevel )
{//結束程式
	printf("Error level = %d",errorlevel);
	if(errorlevel != 0)
	{
		puts("\a");
	}
	exit(errorlevel);
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

void V_Scroll(BYTE sx,BYTE sy,BYTE ey,WORD select,WORD total)
{
	BYTE y,posi;
	double t1;
//	WORD i;

	for(y = sy; y <= ey; y++)
	{
		gotoxy(sx,y);
		WriteChar(0xb0);//直的
	}
	
	//畫捲軸的位置方塊
	if(total > 21)
	{
		if(select == total) //已在最後
		{
			posi = 18;
		}
		else if(select == 0)
		{
			posi = 0;
		}
		else
		{
			t1 = (double)select;
			posi = (BYTE)(t1/((double)total/19.0));
		}
		gotoxy(78,(BYTE)(3+posi));
		WriteChar(0xdb);//
	}
	
	gotoxy(78,2);
	WriteChar(0x1E);//
	gotoxy(78,22);
	WriteChar(0x1F);//
}

void show_device()
{
	WORD i;
	WORD B,D,F;
	BYTE j;
	
	j = 0;
	for(i = sys_info.display_start; i < (WORD)PCI_cnt; i++)
	{
		//ChangeVendor(get_pci[i].Vendor);
		//ChangeClass(get_pci[i].ClassID);
		B = (WORD)((get_pci[i].PCINO) >> 16);
		D = (WORD)((get_pci[i].PCINO) >> 8)&0x000000ff;
		F = (WORD)((get_pci[i].PCINO) & 0x000000ff);
		
		if(get_pci[i].PciE != 0)
		{
			gotoxy(1,(BYTE)(2+j));
			color_printf(B_WHITE | F_BLACK,"*");
		}
		else
		{
			gotoxy(1,(BYTE)(2+j));
			color_printf(B_WHITE | F_BLACK," ");
		}
		
		gotoxy(2,(BYTE)(2+j));
		//temp1[13] = '\0'; //不超過13個字
		color_printf(B_WHITE | F_BLACK,"%4Xh%-13s",get_pci[i].Vendor,ChangeVendor(get_pci[i].Vendor));
		
		gotoxy(23,(BYTE)(2+j));
		color_printf(B_WHITE | F_BLACK,"%4Xh",get_pci[i].Device);
		
		gotoxy(29,(BYTE)(2+j));
		color_printf(B_WHITE | F_BLACK,"%4Xh%-27s",get_pci[i].ClassID,ChangeClass(get_pci[i].ClassID));
		
		gotoxy(65,(BYTE)(2+j));
		color_printf(B_WHITE | F_BLACK,"%02Xh %02Xh %02Xh",B,D,F);
		
		if(j >= 20) // 超過顯示數量
		{
			break;
		}
		j++;
	}
}

void draw_select(void)
{
	WORD B,D,F;
	
	if(sys_info.pre_select != sys_info.current_select)
	{//還原前一個被選到的
		Block(1,(BYTE)(sys_info.pre_select+2),77,(BYTE)(sys_info.pre_select+2),B_WHITE);
		
		//ChangeVendor(get_pci[sys_info.display_start+sys_info.pre_select].Vendor);
		//ChangeClass(get_pci[sys_info.display_start+sys_info.pre_select].ClassID);
		B = (WORD)((get_pci[sys_info.display_start+sys_info.pre_select].PCINO) >> 16);
		D = (WORD)((get_pci[sys_info.display_start+sys_info.pre_select].PCINO) >> 8)&0x000000ff;
		F = (WORD)((get_pci[sys_info.display_start+sys_info.pre_select].PCINO) & 0x000000ff);
		
		if(get_pci[sys_info.display_start+sys_info.pre_select].PciE != 0)
		{
			gotoxy(1,(BYTE)(2+sys_info.pre_select));
			color_printf(B_WHITE | F_BLACK,"*");
		}
		else
		{
			gotoxy(1,(BYTE)(2+sys_info.pre_select));
			color_printf(B_WHITE | F_BLACK," ");
		}
		
		gotoxy(2,(BYTE)(2+sys_info.pre_select));
		//temp1[13] = '\0'; //不超過13個字
		color_printf(B_WHITE | F_BLACK,"%4Xh%-13s",get_pci[sys_info.display_start+sys_info.pre_select].Vendor,ChangeVendor(get_pci[sys_info.display_start+sys_info.pre_select].Vendor));
		
		gotoxy(23,(BYTE)(2+sys_info.pre_select));
		color_printf(B_WHITE | F_BLACK,"%4Xh",get_pci[sys_info.display_start+sys_info.pre_select].Device);
		
		gotoxy(29,(BYTE)(2+sys_info.pre_select));
		color_printf(B_WHITE | F_BLACK,"%4Xh%-27s",get_pci[sys_info.display_start+sys_info.pre_select].ClassID,ChangeClass(get_pci[sys_info.display_start+sys_info.pre_select].ClassID));
		
		gotoxy(65,(BYTE)(2+sys_info.pre_select));
		color_printf(B_WHITE | F_BLACK,"%02Xh %02Xh %02Xh",B,D,F);
	}
	
	Block(1,(BYTE)(sys_info.current_select+2),77,(BYTE)(sys_info.current_select+2),B_MAGENTA);
		
	//ChangeVendor(get_pci[sys_info.display_start+sys_info.current_select].Vendor);
	//ChangeClass(get_pci[sys_info.display_start+sys_info.current_select].ClassID);
	B = (WORD)((get_pci[sys_info.display_start+sys_info.current_select].PCINO) >> 16);
	D = (WORD)((get_pci[sys_info.display_start+sys_info.current_select].PCINO) >> 8)&0x000000ff;
	F = (WORD)((get_pci[sys_info.display_start+sys_info.current_select].PCINO) & 0x000000ff);
	
	if(get_pci[sys_info.display_start+sys_info.current_select].PciE != 0)
	{
		gotoxy(1,(BYTE)(2+sys_info.current_select));
		color_printf(B_MAGENTA | F_WHITE,"*");
	}
	else
	{
		gotoxy(1,(BYTE)(2+sys_info.current_select));
		color_printf(B_MAGENTA | F_WHITE," ");
	}
		
	gotoxy(2,(BYTE)(2+sys_info.current_select));
	temp1[13] = '\0'; //不超過13個字
	color_printf(B_MAGENTA | F_WHITE,"%4Xh%-13s",get_pci[sys_info.display_start+sys_info.current_select].Vendor,ChangeVendor(get_pci[sys_info.display_start+sys_info.current_select].Vendor));
	
	gotoxy(23,(BYTE)(2+sys_info.current_select));
	color_printf(B_MAGENTA | F_WHITE,"%4Xh",get_pci[sys_info.display_start+sys_info.current_select].Device);
	
	gotoxy(29,(BYTE)(2+sys_info.current_select));
	color_printf(B_MAGENTA | F_WHITE,"%4Xh%-27s",get_pci[sys_info.display_start+sys_info.current_select].ClassID,ChangeClass(get_pci[sys_info.display_start+sys_info.current_select].ClassID));
	
	gotoxy(65,(BYTE)(2+sys_info.current_select));
	color_printf(B_MAGENTA | F_WHITE,"%02Xh %02Xh %02Xh",B,D,F);
	
	V_Scroll(78,3,21,(WORD)(sys_info.display_start+sys_info.current_select),PCI_cnt);
}

void tool_bar(int sld)
{
	gotoxy(1,23);
	
	if(sld==0)
	{
		color_printf(B_BLUE | F_LIGHT_WHITE," Enter:View/Edit        :Move      F10:Exit     *:PCI-Express                  ");
		gotoxy(23,23);
		WriteChar(0x18);//
		gotoxy(24,23);
		WriteChar(0x19);//
	}
	else
	{
		color_printf(B_BLUE | F_LIGHT_WHITE,"                     :Move  ESC:Return  F10:Exit  PgUp/PgDown:Change page");
		
		//Block(1,1,78,1,B_BLUE); //清除vendor ,device等字
		
		gotoxy(18,23);
		WriteChar(0x18);//
		gotoxy(19,23);
		WriteChar(0x19);//
		gotoxy(20,23);
		WriteChar(0x1b);//
		gotoxy(21,23);
		WriteChar(0x1a);//
	}
}

void Col_NO(void)
{//畫垂直的數字
	int i,j,end,posi;
	
	j = 0;
	if(sys_info.reg_start < 16)
	{
		j = sys_info.reg_start;
		end = 16-sys_info.reg_start;
		//畫出直的數字
		for(i = 0; i < end; i++)
		{
			gotoxy(1,(BYTE)(4+i));
			color_printf(B_BROWN | F_WHITE,"%03Xx",j);
			j++;
		}
	}
	if(get_pci[sys_info.display_start+sys_info.current_select].PciE != 0)
	{
		if(j != 0) //有畫前256的欄號
		{
			end = 19-(16-sys_info.reg_start);
			posi = 16-sys_info.reg_start;
		}
		else
		{
			end = 19;
			posi = 0;
			j = sys_info.reg_start;
		}
		for(i = 0; i < end; i++)
		{ 
			gotoxy(1,(BYTE)(4+posi+i));
			if(j < 0x100)
			{
				color_printf(B_GREEN | F_LIGHT_WHITE,"%03Xx",j);
			}
			else
			{
				color_printf(B_GREEN | F_LIGHT_WHITE,"    ");
			}
			j++;
		}
	}
}

void reg_cursor(void)
{
	BYTE x,tmp;

	tmp = sys_info.reg_x / 2;
	
	x = (BYTE)(sys_info.reg_x + tmp+6);
	gotoxy(x,(BYTE)(sys_info.reg_y+4));
}

void write_enable(void)
{
	gotoxy(1,23);
	
	if(sys_info.write_en==0)
	{
		color_printf(B_BLUE | F_GRAY,"               ");
	}
	else
	{
		color_printf(B_BLUE | F_LIGHT_WHITE,"    Enter:Write");
	}
}

void reg_input(int ch)
{
	color_printf(B_WHITE | F_BLACK,"%c",ch);
	
	if((sys_info.reg_x % 2)==0) //修改第一個，游標往下一個移動，要補上第2個
	{
		if(ch >= '0' && ch <= '9')
		{
			sys_info.reg_value = (BYTE)(ch-0x30);
		}
		else
		{
			sys_info.reg_value = (BYTE)(ch-0x37);
		}
		sys_info.reg_value <<= 4;
		
		sys_info.reg_value |= (pci_reg[sys_info.reg_y][sys_info.reg_x/2] & 0x0f);
		sys_info.reg_x++;
		sys_info.write_en = 1;
	}
	else //修改第2個，要補上第一個
	{
		sys_info.reg_value = (pci_reg[sys_info.reg_y][sys_info.reg_x/2] & 0xf0);
		if(ch >= '0' && ch <= '9')
		{
			sys_info.reg_value |= (BYTE)(ch-0x30);
		}
		else
		{
			sys_info.reg_value |= (BYTE)(ch-0x37);
		}
		sys_info.write_en = 1;
	}
	write_enable();
	reg_cursor();
	
}

void display_data(int x,int y, BYTE data)
{
	BYTE tmp;
	
	tmp = x * 3+6;
	gotoxy(tmp,(BYTE)(y+4));
	color_printf(B_WHITE | F_BLACK,"%02X",data);
		
	//ASCII code
	gotoxy((BYTE)(62+x),(BYTE)(y+4));
	if(data >= 0x20 && data <= 0x7e)
	{//如果是一般的字元
		color_printf(B_WHITE | F_BLACK,"%c",data);
	}
	else
	{//特殊字元，用.表示
		color_printf(B_WHITE | F_BLACK,".");
	}
}

void Read_pci_reg(void)
{
	DWORD data;
//	BYTE b,d,f;
	int i,off,x,y,j;
	
	x = y = 0;
	off = sys_info.reg_start*16;
	
	for(i = 0; i < 19*4; i++)
	{
		if(get_pci[sys_info.display_start+sys_info.current_select].PciE==0)
		{
			data = read_pci_dword(sys_info.select_bus,sys_info.select_dev,sys_info.select_func,off);
		}
		else
		{
			if((sys_info.reg_start*16+i) >= 0x1000)
			{
				break;
			}
			else
			{
				into_PT_mode();
	
				data = read_mem_dword(Pci_E_addr+off);
	
				into_RL_mode();
				//data = 0xff;
			}
		}
		off += 4;
		for(j = 0; j < 4; j++)
		{
			pci_reg[y][x] = (BYTE)(data >> (8*j));
			x++;
		}
		if(x == 16)
		{
			x = 0;
			y++;
		}
	}
	
	HideCursor();
	
	//show data out
	x = y = 0;
	for(i = 0; i < 19*16; i++)
	{
		if((sys_info.reg_start*16)+i >= 0x1000)
		{
			BYTE off;
			
			off = (BYTE)(sys_info.reg_start-0xed);
			Block(6,(BYTE)(20-off),78,22,B_WHITE);
			if(off != 0)
			{
				sys_info.reg_y -= off;
			}
			break;
		}
		else
		{
			display_data(x,y,pci_reg[y][x]);
		}
		x++;
		if(x == 16)
		{
			x = 0;
			y++;
		}
		if(get_pci[sys_info.display_start+sys_info.current_select].PciE==0)
		{
			if(i == ((16*16)-1))
			{
				break;
			}
		}
	}
	
	reg_cursor();
}

void Edit_reg(void)
{
	int ch1,ch2,max_y;
	DWORD addr;
//	WORD B,D,F;
	
	//initial parameters
	sys_info.reg_x = 0;
	sys_info.reg_y = 0;
	sys_info.reg_start = 0;
	sys_info.write_en = 0; //不能寫入
	
	Block(1,2,78,22,B_WHITE);
	
	//V_Scroll(78,3,21,0,0xFFF,1);
	
	//顯示被選擇的裝置資料
	//ChangeVendor(get_pci[sys_info.display_start+sys_info.current_select].Vendor);
	//ChangeClass(get_pci[sys_info.display_start+sys_info.current_select].ClassID);
	sys_info.select_bus = (BYTE)((get_pci[sys_info.display_start+sys_info.current_select].PCINO) >> 16);
	sys_info.select_dev = (BYTE)((get_pci[sys_info.display_start+sys_info.current_select].PCINO) >> 8)&0x000000ff;
	sys_info.select_func = (BYTE)((get_pci[sys_info.display_start+sys_info.current_select].PCINO) & 0x000000ff);
	
	if(Search_PciE_ex(sys_info.select_bus,sys_info.select_dev,sys_info.select_func) != 0)
	{//無法從memory中讀到資料，轉為PCI的IO方式
		get_pci[sys_info.display_start+sys_info.current_select].PciE=0;
	}
	
	Block(1,2,78,2,B_MAGENTA);
		
	gotoxy(2,2);
	temp1[13] = '\0'; //不超過13個字
	color_printf(B_MAGENTA | F_LIGHT_WHITE,"%4Xh%-13s",get_pci[sys_info.display_start+sys_info.current_select].Vendor,ChangeVendor(get_pci[sys_info.display_start+sys_info.current_select].Vendor));
	
	gotoxy(23,2);
	color_printf(B_MAGENTA | F_LIGHT_WHITE,"%4Xh",get_pci[sys_info.display_start+sys_info.current_select].Device);
	
	gotoxy(29,2);
	color_printf(B_MAGENTA | F_LIGHT_WHITE,"%4Xh%-27s",get_pci[sys_info.display_start+sys_info.current_select].ClassID,ChangeClass(get_pci[sys_info.display_start+sys_info.current_select].ClassID));
	
	gotoxy(65,2);
	color_printf(B_MAGENTA | F_LIGHT_WHITE,"%02Xh %02Xh %02Xh",sys_info.select_bus,sys_info.select_dev,sys_info.select_func);
	
	//畫出橫的數字
	gotoxy(1,3);
	color_printf(B_BROWN | F_WHITE,"   x: 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F            ASCII code    ");
	
	Col_NO(); // 垂直數字
	
	Read_pci_reg();

	reg_cursor();
	ShowCursor();
	
	if(get_pci[sys_info.display_start+sys_info.current_select].PciE != 0)
	{
		max_y = 0x1000;
		max_page = 0x1000/0x130;
	}
	else
	{
		max_y = 15;
		max_page = 0;
	}
	
	while(1)
	{
		if(kbhit() != 0)
		{
			ch1 = getch();
			if(ch1 == 0) //特殊功能鍵
			{
				ch2 = getch();
					//gotoxy(1,24);
					//color_printf(F_BLACK | B_CYAN,"ch2=%x      ",ch2);
				switch(ch2)
				{
					case 0x50: //下箭頭
						if(sys_info.reg_y < max_y)
						{
							if(sys_info.write_en != 0)
							{
								//還原成原本的文字
								display_data(sys_info.reg_x/2,sys_info.reg_y,pci_reg[sys_info.reg_y][sys_info.reg_x/2]);
							}
							if(sys_info.reg_y < 18)
							{
								sys_info.reg_y++;
							}
							else
							{//更新資料
								if((sys_info.reg_start+sys_info.reg_y) < 0xff)
								{
									sys_info.reg_start++;
									max_page = (0x1000-(sys_info.reg_start*16))/0x130;
									Col_NO(); // 垂直數字
									Read_pci_reg();
									ShowCursor();
								}
							}
							sys_info.write_en = 0;
						}
						break;
						
					case 0x48: //上箭頭
						if(sys_info.reg_y != 0)
						{
							
							if(sys_info.write_en != 0)
							{
								//還原成原本的文字
								display_data(sys_info.reg_x/2,sys_info.reg_y,pci_reg[sys_info.reg_y][sys_info.reg_x/2]);
							}
							sys_info.reg_y--;
							sys_info.write_en = 0;
						}
						else
						{//如果最上面還有資料
							if(sys_info.reg_start != 0)
							{
								sys_info.reg_start--;
								max_page = (0x1000-(sys_info.reg_start*16))/0x130;
								Col_NO(); // 垂直數字
								Read_pci_reg();
								ShowCursor();
							}
						}
						break;
						
					case 0x4b: //向左箭頭
						if(sys_info.reg_x != 0)
						{
							if((sys_info.reg_x %2)==0) //換到其它欄了，取消write
							{
								if(sys_info.write_en != 0)
								{
									//還原成原本的文字
									display_data(sys_info.reg_x/2,sys_info.reg_y,pci_reg[sys_info.reg_y][sys_info.reg_x/2]);
								}
								sys_info.write_en = 0;
							}
							sys_info.reg_x--;
						}
						else if(sys_info.reg_y != 0)
						{
							if(sys_info.write_en != 0)
							{
								//還原成原本的文字
								display_data(sys_info.reg_x/2,sys_info.reg_y,pci_reg[sys_info.reg_y][sys_info.reg_x/2]);
							}
							
							sys_info.reg_x=31;
							sys_info.reg_y--;
							sys_info.write_en = 0;
						}
						break;
						
					case 0x4d: //向右箭頭
						if(sys_info.reg_x < 31)
						{
							if((sys_info.reg_x %2) != 0) //換到其它欄了，取消write
							{
								if(sys_info.write_en != 0)
								{
									//還原成原本的文字
									display_data(sys_info.reg_x/2,sys_info.reg_y,pci_reg[sys_info.reg_y][sys_info.reg_x/2]);
								}
								sys_info.write_en = 0;
							}
							sys_info.reg_x++;
							
							//
						}
						else if(sys_info.reg_y < max_y)//準備換行
						{
							if(sys_info.write_en != 0)
							{
								//還原成原本的文字
								display_data(sys_info.reg_x/2,sys_info.reg_y,pci_reg[sys_info.reg_y][sys_info.reg_x/2]);
							}
							sys_info.reg_x=0;
							sys_info.reg_y++;
							sys_info.write_en = 0;
						}
						break;
						
					case 0x49: //page up
						if(sys_info.reg_start != 0) //只要有上捲就可以跳頁
						{
							//檢查是否還有19行
							if(sys_info.reg_start > 19)
							{
								sys_info.reg_start -= 19;
							}
							else
							{
								sys_info.reg_start = 0;
							}
							max_page = (0x1000-(sys_info.reg_start*16))/0x130;
//								gotoxy(1,24);
//								color_printf(B_BLACK | F_WHITE," mp:%d ",max_page);
//								color_printf(B_BLACK | F_WHITE," RS:%x ",sys_info.reg_start);
							sys_info.write_en = 0;
							Col_NO(); // 垂直數字
							Read_pci_reg();
							ShowCursor();
						}
						break;
						
					case 0x51: //page down
						if(max_page != 0) //只要下面還有資料就可以跳頁
						{
							//檢查是否還有19行
							if((sys_info.reg_start+sys_info.reg_y) < 0xe4)
							{
								sys_info.reg_start += 19;
							}
							else
							{
								sys_info.reg_start = 0xed;
							}
							max_page = (0x1000-(sys_info.reg_start*16))/0x130;
//								gotoxy(1,24);
//								color_printf(B_BLACK | F_WHITE," mp:%d ",max_page);
//								color_printf(B_BLACK | F_WHITE," RS:%x ",sys_info.reg_start);
							sys_info.write_en = 0;
							Col_NO(); // 垂直數字
							Read_pci_reg();
							ShowCursor();
						}
						break;
							
					case 0x44: // F10 Exit
						clrscr();
						ShowCursor();
						quit(0);
				}
				//	gotoxy(1,24);
				//	color_printf(F_BLACK | B_CYAN,"x=%d y=%d start=%d     ",sys_info.reg_x,sys_info.reg_y,sys_info.reg_start);
				//V_Scroll(78,3,21,(sys_info.reg_y+sys_info.reg_start),0xFFF,1);
				write_enable();
				reg_cursor();
			}
			else if(ch1 == 27) //ESC
			{
				HideCursor();
				return;
			}
			else if(ch1 == 13) //Enter(使用者寫入資料到PCI reg)
			{
				if(sys_info.write_en != 0)
				{
					if(get_pci[sys_info.display_start+sys_info.current_select].PciE==0)
					{
						pci_reg[sys_info.reg_y][sys_info.reg_x/2] = sys_info.reg_value;
						//寫回PCI deivce
						write_pci_byte(sys_info.select_bus,sys_info.select_dev,sys_info.select_func,(sys_info.reg_y*16+sys_info.reg_x/2),sys_info.reg_value);
						//讀回來更新
						sys_info.reg_value = read_pci_byte(sys_info.select_bus,sys_info.select_dev,sys_info.select_func,(sys_info.reg_y*16+sys_info.reg_x/2));;
					
						pci_reg[sys_info.reg_y][sys_info.reg_x/2] = sys_info.reg_value;
					
						display_data(sys_info.reg_x/2,sys_info.reg_y,sys_info.reg_value);
					
						sys_info.write_en = 0;
						write_enable();
						reg_cursor();
					}
					else
					{
						pci_reg[sys_info.reg_y][sys_info.reg_x/2] = sys_info.reg_value;
						
						addr = Pci_E_addr + sys_info.reg_start*16 + sys_info.reg_y*16 + (sys_info.reg_x/2);
						
						into_PT_mode();
	
						write_mem_byte(addr,sys_info.reg_value);
						sys_info.reg_value = read_mem_byte(addr);
						
						into_RL_mode();
					
						pci_reg[sys_info.reg_y][sys_info.reg_x/2] = sys_info.reg_value;
					
						display_data(sys_info.reg_x/2,sys_info.reg_y,sys_info.reg_value);
					
						sys_info.write_en = 0;
						write_enable();
						reg_cursor();
					}
				}
			}
			else if((ch1 >= '0' && ch1 <= '9') || (ch1 >='A' && ch1 <= 'F'))
			{
				reg_input(ch1);
				
			}
			else if(ch1 >='a' && ch1 <= 'f')
			{
				reg_input((ch1-0x20));
			}
		}
	}
}



void GUI( void )
{
	int ch1,ch2;
	
	clrscr();
	HideCursor();
	
	Block(0,0,79,24,B_BLUE);
	
	gotoxy(0,0);
	color_printf(B_BROWN | F_BLUE,"                              DOSPCI.EXE Rev:v1.0                                        ");
	
	gotoxy(0,1);
	color_printf(B_BLUE | F_LIGHT_GREEN,"  Vendor              Device  Class                              Bus/Dev/Func   ");
	
	Block(1,2,78,22,B_WHITE);
	
	tool_bar(0);
	
	gotoxy(0,24);
	color_printf(B_BROWN | F_BLUE,"                                                                         Intra  ");
	
	V_Scroll(78,2,22,0,PCI_cnt);
	
	
	//initial system info
	sys_info.current_select = 0;
	sys_info.pre_select = 0;
	sys_info.display_start = 0; 
	
	
	//show all PCI devices
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
//						color_printf(F_BLACK | B_CYAN,"ch1 is %XH, ch2 is %XH\n",ch1,ch2);
//re_loop:
					switch(ch2)
					{
						case 0x50: //下箭頭
							if(sys_info.current_select < 20)
							{
								if(sys_info.current_select < (BYTE)(PCI_cnt-1)) //小於總裝置數才可以下移
								{
									sys_info.pre_select = sys_info.current_select;
									sys_info.current_select ++;
								}
							}
							else //超過顯示範圍，判斷是否下捲
							{
								if((sys_info.display_start+sys_info.current_select) < (BYTE)(PCI_cnt-1)) //下面還有裝置，下捲
								{
									sys_info.pre_select = sys_info.current_select;
									sys_info.display_start++;
									show_device();
								}
							}
							break;
						
						case 0x48: //上箭頭
							if(sys_info.current_select > 0)
							{
								sys_info.pre_select = sys_info.current_select;
								sys_info.current_select--;
							}
							else //超過顯示範圍，判斷是否上捲
							{
								if((sys_info.display_start+sys_info.current_select) != 0) // 上面還有裝置，上捲
								{
									sys_info.pre_select = sys_info.current_select;
									sys_info.display_start--;
									show_device();
								}
							}
								
							break;

						case 0x44: // F10 Exit
							clrscr();
							ShowCursor();
							return;
					}
					//	gotoxy(1,24);
					//	color_printf(F_BLACK | B_CYAN,"cur=%d pre=%d dis=%d",sys_info.current_select,sys_info.pre_select,sys_info.display_start);
					draw_select();
					break;
					
				case 13://Enter(使用者選擇裝置)
					tool_bar(1);
					Edit_reg();
					
					//選擇完，回復未選擇前顯示
					sys_info.pre_select = sys_info.current_select;
					Block(1,2,78,22,B_WHITE);
					V_Scroll(78,2,22,0,PCI_cnt);
					show_device();
					draw_select();
					tool_bar(0);
					break;
			}//end of switch(ch1)
		}//end of if(kbhit())
	}
}

int Search_PciE_ex(BYTE bus,BYTE dev,BYTE func)
{
	int cct=0;
	DWORD tmp,data1,data2;
	
	/*
	PCI bus address to Memory address format:
	+-----------------------------------------+
	| 1110 bbbb bbbb dddd dfff 0000 0000 0000 |
	+-----------------------------------------+
	   ^
	   + OEM define
	 這裡是偷懶的作法，正確作法應該是要去讀取ACPI的MCFG，從裡面得到PCI Express base address
	 
	*/
	
	data1 = read_pci_dword(bus,dev,func,0);
	
	Pci_E_addr = 0x10000000;
	
	into_PT_mode();
	while(1)
	{
		if((Pci_E_addr&0xF0000000)!=0xF0000000)
		{
			Pci_E_addr += cct * 0x10000000;
			if(!cct)
			{
				tmp = (DWORD)bus;
				Pci_E_addr |= tmp << 20;
				tmp = (DWORD)dev;
				Pci_E_addr |= tmp << 15;
				tmp = (DWORD)func;
				Pci_E_addr |= tmp << 12;
			}
			cct++;
		}
		else
		{
			into_RL_mode();
			return 1;
		}

		data2 = read_mem_dword(Pci_E_addr);
		if(data1 == data2)
		{//透過IO讀到的要跟memory讀到的一樣
			break;
		}
	}
	
	into_RL_mode();
	
	return 0;
}


