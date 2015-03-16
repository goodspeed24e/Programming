#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include "func.h"

BYTE func_storebuf[200];
int ReadFile(FILE *fp,char *data,int func)
{
	char *p;
	int len;
	char buf[500];
	
	while(1)
	{
		p = fgets(buf,500,fp);
		if(!p)
		{
			return 0;
		}
		//	printf("got:%s\n",p);
		len = strlen(p);
		if(len < 3)
		{
			continue;
		}
		
		if(func)
		{
			//去除頭無用字
			while(1)
			{
				if(*p < '!')
				{
					p++;
				}
				else
				{
					break;
				}
			}
		
			len = strlen(p);
			if(len < 3)
			{
				continue;
			}
		}
		
		len = strlen(buf)-1;
		//去除尾無用字
		while(1)
		{
			if(buf[len] < '!')
			{
				buf[len] = '\0';
				len--;
			}
			else
			{
				break;
			}
		}
		
		len = strlen(p);
		if(len < 3)
		{
			continue;
		}
		
		if(*p == '#')
		{
			continue;
		}
		
		strcpy(data,p);
		//pp = p;
		return len;
	}
}

int find_main(FILE *fp,char *want)
{
	char buf[500];
	
	while(1)
	{
		
		memset(buf,0,sizeof(buf));
		if(!ReadFile(fp,buf,1))
		{
			break;
		}
		
		if(!stricmp(buf,want))
		{//找到了
			//printf("got=%s\n",ptr);
			//break;
			return 0;
		}
	}
	return 1;
}

char *BreakBuf(char *buf)
{
	//把=變\0
	while(1)
	{
		buf++;
		if(*buf == '=')
		{
			*buf = '\0';
			buf++;
			break;
		}
		else if(*buf == '\0')
		{
			return 0;
		}
	}
		
	return buf;
}

int find_item(FILE *fp,char *want, char *resp)
{
	char buf[500];
	char *p;
	
	while(1)
	{
		memset(buf,0,sizeof(buf));
		if(!ReadFile(fp,buf,1))
		{
			break;
		}
		p = buf;
		
		if(*p=='[') //另一個標籤開始，不處理
		{
			return 1;
		}
		
		//把=變\0
		p = BreakBuf(buf);
		
		if(!p)
		{
			return 1;
		}
		
		if(!stricmp(buf,want))
		{//找到字串
			strcpy(resp,&(buf[strlen(buf)+1]));
			//printf("got=%s\n",resp);
			//break;
			return 0;
		}
	}
	return 1;
}

DWORD GetPrivateProfileInt(char *sect,char *key,int def_value,char *path)
{
	FILE *fp;
	int len;
	char tmp1[200],tmp2[200];
	DWORD vv;
	
	vv = (DWORD)def_value;
	fp = fopen(path,"rt");
	if(!fp)
	{
		return vv;
	}
	
	sprintf(tmp1,"[%s]",sect);
	if(!find_main(fp,tmp1)) //有找到資料再處理
	{
		if(!find_item(fp,key,tmp2)) //有找到資料再處理
		{
			//判斷是十進位或16進位
//				printf("I got %s\n",tmp2);
			len = strlen(tmp2);
			if(tmp2[len-1] == 'h' || tmp2[len-1] == 'H')
			{
				tmp2[len-1] = '\0';
				hextoi(tmp2,(DWORD *)&vv);
			}
			else
			{
				vv = (DWORD)atoi(tmp2);
			}
		}
	}
	fclose(fp);
	return vv;
}

void GetPrivateProfileString(char *sect,char *key,char *def_value,char *data_want,int d_size,char *path)
{
	FILE *fp;
	char tmp1[200],tmp2[200];
	int len;
	
	strcpy(data_want,def_value);
	fp = fopen(path,"rt");
	if(!fp)
	{
		return;
	}
	
	sprintf(tmp1,"[%s]",sect);
	if(!find_main(fp,tmp1)) //有找到資料再處理
	{
		if(!find_item(fp,key,tmp2)) //有找到資料再處理
		{
//				printf("got %s\n",tmp2);
			memset(data_want,0,sizeof(data_want));
			len = strlen(tmp2);
			
			if(!len)
			{
				strcpy(data_want,def_value);
			}
			else if(len < d_size)
			{
				strcpy(data_want,tmp2);
				//data_want[len] = '\0';
			}
			else
			{
				memcpy(data_want,tmp2,d_size);
				//data_want[d_size-1] = '\0';
			}
//				printf("I got: %s\n",tmp2);
		}
	}
	fclose(fp);
	return;
}

void clrscr(void)
{
	gotoxy(0,0);
	set_windows(0,0,79,24,0,F_WHITE);
	gotoxy(0,0);
}

BYTE getx( void )
{
	BYTE x;
	
	__asm 
	{
		mov ah,03h
		mov bh,00h
		int 10h
		mov x,dl
	};
	
	return x;
}

BYTE gety( void )
{
	BYTE y;
	
	_asm 
	{
		mov ah,03h
		mov bh,00h
		int 10h
		mov y,dh
	};
	
	return y;
}

void gotoxy( BYTE x, BYTE y )
{
	_asm 
	{
		mov ah,02h
		mov bh,00h
		mov dh,y
		mov dl,x
		int 10h
	};
}

void WriteChar(BYTE cChar)
{
	_asm{
		cli
		mov ah,0ah
		mov al,cChar
		mov bh,0
		mov cx,1
		int 10h
		sti
	}
}

void setcursor( BYTE start, BYTE end )
{
	//default start=11 end=12
	_asm {
		mov ah,01h
		mov ch,start
		mov cl,end
		int 10h
	}
}

void ShowCursor(void)
{
	_asm
	{
		mov ah,01
		mov ch,0Eh
		mov cl,0Fh
		int 10h
	}
};


void HideCursor( void )
{
	_asm
	{
		mov ah,01
		mov ch,2Eh
		mov cl,15
		int 10h
	};
}

int hextoi(BYTE *p,DWORD *data)                   // convert Hex ASCII to integer
{
	DWORD v=0,tmp=0;
	int count=0;
	
	
	while(1)
	{
		if (*p >= '0' && *p <= '9' )
		{
			tmp = *p - 0x30;
		}
		else if(*p >= 'A' && *p <= 'F')
		{
			tmp = *p - 0x37;
		}
		else if(*p >= 'a' && *p <= 'f' )
		{
			tmp = *p - 0x57;
		}
		else if(*p == '\0')
		{
			break;
		}
		else
		{
			puts("( Hex ASCII to Int )Input is not in the Hex range!\n");
			puts("\a");
			return 1;
		}
		count++;
		if(count > 8)
		{
			break;
		}
		v <<= 4;
		v |= tmp;
		p++;
	}

	*data = v;
	return 0;
}

void color_char( BYTE ch, BYTE color)
{
	/*_asm
	{
		mov ah,9
		mov al,ch
		mov bh,0
		mov bl,color
		mov ch,0
		mov cl,1
		int 10h
	};*/
	
	union REGS regs;
	
	regs.h.ah = 0x09;
	regs.h.al = ch;
	regs.h.bh = 0;
	regs.h.bl = color;
	regs.h.cl = (BYTE)1;
	regs.h.ch = (BYTE)0;
	int86(0x10,&regs,&regs);
}

void color_printf(BYTE color, const char *formatstr,...)
{
	va_list args;
	int i,len,tmp;
	BYTE x,y;
	
	memset(func_storebuf,0,sizeof(func_storebuf));
	va_start(args, formatstr);
	vsprintf(func_storebuf, formatstr, args);
	va_end(args);

	len = strlen(func_storebuf);
	x = getx();
	y = gety();
	for(i = 0; i < len; i++)
	{
		if(func_storebuf[i] != 0x0d && func_storebuf[i] != 0x0a )
		{
			color_char(func_storebuf[i],color);
			x++;
		}
		else if(func_storebuf[i] == '\r')
		{
			x = 0;
		}
		else if(func_storebuf[i] == '\b')
		{
			if(x != 0)
			{
				x--;
			}
		}
		else if(func_storebuf[i] == '\t')
		{
			if(x <= 64)
			{
				tmp = (x/8)+1;
				x= 8*tmp;
			}
			else
			{
				x = 0;
				y++;
				if(y == 24)
				{
					set_windows(0,0,79,23,1,B_BLACK);
					y--;
				}
			}
		}
		else
		{
			x = 0;
			y++;
			if(y == 24)
			{
				set_windows(0,0,79,23,1,B_BLACK);
				y--;
			}
		}
		gotoxy(x,y);
	}
}

void set_windows( BYTE lx, BYTE ly, BYTE rx, BYTE ry ,BYTE row, BYTE color)
{
	_asm {
		cli
		mov ah,06h
		mov al,row     //note row = 0 clear screen
		mov bh,color
		mov ch,ly
		mov cl,lx
		mov dh,ry  //row = 25 - 1 (begin from 0) collon = 80 - 1 (begin form 0)
		mov dl,rx
		int 10h
		sti
	};
}

void ShowTitle(char *title)
{
	int i,len,start;
	char buf[81];
	
	memset(buf,0,sizeof(buf));
	memset(buf,0x20,sizeof(buf)-1);
	len = strlen(title);
	start = 40-(len / 2);
	if(len%2)
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
	printf("================================================================================");
	gotoxy(0,2);
	printf(" Address    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F   ASCII code");
	gotoxy(0,3);
	printf(" --------   -----------------------------------------------   -----------------");
}

void delay1ms(void)
{
	_asm
	{
		mov  dx,1
start:
		mov  cx,42h
		mov  bx,10h
waitonbit:
		in   al,61h
		and  al,10h
		cmp  al,bl
		jz   waitonbit
		xor  bl,10h
		loop waitonbit
		dec  dx
		jnz  start
	}
}
