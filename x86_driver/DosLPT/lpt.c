#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include "func.h"

#define CTRL_PORT 0x37A
#define STATUS_PORT 0x379
#define DATA_PORT 0x378


int HandSharking(void);
int SendByte(BYTE data);
int RecvByte(BYTE *data);
int SendString(char *data);

void main( void )
{
	int ch,send_cnt,rec_cnt;
	char name[20],send_buf[200],rec_buf[100],tmp_buf[100];
	BYTE dd;
	
	if(HandSharking() != 0)
	{
		write_io_byte(DATA_PORT,0x0);
		return;
	}

	clrscr();
  printf("Please input your name:");
  scanf("%s",name);
  
  memset(tmp_buf,0,sizeof(tmp_buf));
  send_cnt = 0;
  memset(rec_buf,0,sizeof(rec_buf));
  rec_cnt = 0;
  printf("\n=================================Chating Area=================================\n");
  

	while(1)
	{
		if(kbhit() != 0)
		{
			ch = getch();
			if(ch == 27)
			{
				return;
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
  				SendString(send_buf);//送出
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
			ch = RecvByte(&dd);
 		 	if(ch==0)
 		 	{
		  	rec_buf[rec_cnt] = (char)dd;
  			rec_cnt++;
		  }
		  else if(ch == 1)
  		{
  			if(rec_cnt != 0)
  			{
  				color_printf(F_CYAN,"%s",rec_buf);
  				memset(rec_buf,0,sizeof(rec_buf));
  				rec_cnt = 0;
  			}
  		}
		}
	}
}

int HandSharking(void)
{
	BYTE data;
	int ch,step=0;
	
	data = read_io_byte(STATUS_PORT);
	if((data & 0xF8) == 0xf8)
	{//對方在等待
		puts("Connecting...(Press ESC to quit)");
		
		while(1)
		{
			if(kbhit() != 0)
			{
				ch = getch();
				if(ch == 27)
				{
					return 1;
				}
			}
			switch(step)
			{
				case 0:
					write_io_byte(DATA_PORT,0x0f);
					step = 1;
					break;
				case 1:
					data = read_io_byte(STATUS_PORT);
					if((data & 0xF8) == 0x50)
					{
						write_io_byte(DATA_PORT,0x1A);
						return 0;
					}
					break;
			}
		}
		
	}
	else
	{//我等待
		write_io_byte(DATA_PORT,0x0f);
		puts("Waiting for connect...(Press ESC to quit)");
		while(1)
		{
			if(kbhit() != 0)
			{
				ch = getch();
				if(ch == 27)
				{
					return 1;
				}
			}
			data = read_io_byte(STATUS_PORT);
			switch(step)
			{
				case 0:
					if((data & 0xF8) == 0xf8)
					{//對方有回應
						write_io_byte(DATA_PORT,0x1A);
						step = 1;
					}
					break;
				case 1:
					if((data & 0xF8) == 0x50)
					{//對方有回應
						return 0;
					}
					break;
			}
		}
	}
	return 0;
}

int SendString(char *data)
{
	int status=0;
  
  while (*data != '\0')
  {
    status = SendByte(*data);
    if(status != 0)
    {
    	break;
    }
    data++;
  }
  return status;
}


int SendByte(BYTE data)
{
	/*
	1. 先將high byte送出(busy:0->1)
	2. 等對方的busy:0->1
	3. 把busy:1->0
	4. 等對方的busy:1->0
	5. 送low byte(busy:0->1)
	6. 重覆2-4
	*/
	int i,cnt;
	BYTE dd;
	
	
	for(i = 0; i < 2; i++)
	{
		cnt = 0;
tx_again:
		dd = data;
		if(i==0)
		{
			dd >>= 4;
		}
		else
		{
			dd &= 0xf;
		}
		write_io_byte(DATA_PORT,dd);
		dd = read_io_byte(STATUS_PORT);
		if((dd & 0x80)==0) //對方未ready
		{
			cnt++;
			if(cnt < 50000)
			{
				goto tx_again;
			}
			return 1;
		}
		
		write_io_byte(DATA_PORT,0x10); //把busy拉low
		cnt = 0;
tx2_again:
		dd = read_io_byte(STATUS_PORT);
		if((dd & 0x80)==0x80) //對方未ready
		{
			cnt++;
			if(cnt < 500)
			{
				goto tx2_again;
			}
			return 1;
		}
		
	}
	
	return 0;

}

int RecvByte(BYTE *data)
{
	/*
  1. 先檢查是否busy:0->1，沒有則離開
	2. 收high byte (busy:0->1)
	3. 設busy:0->1
	3. 等對方busy:1->0
	4. 設定busy:1->0
	5. 等待對方busy:0->1
	6. 收low byte (busy:0->1)
	7. 等對方busy:1->0
	8. 設定busy:1->0
	*/
	BYTE value;
	BYTE dd;
	int cnt,cc;
	
	cnt = 0;
	value=0;
	while(1)
	{
		cc = 0;
rx_again:
		dd = read_io_byte(STATUS_PORT);
		if((dd & 0x80)==0)
		{//沒有東西
			cc++;
			
				*data = value;
			if(cnt != 0)
			{
				if(cc < 5000)
				{
					goto rx_again;
				}
				return -2;
			}
			else
			{
				if(cc < 500)
				{
					goto rx_again;
				}
				return 1;
			}
		}
		
		dd &= 0x78;
		if(cnt==0)
		{//high byte
			dd <<= 1;
		}
		else
		{//low byte
			dd >>= 3;
		}
		value |= dd;
		cnt++;
		
		cc = 0;
		write_io_byte(DATA_PORT,0x0); //把busy拉high
rx2_again:
		dd = read_io_byte(STATUS_PORT);
		if((dd & 0x80) == 0x80)
		{
			cc++;
			if(cc < 500)
			{
				goto rx2_again;
			}
				*data = value;
			return -1;
		}
		
		write_io_byte(DATA_PORT,0x10); //把busy拉low
		
		if(cnt == 2)
		{
			break;
		}
		delay1ms();
	}
	*data = value;
	return 0;
}
