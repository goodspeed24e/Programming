# Compiler and assembler names
CC      = cl /c
ASM     = ml /c


# Flags for release builds
CFLAGS  = /AS /W3 /G3
LFLAGS  = /ST:8192
MFLAGS  = /Zm /W1


# List of objects
DCOBJS  = E820.obj E820_ASM.obj  


# Build For XXX
all:        E820.exe

E820.exe:    $(DCOBJS)
                link $(LFLAGS) $(DCOBJS) ,E820.exe,,,,

# Objects For XXX
E820.obj:    E820.c
                $(CC) $(CFLAGS) E820.c

E820_ASM.obj: E820_ASM.asm
                $(ASM) $(MFLAGS) E820_ASM.asm

