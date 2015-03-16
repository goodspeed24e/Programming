#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include "ide.h"

Controller_info c_info[30];

CheckStruct HDDs[10]=
	{
	 {0x1F0,0,{"Primary Master : "}},
	 {0x1F0,1,{"Primary Slave : "}},
	 {0x170,0,{"Secondary Master : "}},
	 {0x170,1,{"Secondary Slave : "}},
	 {0,0,{""}},
	 {0,0,{""}},
	 {0,0,{""}},
	 {0,0,{""}},
	 {0,0,{""}},
	 {0,0,{""}}
	};

BYTE DataBuff[512];

int controller_cnt;

void main( void )
{
	int i;
	WORD HDDcnt=0;
	BYTE State;
	HDDpara Para;
	
	memset(c_info,0,sizeof(c_info));
	if(SearchPCIDClass() != 0)
	{//有找到新的io port才設定
		for(i = 2; i < controller_cnt; i++)
		{
			HDDs[i*2].Port = c_info[i].Pri_addr;
			HDDs[i*2].Drive = 0;
			HDDs[i*2+1].Port = c_info[i].Pri_addr;
			HDDs[i*2+1].Drive = 1;
		}
	}
	
	for(i = 0; i < controller_cnt*2; i++)
	{//先去抓電腦的所有裝置，並記錄起來，也記到記錄檔
		if(HDDs[i].Port != 0)
		{
			State = IdentifyDevice(HDDs[i].Port,HDDs[i].Drive,DataBuff);

			if(State != 0)
			{
				printf("\n%s",HDDs[i].Name);
				memset(&Para,0,sizeof(Para));
				GetHDDpara(HDDs[i].Port,HDDs[i].Drive,&Para);
				printf("\n  Model: %s",Para.Model);
				printf("  Size: %ldMB  FW: %s  SN: %s\n",Para.Size,Para.FW,Para.Serial);
			}
		}
	}
}


//Device = 0 primary;
//Device = 1 secondary.
//#define DEBUG
BYTE IdentifyDevice(WORD Port,BYTE Device,BYTE *Data)
{
	BYTE Status;
	DWORD i;
	BYTE cmd;
//1. Get CMD chip bus info
//2. Get chennel address PM : 0x10, PS :0x14, SM : 0x18, SS : 0x1C
//3. Send command.(Set requirt register)
	_disable();
	
	cmd = 0xEC;	//do IDENTIFY DEVICE first
	outp(0x70,0x80);
	
get_again:
	if(cmd == 0xA1)
	{
		//reset device
		outp(Port+HDD_DRIVE_HEAD  ,(0xA0|(Device<<4))); //Drive/Head
		outp(Port+HDD_CMD ,0x08); //Command Register (drive 0)
		inp(0x84);
		Delay(80);//必須長一點，避免有些裝置來不及
	}
	else
	{
		Delay(5);//一般裝置reset
	}
	
	outp(Port+HDD_FEATURE,0);//Feature
	outp(Port+HDD_SECTOR_COUNT,0);//Sector Count
	outp(Port+HDD_SECTOR_NUM  ,0); //Sector Number
	outp(Port+HDD_CYL_LOW     ,0); //Cylinder Low
	outp(Port+HDD_CYL_HI      ,0); //Cylinder High
	outp(Port+HDD_DRIVE_HEAD  ,(0xA0|(Device<<4))); //Drive/Head
	outp(Port+HDD_CMD         ,cmd); //Command Register (drive 0)

	inp(0x84);
	//check status. Busy must set.
	Status = inp(Port+HDD_STATUS);
	
	if((Status & STS_ERR) == STS_ERR)
	{//檢查是否有 error 產生
		_enable();
		return 0;
	}
	if((Status & STS_BSY) ==0)
	{
		_enable();
		return 0;//No drive connected.
	}
	
	if(((Status & STS_BSY) ==0)&&((Status & STS_DRQ)==0))//Idel
	{
		if (IsPacketSignature(Port) != 0)
		{
			cmd = 0xA1;	//do IDENTIFY PACKET DEVICE
			goto get_again;//return ABORT;//Packet device found;
		}
		else
		{
			return 0;
		}
	}

	//Wait to enter Transfer Data state
	for(i = 0 ; i < 0x100000; i++)
	{
		Status = inp(Port+HDD_STATUS);
		if((Status & STS_BSY) == 0) //Busy bit clear.
		{
			break;
		}
		Delay(10);
	}
	if(((Status & STS_BSY) ==0)&&((Status & STS_DRQ) ==0))//Idel
	{
		if (IsPacketSignature(Port) != 0)
		{
			cmd = 0xA1;	//do IDENTIFY PACKET DEVICE
			goto get_again;//return ABORT;//Packet device found;
		}
		else
		{
			return 0;
		}
	}

	//Enter Transfer Data state.
	//make sure
	if((((Status & STS_BSY)==0)&&((Status & STS_DRQ)==STS_DRQ)) == 0)//Transfer Data
	{
		return 0;//Unexpect error happen;
	}
	
	Status = GetIdentifyData(Port,Data);
//		printf("status=%x\n",Status);
	outp(0x70,0x00);
	_enable();
	return Status;
}


BYTE IsPacketSignature(WORD Port)
{
	if(inp(Port+HDD_CYL_LOW)!= 0x14)
	{
		return 0; //Cylinder Low
	}
	if(inp(Port+HDD_CYL_HI)!= 0xEB)
	{
		return 0; //Cylinder High
	}
	switch(inp(Port+HDD_DRIVE_HEAD))
	{
		case 0x00 :
		case 0x10 :
		case 0xA0 ://
		case 0xB0 ://Some device return A0,B0 signature as Packet device.
			return 1;//Match Packet signature.
		default:
			return 0;
	}
}


//Get 512 byte form port
//check check sum when byte 511 = 0xA5
// true  1
// false 0
// Packet 0x80
BYTE GetIdentifyData(WORD Port,BYTE *Data)
{
	WORD i;
	WORD *pt;
	BYTE CheckSum;
	
	pt = (WORD *)Data;
	for( i = 0; i < 256; i++)
	{
		*pt = inpw(Port+HDD_DATA);
		pt++;
	}

	if(Data[511]== 0xA5)//The byte 510 is checksum
	{
		CheckSum = 0;
		for(i=0;i<512;i++)
		{
			CheckSum += Data[i];
		}
		if(CheckSum != 0)//Check != 0 means error.
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	//No check sum require
	return 1;
}


BOOL SearchPCIDClass( void )
{
	WORD i,j,k;
	BYTE gclass,gsclass,tp;
	WORD vendor,add;
	int done=0;
	
	controller_cnt = 0;
	for(i = 0; i < 256; i++)
	{
		for(j = 0; j < 32; j++)
		{
			for(k = 0; k < 8; k++)
			{
				if(k == 0)
				{
					tp = (read_pci_byte(i,j,k,0x0e)) & 0x80;
				}
				vendor = (read_pci_word(i,j,k,0x00));
				if(vendor != 0xffff)
				{
					gclass = read_pci_byte(i,j,k,0x0B);
					if(gclass == 0x01)
					{//大量儲存媒體控制器
						gsclass = read_pci_byte(i,j,k,0x0a);
						if(gsclass == 0x01 || gsclass == 0x04)
						{//IDE controller or RAID controller
							done = 0;

							//去暫存器讀位址
							add = read_pci_word((BYTE)i,(BYTE)j,(BYTE)k,0x10);
							if((add & 0x0001) == 0x0001)
							{
								add &= 0xfffe;
								
								if(add != 0 && add != 0x1f0 && add != 0x170)
								{
									c_info[controller_cnt].Pri_addr = add;
								}
								else
								{
									goto qq;
								}
							}
							
							//去暫存器讀位址
							add = read_pci_word((BYTE)i,(BYTE)j,(BYTE)k,0x14);
							if((add & 0x0001) == 0x0001)
							{
								add &= 0xfffe;
								if(add != 0 && add != 0x1f0 && add != 0x170)
								{
									c_info[controller_cnt].Sec_addr = add;
								}
							}
							done++;
							
							c_info[controller_cnt].Bus = i;
							c_info[controller_cnt].Dev = j;
							c_info[controller_cnt].Func = k;
						}

qq:					
						if(done != 0)
						{
							controller_cnt++;
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
	
	controller_cnt += 2;
	if(controller_cnt < 3)
	{
		return 0;
	}
	return 1;
}



//struct HDDpara
//Remove SPACE at end of None-SPACE asscii code.
void GetHDDpara(WORD Port,BYTE Device,HDDpara *Para)
{
	DEVICE_TBL *pt;
	PACKET_TBL *pt2;
	WORD i,j;
	BYTE *p;
	BYTE tmp[40];
	double size,size2;
	
	if((DataBuff[1] & 0x0F) == 0x05)
	{//如果是CD-ROM
up:
		pt2 = (PACKET_TBL *)DataBuff;
		Para->Sector  = 0;
		Para->Cylinder= 0;
		Para->Head    = 0;

		memset(tmp,0,sizeof(tmp));
		for( i = 0; i < 40; i+=2)
		{//兩個一組，相反放，要改回來
			tmp[i]= pt2->Model[i + 1];
			tmp[i+1]=pt2->Model[i];
		}
		memset(Para->Model,0,sizeof(Para->Model));
		//清除中間的空白處，只保留一個
		p = &(Para->Model[0]);
		for(i = 0; i < 40; i++)
		{
			*p = tmp[i];
			if(tmp[i] == ' ' && tmp[i + 1] == ' ')
			{
				for(j = i; j < 40; j++)
				{
					if(tmp[j] != ' ')
					{
						i = j - 1;
						break;
					}
				}
				if(j == 40)
				{
//					p++;
					break;
				}
			}
			p++;
		}
		*p = '\0';
		
		memset(tmp,0,sizeof(tmp));
		memset(Para->Serial,0,sizeof(Para->Serial));
		for( i = 0; i < 20; i+=2)
		{//兩個一組，相反放，要改回來
			tmp[i]= pt2->Serial[i + 1];//跳過前面的空白
			tmp[i+1]=pt2->Serial[i];
		}
		p = tmp;//因為存放位置有前後之分，所以要先搬到最前面
		j = 0;
		for(i = 0; i < 20; i++)
		{
			if(*p != ' ')
			{
				Para->Serial[j] = *p;
				j++;
			}
			p++;
		}
		Para->Serial[j] = '\0';//在空白處補上結束符號
		
		memset(Para->FW,0,sizeof(Para->FW));
		for( i = 0; i < 8; i+=2)
		{//兩個一組，相反放，要改回來
			Para->FW[i]= pt2->FW[i +1];
			Para->FW[i+1]=pt2->FW[i];
		}
		p = &(Para->FW[0]);//在空白處補上結束符號
		for(i = 0; i < 8; i++)
		{
			if(*p == ' ')
			{
				*p = '\0';
			}
			p++;
		}
		Para->LBA = 0;
	}
	else if((DataBuff[1] & 0x0F) == 0x01)
	{
		goto up;
	}
	else
	{
		pt = (DEVICE_TBL *)DataBuff;
		Para->Sector  = pt->Sector;
		Para->Cylinder= pt->Cylinder;
		Para->Head    = pt->Head;
		
		memset(tmp,0,sizeof(tmp));
		for( i = 0; i < 40; i+=2)
		{//兩個一組，相反放，要改回來
			tmp[i]= pt->Model[i + 1];
			tmp[i+1]=pt->Model[i];
		}
		
		memset(Para->Model,0,sizeof(Para->Model));
		//清除中間的空白處，只保留一個
		p = &(Para->Model[0]);
		for(i = 0; i < 40; i++)
		{
			*p = tmp[i];
			if(tmp[i] == ' ' && tmp[i + 1] == ' ')
			{
				for(j = i; j < 40; j++)
				{
					if(tmp[j] != ' ')
					{
						i = j - 1;
						break;
					}
				}
				if(j == 40)
				{
//					p++;
					break;
				}
			}
			p++;
		}
		*p = '\0';
		
		memset(tmp,0,sizeof(tmp));
		memset(Para->Serial,0,sizeof(Para->Serial));
		for( i = 0; i < 20; i+=2)
		{//兩個一組，相反放，要改回來
			tmp[i]= pt->Serial[i + 1];//跳過前面的空白
			tmp[i+1]=pt->Serial[i];
		}
		p = tmp;//因為存放位置有前後之分，所以要先搬到最前面
		j = 0;
		for(i = 0; i < 20; i++)
		{
			if(*p != ' ')
			{
				Para->Serial[j] = *p;
				j++;
			}
			p++;
		}
		Para->Serial[j] = '\0';//在空白處補上結束符號
		
		memset(Para->FW,0,sizeof(Para->FW));
		for( i = 0; i < 8; i+=2)
		{//兩個一組，相反放，要改回來
			Para->FW[i]= pt->FW[i +1];
			Para->FW[i+1]=pt->FW[i];
		}
		p = &(Para->FW[0]);//在空白處補上結束符號
		for(i = 0; i < 8; i++)
		{
			if(*p == ' ')
			{
				*p = '\0';
			}
			p++;
		}

		if(pt->LBA != 0x0fffffff)
		{
			Para->LBA = pt->LBA;
			size2 = 0;
		}
		else //超過137G
		{
			Para->LBA = pt->Ex_LBA1;
			Para->Ex_LBA = pt->Ex_LBA2;
			
			size2 = (double)Para->Ex_LBA;
			size2 *= 512.0;//512byte per track.
			size2 /= 1024.0; //單位KB
			size2 /= 1024.0; //單位MB
			size2 *= 2097151.99951; //回復真正值
		}
		
		size = (double)Para->LBA;
		size *= 512.0;//512byte per track.
		size /= 1024.0; //單位KB
		size /= 1024.0; //單位MB
		size += size2;
		Para->Size = (DWORD)size;
	}
}


void Delay(int times)
{
	int i;
	
	for(i = 0; i < times; i++)
	{
		delay1ms();
	}
}
