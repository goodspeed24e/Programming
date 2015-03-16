
#include <windows.h>
#include <winioctl.h>
#include <stddef.h>

#include "def.h"
#include "myio.h"

ULONG WINAPI pciConfigRead(ULONG pci_address,ULONG reg_address, BYTE *data , ULONG size)
{
	MYIO_PCICFGREAD_INPUT buf;
	DWORD ReturnedLength;
	BOOL IoctlResult;
	
	buf.pci_address = pci_address;
	buf.pci_offset = reg_address;
	IoctlResult = DeviceIoControl(
					hDriver,
					IOCTL_PCI_READ_CFG,
					&buf,
					sizeof(buf),
					data,
					size,
					&ReturnedLength,
					NULL);

	if (!IoctlResult)                            // Did the IOCTL succeed?
	{
		return GetLastError();
	}

      
	return 0;
}


bool _stdcall read_pci_byte(BYTE bus,BYTE dev,BYTE func,ULONG offset,PBYTE data)
{
	DWORD addr;

	addr = pciBusDevFunc(bus,dev,func);

 	if(pciConfigRead(addr,offset,data,1))
 	{
 		return false;
 	}
	return true;
}

bool _stdcall read_pci_word(BYTE bus,BYTE dev,BYTE func,ULONG offset,PWORD data)
{
  DWORD addr;

	addr = pciBusDevFunc(bus,dev,func);

 	if(pciConfigRead(addr,offset,(PBYTE)data,2))
 	{
 		return false;
 	}
	
	return true;
}

bool _stdcall read_pci_dword(BYTE bus,BYTE dev,BYTE func,ULONG offset,PDWORD data)
{
  DWORD addr;

	addr = pciBusDevFunc(bus,dev,func);

 	if(pciConfigRead(addr,offset,(PBYTE)data,4))
 	{
 		return false;
 	}

	return true;
}

ULONG pciConfigWrite(ULONG pci_address,ULONG reg_address, BYTE *data , int size)
{
	MYIO_PCICFGWRITE_INPUT	*w_input;
	DWORD ReturnedLength;
	int w_input_size;
	BOOL IoctlResult;
	
	w_input_size = offsetof(MYIO_PCICFGWRITE_INPUT, data) + size;
	w_input = (MYIO_PCICFGWRITE_INPUT*)malloc(w_input_size);
	if(w_input == NULL)
		return (-1);
	memcpy(w_input->data, data, size);
	w_input->pci_address = pci_address;
	w_input->pci_offset = reg_address;
	IoctlResult = DeviceIoControl(
					hDriver,
					IOCTL_PCI_WRITE_CFG,
					w_input,
					w_input_size,
					NULL,
					0,
					&ReturnedLength,
					NULL);

	free(w_input);
	if (!IoctlResult)                            // Did the IOCTL succeed?
	{
		return GetLastError();
	}
	return 0;
}

bool _stdcall write_pci_byte(BYTE bus,BYTE dev,BYTE func,ULONG offset,BYTE value)
{
	DWORD addr;

	addr = pciBusDevFunc(bus,dev,func);

 	if(pciConfigWrite(addr,offset,&value,sizeof(value)))
 	{
 		return false;
 	}
 	return true;
}

bool _stdcall write_pci_word(BYTE bus,BYTE dev,BYTE func,ULONG offset,WORD value)
{
	DWORD addr;

	addr = pciBusDevFunc(bus,dev,func);

 	if(pciConfigWrite(addr,offset,(BYTE *)&value,sizeof(value)))
 	{
 		return false;
 	}
 	return true;
}

bool _stdcall write_pci_dword(BYTE bus,BYTE dev,BYTE func,ULONG offset,DWORD value)
{
	DWORD addr;

	addr = pciBusDevFunc(bus,dev,func);

 	if(pciConfigWrite(addr,offset,(BYTE *)&value,sizeof(value)))
 	{
 		return false;
 	}
 	return true;
}

