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
DCOBJS  = mem.obj mem_asm.obj func.obj

#
# Build For XXX
#
all:        DosMem.exe

DosMem.exe:    $(DCOBJS)
                link $(LFLAGS) $(DCOBJS) ,DosMem.exe,,,,

#
# Objects For XXX
#
mem.obj:    mem.c
                $(CC) $(CFLAGS) mem.c

func.obj:    func.c
                $(CC) $(CFLAGS) func.c

mem_asm.obj:    mem_asm.asm
                $(ASM) $(MFLAGS) mem_asm.asm
