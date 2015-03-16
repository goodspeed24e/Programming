# Compiler and assembler names
CC      = cl /c
ASM     = ml /c


# Flags for release builds
CFLAGS  = /AS /W3 /G3
LFLAGS  = /ST:8192
MFLAGS  = /Zm /W1

# List of objects
DCOBJS  = RS232.obj mem_asm.obj func.obj

# Build For XXX
all:        DosCOM.exe

DosCOM.exe:    $(DCOBJS)
                link $(LFLAGS) $(DCOBJS) ,DosCOM.exe,,,,

# Objects For XXX
RS232.obj:    RS232.c
                $(CC) $(CFLAGS) RS232.c
func.obj:    func.c
                $(CC) $(CFLAGS) func.c

mem_asm.obj:    mem_asm.asm
                $(ASM) $(MFLAGS) mem_asm.asm
                