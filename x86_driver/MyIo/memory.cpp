
#include <windows.h>
#include <winioctl.h>
#include <stddef.h>
#include "def.h"
#include "myio.h"


ULONG _MemReadBlock(ULONG address, PBYTE data, ULONG count, ULONG unitsize)
{
	MYIO_MEMREAD_INPUT param;
	BOOL IoctlResult;
	ULONG	ReturnedLength;
	ULONG	size;
	
	param.address = address;
	param.unitsize = unitsize;
	param.count = count;
	size = param.unitsize * param.count;
	IoctlResult = DeviceIoControl(
									hDriver,							// Handle to device
									IOCTL_MYIO_MEM_READ,				// IO Control code
									&param,							// Buffer to driver
									sizeof(MYIO_MEMREAD_INPUT),	// Length of buffer in bytes.
									data,							// Buffer from driver.
									size,							// Length of buffer in bytes.
									&ReturnedLength,				// Bytes placed in outbuf.
									NULL							// NULL means wait till I/O completes.
									);

	if(IoctlResult && ReturnedLength == size)
	{
		return param.count;
	}
	else
	{
		return 0;
	}
}

bool _stdcall read_mem_byte(ULONG address, PBYTE data)
{
	if(_MemReadBlock(address, data, 1, 1))
	{
		return true;
	}
  return false;
}

bool _stdcall read_mem_word(ULONG address, PWORD data)
{
	if(_MemReadBlock(address, (PBYTE)data, 1, 2))
	{
		return true;
	}
  return false;
}

bool _stdcall read_mem_dword(ULONG address, PDWORD data)
{
	if(_MemReadBlock(address, (PBYTE)data, 1, 4))
	{
		return true;
	}
  return false;
}

ULONG	_MemWriteBlock(ULONG address, PBYTE data, ULONG count, ULONG unitsize)
{
	MYIO_MEMWRITE_INPUT *param;
	BOOL IoctlResult;
	ULONG	ReturnedLength;
	ULONG	size;
	size = offsetof(MYIO_MEMWRITE_INPUT,data) + count*unitsize;
	param = (MYIO_MEMWRITE_INPUT*)malloc(size);
	param->address = address;
	param->unitsize = unitsize;
	param->count = count;
	memcpy(&param->data, data, count*unitsize);
	IoctlResult = DeviceIoControl(
                        hDriver,
                        IOCTL_MYIO_MEM_WRITE,
                        param,     
                        size,
                        NULL,
                        0,
                        &ReturnedLength,
                        NULL
                        );
	free(param);

	if(IoctlResult)
	{
		return param->count;
	}
	else
	{
		return 0;
	}
}

bool _stdcall write_mem_byte(ULONG address, PBYTE data)
{
	if(_MemWriteBlock(address,data,1,1))
	{
		return true;
	}
	return false;
}

bool _stdcall write_mem_word(ULONG address, PBYTE data)
{
	if(_MemWriteBlock(address,data,1,2))
	{
		return true;
	}
	return false;
}

bool _stdcall write_mem_dword(ULONG address, PBYTE data)
{
	if(_MemWriteBlock(address,data,1,4))
	{
		return true;
	}
	return false;
}


