#The contents of hello.mak are listed below.

!include $(SDK_INSTALL_DIR)\build\$(SDK_BUILD_ENV)\sdk.env

BASE_NAME = hello
IMAGE_ENTRY_POINT = InitializeHelloApplication

# Globals needed by master.mak
TARGET_APP = $(BASE_NAME)
SOURCE_DIR = $(SDK_INSTALL_DIR)\apps\$(BASE_NAME)
BUILD_DIR = $(SDK_BUILD_DIR)\apps\$(BASE_NAME)

# Include paths
!include $(SDK_INSTALL_DIR)\include\$(EFI_INC_DIR)\makefile.hdr
INC = -I $(SDK_INSTALL_DIR)\include\$(EFI_INC_DIR) \
      -I $(SDK_INSTALL_DIR)\include\$(EFI_INC_DIR)\$(PROCESSOR) $(INC)


all : dirs $(LIBS) $(OBJECTS)

# Program object files
OBJECTS = $(OBJECTS) $(BUILD_DIR)\$(BASE_NAME).obj


# Source file dependencies
$(BUILD_DIR)\$(BASE_NAME).obj : $(*B).c $(INC_DEPS)


# Handoff to master.mak
!include $(SDK_INSTALL_DIR)\build\master.mak