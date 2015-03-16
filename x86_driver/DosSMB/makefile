#
# Compiler and assembler names
#
CC      = cl /c
ASM     = ml /c

#
# Flags for release builds
#
CFLAGS  = /AS /W3 /G3
LFLAGS  = /ST:8192
MFLAGS  = /Zm /W1

#
# List of objects
#
DCOBJS  = smb.obj func.obj mem_asm.obj 

#
# Build For XXX
#
all:        DosSMB.exe

DosSMB.exe:    $(DCOBJS)
                link $(LFLAGS) $(DCOBJS) ,DosSMB.exe,,,,

#
# Objects For XXX
#
smb.obj:    smb.c
                $(CC) $(CFLAGS) smb.c

func.obj:    func.c
                $(CC) $(CFLAGS) func.c

mem_asm.obj:    mem_asm.asm
                $(ASM) $(MFLAGS) mem_asm.asm
