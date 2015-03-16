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

void Jump_str(void); //���L�C�@��table�᭱�����[�r��
int FindTable(int sld); //��M���w��table
int FindEntry(void); //��MSMBIOS table���i�J�I
void Read_Entry(void); //Ū��entry���
void quit(int errorlevel); //�����{��
void ShowTtile(void); //��ܵe���W�誺���Y
void ShowHotKey(int sld); //��ܵe���U�誺������
int ShowTypes(void); //��ܷQ�n��table
int CheckPosi(int more); //�ˬd��ܭ���(����table�ܤj�A�����������)
void Inc_ID(void); //����U�@��table
void Dec_ID(void); //����e�@��table
int InputType(void); //�B�z�ϥΪ̿�J�n��ܪ�table
void GetAttachedString(char *str,int sw); //���o���[�btable�᭱���r��
char *GetString(int tp,int index,int offset); //���o���J��O���餤���r��
void Load_String(void); //���J�r���O���餤
char *CalSize(WORD dd); //�ഫtable 17���O����j�p

void ReportEntry(void); //Entry��ƸѪR
int ReportTp0(void); //table 0 ��ƸѪR
int ReportTp1(void); //table 1 ��ƸѪR
int ReportTp2(void); //table 2 ��ƸѪR
int ReportTp3(void); //table 3 ��ƸѪR
int ReportTp4(void); //table 4 ��ƸѪR
int ReportTp5(void); //table 5 ��ƸѪR
int ReportTp6(void); //table 6 ��ƸѪR
int ReportTp7(void); //table 7 ��ƸѪR
int ReportTp8(void); //table 8 ��ƸѪR
int ReportTp9(void); //table 9 ��ƸѪR
int ReportTp10(void); //table 10 ��ƸѪR
int ReportTp11(void); //table 11 ��ƸѪR
int ReportTp12(void); //table 12 ��ƸѪR
int ReportTp13(void); //table 13 ��ƸѪR
int ReportTp14(void); //table 14 ��ƸѪR
int ReportTp15(void); //table 15 ��ƸѪR
int ReportTp16(void); //table 16 ��ƸѪR
int ReportTp17(void); //table 17 ��ƸѪR
int ReportTp18(void); //table 18 ��ƸѪR
int ReportTp19(void); //table 19 ��ƸѪR
int ReportTp20(void); //table 20 ��ƸѪR
int ReportTp21(void); //table 21 ��ƸѪR
int ReportTp22(void); //table 22 ��ƸѪR
int ReportTp23(void); //table 23 ��ƸѪR
int ReportTp24(void); //table 24 ��ƸѪR
int ReportTp25(void); //table 25 ��ƸѪR
int ReportTp26(void); //table 26 ��ƸѪR
int ReportTp27(void); //table 27 ��ƸѪR
int ReportTp28(void); //table 28 ��ƸѪR
int ReportTp29(void); //table 29 ��ƸѪR
int ReportTp30(void); //table 30 ��ƸѪR
int ReportTp32(void); //table 32 ��ƸѪR
int ReportTp33(void); //table 33 ��ƸѪR
int ReportTp34(void); //table 34 ��ƸѪR
int ReportTp35(void); //table 35 ��ƸѪR
int ReportTp36(void); //table 36 ��ƸѪR
int ReportTp37(void); //table 37 ��ƸѪR
int ReportTp38(void); //table 38 ��ƸѪR
int ReportTp39(void); //table 39 ��ƸѪR
void ReportTp126(void); //table 126 ��ƸѪR
void ReportEnd(void); //table 127 ��ƸѪR
void ReportOEM(void);//oem table������

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
