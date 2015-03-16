#include "efi.h"
#include "efilib.h"

EFI_STATUS
InitializeHelloLibApplication (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
    )
{
    InitializeLib (ImageHandle, SystemTable);
    Print(L"\n\n\nHelloLib application started\n\n\n");
    Print(L"\nHit any key to exit this image\n");
    WaitForSingleEvent(ST->ConIn->WaitForKey,0);
    ST->ConOut->OutputString (ST->ConOut, L"\n\r\n\r");
    return EFI_SUCCESS;
}
