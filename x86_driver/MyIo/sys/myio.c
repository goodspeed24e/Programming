#include <ntddk.h>
#include <stddef.h>
#include "myio.h"


//#define _AMD64
//#define _NT4

#define IOPM_SIZE 0x2000
typedef char IOPM[IOPM_SIZE];
IOPM *pIOPM = NULL;

//
NTSTATUS MyIoDispatch(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
void MyIoUnload(IN PDRIVER_OBJECT DriverObject);

void Ke386SetIoAccessMap(int, IOPM *);
void Ke386QueryIoAccessMap(int, IOPM *);
void Ke386IoSetAccessProcess(PEPROCESS, int);

static ULONG dwRefCount;

NTSTATUS DriverEntry( IN PDRIVER_OBJECT  DriverObject,
                      IN PUNICODE_STRING RegistryPath)
{
	UNICODE_STRING  DeviceNameUnicodeString;
  UNICODE_STRING  DeviceLinkUnicodeString;
	NTSTATUS Status;
	PDEVICE_OBJECT DeviceObject = NULL;
	
	#ifdef ENABLEINT3
	_asm {
		INT 3;
	}
#endif
	
	RtlInitUnicodeString (&DeviceNameUnicodeString, DEVICE_NAME);
	
	// Create our device.
	Status = IoCreateDevice (DriverObject,
                             0,
                             &DeviceNameUnicodeString,
                             FILE_DEVICE_MYIO,
                             0,
                             //TRUE,		// This is    an exclusive device
                             FALSE,     // This isn't an exclusive device
                             &DeviceObject);
	
	if (NT_SUCCESS(Status))
  {
    // Create dispatch points for device control, create, close.

		DriverObject->MajorFunction[IRP_MJ_CREATE]          = 
		DriverObject->MajorFunction[IRP_MJ_CLOSE]           = 
		DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]  = MyIoDispatch;
		DriverObject->DriverUnload                          = MyIoUnload;

    // Create a symbolic link, e.g. a name that a Win32 app can specify
    // to open the device.

    RtlInitUnicodeString (&DeviceLinkUnicodeString, DOS_DEVICE_NAME);

    Status = IoCreateSymbolicLink (&DeviceLinkUnicodeString,
                                     &DeviceNameUnicodeString);

    if (!NT_SUCCESS(Status))
    {
      // Symbolic link creation failed- note this & then delete the
      // device object (it's useless if a Win32 app can't get at it).

      IoDeleteDevice (DeviceObject);
    }
		
		dwRefCount = NT_SUCCESS(Status) ? 0 : (ULONG)-1;
		
  }
	
	return Status;
}

// Process the IRPs sent to this device

NTSTATUS MyIoDispatch(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	PIO_STACK_LOCATION pIrpStack;
	NTSTATUS Status;
	int index;

	//	Initialize the irp info field.
	//	This is used to return the number of bytes transfered.

	Irp->IoStatus.Information = 0;

	pIrpStack = IoGetCurrentIrpStackLocation(Irp);

    //  Set default return status
	Status = STATUS_NOT_IMPLEMENTED;

	// Dispatch based on major fcn code.

	switch (pIrpStack->MajorFunction)
	{
		case IRP_MJ_CREATE:
			if(dwRefCount!=(ULONG)-1)
				dwRefCount++;
			Status = STATUS_SUCCESS;
			break;

		case IRP_MJ_CLOSE:
			if(dwRefCount!=(ULONG)-1)
				dwRefCount--;
			Status = STATUS_SUCCESS;
			break;

		case IRP_MJ_DEVICE_CONTROL: //
			//  Dispatch on IOCTL
			switch (pIrpStack->Parameters.DeviceIoControl.IoControlCode)
			{//依照選擇功能執行不同程式
        
				case IOCTL_MYIO_MEM_READ:
					Status = IoctlReadMem(Irp->AssociatedIrp.SystemBuffer,
					                      pIrpStack->Parameters.DeviceIoControl.InputBufferLength,
                                Irp->AssociatedIrp.SystemBuffer,
                            		pIrpStack->Parameters.DeviceIoControl.OutputBufferLength,
                                (ULONG*)&Irp->IoStatus.Information);
					break;
				case IOCTL_MYIO_MEM_WRITE:
					Status = IoctlWriteMem(Irp->AssociatedIrp.SystemBuffer,
                                 pIrpStack->Parameters.DeviceIoControl.InputBufferLength,
                                 Irp->AssociatedIrp.SystemBuffer,
                                 pIrpStack->Parameters.DeviceIoControl.OutputBufferLength,
                                 (ULONG*)&Irp->IoStatus.Information);
					break;
				case IOCTL_MYIO_IO_BYTE_READ:
				case IOCTL_MYIO_IO_WORD_READ:
				case IOCTL_MYIO_IO_DWORD_READ:
					Status = IoctlReadIo(pIrpStack->Parameters.DeviceIoControl.IoControlCode,
                                    Irp->AssociatedIrp.SystemBuffer,
                                    pIrpStack->Parameters.DeviceIoControl.InputBufferLength,
                                    Irp->AssociatedIrp.SystemBuffer,
                                    pIrpStack->Parameters.DeviceIoControl.OutputBufferLength,
                                    (ULONG*)&Irp->IoStatus.Information);
					break;
				
				case IOCTL_MYIO_IO_BYTE_WRITE:
				case IOCTL_MYIO_IO_WORD_WRITE:
				case IOCTL_MYIO_IO_DWORD_WRITE:
					Status = IoctlWriteIo(pIrpStack->Parameters.DeviceIoControl.IoControlCode,
																		Irp->AssociatedIrp.SystemBuffer,
																		pIrpStack->Parameters.DeviceIoControl.InputBufferLength,
																		Irp->AssociatedIrp.SystemBuffer,
																		pIrpStack->Parameters.DeviceIoControl.OutputBufferLength,
																		(ULONG*)&Irp->IoStatus.Information);
					break;
				
				case IOCTL_PCI_READ_CFG:
					Status = IoctlReadCfg(Irp->AssociatedIrp.SystemBuffer,
																	pIrpStack->Parameters.DeviceIoControl.InputBufferLength,
																	Irp->AssociatedIrp.SystemBuffer,
																	pIrpStack->Parameters.DeviceIoControl.OutputBufferLength,
																	(ULONG*)&Irp->IoStatus.Information);
					break;

				case IOCTL_PCI_WRITE_CFG:
					Status = IoctlWriteCfg(Irp->AssociatedIrp.SystemBuffer,
																			pIrpStack->Parameters.DeviceIoControl.InputBufferLength,
																			Irp->AssociatedIrp.SystemBuffer,
																			pIrpStack->Parameters.DeviceIoControl.OutputBufferLength,
																			(ULONG*)&Irp->IoStatus.Information);
					break;
				
				case IOCTL_GET_REFCOUNT:
					*(PULONG)Irp->AssociatedIrp.SystemBuffer = dwRefCount;
					Irp->IoStatus.Information = sizeof(dwRefCount);
					Status = STATUS_SUCCESS;
					break;
			}
			break;
	}

	// We're done with I/O request.  Record the status of the I/O action.
	Irp->IoStatus.Status = Status;

	// Don't boost priority when returning since this took little time.
	IoCompleteRequest(Irp, IO_NO_INCREMENT );
	
	return Status;
}

// Delete the associated device and return

void MyIoUnload(IN PDRIVER_OBJECT DriverObject)
{
  NTSTATUS Status;
	CM_RESOURCE_LIST NullResourceList;
	BOOLEAN ResourceConflict;
	UNICODE_STRING Win32DeviceName;

	RtlInitUnicodeString(&Win32DeviceName, DOS_DEVICE_NAME);

	Status = IoDeleteSymbolicLink(&Win32DeviceName);
	if (NT_SUCCESS(Status))
	{
		IoDeleteDevice (DriverObject->DeviceObject);
	}
}

NTSTATUS IoctlReadMem(void *lpInBuffer, ULONG nInBufferSize, void *lpOutBuffer, ULONG nOutBufferSize, ULONG *lpBytesReturned)
{
	MYIO_MEMREAD_INPUT *read_param;
	ULONG	size;
	PHYSICAL_ADDRESS address;
	PVOID	maped;
	BOOLEAN	err;
	
	if( nInBufferSize != sizeof(MYIO_MEMREAD_INPUT) )
	{
		return STATUS_INVALID_PARAMETER;
	}
	read_param	= (MYIO_MEMREAD_INPUT *) lpInBuffer;
	size = read_param->unitsize * read_param->count;

	if ( nOutBufferSize < size )
	{
		return STATUS_INVALID_PARAMETER;
	}

	address.HighPart = 0;
	address.LowPart = read_param->address;

	maped = MmMapIoSpace(address, size, FALSE);

	err = FALSE;
	switch(read_param->unitsize)
	{
		case 1:
			READ_REGISTER_BUFFER_UCHAR(maped, lpOutBuffer, read_param->count);
			break;
		case 2:
			READ_REGISTER_BUFFER_USHORT(maped, lpOutBuffer, read_param->count);
			break;
		case 4:
			READ_REGISTER_BUFFER_ULONG(maped, lpOutBuffer, read_param->count);
			break;
		default:
			err = TRUE;
	}

	MmUnmapIoSpace(maped, size);

	if(err)
		return STATUS_INVALID_PARAMETER;

	*lpBytesReturned = nOutBufferSize;

	return STATUS_SUCCESS;
}

NTSTATUS IoctlWriteMem(	void *lpInBuffer, ULONG nInBufferSize, void *lpOutBuffer, ULONG nOutBufferSize, ULONG *lpBytesReturned)
{
	MYIO_MEMWRITE_INPUT *write_param;
	ULONG size;
	PHYSICAL_ADDRESS address;
	PVOID	maped;
	BOOLEAN	err;

	if( nInBufferSize < offsetof(MYIO_MEMWRITE_INPUT,data) )
	{
		return STATUS_INVALID_PARAMETER;
	}

	write_param = (MYIO_MEMWRITE_INPUT *)lpInBuffer;

	size = write_param->unitsize * write_param->count;
	if( nInBufferSize < size + offsetof(MYIO_MEMWRITE_INPUT, data))
	{
		return STATUS_INVALID_PARAMETER;
	}

	address.HighPart = 0;
	address.LowPart = write_param->address;

	maped = MmMapIoSpace(address, size, FALSE);

	err = FALSE;
	switch(write_param->unitsize)
	{
		case 1:
			WRITE_REGISTER_BUFFER_UCHAR(maped, (UCHAR*)&write_param->data, write_param->count);
			break;
		case 2:
			WRITE_REGISTER_BUFFER_USHORT(maped, (USHORT*)&write_param->data, write_param->count);
			break;
		case 4:
			WRITE_REGISTER_BUFFER_ULONG(maped, (ULONG*)&write_param->data, write_param->count);
			break;
		default:
			err = TRUE;
	}

	MmUnmapIoSpace(maped, size);

	if(err)
		return STATUS_INVALID_PARAMETER;

	*lpBytesReturned = 0;

	return STATUS_SUCCESS;
}

NTSTATUS IoctlReadIo(ULONG IoctlCode,void *lpInBuffer, ULONG nInBufferSize, void *lpOutBuffer, ULONG nOutBufferSize, ULONG *lpBytesReturned)
{
	ULONG DataBufferSize;
	//ULONG nPort; 
	USHORT nPort;
	
	switch (IoctlCode)
	{
		default:                    // There isn't really any default but this will quiet the compiler.
		case IOCTL_MYIO_IO_BYTE_READ:
			DataBufferSize = sizeof(UCHAR);
			break;
		case IOCTL_MYIO_IO_WORD_READ:
			DataBufferSize = sizeof(USHORT);
			break;
		case IOCTL_MYIO_IO_DWORD_READ:
			DataBufferSize = sizeof(ULONG);
			break;
	}
	
	if(nOutBufferSize < DataBufferSize )
	{
		return STATUS_INVALID_PARAMETER;
	}

	// Buffers are big enough.
	nPort = *(USHORT*)lpInBuffer; // Get the I/O port number from the buffer.

	switch (IoctlCode)
	{
		case IOCTL_MYIO_IO_BYTE_READ:
			*(PUCHAR)lpOutBuffer = READ_PORT_UCHAR((PUCHAR)(nPort) );
			break;
		case IOCTL_MYIO_IO_WORD_READ:
			*(PUSHORT)lpOutBuffer = READ_PORT_USHORT((PUSHORT)(nPort) );
			break;
		case IOCTL_MYIO_IO_DWORD_READ:
			*(PULONG)lpOutBuffer = READ_PORT_ULONG((PULONG)(nPort) );
			break;
	}
    
	*lpBytesReturned = DataBufferSize;

	return STATUS_SUCCESS;
}

NTSTATUS IoctlWriteIo(ULONG IoctlCode,void *lpInBuffer, ULONG nInBufferSize, void *lpOutBuffer, ULONG nOutBufferSize,	ULONG *lpBytesReturned)
{
	ULONG DataBufferSize;
	//ULONG nPort; 
	USHORT nPort;
	MYIO_WRITE_INPUT* InBuffer;
	
	
	InBuffer = (MYIO_WRITE_INPUT*) lpInBuffer;

	switch (IoctlCode)
	{
		default:  // There isn't really any default but this will quiet the compiler.
		case IOCTL_MYIO_IO_BYTE_WRITE:
			DataBufferSize = sizeof(UCHAR);
			break;
		case IOCTL_MYIO_IO_WORD_WRITE:
			DataBufferSize = sizeof(USHORT);
			break;
		case IOCTL_MYIO_IO_DWORD_WRITE:
			DataBufferSize = sizeof(ULONG);
			break;
	}

	if ( nInBufferSize < (sizeof(ULONG) + DataBufferSize) )
	{
		return STATUS_INVALID_PARAMETER;
	}

	nPort = (USHORT)InBuffer->PortNumber;

	switch (IoctlCode)
	{
		case IOCTL_MYIO_IO_BYTE_WRITE:
			WRITE_PORT_UCHAR((PUCHAR)nPort, InBuffer->CharData );
			break;
		case IOCTL_MYIO_IO_WORD_WRITE:
			WRITE_PORT_USHORT((PUSHORT)nPort, InBuffer->ShortData );
			break;
		case IOCTL_MYIO_IO_DWORD_WRITE:
			WRITE_PORT_ULONG((PULONG)nPort, InBuffer->LongData );
			break;
	}
	return STATUS_SUCCESS;
}

NTSTATUS IoctlReadCfg(void *lpInBuffer, ULONG nInBufferSize,void *lpOutBuffer,ULONG nOutBufferSize,ULONG *lpBytesReturned)
{
	MYIO_PCICFGREAD_INPUT *read_param;
	NTSTATUS status;

	if ( nInBufferSize != sizeof(MYIO_PCICFGREAD_INPUT) )
	{
		return STATUS_INVALID_PARAMETER;
	}
	read_param	= (MYIO_PCICFGREAD_INPUT *) lpInBuffer;


	status = pciConfigRead(read_param->pci_address, read_param->pci_offset,lpOutBuffer, nOutBufferSize);

	if(status == STATUS_SUCCESS)
	{
		*lpBytesReturned = nOutBufferSize;
	}
	else
	{
		*lpBytesReturned = 0;
	}

	return status;
}

NTSTATUS IoctlWriteCfg(void *lpInBuffer,ULONG nInBufferSize,void *lpOutBuffer,ULONG nOutBufferSize,ULONG *lpBytesReturned)
{
	MYIO_PCICFGWRITE_INPUT *write_param;
	ULONG writesize;
	NTSTATUS status;

	if ( nInBufferSize < offsetof(MYIO_PCICFGWRITE_INPUT,data))
	{
		return STATUS_INVALID_PARAMETER;
	}

	write_param = (MYIO_PCICFGWRITE_INPUT *)lpInBuffer;
	writesize = nInBufferSize - offsetof(MYIO_PCICFGWRITE_INPUT, data);
	
	*lpBytesReturned = 0;

	return pciConfigWrite(write_param->pci_address,write_param->pci_offset,&write_param->data,writesize);
}

NTSTATUS pciConfigRead(ULONG pci_address, ULONG offset, void *data, int len)
{
	PCI_SLOT_NUMBER slot;
	int err;
	ULONG BusNumber;

	BusNumber = pciGetBus(pci_address);
	slot.u.AsULONG = 0;
	slot.u.bits.DeviceNumber = pciGetDev(pci_address);
	slot.u.bits.FunctionNumber = pciGetFunc(pci_address);
	err = HalGetBusDataByOffset(PCIConfiguration,BusNumber,slot.u.AsULONG,data,offset,len);
	if(err == 0)
		return PCI_ERR_BUSNOTEXIST;
	
	if(len != 2 && err == 2)
		return PCI_ERR_NODEVICE;
	
	if(len != err)
		return PCI_ERR_CONFREAD;
	
	return STATUS_SUCCESS;
}

NTSTATUS pciConfigWrite(ULONG pci_address, ULONG offset, void *data, int len)
{
	PCI_SLOT_NUMBER slot;
	int err;
	ULONG BusNumber;

	BusNumber = pciGetBus(pci_address);

	slot.u.AsULONG = 0;
	slot.u.bits.DeviceNumber = pciGetDev(pci_address);
	slot.u.bits.FunctionNumber = pciGetFunc(pci_address);
	err = HalSetBusDataByOffset(PCIConfiguration,BusNumber,slot.u.AsULONG,data,offset,len);
	if(err != len )
		return PCI_ERR_CONFWRITE;
	
	return STATUS_SUCCESS;
}


