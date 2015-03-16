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
DCOBJS  = main.obj mem_asm.obj func.obj

#
# Build For XXX
#
all:        DosDMI.exe

DosDMI.exe:    $(DCOBJS)
                link $(LFLAGS) $(DCOBJS) ,DosDMI.exe,,,,

#
# Objects For XXX
#
main.obj:    main.c
                $(CC) $(CFLAGS) main.c

func.obj:    func.c
                $(CC) $(CFLAGS) func.c

mem_asm.obj:    mem_asm.asm
                $(ASM) $(MFLAGS) mem_asm.asm
