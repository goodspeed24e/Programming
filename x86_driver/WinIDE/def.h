#define SYNTEX_ERR 4
#define FILE_ERROR 6
#define CHECK_ERROR 5

#define HDD_DATA         0//Data
#define HDD_ERROR        1//Error Code
#define HDD_FEATURE      1//Feature
#define HDD_SECTOR_COUNT 2//Sector Count
#define HDD_SECTOR_NUM   3//Sector Number
#define HDD_CYL_LOW      4//Cylinder Low
#define HDD_CYL_HI       5//Cylinder High
#define HDD_DRIVE_HEAD   6//Drive/Head
#define HDD_CMD          7//Command Register  (write only)
#define HDD_STATUS       7//Status Register   (read only)

#define STS_BSY  0x80
#define STS_DRDY 0x40
#define STS_DF   0x20
#define STS_DRQ  0x08
#define STS_ERR  0x01
#define STS_CHK  0x01 //For packet device.

#define ABORT 0x80 //Indicate command Abbort.

//typedef struct
struct Controller_info
{
	WORD Pri_addr;
	WORD Sec_addr;
	WORD Bus;
	WORD Dev;
	WORD Func;
};

//typedef struct
struct CheckStruct
{
	WORD Port;
	BYTE  Drive;
//	BYTE  Name[21];
};

//typedef struct
struct DEVICE_TBL
{
	WORD Config;		//0 General configuration bit-significant information
	WORD Cylinder;		//1
	WORD Specific;		//2
	WORD Head;		//3
	DWORD Retired;		//4-5
	WORD Sector;		//6
	WORD Retired2[3];	//7-9
	BYTE Serial[20];	//10-19
	DWORD Retired3;		//20-21
	WORD Obsolete;		//22
	BYTE FW[8];		//23-26
	BYTE Model[40];		//27-46
	WORD MaxTransByte;	//47
	WORD Reserved;		//48
	WORD Capability[2];	//49-50
	DWORD Obsolete2;	//51-52
	WORD DataValid;		//53
	WORD CurrentCylinder;	//54
	WORD CurrentHead;	//55
	WORD CurrentSector;	//56
	DWORD CurrentCapacity;	//57-58
	WORD SectorSetting;	//59
	DWORD LBA;		//60-61
	WORD Unused[38];	//62-99
	DWORD Ex_LBA1;	//100-101
	DWORD Ex_LBA2;	//102-103
};

//typedef struct
struct PACKET_TBL
{
	WORD Config;		//0
	WORD Reserved;		//1
	WORD Unique;		//2
	WORD Reserved1[7];	//3-9
	BYTE Serial[20];	//10-19
	BYTE Rev[6];		//20-22
	BYTE FW[8];		//23-26
	BYTE Model[40];		//27-46
	WORD Reserved2[2];	//47-48
	WORD Capability;	//49
	WORD Reserved3;		//50
	WORD Obsolete;		//51-52
	WORD DataValid;		//53
};

//typedef struct 
struct HDDpara
{
	BYTE Model[41];
	BYTE Serial[20];
	BYTE FW[9];
	WORD Cylinder;
	WORD Head;
	WORD Sector;
	DWORD Capacity;
	DWORD LBA;
	DWORD Size;//裝置容量
	WORD ID;//0(P-M),1(P-S),2(S-M,3(S-S)
	BOOL Devicetype;//裝置種類，0：硬碟，1：cd-rom，2：tape
	BOOL Installed;//裝置是否存在
	DWORD Ex_LBA;
};
