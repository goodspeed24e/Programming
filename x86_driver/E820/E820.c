#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dos.h>

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef unsigned char	BOOL;

char type_str[][25]=
{
	"AddressRangeMemory",
	"AddressRangeReserved",
	"AddressRangeACPI",
	"AddressRangeNVS",
	"AddressRangeUnusable"
};

extern DWORD Int_E820(DWORD bx,WORD seg,WORD offset,DWORD len);

void main(void)
{//想知道更多，請看ACPI spec第14章
	BYTE buf[20];
	DWORD bx=0,type;
	WORD seg,offset;
	int i;
	BYTE far *pt;
	//BOOL Got_flag=0;
	int cnt=0;

	pt = (BYTE far *)buf;
	seg = FP_SEG(pt);
	offset = FP_OFF(pt);
	
	puts(" NO    Base Address           Length                        Type");
	puts("---+-------------------+-------------------+---------------------------------");
	do
	{
		memset(buf,0,sizeof(buf));
		bx = Int_E820(bx,seg,offset,sizeof(buf));
	
		if(bx != 0xffffffff)
		{
			printf(" %02d: %02X%02X%02X%02X_%02X%02X%02X%02X ",cnt,buf[7],buf[6],buf[5],buf[4],buf[3],buf[2],buf[1],buf[0]);
			printf("  %02X%02X%02X%02X_%02X%02X%02X%02X ",buf[15],buf[14],buf[13],buf[12],buf[11],buf[10],buf[9],buf[8]);
			
			type = 0;//type
			for(i = 3; i >= 0; i--)
			{
				type <<= 8;
				type |= buf[i+16];
			}
			if(type > 5)
			{
				printf("  Unknown\n");
			}
			else
			{
				printf("  %s\n",type_str[type]);
			}
			cnt++;
		}
		else
		{
			printf("E820 Fail\n");
			break;
		}
	}while(bx);
}




