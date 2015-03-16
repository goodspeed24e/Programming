#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "func.h"
#include "dosipmi.h"

void menu(void)
{
	printf("\n\nUsage:\n");
	printf("DOSIPMI [ipmi cmd]: Command line mode\n");
	printf("DOSIPMI           : GUI mode");
}

void SendCommand(void)
{
	int i;
	
	if(!Send2KCS())
	{//命令成功，接收
		for(i = 0; i < IPMI_rsplen; i++)
		{
			printf("%02X ",IPMI_response[i]);
		}
		printf("\n");
	}
}

void ShowTtile(void)
{
	int i,len,start;
	BYTE x,y;
	char buf[81],title[80];
	
	x = getx();
	y = gety();

	strcpy(title,"DOSIPMI");
	
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
	gotoxy(x,y);
}

	
void GUI(void)
{
	int i,len,flag;
	char buf[MAX_CMD_LEN*3];
	char *p;
	int ch;
	BYTE x,y;
	
	clrscr();
	ShowTtile();
	printf("\nType \'QUIT\' to close this program\n");
	//gotoxy(0,1);
	while(1)
	{
		ShowTtile();
		printf("=>");
		memset(buf,0,sizeof(buf));
		len = 0;
		while(1)
		{
			ch = getch();
			if((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch==' ')
			{
				buf[len] = (char)ch;
				len++;
				printf("%c",ch); //只顯示允許的字元
			}
			else if(ch == 0x0d)
			{//enter
				printf("\n");
				break;
			}
			else if(ch == 0x08)
			{//倒退鍵
				if(len > 0)
				{
					len--;
					buf[len] = '\0';
					
					x = getx();
					if(x==0)
					{//刪上一行的最後面
						y = gety()-1;
						gotoxy(79,y);
						printf(" ");
					}
					else
					{
						printf("\b \b");
					}
				}
			}
		}
				
		if(!stricmp(buf,"quit"))
			break;
		
		//	printf("%s\n",buf);
			
		flag = 0;
		for(i = 0; i < len; i++)
		{
			if(!((buf[i] >= '0' && buf[i] <= '9') || (buf[i] >= 'A' && buf[i] <= 'F') || (buf[i] >= 'a' && buf[i] <= 'f') || buf[i]==' '))
			{
				printf("\nError!!\n Not 0~9 or A~f or SPACE\n");
				flag = 1;
				break;
			}
		}
		
		if(flag == 1)
			continue;
		
		//	printf("%s\n",buf);
		
		IPMI_reqlen = 0;
		memset(IPMI_request,0,sizeof(IPMI_request));
		
		flag = 0;
		p = strtok( buf," ");
		while( p != NULL )
		{
			len = strlen(p);
			if(len > 2)
			{
				printf("\nError!!\nInvalid Command(2-digital only)\n");
				flag = 1;
				break;
			}
			
			IPMI_request[IPMI_reqlen] = (BYTE)strtoul(p,NULL,16);
			IPMI_reqlen++;
			
			if(IPMI_reqlen >= MAX_CMD_LEN)
			{
				printf("\nError!!\nCommand too long to process\n");
				flag = 1;
				break;
			}
			// Get next token: 
			p = strtok( NULL, " " );
		}
		
		if(flag == 1)
			continue;
		
		SendCommand();
	}
}
	

void main(int argc, char **argv)
{
	char **p;
	int i,n,len;
	FILE *fp;
	int func;
	
	if(argc < 2)
	{//畫面模式，執行quit才結束程式
		func = 1;
	}
	else
	{//命令列模式，執行完命令就結束程式
		func = 0;
		
		p = argv+1;
		n = argc-1;
		i = 0;
		IPMI_reqlen = 0;
		memset(IPMI_request,0,sizeof(IPMI_request));
		
		while(n > 0)
		{
			if((*p)[0] == '/')
			{
				menu();
				return;
			}
			
			len = strlen(p[i]);
			if(len >= 3)
			{//最多2位數
				menu();
				return;
			}
			
			//command[cnt] = (BYTE)strtoul(p[i],NULL,16);
			IPMI_request[IPMI_reqlen] = (BYTE)strtoul(p[i],NULL,16);
			IPMI_reqlen++;
			i++;
			n--;
		}
	}
	
	//從 set.ini 讀取KCS值
	fp = fopen("set.ini","rt");
	if(!fp)
	{
		printf("\nError!!\nCan NOT find SET.INI for KCS address\n");
		return;
	}
	fclose(fp);
	
	KCS_DATA = (WORD)GetPrivateProfileInt("KCS","KCS_DATA",0,"set.ini");
	KCS_STATUS = KCS_CTRL = (WORD)GetPrivateProfileInt("KCS","KCS_CTRL",0,"set.ini");
	

	if(func == 0)
	{//command line mode
		SendCommand();
	}
	else
	{
		GUI();
	}
	
}
