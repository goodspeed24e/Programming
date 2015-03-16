#include "stdafx.h"
#include "myio.h"
#include "def.h"


extern BYTE IC_Addr;
extern void Delay_1us(DWORD delay);

//IIC
void reset_iic( void )
{
	//write_io_byte(P_DATA,0x21); 
	write_io_byte(P_DATA,0x12); //SCL=1, EN=1(D), SDA=1
}


int write_byte( WORD address, BYTE data )
{
	BYTE tmp;
	int i;
	
	StartC();
	Send8bit(IC_Addr);//send 'write' CONTROL byte
	if(W_ACK() != 0)
	{
		return 1;
	}
	
	tmp = (BYTE)(address & 0x00ff);
	Send8bit(tmp);// low addr
	if(W_ACK() != 0)
	{
		return 1;
	}
	Send8bit(data);//send data
	if(W_ACK() != 0)
	{
		return 1;
	}
	StopC();
	
	//一定要做下面的信號，不然下一個命令會失敗
	for(i = 0;i < 30; i++)
	{
		S_CK();
	}
	return 0;
}

/*int write_page( WORD address, WORD len, BYTE *data )
{
	BYTE tmp,value;
	WORD i;
	
	StartC();
	Send8bit(IC_Addr);//send 'write' CONTROL byte
//		AfxMessageBox("Address send");
	if(W_ACK())
	{
		return 1;
	}
	//if(!ic_info.single_addr) //雙位址
	//{
	//	tmp = (BYTE)(address >> 8);
	//	Send8bit(tmp);// high addr
	//	if(W_ACK())
	//	{
	//		return 1;
	//	}
	//}
	tmp = (BYTE)(address & 0x00ff);
	Send8bit(tmp);// low addr
	if(W_ACK())
	{
		return 1;
	}
	
	for(i = 0; i < len; i++)
	{
		value = data[i];
		Send8bit(value);//send data
		if(W_ACK())
		{
			return 1;
		}
	}
	StopC();
	
	//一定要做下面的信號，不然下一個命令會失敗
	///for(i = 0;i < 30; i++)
	///{
	///	S_CK();
	///}

	//拉長每個交易時間
	for(i = 0; i < pgw_cycle; i++)
	{
		outportb(P_DATA,0x00);	// scl=~1, en=0(D), sda = ~1
		Delay_1us(IC_24_DELAY);
	}
	return 0;
}*/

int read_byte( WORD address, BYTE *data )
{	
	BYTE tmp;
	
	//先送出 讀取的EEPROM位址
	StartC();
	Send8bit(IC_Addr);//send 'write' CONTROL byte
	if(W_ACK() != 0)
	{
		return 1;
	}
	tmp = (BYTE)(address & 0x00ff);
	Send8bit(tmp);// low addr
	if(W_ACK() != 0)
	{
		return 2;
	}
	
	//開始讀資料
	StartC();
	Send8bit((BYTE)(IC_Addr|0x01));//send 'read' CONTROL byte
	if(W_ACK() != 0)
	{
		return 3;
	}
	tmp = Recv8bit();
	S_CK();
	StopC();
	*data = tmp;
	return 0;
}

/*int read_page( WORD address,DWORD len, BYTE *data )
{	
	BYTE tmp;
	DWORD i;
	
	//先送出 讀取的EEPROM位址
	StartC();
	Send8bit(IC_Addr);//send 'write' CONTROL byte
	if(W_ACK())
	{
		return 1;
	}
	//if(!ic_info.single_addr) //雙位址
	//{
	//	tmp = (BYTE)(address >> 8);
	//	Send8bit(tmp);// high addr
	//	if(W_ACK())
	//	{
	//		return 1;
	//	}
	//}
	tmp = (BYTE)(address & 0x00ff);
	Send8bit(tmp);// low addr
	if(W_ACK())
	{
		return 1;
	}
	
	//開始讀資料
	StartC();
	Send8bit((BYTE)(IC_Addr|0x01));//send 'read' CONTROL byte
	if(W_ACK())
	{
		return 1;
	}
	
	for(i = 0; i <= len; i++)
	{
		data[i] = Recv8bit();
		S_ACK();
		if(!test_flag)
		{
			posi = (i*100)/len; //(int)(((float)i/(float)len)*100);
		}
	}
	S_CK();
	StopC();
	for(i = 0;i < 10; i++)
	{
		S_CK();
	}
	return 0;
}
*/

void StartC( void )
{
	//       |      |
	//SCL  --+------+--|
	//       |      |  |_______
	//       |      |
	//       |      |
	//SDA  --+--|   |
	//       |  |___|___
	//       |      |

	write_io_byte(P_DATA,0x12);	// scl=1, en=0(E), sda=1
	Delay_1us(IC_24_DELAY);

	write_io_byte(P_DATA,0x10);	// scl=1, en=0(E), sda=0
	Delay_1us(IC_24_DELAY);

	write_io_byte(P_DATA,0x00);	// scl=0, en=0(E) sda=0
	Delay_1us(IC_24_DELAY);
}

void StopC( void )
{
	//            |    |
	//SCL        -+----+--
	//    ------/ |    |
	//            |    |
	//            |    |
	//SDA         |  --+---
	//   ---------+-/  |
	//            |    |
	
	//要先將SDA拉為0
	write_io_byte(P_DATA,0x00);	// scl=0, en=0(E), sda=0
	Delay_1us(IC_24_DELAY);
	
	write_io_byte(P_DATA,0x10);	// scl=1, en=0(E), sda=0
	Delay_1us(IC_24_DELAY);

	write_io_byte(P_DATA,0x11);	// scl=1, en=1(D), sda=1
	Delay_1us(IC_24_DELAY);

}

void Send8bit( BYTE data )
{
	//       |    |
	//SCL    |   -+----
	//    ---+--/ |    \---
	//       |    |    
	//       |    |
	//SDA    | ---+----
	//   ----+/---+----\----
	//       |    |     
	
	BYTE tmp;
	int i;

	for (i = 7; i >= 0; i--)
	{
		tmp = ((data >> i) & 0x01); //scl=0, en=0(E), sda=x
		write_io_byte(P_DATA,tmp);	//send data
		Delay_1us(IC_24_DELAY);
		
		tmp |= 0x10;
		write_io_byte(P_DATA,tmp);	// scl=1, en=0(E), sda=x
		Delay_1us(IC_24_DELAY);
		
		write_io_byte(P_DATA,0x00);	// scl=0, en=0(E), sda=0
		Delay_1us(IC_24_DELAY);
	}
	write_io_byte(P_DATA,0x02);// scl=0, en=1(D), sda=?

}


BYTE Recv8bit( void )
{
	//       |    |
	//SCL    |   -+----
	//    ---+--/ |    \---
	//       |    |    
	//       |    |
	//SDA    | ---+----
	//   ----+/---+----\----
	//       |    |     
	
	BYTE tmp,data;
	char i;

	data = 0;
	for (i = 0; i < 8; i++)
	{
		write_io_byte(P_DATA,0x12);	// scl=1, en=1(D), sda=?
		Delay_1us(IC_24_DELAY);

		data <<=1;
		//tmp = inportb(P_STATUS);
		read_io_byte(P_STATUS,&tmp);
		tmp &= 0x10;
		tmp >>= 4;
		data |= tmp;
		
		write_io_byte(P_DATA,0x02);	// scl=0, en=1(D),sda=?
		Delay_1us(IC_24_DELAY);
	}
	return data;
}

BYTE W_ACK( void )
{// wait Acknowledge
	//       |    |
	//SCL    | ---+--
	//    ---+/   |  \---
	//       |    |    
	//       |    |
	//SDA----+    |   ---
	//       |\---+--/
	//       |    |     
	BYTE i;
	DWORD timeout=0;

	write_io_byte(P_DATA,0x12);	// scl=1, en=1(D), sda=?
	Delay_1us(IC_24_DELAY);
	
	do
	{
		read_io_byte(P_STATUS,&i);
		i &= 0x10;
		i >>= 4;
		Delay_1us(IC_24_DELAY);

		timeout ++;
		if(timeout > 3000)
		{
			return 1;
		}
	}while(i != 0);
	write_io_byte(P_DATA,0x02);	// scl=0, en=1(D),sda=?
	Delay_1us(IC_24_DELAY);

	return 0;
}

void S_CK( void )                  // send clock
{
	write_io_byte(P_DATA,0x12);	// scl=1, en=1(D),sda=?
	Delay_1us(IC_24_DELAY);

	write_io_byte(P_DATA,0x02);	// scl=0, en=1(D),sda=?
	Delay_1us(IC_24_DELAY);
}

void S_ACK( void )                  // send acknowledge
{
	//       |    |
	//SCL    | ---+--
	//    ---+/   |  \---
	//       |    |    
	//       |    |
	//SDA----+    |   ---
	//       |\---+--/
	//       |    |
	write_io_byte(P_DATA,0x00);	// scl=0, en=0(E),sda=0
	Delay_1us(IC_24_DELAY);

	write_io_byte(P_DATA,0x10);	// scl=1, en=0(E),sda=0
	Delay_1us(IC_24_DELAY);

	write_io_byte(P_DATA,0x02);	// scl=0, en=1(D),sda=?
	Delay_1us(IC_24_DELAY);
}
