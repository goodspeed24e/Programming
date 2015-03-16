#include "efi.h"
#include "efilib.h"

EFI_STATUS
InitializeHelloApplication(
IN EFI_HANDLE ImageHandle,
IN EFI_SYSTEM_TABLE *SystemTable
)
{
  InitializeLib(ImageHandle, SystemTable);
  Print(L"\n\n\nEfiLib application started\n\n\n");
  Print(L"\nHit any key to exit this image\n");
  WaitForSingleEvent(SystemTable->ConIn->WaitForKey,0);
  SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\n\r\n\r");
  return EFI_SUCCESS;
}
