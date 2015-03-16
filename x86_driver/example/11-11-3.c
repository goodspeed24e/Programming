#include "efi.h"
#include "efilib.h"
#include <atk_libc.h>
#include <stdio.h>


EFI_STATUS
InitializeHelloApplication(
IN EFI_HANDLE ImageHandle,
IN EFI_SYSTEM_TABLE *SystemTable
)
{
  InitializeLibC(ImageHandle, SystemTable);
  printf("Hello LibC application started\n\n\n");
  printf("Hit C/R to exit this image\n");
  return( getchar());
}
