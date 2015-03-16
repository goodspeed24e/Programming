#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include "func.h"

#define true	1
#define false	0

void init_232(void);
BYTE read_232(void);
void send_232(char *str);

WORD Line_Control=0x2fb;
WORD Receive_Buf=0x2f8;
WORD Send_Buf=0x2f8;
WORD Div_Latch_L=0x2f8;
WORD Div_Latch_H=0x2f9;
WORD Modem_Reg=0x2fc;
WORD Line_Status=0x2fd;
WORD Int_Enable=0x2f9;

void main( void )
{
  int ch,send_cnt,rec_cnt;
  BYTE dd;
  char name[20];
  char send_buf[200],rec_buf[100],tmp_buf[100];
  
  clrscr();
  printf("Please input your name:");
  scanf("%s",name);
  printf("Which RS232 for transfer? (\'1\' or \'2\')");
  while(1)
  {
 		ch = getch();
  	if(ch == '1')
  	{
  		Line_Control |= 0x100;
  		Receive_Buf |= 0x100;
  		Send_Buf |= 0x100;
  		Div_Latch_L |= 0x100;
  		Div_Latch_H |= 0x100;
  		Modem_Reg |= 0x100;
  		Line_Status |= 0x100;
  		Int_Enable |= 0x100;
  		break;
  	}
  	else if(ch == '2')
  	{
  		break;
  	}
  }
  init_232();
  
  memset(tmp_buf,0,sizeof(tmp_buf));
  send_cnt = 0;
  memset(rec_buf,0,sizeof(rec_buf));
  rec_cnt = 0;
  printf("\n=================================Chating Area=================================\n");
  while(1)
  {//無盡迴圈，反覆讀、送資料
  	if(kbhit() != 0)
  	{
  		ch = getch();
  		if(ch == 27)
  		{
  			break;
  		}
  		else if(ch==0)
  		{//特殊鍵，不處理
  			ch = getch();
  		}
  		else
  		{
  			if(ch == 0x0d)
  			{
  				printf("\n");
  				memset(send_buf,0,sizeof(send_buf));
  				sprintf(send_buf,"%s: %s\n\0",name,tmp_buf);
  				send_232(send_buf);//送出
  				memset(tmp_buf,0,sizeof(tmp_buf));
  				send_cnt = 0;
  			}
  			else if(ch == 0x08)
  			{
  				if(send_cnt != 0)
  				{
  					printf("\b \b");
  					send_cnt--;
  					tmp_buf[send_cnt] = 0;
  				}
  			}
  			else
  			{
  				printf("%c",ch); //顯示
  				tmp_buf[send_cnt] = ch;
  				send_cnt++;
  			}
  		}
  	}
  	else
  	{
  		dd = read_232();
  		if(dd == 0xff)
  		{
  			if(rec_cnt != 0)
  			{
  				color_printf(F_CYAN,"%s",rec_buf);
  				memset(rec_buf,0,sizeof(rec_buf));
  				rec_cnt = 0;
  			}
  		}
  		else
  		{
  			rec_buf[rec_cnt] = (char)dd;
  			rec_cnt++;
  		}
  	}
  }
}

void init_232(void)
{
  BYTE lc;
  int i;

  lc = 0x03;
  lc |= 0x80;
  outp(Line_Control,lc);// set COM1 DLAB=1
  outp(Div_Latch_L,0x0c);// LSB (for COM1 setting; info from SMC) 0x0c,9600;0x01,115200
  outp(Div_Latch_H,0x00);// MSB (for COM1 setting; info from SMC)
  lc &= 0x7f;
  outp(Line_Control,lc);// set COM1 DLAB=0
  
  for(i = 0; i < 10; i++)
	{
		delay1ms();
	}
  
  while(read_232()==0);
}

/*
+=========================================+
| retrun   0 Read PASS data in rd232_data |
| retrun 0xff Read Fail                   |
+=========================================+ 
*/
BYTE read_232( void )
{//receive data from RS232
  BYTE data;
  int timer=0;
  
  while((inp(Line_Status) & 0x01)==0x00)
  {
    timer++;
    if(timer >= 0xff)
    {
      return 0xff;//fail 0xff
    }
  }
  data = inp(Receive_Buf);
  return data;
}

void send_232( char *str )
{// send data to RS232
  BYTE status;
  
  while (*str != '\0')
  {
    status = inp(Line_Status);
    while((status & 0x20) != 0x20)
    {
      status = inp(Line_Status);
    }
    outp(Send_Buf,*str);
    str++;
  }
}

