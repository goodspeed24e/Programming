
#ifndef _MYIO_H_
#define _MYIO_H_

#ifdef MYIO_DLL
#define MYIO_API _declspec(dllexport)
#else
#define MYIO_API _declspec(dllimport)
#endif

extern "C"
{
	MYIO_API bool _stdcall OnMyIo();
  MYIO_API void _stdcall OffMyIo();
	MYIO_API bool _stdcall read_mem_byte(ULONG address, PBYTE data);
	MYIO_API bool _stdcall read_mem_word(ULONG address, PWORD data);
  MYIO_API bool _stdcall read_mem_dword(ULONG address, PDWORD data);
  MYIO_API bool _stdcall write_mem_byte(ULONG address, PBYTE data);
  MYIO_API bool _stdcall write_mem_word(ULONG address, PBYTE data);
  MYIO_API bool _stdcall write_mem_dword(ULONG address, PBYTE data);
  MYIO_API bool _stdcall read_io_byte(WORD address,PBYTE data);
  MYIO_API bool _stdcall read_io_word(WORD address,PWORD data);
  MYIO_API bool _stdcall read_io_dword(WORD address,PDWORD data);
  MYIO_API void _stdcall write_io_byte(WORD address, BYTE data);
  MYIO_API void _stdcall write_io_word(WORD address, WORD data);
  MYIO_API void _stdcall write_io_dword(WORD address, DWORD data);
 	MYIO_API bool _stdcall read_pci_byte(BYTE bus,BYTE dev,BYTE func,ULONG offset,PBYTE data);
  MYIO_API bool _stdcall read_pci_word(BYTE bus,BYTE dev,BYTE func,ULONG offset,PWORD data);
  MYIO_API bool _stdcall read_pci_dword(BYTE bus,BYTE dev,BYTE func,ULONG offset,PDWORD data);
  MYIO_API bool _stdcall write_pci_byte(BYTE bus,BYTE dev,BYTE func,ULONG offset,BYTE value);
  MYIO_API bool _stdcall write_pci_word(BYTE bus,BYTE dev,BYTE func,ULONG offset,WORD value);
  MYIO_API bool _stdcall write_pci_dword(BYTE bus,BYTE dev,BYTE func,ULONG offset,DWORD value);
}


#endif

