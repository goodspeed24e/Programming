
//
// HelloWorld.c
//
#include "EfiShellLib.h"
#include "Helloworld.h"

//
// This is the generated header file which includes whatever needs 
// to be exported (string tokens)
//
#include STRING_DEFINES_FILE
//
// This will be replaced by build tool with the name of array in
// automatically generated .c file
//
extern UINT8 STRING_ARRAY_NAME[];
//
// Entry point declaration
//
#ifdef EFI_BOOTSHELL
EFI_APPLICATION_ENTRY_POINT (HelloMain)
#endif
//
// Entry point function - HelloMain
//
EFI_STATUS
EFIAPI
HelloMain (
  IN EFI_HANDLE                            ImageHandle,
  IN EFI_SYSTEM_TABLE                      *SystemTable
  )
{
  EFI_HII_HANDLE	HiiHandle;
  EFI_GUID		HelloGuid = HELLOWORLD_STRING_PACK_GUID;
 //
 // Initialize the execution environment first
 //
  EFI_SHELL_APP_INIT (ImageHandle, SystemTable);
 //
 // If we are to use strings in application, we must call   
 // EFI_SHELL_STR_INIT() first to register our string package 
 // to HII database
 //  
  EFI_SHELL_STR_INIT (HiiHandle, STRING_ARRAY_NAME, HelloGuid);


  //
  // Check the required version of EFI system
  // At least, we should run on a system that keeps to EFI1.02 SPEC
  //
  if (!EFI_PROPER_VERSION (0, 99)) {
    PrintToken (
      STRING_TOKEN (STR_SHELLENV_GNC_COMMAND_NOT_SUPPORT),
      HiiHandle,
      L"helloworld",
      EFI_VERSION_0_99 
      );
LibUnInitializeStrings();
return EFI_UNSUPPORTED;
}
  //
  // Say Hello to the world
  //
  PrintToken (STRING_TOKEN(STR_HELLOWORLD), HiiHandle);
  //
  // Say Goodbye to the world
  //
   PrintToken (STRING_TOKEN(STR_GOODBYE), HiiHandle);
  
  LibUnInitializeStrings ();
  return EFI_SUCCESS;
}

