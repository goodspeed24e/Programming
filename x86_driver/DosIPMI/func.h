#ifndef _FUNC_H_
#define _FUNC_H_

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef unsigned char	BOOL;

extern void into_PT_mode(void);
extern void into_RL_mode(void);
extern DWORD read_mem_dword(DWORD addr);
extern WORD  read_mem_word(DWORD addr);
extern BYTE  read_mem_byte(DWORD addr);
extern void write_mem_byte(DWORD addr,BYTE data);
extern DWORD read_io_dword(WORD port);
extern void write_io_dword(WORD port, DWORD data32);
extern WORD read_io_word(WORD port);
extern void write_io_word(WORD port, WORD data16);
extern BYTE read_io_byte(WORD port);
extern void write_io_byte(WORD port, BYTE data8);
//extern long read_io_index_data_offset_dword(int index, int data, int offset);
//extern void write_io_index_data_offset_dword(int index, int data, int offset,long data32);
//extern int read_io_index_data_offset_word(int index, int data, int offset);
//extern void write_io_index_data_offset_word(int index, int data, int offset,int data16);
//extern char read_io_index_data_offset_byte(int index, int data, int offset);
//extern void write_io_index_data_offset_b(int index, int data, int offset,char data8);
extern void write_pci_byte (int bus, int device, int function, int offset, WORD data);
extern void write_pci_word (int bus, int device, int function, int offset, WORD data);
extern void write_pci_dword (int bus, int device, int function, int offset, DWORD data);
extern BYTE read_pci_byte (int bus, int device, int function, int offset);
extern WORD read_pci_word (int bus, int device, int function, int offset);
extern DWORD read_pci_dword (int bus, int device, int function, int offset);

//�e����
#define	F_BLACK		0x00	//��
#define	F_BLUE		0x01	//��
#define	F_GREEN		0x02	//��
#define	F_CYAN		0x03	//�C
#define	F_RED		0x04	//��
#define	F_MAGENTA	0x05	//��
#define	F_BROWN		0x06	//��
#define	F_WHITE		0x07	//��
#define	F_GRAY		0x08	//��
#define	F_LIGHT_BLUE	0x09	//�G��
#define	F_LIGHT_GREEN	0x0A	//�G��
#define	F_LIGHT_CYAN	0x0B	//�G�C
#define	F_LIGHT_RED	0x0C	//�G��
#define	F_LIGHT_MAGENTA	0x0D	//�G��
#define	F_YELLOW	0x0E	//��
#define	F_LIGHT_WHITE	0x0F	//�G��

//�I����
#define	B_BLACK		0x00	//��
#define	B_BLUE		0x10	//��
#define	B_GREEN		0x20	//��
#define	B_CYAN		0x30	//�C
#define	B_RED		0x40	//��
#define	B_MAGENTA	0x50	//��
#define	B_BROWN		0x60	//��
#define	B_WHITE		0x70	//��
#define	B_GRAY		0x80	//��
#define	B_LIGHT_BLUE	0x90	//�G��
#define	B_LIGHT_GREEN	0xA0	//�G��
#define	B_LIGHT_CYAN	0xB0	//�G�C
#define	B_LIGHT_RED	0xC0	//�G��
#define	B_LIGHT_MAGENTA	0xD0	//�G��
#define	B_YELLOW	0xE0	//��
#define	B_LIGHT_WHITE	0xF0	//�G��

void clrscr(void);
void gotoxy(BYTE x,BYTE y);
BYTE getx(void);
BYTE gety(void);
void WriteChar(BYTE cChar);
void ShowCursor(void);
void HideCursor(void);
void setcursor( BYTE start, BYTE end );
int hextoi(BYTE *p,DWORD *data);
void color_char( BYTE ch, BYTE color);
void color_printf(BYTE color, const char *formatstr,...);
void set_windows( BYTE lx, BYTE ly, BYTE rx, BYTE ry ,BYTE row, BYTE color);
void ShowTitle(char *title);
void delay1ms(void);

DWORD GetPrivateProfileInt(char *sect,char *key,int def_value,char *path);
void GetPrivateProfileString(char *sect,char *key,char *def_value,char *data_want,int d_size,char *path);

#endif
