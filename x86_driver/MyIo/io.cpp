
#include <windows.h>
#include <winioctl.h>
#include <stddef.h>
#include <conio.h>

#include "def.h"
#include "myio.h"

bool _stdcall read_io_byte(WORD address,PBYTE data)
{
#ifndef _X86_64
	BOOL IoctlResult;
	DWORD	ReturnedLength;
	
	if(drivertype & LIB_IO_FUNC_USE)
	{//for windows 95/98
		*data = _inp((USHORT)address);
		return true;
	}
	
	IoctlResult = DeviceIoControl(
					hDriver,
					IOCTL_MYIO_IO_BYTE_READ,
					&address,
					sizeof(address),
					data,
					1,
					&ReturnedLength,
					NULL);
#endif
	return true;
}

bool _stdcall read_io_word(WORD address,PWORD data)
{
#ifndef _X86_64
	BOOL IoctlResult;
	ULONG	ReturnedLength;

	if(drivertype & LIB_IO_FUNC_USE)
	{//for windows 95/98
		*data = _inpw((USHORT)address);
		return true;
	}

	IoctlResult = DeviceIoControl(
					hDriver,
					IOCTL_MYIO_IO_WORD_READ,
					&address,     
					sizeof(address),
					data,
					2,
					&ReturnedLength,
					NULL);
#endif
	return true;
}

bool	_stdcall read_io_dword(WORD address,PDWORD data)
{
#ifndef _X86_64
	BOOL IoctlResult;
	ULONG	ReturnedLength;

	if(drivertype & LIB_IO_FUNC_USE)
	{//for windows 95/98
		*data = _inpd((USHORT)address);
		return true;
	}

	IoctlResult = DeviceIoControl(
					hDriver,
					IOCTL_MYIO_IO_DWORD_READ,
					&address,     
					sizeof(address),
					data,
					4,
					&ReturnedLength,
					NULL);
#endif
	return true;
}

void _stdcall write_io_byte(WORD address, BYTE data)
{
#ifndef _X86_64
	BOOL IoctlResult;
	ULONG	ReturnedLength;
	ULONG   DataLength;
	MYIO_WRITE_INPUT InputBuffer;    // Input buffer for DeviceIoControl

	if(drivertype & LIB_IO_FUNC_USE)
	{
		_outp((USHORT)address, data);
		return;
	}

	InputBuffer.CharData = data;
	InputBuffer.PortNumber = address;
	DataLength = offsetof(MYIO_WRITE_INPUT, CharData) + sizeof(InputBuffer.CharData);

	IoctlResult = DeviceIoControl(
					hDriver,
					IOCTL_MYIO_IO_BYTE_WRITE,
					&InputBuffer,     
					DataLength,
					NULL,
					0,
					&ReturnedLength,
					NULL);

#endif
}

void _stdcall write_io_word(WORD address, WORD data)
{
#ifndef _X86_64
	BOOL IoctlResult;
	ULONG	ReturnedLength;
	ULONG   DataLength;
	MYIO_WRITE_INPUT InputBuffer;    // Input buffer for DeviceIoControl

	if(drivertype & LIB_IO_FUNC_USE)
	{
		_outpw((USHORT)address, data);
		return;
	}

	InputBuffer.ShortData = data;
	InputBuffer.PortNumber = address;
	DataLength = offsetof(MYIO_WRITE_INPUT, CharData) + sizeof(InputBuffer.ShortData);

	IoctlResult = DeviceIoControl(
					hDriver,
					IOCTL_MYIO_IO_WORD_WRITE,
					&InputBuffer,     
					DataLength,
					NULL,
					0,
					&ReturnedLength,
					NULL);

#endif
}

void _stdcall write_io_dword(WORD address, DWORD data)
{
#ifndef _X86_64
	BOOL IoctlResult;
	ULONG	ReturnedLength;
	ULONG   DataLength;
	MYIO_WRITE_INPUT InputBuffer;    // Input buffer for DeviceIoControl

	if(drivertype & LIB_IO_FUNC_USE)
	{
		_outpd((USHORT)address, data);
		return;
	}

	InputBuffer.LongData = data;
	InputBuffer.PortNumber = address;
	DataLength = offsetof(MYIO_WRITE_INPUT, CharData) + sizeof(InputBuffer.LongData);

	IoctlResult = DeviceIoControl(
					hDriver,
					IOCTL_MYIO_IO_DWORD_WRITE,
					&InputBuffer,     
					DataLength,
					NULL,
					0,
					&ReturnedLength,
					NULL);

#endif
}







