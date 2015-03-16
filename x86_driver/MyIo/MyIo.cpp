#include <stdio.h>
#include <windows.h>
#include <winioctl.h>
#include "def.h"
#include "myio.h"

#pragma comment(lib, "User32.lib")

#define SM_SERVERR2 89

typedef enum _tag_DLLSTATUS {
	DLLSTATUS_NOERROR = 0,
	DLLSTATUS_DRIVERNOTLOADED,
	DLLSTATUS_NOTSUPPORTEDPLATFORM,
	DLLSTATUS_OTHERERROR,
	DLLSTATUS_MODE_X86_64,
} DLLSTATUS;

typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);

char DriverID[MAX_PATH];		//"MyIo"
char DriverFileName[MAX_PATH];	//"MyIo.sys" or MyIoX64.sys
char DriverName[MAX_PATH];		//"MyIo"
char szWinIoDriverPath[MAX_PATH];
OSVERSIONINFOEX osvi;

HANDLE hDriver = INVALID_HANDLE_VALUE;
HINSTANCE g_hModule = NULL;
int drivertype = 0;
static DLLSTATUS status = DLLSTATUS_OTHERERROR;

int GetFileInternalName(const char *file,char *name);
BOOL IsWow64(VOID);
int oscheck(void);
//int initialize(HMODULE ghInst);
bool Opendriver(void);
bool _stdcall LoadDriver(char *filename);
bool _stdcall UnloadDriver(char *drivername);
DWORD GetRefCount(HANDLE hHandle);


bool GetDriverPath()
{
  PSTR pszSlash;

  if (!GetModuleFileName(GetModuleHandle(NULL), szWinIoDriverPath, sizeof(szWinIoDriverPath)))
    return false;

  pszSlash = strrchr(szWinIoDriverPath, '\\');

  if (pszSlash)
    pszSlash[1] = 0;
  else
    return false;

  strcat(szWinIoDriverPath, DriverFileName);

  return true;
}

bool _stdcall OnMyIo()
{
	int ostype;

	drivertype = 0;
	ostype = oscheck();
	if(!(ostype >= 2 && ostype <= 4))
		return false;
	
	strcpy(DriverID,"MYIO");
	switch(ostype)
	{
		case 4:// NT x64
		case 3:// NT
			if(ostype==4)
			{
				strcpy(DriverFileName, "MyIoX64.sys");
			}
			else
			{
				if(osvi.dwMajorVersion!=4)
				{
					strcpy(DriverFileName, "MyIo.sys");
				}
				else
				{//not support NT4
					status = DLLSTATUS_NOTSUPPORTEDPLATFORM;
					break;
				}
			}
				
				
			strcpy(DriverName,"\\\\.\\MYIO");
			drivertype |= SYS_DRIVER_USE;
			status = DLLSTATUS_NOERROR;
			break;
		//case 2:// 95 98̏轍
		//	drivertype |= VXD_DRIVER_USE;
		//	drivertype |= PCIBIOS_READY;
		//	drivertype |= LIB_IO_FUNC_USE;
		//	status = DLLSTATUS_NOERROR;
		//	break;
		default:// NT 95/98ȊO̏轍
			status = DLLSTATUS_NOTSUPPORTEDPLATFORM;
			break;
	}
	if(status == DLLSTATUS_NOTSUPPORTEDPLATFORM)
		return false;

	///init_isr();
	
		//strcpy(DriverName,"\\\\.\\MYIO");
	//open driver
	Opendriver();
	// If the driver is not running, install it
	if (hDriver == INVALID_HANDLE_VALUE)
	{
		GetDriverPath();
			//MessageBox(NULL,szWinIoDriverPath,"note",MB_OK);
		if(LoadDriver(szWinIoDriverPath)==false)
		{
				//MessageBox(NULL,"load driver","fail",MB_OK);
			return false;
		}
		
		if(Opendriver()==false)
		{
				//MessageBox(NULL,"2nd open driver","fail",MB_OK);
			status = DLLSTATUS_OTHERERROR;
			return false;
		}
	}

	// Enable I/O port access for this process
		/*if(!DeviceIoControl(hDriver, IOCTL_MYIO_ENABLEDIRECTIO, NULL,0, NULL, 0, &dwBytesReturned, NULL))
		{
				MessageBox(NULL,"Enable IO fail","fail",MB_OK);
			return false;
		}*/
	
	
	//if(drivertype & SYS_DRIVER_USE)
	//{
		/*for(i=0;i<16;i++)
		{
			res = initialize(g_hModule);
			if(res == 0){break;}
			Sleep(100);
		}*/
	/*}
	else if(drivertype & VXD_DRIVER_USE)
	{
		res = initialize_vxd(g_hModule);
	}
	else
	{
		res = 3;
	}*/
	
	/*switch ( res )
	{
		case 0:
			status = DLLSTATUS_NOERROR;
			break;
		case 2:
			handle = NULL;
			status = DLLSTATUS_DRIVERNOTLOADED;
			break;
		default:
			handle = NULL;
			status = DLLSTATUS_OTHERERROR;
			break;
	}*/
	
	return true;
}

void _stdcall OffMyIo()
{
	DWORD dwRefCount;//,dwBytesReturned;

	dwRefCount = GetRefCount(hDriver);

	if(hDriver)
	{
			//DeviceIoControl(hDriver, IOCTL_MYIO_DISABLEDIRECTIO, NULL, 0, NULL, 0, &dwBytesReturned, NULL);
		CloseHandle(hDriver);
	}
	
	if(drivertype & SYS_DRIVER_USE)
	{
		if(dwRefCount==1)
			UnloadDriver(DriverID);
	}
		
	hDriver = NULL;
	status = DLLSTATUS_OTHERERROR;
}

int GetFileInternalName(const char *file,char *name)
{
	VS_FIXEDFILEINFO vffi;
	ULONG reserved = 0;	
	UINT size;
	char *buf = NULL, *vbuf;
	char str[256];
	int  Locale = 0;

	size = GetFileVersionInfoSize((char*)file,&reserved);
	str[0] = '\0';
	vbuf = (char*)malloc(size);

	if(GetFileVersionInfo((char*)file, 0, size, vbuf))
	{
		VerQueryValue(vbuf,TEXT("\\"),(void**)&buf,&size);
		CopyMemory( &vffi, buf, sizeof(VS_FIXEDFILEINFO));

		VerQueryValue(vbuf, "\\VarFileInfo\\Translation", (void**)&buf, &size);
		CopyMemory(&Locale, buf, sizeof(int));
		wsprintf(str,"\\StringFileInfo\\%04X%04X\\%s",LOWORD(Locale), HIWORD(Locale),"InternalName");
		VerQueryValue(vbuf,str,(void**)&buf,&size);

		strcpy(str,buf);
		if(name != NULL)
		{
			strcpy(name,buf);
		}
	}
	if(vbuf)
		free(vbuf);

	return 0;
}

//
// OS̎혞𒲂ׂ适
//   0:
//   1: windows 3.1
//   2: windows 95
//   3: windows NT
//   4: windows NT x64
//   -1:
typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE hProcess,PBOOL Wow64Process);

BOOL IsWow64(VOID)
{
	BOOL bIsWow64 = FALSE;
	
	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle("kernel32"),"IsWow64Process");
	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
		{
			// handle error
			//bIsWow64 = FALSE;
		}
	}
	return bIsWow64;
}

int oscheck(void)
{
	//OSVERSIONINFO os;
	
	//os.dwOSVersionInfoSize = sizeof(os);
	//if(GetVersionEx(&os) == 0)
	//OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;
	PGNSI pGNSI;
	//PGPI pGPI;
	BOOL bOsVersionInfoEx;
//	DWORD dwType;
	int os_64bit = 3; //default is 32-bit os
	
	ZeroMemory(&si, sizeof(SYSTEM_INFO));
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
		return 1;

	// Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
	pGNSI = (PGNSI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")),"GetNativeSystemInfo");
	
	if(NULL != pGNSI)
		pGNSI(&si);
	else
		GetSystemInfo(&si);
		
	switch(osvi.dwPlatformId)
	{
		case VER_PLATFORM_WIN32s: //3.1
			return 1;
		case VER_PLATFORM_WIN32_WINDOWS: //win 9x
			return 2;
		case VER_PLATFORM_WIN32_NT: //nt, 2000
			/*if(osvi.dwMajorVersion > 4 )
			{
				// Test for the specific product.
		
				if( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1 )
				{//W7, W2K8R2
					os_64bit = 4;
				}
				
				if( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 )
				{
					if( osvi.wProductType == VER_NT_WORKSTATION )
					{//vista
					}
					else
					{//W2K8
					}
					if(si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
					{
						os_64bit = 4;
					}
					else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
					{//32-bit
					}
				}
		
				else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
				{
					if( GetSystemMetrics(SM_SERVERR2) )
					{//W2k3R2
					}
					else if ( osvi.wSuiteMask==VER_SUITE_STORAGE_SERVER )
					{//WS2k3
					}
					else if ( osvi.wSuiteMask==0x00008000)//VER_SUITE_WH_SERVER )
					{//WHS
					}
					else if( osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
					{//XP64
						os_64bit = 4;
					}
					else
					{//XP32
					}
						//strcpy(pszOS,"Windows Server 2003, ");
						//strcpy(pszOS,"W2k3");
					
					// Test for the server type.
					if ( osvi.wProductType != VER_NT_WORKSTATION )
					{
						if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_IA64 )
						{//IA64
							//
						}
						else if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
						{//x64
							os_64bit = 4;
						}
						else
						{//x32

						}
					}
				}
			}
			return os_64bit;*/
			
#ifdef _X86_64
			return 4;
#else
			return IsWow64() ? 4 : 3;	//Windowx XP 64Bit Edition or Windows NT
#endif
		default:
			return -1;
	}
}

bool Opendriver(void)
{
//	DWORD	dwStatus;

	hDriver = CreateFile(
    DriverName,
    GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_READ | FILE_SHARE_WRITE,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL
    );

	//dwStatus = GetLastError();

	if (hDriver == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	return true;
}

bool _stdcall LoadDriver(char *filename)
{
	SC_HANDLE	hSCManager;
	SC_HANDLE	hService;
	SERVICE_STATUS	serviceStatus;
	bool	ret;

	//
	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if(!hSCManager)
	{
			MessageBox(NULL,"open scm 1","fail",MB_OK);
		return false;
	}

	//K¬dservice¬O§_¤w¶}±Ѝ
	hService = OpenService( hSCManager,DriverID,SERVICE_ALL_ACCESS);
	if(hService)
	{
		ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus);
		DeleteService(hService);
		CloseServiceHandle(hService);
	}
	//
	hService = CreateService(hSCManager,
		DriverID,
		DriverID,
		SERVICE_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER, //
		SERVICE_DEMAND_START,  //StartService()
		SERVICE_ERROR_NORMAL,
		filename,            //
		NULL,NULL,NULL,NULL,NULL);

	ret = false;
	if(hService)
	{
		//
		ret = StartService(hService, 0, NULL) || GetLastError() == ERROR_SERVICE_ALREADY_RUNNING;
		/*if(ret == false)
		{
			MessageBox(NULL,"start service","fail",MB_OK);
		}*/
		//
		CloseServiceHandle(hService);
	}
	/*else
	{
		MessageBox(NULL,"create service","fail",MB_OK);
	}*/
	
	//
	CloseServiceHandle(hSCManager);

	return ret;
}

bool _stdcall UnloadDriver(char *drivername)
{
	SC_HANDLE	hSCManager;
	SC_HANDLE	hService;
	SERVICE_STATUS  serviceStatus;
	bool	ret;

	//
	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if(!hSCManager)
		return false;

	//
	hService = OpenService(hSCManager, drivername, SERVICE_ALL_ACCESS);
	CloseServiceHandle(hSCManager);
	ret = false;
	if(hService)
	{
		//
		ret = ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus);

		//
		if(ret == true)
			ret = DeleteService(hService);

		//
		CloseServiceHandle(hService);
	}
	//
	

	return ret;
}

DWORD GetRefCount(HANDLE hHandle)
{
	DWORD dwRefCount;
	ULONG ReturnedLength, IoctlResult;

	dwRefCount = (DWORD)-1;

	if(hHandle)
	{
		IoctlResult = DeviceIoControl(
                            hHandle,
                            IOCTL_GET_REFCOUNT,
                            NULL,
                            0,
                            &dwRefCount,
                            sizeof(dwRefCount),
                            &ReturnedLength,
                            NULL
                            );
	}
	if(!IoctlResult) dwRefCount = (DWORD)-1;

	return dwRefCount;
}
