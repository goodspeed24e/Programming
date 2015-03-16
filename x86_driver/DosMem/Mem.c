#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "func.h"


DWORD addr=0;
BYTE dataBuf[16][16],cursor_x,cursor_y,tmp_value;
BOOL modify_first=0;

void ReadData(void);
void show_all(void);
void display_data(BYTE x,BYTE y,BYTE data);
void EditMemory(int ch);
void reg_cursor(void);
void ShowHotKey(void);
void SetAddress(void);
void SearchData(int sld);

void main(int argc, char **argv)
{
	int ch;
	BYTE x,y;

	if(argc > 1)
	{
		hextoi(*(argv+1),&addr);//
	}
	
	
	into_PT_mode();
	HideCursor();
	
	clrscr();
	ShowTitle("DosMem v1.0");
	
	ShowHotKey();
	
	ReadData();
	
	show_all();
	
	gotoxy(12,4);
	ShowCursor();

	cursor_x = 0;
	cursor_y = 0;
	while(1)
	{
		ch = getch();
		switch(ch)
		{
			case 0: //特殊鍵，再抓一次
				ch = getch();
				if(ch == 0x48)
				{//上
					if(cursor_y != 0)
					{
						cursor_y--;
						reg_cursor();
					}
				}
				else if(ch == 0x50)
				{//下
					if(cursor_y < 15)
					{
						cursor_y++;
						reg_cursor();
					}
				}
				else if(ch == 0x4b)
				{//左
					if(cursor_x != 0)
					{
						cursor_x--;
						reg_cursor();
					}
					else if(cursor_y != 0)
					{
						cursor_y--;
						cursor_x = 31;
						reg_cursor();
					}
				}
				else if(ch == 0x4d)
				{//右
					if(cursor_x <= 30)
					{
						cursor_x++;
						reg_cursor();
					}
					else if(cursor_y < 15)
					{
						cursor_x = 0;
						cursor_y++;
						reg_cursor();
					}
				}
				else if(ch == 0x49)
				{//page up
					if(addr > 0)
					{
						if(addr > 255)
						{
							addr -= 256;
						}
						else
						{
							addr = 0;
						}
						ReadData();
						show_all();
						gotoxy(12,4);
						cursor_x = 0;
						cursor_y = 0;
					}
				}
				else if(ch == 0x51)
				{//page down
					if(addr < 0xffffff00)
					{
						if(addr >= 0xffffff00)
						{
							addr = 0xffffff00;
						}
						else
						{
							addr += 256;
						}
						ReadData();
						show_all();
						gotoxy(12,4);
						cursor_x = 0;
						cursor_y = 0;
					}
				}
				break;
			case 27:
				goto ex_while;
				break;
			case 13:
				//edit save
				x = getx();
				y = gety();
				gotoxy(73,22);
				printf("Save");
				gotoxy(x,y);
				setcursor(0,13);
				while(1)
				{
					ch = getch();
					if((ch >= '0' && ch <= '9')||(ch >= 'A' && ch <= 'F'))
					{
						EditMemory(ch);
					}
					else if(ch >='a' && ch <= 'f')
					{
						EditMemory((ch-0x20));
					}
					else if(ch == 13)
					{
						modify_first = 0;
						if((cursor_x%2) != 0)
						{
							cursor_x--;
						}
						write_mem_byte(addr+cursor_y*16+(cursor_x/2),tmp_value);
						dataBuf[cursor_y][cursor_x/2] = read_mem_byte(addr+cursor_y*16+cursor_x/2);
						display_data((BYTE)(cursor_x/2),cursor_y,dataBuf[cursor_y][cursor_x/2]);
						break;
					}
					else if(ch == 27)
					{
						modify_first = 0;
						if((cursor_x%2) != 0)
						{
							cursor_x--;
						}
						display_data((BYTE)(cursor_x/2),cursor_y,dataBuf[cursor_y][cursor_x/2]);
						break;
					}
				}
				gotoxy(x,y);
				setcursor(11,12);
				ShowHotKey();
				break;
			case 'A':
			case 'a':
				SetAddress();
				break;
			case 'S':
			case 's':
				SearchData(0);
				break;
			case 'H':
			case 'h':
				SearchData(1);
				break;
		}
	}
ex_while:
	into_RL_mode();
	gotoxy(0,22);
}

void SearchData(int sld)
{
	int ch,cnt,j,flag;
	char buf[20];
	BYTE data;
	DWORD i,bk_addr;
	
	gotoxy(0,21);
	if(sld==0)
	{
		puts(" Please input string for search (MAX.16 chars):                                ");
		gotoxy(47,21);
	}
	else
	{
		puts(" Please input value in HEX for search (MAX.=0xFFFFFFFF):                       ");
		gotoxy(56,21);
	}
	
	cnt = 0;
	memset(buf,0,sizeof(buf));
	while(1)
	{
		ch = getch();
		if(ch == 27)
		{
			break;
		}
		else if(ch == 13)
		{
			if(sld != 0)
			{//要找Hex, 先轉換
				hextoi(buf,&i);
				cnt /= 2;
				buf[0] = (char)(i&0xff);
				buf[1] = (char)((i>>8)&0xff);
				buf[2] = (char)((i>>16)&0xff);
				buf[3] = (char)((i>>24)&0xff);
			}
			
			flag = 0;
			gotoxy(0,21);
			puts("  Searchng...                                                                  ");
			gotoxy(0,22);
			puts(" Enter: Stop  ESC: Return                                                      ");
			
			bk_addr = addr;
			for(i = addr; i < 0xffffffff; i++)
			{
				if((i % 0x100)==0)
				{
					gotoxy(13,21);
					printf("%lX",i);
				}
				
				data = read_mem_byte(i);
				if(data == buf[0])
				{
					for(j = 1; j < cnt; j++)
					{
						data = read_mem_byte((DWORD)(i+j));
						if(data != buf[j])
						{
							break;
						}
					}
					if(j == cnt)
					{
						flag = 1;
					}
				}
				if(kbhit() != 0)
				{
					goto ckch;
				}
				if(flag != 0)
				{
					addr = i;
					ReadData();
					show_all();
					
					flag = 0;
ckch:					
					gotoxy(11,22);

					ch = getch();
					if(ch == 27)
					{
						addr = bk_addr;
						ReadData();
						show_all();
						ShowHotKey();
						return;
					}
					else if(ch == 13)
					{
						addr = i;
						show_all();
						ShowHotKey();
						return;
					}
				}
			}
			addr = bk_addr;
			ReadData();
			show_all();
			break;
		}
		else if(ch == 0x08)
		{//倒退鍵
			if(cnt != 0)
			{
				cnt--;
				buf[cnt] = 0;
				printf("\b \b");
			}
		}
		else
		{
			if(sld==0)
			{
				if(cnt < 20)
				{
					buf[cnt] = ch;
					cnt++;
					printf("%c",ch);
				}
			}
			else
			{
				if(cnt < 8 && ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')))
				{
					buf[cnt] = ch;
					cnt++;
					printf("%c",ch);
				}
			}
		}
	}
	ShowHotKey();
}

void SetAddress(void)
{
	int ch,cnt;
	char buf[60];
	
	gotoxy(0,21);
	puts("  New Address:                                                                 ");
	gotoxy(14,21);
	
	cnt = 0;
	memset(buf,0,sizeof(buf));
	while(1)
	{
		ch = getch();
		if(ch == 27)
		{
			break;
		}
		else if(ch == 13)
		{
			hextoi(buf,&addr);
			ReadData();
			show_all();
			//gotoxy(12,4);
			break;
		}
		else if(ch == 0x08)
		{//倒退鍵
			if(cnt != 0)
			{
				cnt--;
				buf[cnt] = 0;
				printf("\b \b");
			}
		}
		else if((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
		{
			if(cnt < 8)
			{
				buf[cnt] = ch;
				cnt++;
				printf("%c",ch);
			}
		}
	}
	ShowHotKey();
}

void ShowHotKey(void)
{
	BYTE x,y;
	
	x = getx();
	y = gety();
	
	gotoxy(0,20);
	printf("================================================================================");
	gotoxy(0,21);
	color_printf(B_BROWN | F_WHITE," 'A':Set address  'S':Search String  'H':Search HEX                             ");
	gotoxy(0,22);
	color_printf(B_BROWN | F_WHITE," ESC:Quit  PgUp:Address-256  PgDown:address+256      :Move cursor  Enter:Edit   ");
	gotoxy(49,22);
	WriteChar(0x18);
	gotoxy(50,22);
	WriteChar(0x19);
	gotoxy(51,22);
	WriteChar(0x1b);
	gotoxy(52,22);
	WriteChar(0x1a);
	
	gotoxy(x,y);
}

void reg_cursor(void)
{
	BYTE x,tmp;

	tmp = cursor_x / 2;
	
	x = (BYTE)(cursor_x + tmp+12);
	gotoxy(x,(BYTE)(cursor_y+4));
}

void ReadData(void)
{
	DWORD i,data;
	int j;
	
	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 16; j+=4)
		{
			data = read_mem_dword((DWORD)(addr+i*16+j));
			dataBuf[i][j] = (BYTE)(data & 0xFF);
			dataBuf[i][j+1] = (BYTE)((data>>8) & 0xFF);
			dataBuf[i][j+2] = (BYTE)((data>>16) & 0xFF);
			dataBuf[i][j+3] = (BYTE)((data>>24) & 0xFF);
		}
			//printf("\n");
	}
}

void show_all(void)
{
	DWORD i;
	int j;
	
	for(i = 0; i < 16; i++)
	{
		gotoxy((BYTE)1,(BYTE)(4+i));
		printf("%08lX",addr+(i<<4));
		
		for(j = 0; j < 16; j++)
		{
			display_data((BYTE)j,(BYTE)i,dataBuf[i][j]);
		}
	}
	gotoxy(12,4);
	cursor_x = 0;
	cursor_y = 0;
}

void display_data(BYTE x,BYTE y,BYTE data)
{
	BYTE tmp;
	
	tmp = x * 3+12;
	gotoxy(tmp,(BYTE)(y+4));
	printf("%02X",data);
	
	//ASCII code
	gotoxy((BYTE)(62+x),(BYTE)(y+4));
	if(data >= 0x20 && data <= 0x7e)
	{//如果是一般的字元
		printf("%c",data);
	}
	else
	{//特殊字元，用.表示
		printf(".");
	}
}

void EditMemory(int ch)
{
		//BYTE x,y;
		
	printf("%c",ch);
	
	if((cursor_x % 2)==0) //修改第一個，游標往下一個移動，要補上第2個
	{
		if(ch >= '0' && ch <= '9')
		{
			tmp_value = (BYTE)(ch-0x30);
		}
		else
		{
			tmp_value = (BYTE)(ch-0x37);
		}
		tmp_value <<= 4;
		
		tmp_value |= (dataBuf[cursor_y][cursor_x/2] & 0x0f);
		cursor_x++;
		modify_first = 1;
			/*x = getx();
			y = gety();
			gotoxy(65,21);
			printf("1mf=%d",modify_first);
			gotoxy(x,y);*/
		///sys_info.write_en = 1;
	}
	else //修改第2個，要補上第一個
	{
			/*x = getx();
			y = gety();
			gotoxy(65,21);
			printf("2mf=%d",modify_first);
			gotoxy(x,y);*/
		if(modify_first==0)
		{
			tmp_value = (dataBuf[cursor_y][cursor_x/2] & 0xf0);
		}
		if(ch >= '0' && ch <= '9')
		{
			tmp_value |= (BYTE)(ch-0x30);
		}
		else
		{
			tmp_value |= (BYTE)(ch-0x37);
		}
		///sys_info.write_en = 1;
	}
	///write_enable();
	reg_cursor();
}


