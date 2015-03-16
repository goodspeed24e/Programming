#include "..\\def.h"

// NT device name
#define DEVICE_NAME L"\\Device\\MyIo"
#define DOS_DEVICE_NAME L"\\DosDevices\\MyIo"


#define pciGetBus(BXreg)		((BXreg>>8)&0xff)
#define pciGetDev(BXreg)		((BXreg>>3)&0x1f)
#define pciGetFunc(BXreg)		(BXreg&7)

#define N_ISR	16

// driver local data structure specific to each device object
typedef struct _LOCAL_DEVICE_INFO {
    ULONG               DeviceType;     // Our private Device Type
    PDEVICE_OBJECT      DeviceObject;   // The Gpd device object.
	struct {
	    PKINTERRUPT	InterruptObject;
		BOOLEAN				SetupOK;		// after call setup interrupt set TRUE
	    KAFFINITY			Affinity;
	    KIRQL				irql;
		ULONG				MappedVector;
		KINTERRUPT_MODE		InterruptMode;
		BOOLEAN				ShareVector;

		HANDLE Handle ;
		PKEVENT Event ;
	} table[N_ISR];

} LOCAL_DEVICE_INFO, *PLOCAL_DEVICE_INFO;

NTSTATUS IoctlReadMem(void *lpInBuffer,ULONG nInBufferSize,void *lpOutBuffer,ULONG nOutBufferSize,ULONG *lpBytesReturned);
NTSTATUS IoctlWriteMem(void *lpInBuffer,ULONG nInBufferSize,void *lpOutBuffer,ULONG nOutBufferSize,ULONG *lpBytesReturned);
NTSTATUS IoctlReadIo(ULONG IoctlCode,void *lpInBuffer,ULONG nInBufferSize,void *lpOutBuffer,ULONG nOutBufferSize,ULONG *lpBytesReturned);
NTSTATUS IoctlWriteIo(ULONG IoctlCode,void *lpInBuffer,ULONG nInBufferSize,void *lpOutBuffer,ULONG nOutBufferSize,ULONG *lpBytesReturned);
NTSTATUS IoctlReadCfg(void *lpInBuffer, ULONG nInBufferSize,void *lpOutBuffer,ULONG nOutBufferSize,ULONG *lpBytesReturned);
NTSTATUS IoctlWriteCfg(void *lpInBuffer,ULONG nInBufferSize,void *lpOutBuffer,ULONG nOutBufferSize,ULONG *lpBytesReturned);
NTSTATUS pciConfigRead(ULONG pci_address, ULONG offset, void *data, int len);
NTSTATUS pciConfigWrite(ULONG pci_address, ULONG offset, void *data, int len);
