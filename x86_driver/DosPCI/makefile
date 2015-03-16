#
# Compiler and assembler names
#
CC      = cl /c
ASM     = ml /c

#
# Flags for debugging builds
#
#CFLAGS = /AL /Zi /W3 /Od /nologo /Gs /DNORMAL
#LFLAGS = /co /map /ST:8192
#MFLAGS = /Zm /Zi /W1 /Sa /Fl

#
# Flags for release builds
#
CFLAGS  = /AS /W3 /G3
LFLAGS  = /ST:8192
MFLAGS  = /Zm /W1

#
# List of objects
#
DCOBJS  = pci.obj func.obj mem_asm.obj #io_pci.obj 

#
# Build For XXX
#
all:        DosPCI.exe

DosPCI.exe:    $(DCOBJS)
                link $(LFLAGS) $(DCOBJS) ,DosPCI.exe,,,,

#
# Objects For XXX
#
PCI.obj:    PCI.c
                $(CC) $(CFLAGS) PCI.c
func.obj:  func.c
                $(CC) $(CFLAGS) func.c
                
#io_pci.obj: IO_PCI.asm
#                $(ASM) $(MFLAGS) IO_PCI.asm

mem_asm.obj: mem_asm.asm
                $(ASM) $(MFLAGS) mem_asm.asm
