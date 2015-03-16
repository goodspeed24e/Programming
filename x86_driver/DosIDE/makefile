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
DCOBJS  = ide.obj mem_asm.obj func.obj

#
# Build For XXX
#
all:        DosIDE.exe

DosIDE.exe:    $(DCOBJS)
                link $(LFLAGS) $(DCOBJS) ,DosIDE.exe,,,,

#
# Objects For XXX
#
ide.obj:    ide.c
                $(CC) $(CFLAGS) ide.c

func.obj:    func.c
                $(CC) $(CFLAGS) func.c

mem_asm.obj:    mem_asm.asm
                $(ASM) $(MFLAGS) mem_asm.asm
