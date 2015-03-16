#ifndef _MAIN_H_
#define _MAIN_H_

BYTE data_buf[0x2000];
DWORD tp_str[40][6];
DWORD EntryAddr;
DWORD tp_Addrs[100][2];
int tp_cnt;
int data_len;
//FILE *fp,*fpt;
int type_sld=0;
char SMB_string[200];
float smb_ver;
int length_err;

void Jump_str(void); //跳過每一個table後面的附加字串
int FindTable(int sld); //找尋指定的table
int FindEntry(void); //找尋SMBIOS table的進入點
void Read_Entry(void); //讀取entry資料
void quit(int errorlevel); //結束程式
void ShowTtile(void); //顯示畫面上方的標頭
void ShowHotKey(int sld); //顯示畫面下方的控制鍵
int ShowTypes(void); //顯示想要的table
int CheckPosi(int more); //檢查顯示頁面(有些table很大，必須分頁顯示)
void Inc_ID(void); //移到下一個table
void Dec_ID(void); //移到前一個table
int InputType(void); //處理使用者輸入要顯示的table
void GetAttachedString(char *str,int sw); //取得附加在table後面的字串
char *GetString(int tp,int index,int offset); //取得載入到記憶體中的字串
void Load_String(void); //載入字串到記憶體中
char *CalSize(WORD dd); //轉換table 17的記憶體大小

void ReportEntry(void); //Entry資料解析
int ReportTp0(void); //table 0 資料解析
int ReportTp1(void); //table 1 資料解析
int ReportTp2(void); //table 2 資料解析
int ReportTp3(void); //table 3 資料解析
int ReportTp4(void); //table 4 資料解析
int ReportTp5(void); //table 5 資料解析
int ReportTp6(void); //table 6 資料解析
int ReportTp7(void); //table 7 資料解析
int ReportTp8(void); //table 8 資料解析
int ReportTp9(void); //table 9 資料解析
int ReportTp10(void); //table 10 資料解析
int ReportTp11(void); //table 11 資料解析
int ReportTp12(void); //table 12 資料解析
int ReportTp13(void); //table 13 資料解析
int ReportTp14(void); //table 14 資料解析
int ReportTp15(void); //table 15 資料解析
int ReportTp16(void); //table 16 資料解析
int ReportTp17(void); //table 17 資料解析
int ReportTp18(void); //table 18 資料解析
int ReportTp19(void); //table 19 資料解析
int ReportTp20(void); //table 20 資料解析
int ReportTp21(void); //table 21 資料解析
int ReportTp22(void); //table 22 資料解析
int ReportTp23(void); //table 23 資料解析
int ReportTp24(void); //table 24 資料解析
int ReportTp25(void); //table 25 資料解析
int ReportTp26(void); //table 26 資料解析
int ReportTp27(void); //table 27 資料解析
int ReportTp28(void); //table 28 資料解析
int ReportTp29(void); //table 29 資料解析
int ReportTp30(void); //table 30 資料解析
int ReportTp32(void); //table 32 資料解析
int ReportTp33(void); //table 33 資料解析
int ReportTp34(void); //table 34 資料解析
int ReportTp35(void); //table 35 資料解析
int ReportTp36(void); //table 36 資料解析
int ReportTp37(void); //table 37 資料解析
int ReportTp38(void); //table 38 資料解析
int ReportTp39(void); //table 39 資料解析
void ReportTp126(void); //table 126 資料解析
void ReportEnd(void); //table 127 資料解析
void ReportOEM(void);//oem table資料顯示

char TableName[][33]=
	{
	 {"Entry Point Structure"}, //-1
	 {"BIOS Information"}, //0
	 {"System Information"},
	 {"Base Board Information"},
	 {"System Enclosure or Chassis"},
	 {"Processor Information"},
	 {"Memory Controller Information"},
	 {"Memory Module Information"},
	 {"Cache Information"},
	 {"Port Connector Information"},
	 {"System Slots"},
	 {"On Board Devices Information"}, //10
	 {"OEM String"},
	 {"System Configuration Options"},
	 {"BIOS Language Information"},
	 {"Group Associations"},
	 {"System Event Log"},
	 {"Physical Memory Array"},
	 {"Memory Device"},
	 {"32-bit Memory Error Information"},
	 {"Memory Array Mapped Address"},
	 {"Memory Device Mapped Address"}, //20
	 {"Build-in Pointing Device"},
	 {"Portable Battery"},
	 {"System Reset"},
	 {"Hardware Security"},
	 {"System Power Controls"},
	 {"Voltage Probe"},
	 {"Cooling Device"},
	 {"Temperature Probe"},
	 {"Electrical Current Probe"},
	 {"Out-of-Band Remote Access"}, //30
	 {""},
	 {"System Boot Information"},
	 {"Memory Error Information"},
	 {"Management Device"},
	 {"MAnagement Device Component"},
	 {"Management Device Threshold Data"},
	 {"Memory Channel"},
	 {"IPMI Device Information"},
	 {"System Power Supply"},
	 {"Inactive"}
	};

extern into_big_mode(void);
extern into_real_mode(void);
extern DWORD MemRead32(DWORD addr);
extern WORD MemRead16(DWORD addr);
extern BYTE MemRead8(DWORD addr);
extern void MemWrite8(DWORD addr,BYTE data);

#endif
