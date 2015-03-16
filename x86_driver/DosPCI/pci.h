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
	BYTE current_select; //目前畫面上被選到的位置
	BYTE pre_select; //上一個選到的位置
	BYTE display_start; //開始顯示的pci deivce號碼
	BYTE reg_x;
	BYTE reg_y;
	WORD reg_start;
	BYTE reg_value; //user輸入要儲存的資料
	BYTE write_en; //user有輸入資料，致能寫入
	BYTE select_bus; //被選擇的裝置bus值
	BYTE select_dev;
	BYTE select_func;
}SYSTEM_Info;


#endif
