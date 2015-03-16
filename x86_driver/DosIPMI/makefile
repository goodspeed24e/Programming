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
DCOBJS  = dosipmi.obj func.obj mem_asm.obj kcs.obj

#
# Build For XXX
#
all:        DosIPMI.exe

DosIPMI.exe:    $(DCOBJS)
                link $(LFLAGS) $(DCOBJS) ,DosIPMI.exe,,,,

#
# Objects For XXX
#
dosipmi.obj:    dosipmi.c
                $(CC) $(CFLAGS) dosipmi.c

func.obj:    func.c
                $(CC) $(CFLAGS) func.c

kcs.obj:    kcs.c
                $(CC) $(CFLAGS) kcs.c

mem_asm.obj:    mem_asm.asm
                $(ASM) $(MFLAGS) mem_asm.asm
