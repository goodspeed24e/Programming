#ifndef _PCI_H_
#define _PCI_H_

typedef struct
{
	WORD Vendor;
	WORD Device;
	WORD ClassID;
	BYTE FW;
	DWORD PCINO;
	BYTE IRQ;
	BOOL PciE;
}PCI_info;

void GetDeviceName(void);
void SearchPCIdevicename(void);
BOOL GetInputData(void);
char *ChangeVendor(WORD Vendor);
char *ChangeClass(WORD ClassID);
void GetAllPCI(void);
void SearchPCIBus(void);
void ShowReg(void);
void quit(int errorlevel);
void GUI(void);
int Search_PciE_ex(BYTE bus,BYTE dev,BYTE func);

typedef struct
{
	BYTE current_select; //�ثe�e���W�Q��쪺��m
	BYTE pre_select; //�W�@�ӿ�쪺��m
	BYTE display_start; //�}�l��ܪ�pci deivce���X
	BYTE reg_x;
	BYTE reg_y;
	WORD reg_start;
	BYTE reg_value; //user��J�n�x�s�����
	BYTE write_en; //user����J��ơA�P��g�J
	BYTE select_bus; //�Q��ܪ��˸mbus��
	BYTE select_dev;
	BYTE select_func;
}SYSTEM_Info;


#endif
