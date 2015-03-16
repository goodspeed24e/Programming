	title   MEM_ASM.asm
        .model  small
        .586p

;---------MACROs-------------------------------------------------------------

RESTORE_REGISTERS  MACRO
	popf	; Restore all flags
	pop     es
	pop     ds
	pop     edi
	pop     esi
	pop     edx
	pop     ecx
	pop     ebx
	pop     eax
ENDM

HEAD_BG	MACRO
	push    bp
	mov     bp, sp
	sub     sp, 8
	
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi
	push	edi
	push	ds
	push	es
	pushf	; save the flags
ENDM

HEAD_END	MACRO
	mov     sp, bp
	pop     bp
	ret
ENDM

;---------------------------------------------------------------------------------
public	_Check_A20
public	_into_PT_mode
public	_into_RL_mode
public  Enable_A20

public	_load_PT_inside
public	_load_RL_inside

public  _read_mem_dword
public	_read_mem_word
public	_read_mem_byte
public	_write_mem_byte

public  _read_io_dword
public  _write_io_dword
public  _read_io_word
public  _write_io_word
public  _read_io_byte
public  _write_io_byte
public  _write_pci_byte
public  _write_pci_word
public  _write_pci_dword
public  _read_pci_byte
public  _read_pci_word
public  _read_pci_dword

PE              equ     0001h           ; Protection mode enable
REAL_SEL        equ     1 * Size desc_386
BIG_SEL         equ     3 * Size desc_386        ;           *B0



;******************************************************************************
;
;       Real_desc equates
;
;******************************************************************************
;
RLIMIT          equ     0FFFFh          ; Segment limit bits 15:00
RBASEL          equ     00000h          ; Base bits 15:00
RBASE           equ     00h             ; Base bits 23:16
RACCESS         equ     10010010b       ; Access byte
RGRAND          equ     00h             ; G, D,   limit bits 19:16
RBASEH          equ     00h             ; Base bits 31:24

;******************************************************************************
;
;       CS_desc equates
;
;******************************************************************************
;
CLIMIT          equ     0FFFFh          ; CS segment limit bits 15:00
CBASEL          equ     00000h          ; CS base bits 15:00
CBASE           equ     01h             ; CS base bits 23:16
CACCESS         equ     10011010b       ; CS access byte
CGRAND          equ     01h             ; CS G, D,   limit bits 19:16
CBASEH          equ     00h             ; CS base bits 31:24

;
;******************************************************************************
;
;       BIG_desc equates (Map entire 4 gig space)                           *B0
;
;******************************************************************************
BLIMIT          equ     0FFFFh          ; Segment limit bits 15:00
BBASEL          equ     00000h          ; Base bits 15:00
BBASE           equ     00h             ; Base bits 23:16
BACCESS         equ     10010010b       ; Access byte
BGRAND          equ     8Fh             ; G, D,   limit bits 19:16
BBASEH          equ     00h             ; Base bits 31:24

;******************************************************************************
;
; PCI read/write
;
;******************************************************************************
PCI_CFG_READ_BYTE               EQU     0h
PCI_CFG_READ_WORD               EQU     1h
PCI_CFG_READ_DWORD              EQU     2h
PCI_CFG_WRITE_BYTE              EQU     3h
PCI_CFG_WRITE_WORD              EQU     4h
PCI_CFG_WRITE_DWORD             EQU     5h

CFG_DATA_PORT                   EQU     0CFCh
CFG_ADDR_PORT                   EQU     0CF8H

;---------------------------------------------------------------------------------

_TEXT	segment public use16 'code'
	assume  cs: _TEXT

;------------------------------------------------------------------------------
; for PT real mode
;------------------------------------------------------------------------------

desc_386        struc                   ; 386 descriptor
limit_386       dw      ?               ; Limit bits 15:0
base_low_386    dw      ?               ; Low 16 bits of 32-bit address
base_386        db      ?               ; Mid 8 bits of 32-bit address
access_386      db      ?               ; Access rights byte
gd_limit_386    db      ?               ; Grand, operand, limit bits 19:16
base_high_386   db      ?               ; High 8 bits of 32-bit address
desc_386        ends

ZGDT            label   FWord
GDT             dw      GDTABLE_LIMIT   ; Limit bits 15:0
                dw      ?               ; Base  bits 15:0
                db      ?               ; Base  bits 23:16
                db      0

GDTable         label   word
Null_desc       desc_386        <0,0,0,0,0,0>
Real_desc       desc_386        <RLIMIT,RBASEL,RBASE,RACCESS,RGRAND,RBASEH>
CS_desc         desc_386        <CLIMIT,CBASEL,CBASE,CACCESS,CGRAND,CBASEH>
BIG_desc        desc_386        <BLIMIT,BBASEL,BBASE,BACCESS,BGRAND,BBASEH>
GDTABLE_LIMIT = ($-GDTABLE-1)
;------------------------------------------------------------------------------

_Check_A20	proc	near

	HEAD_BG
	
	xor	ax, ax
	mov	ds, ax
	not	ax
	mov	es, ax
	cli
	mov	al, BYTE PTR ds:[0]
	mov	ah, es:[10h]
	cmp	al, ah
	je	RLMod
	RESTORE_REGISTERS
	mov     al,1
	HEAD_END
RLMod:
	RESTORE_REGISTERS
	mov     al,0
	HEAD_END
_Check_A20 endp

;=================================================================
;       into big mode
;=================================================================

_into_PT_mode    proc    near
  HEAD_BG
        
  pushf
  cli
        
  ;Data GDT
  ;
  mov     ax,cs
  mov     ds,ax
        
  xor     eax,eax
  mov     edx,eax
  lea     dx,Offset GDTable
  mov     ax,cs
  shl     eax,4
  add     eax,edx
  mov	    bx,Offset ZGDT
  mov     DWord Ptr ds:[bx+2],eax

  call    Enable_A20

  push    eax

  lgdt    fword ptr cs:zgdt       ;;; load GDT register

  mov     eax,cr0                 ;;; move cr0 to eax
  or      ax,PE                   ;;; set protection mode enable bit

  mov     cr0,eax                 ;;; now in protected mode
  jmp     $+2                     ;;; flush prefetch queue

  mov     ax,BIG_SEL              ;;; BIG selector
  mov     es,ax                   ;;; load ES with BIG selector
  mov     ds,ax                   ;;; load DS with BIG selector

  mov     eax,cr0                 ;;; move cr0 to eax
  and     ax,NOT PE               ;;; clear protection mode enable bit
  mov     cr0,eax                 ;;; back in real mode
  jmp     $+2                     ;;; flush prefetch queue

  pop     eax

  xor     ax,ax
  mov     ds,ax
  mov     es,ax
  popf
        
  RESTORE_REGISTERS
	HEAD_END
  ret

_into_PT_mode    endp


;=================================================================
;       Return to real mode
;=================================================================

_into_RL_mode   proc    near

	HEAD_BG
	cli
	
  pushf
  cli
  push    eax

  lgdt    fword ptr cs:zgdt       ;;; load GDT register

  mov     eax,cr0                 ;;; move cr0 to eax
  or      ax,PE                   ;;; set protection mode enable bit

  mov     cr0,eax                 ;;; now in protected mode
  jmp     $+2                     ;;; flush prefetch queue

  mov     ax,REAL_SEL             ;;; real selector
  mov     es,ax                   ;;; load ES with real selector
  mov     ds,ax                   ;;; load DS with real selector

  mov     eax,cr0                 ;;; move cr0 to eax
  and     ax,NOT PE               ;;; clear protection mode enable bit
  mov     cr0,eax                 ;;; back in real mode
  jmp     $+2                     ;;; flush prefetch queue

  pop     eax
  popf
	
	RESTORE_REGISTERS
	HEAD_END
	ret

_into_RL_mode   endp


;=================================================================
;       into big mode inside
;=================================================================

_load_PT_inside    proc    near
        
  pushf
  cli
        
  ;Data GDT
  ;
  mov     ax,cs
  mov     ds,ax
        
  xor     eax,eax
  mov     edx,eax
  lea     dx,Offset GDTable
  mov     ax,cs
  shl     eax,4
  add     eax,edx
  mov     bx,Offset ZGDT
  mov     DWord Ptr ds:[bx+2],eax

  call    Enable_A20

  push    eax

  lgdt    fword ptr cs:zgdt       ;;; load GDT register

  mov     eax,cr0                 ;;; move cr0 to eax
  or      ax,PE                   ;;; set protection mode enable bit

  mov     cr0,eax                 ;;; now in protected mode
  jmp     $+2                     ;;; flush prefetch queue

  mov     ax,BIG_SEL              ;;; BIG selector
  mov     es,ax                   ;;; load ES with BIG selector
  mov     ds,ax                   ;;; load DS with BIG selector

  mov     eax,cr0                 ;;; move cr0 to eax
  and     ax,NOT PE               ;;; clear protection mode enable bit
  mov     cr0,eax                 ;;; back in real mode
  jmp     $+2                     ;;; flush prefetch queue

  pop     eax

  xor     ax,ax
  mov     ds,ax
  mov     es,ax

  popf
  ret

_load_PT_inside    endp

;=================================================================
;       Return to real mode inside
;=================================================================

_load_RL_inside   proc    near

  pushf
  cli
  push    eax

  lgdt    fword ptr cs:zgdt       ;;; load GDT register

  mov     eax,cr0                 ;;; move cr0 to eax
  or      ax,PE                   ;;; set protection mode enable bit

  mov     cr0,eax                 ;;; now in protected mode
  jmp     $+2                     ;;; flush prefetch queue

  mov     ax,REAL_SEL             ;;; real selector
  mov     es,ax                   ;;; load ES with real selector
  mov     ds,ax                   ;;; load DS with real selector

  mov     eax,cr0                 ;;; move cr0 to eax
  and     ax,NOT PE               ;;; clear protection mode enable bit
  mov     cr0,eax                 ;;; back in real mode
  jmp     $+2                     ;;; flush prefetch queue

  pop     eax
  popf
 
  ret

_load_RL_inside   endp

Enable_A20      proc    near
  push    ax

  cli                             ;;; Disable interrupts

@@:     in      al, 64h                 ;;; Check ibf
  and     al, 02h                 ;;; Ibf set?
  jnz     @b                      ;;; Yep.  Wait

  mov     al,0d1h                 ;;;  Y: Write to kbd output port
  out     64h,al                  ;;;

@@:     in      al, 64h                 ;;; Check ibf
  and     al, 02h                 ;;; Ibf set?
  jnz     @b                      ;;; Yep.  Wait

  jmp     $+2                     ;;; Insure timing
  jmp     $+2                     ;;;               requirements meet

  mov     al,0dfh                 ;;;  Y:
  out     60h,al                  ;;; Enable A20

@@:     in      al, 64h                 ;;; Check ibf
  and     al, 02h                 ;;; Ibf set?
  jnz     @b                      ;;; Yep.  Wait

  mov     al,0FFh                 ;;;  Nop to see it get eaten
  out     64h,al          ;;;

@@:     in      al, 64h                 ;;; Check ibf
  and     al, 02h                 ;;; Ibf set?
  jnz     @b                      ;;; Yep.  Wait

  xor     al,al                   ;;; Set status to OK

  pop     ax
  ret
Enable_A20      endp

;=================================================================
;       read 32 bits data from memory
;=================================================================
_read_mem_dword	proc	near
  HEAD_BG
	cli

	mov ax,0
	mov ds,ax
	mov es,ax

	mov eax, dword ptr [bp+4]     ; Load address
	mov edi,eax

	mov eax,dword ptr ds:[edi]    ; read it
        
	mov     dword ptr [bp-4], eax   ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     ax, word ptr [bp-4]     ; Save low word into ax
  mov     dx, word ptr [bp-2]     ; Save high word into dx
  sti
  HEAD_END

_read_mem_dword    endp

;=================================================================
;       read 16 bits data from memory
;=================================================================
_read_mem_word	proc	near
  HEAD_BG
	cli

	mov ax,0
	mov ds,ax
	mov es,ax

	mov eax, dword ptr [bp+4]     ; Load address
	mov edi,eax

	mov ax,word ptr ds:[edi]    ; read it
        
	mov     word ptr [bp-4], ax   ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     ax, word ptr [bp-4]     ; Save low word into ax
  sti
  HEAD_END

_read_mem_word    endp

;=================================================================
;       read 8 bits data from memory
;=================================================================
_read_mem_byte	proc	near
  HEAD_BG
	cli

	mov ax,0
	mov ds,ax
	mov es,ax

	mov eax, dword ptr [bp+4]     ; Load address
	mov edi,eax

	mov al,byte ptr ds:[edi]    ; read it
        
	mov     byte ptr [bp-4], al   ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     al, byte ptr [bp-4]     ; Save low word into ax
  sti
  HEAD_END

_read_mem_byte    endp


;=================================================================
;       write 8 bit data to memory
;=================================================================

_write_mem_byte	proc	near

	HEAD_BG
	cli

	mov ax,0
	mov ds,ax
	mov es,ax

	mov eax, dword ptr [bp+4]     ; Load address
	mov edi,eax

	mov al, byte ptr [bp+8]     ; Load data
	mov byte ptr ds:[edi],al    ;write to
        
  sti
	RESTORE_REGISTERS
	HEAD_END
_write_mem_byte endp

;==================================================================================

_Read_io_dword   proc    near
  HEAD_BG
	cli                 ;

  mov     dx, word ptr [bp+4]     ; Load port address
  in      eax, dx                 ; Read the port data

  mov     dword ptr [bp-4], eax   ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     ax, word ptr [bp-4]     ; Save low word into ax
  mov     dx, word ptr [bp-2]     ; Save high word into dx
  HEAD_END

_Read_io_dword    endp


;==================================================================================
;Routine name : write_io_dword
;Purpose      : write a double word from an I/O port
;==================================================================================
_Write_io_dword   proc    near
  HEAD_BG
	cli

  mov     dx, word ptr [bp+4]     ; Load port address
  mov     eax, dword ptr [bp+6]   ; Load data value
  out     dx, eax                 ; Write the port data
  RESTORE_REGISTERS               ; Restore all registers
  HEAD_END

_Write_io_dword   endp


;==================================================================================
;Routine name : Read_io_word
;Purpose      : Read a word from an I/O port
;==================================================================================
_Read_io_word   proc    near
  HEAD_BG
	cli
  mov     dx, word ptr [bp+4]     ; Load port address
  in      ax, dx                  ; Read the port data
  mov     word ptr [bp-2],ax      ; Save word into ax
  RESTORE_REGISTERS               ; Restore all registers
  mov     ax, word ptr [bp-2]     ; Save word into ax
  HEAD_END
_Read_io_word    endp


;==================================================================================
;Routine name : write_io_word
;Purpose      : write a word from an I/O port
;==================================================================================
_Write_io_word   proc    near
  HEAD_BG
	cli
  mov     dx, word ptr [bp+4]     ; Load port address
  mov     ax, word ptr [bp+6]     ; Load data value
  out     dx, ax                  ; Write the port data
  RESTORE_REGISTERS               ; Restore all registers
  HEAD_END

_Write_io_word   endp


;==================================================================================
;Routine name : Read_io_byte
;Purpose      : Read a byte from an I/O port
;==================================================================================
_Read_io_byte   proc    near
  HEAD_BG
	cli
  mov     dx, word ptr [bp+4]     ; Load port address
  in      al, dx                  ; Read the port data
  mov     byte ptr [bp-2], al     ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     al, byte ptr [bp-2]     ; Save byte into al
  HEAD_END
_Read_io_byte    endp


;==================================================================================
;Routine name : write_io_byte
;Purpose      : write a byte from an I/O port
;==================================================================================
_Write_io_byte   proc    near
  HEAD_BG
	cli
  mov     dx, word ptr [bp+4]     ; Load port address
  mov     al, byte ptr [bp+6]     ; Load data value
  out     dx, al                  ; Write the port data
  RESTORE_REGISTERS               ; Restore all registers
  HEAD_END

_Write_io_byte   endp

;==================================================================================
;Routine name : write_pci_byte
;Purpose      : write a byte to pci register
;==================================================================================
_Write_pci_byte   proc    near
  HEAD_BG
	cli

  mov     al, byte ptr [bp+4]     ; Load bus number (0-255)
  mov     bh,al                   ;
  mov     al, byte ptr [bp+6]     ; Load device number (0-31)
  shl     al,3                    ;
  mov     bl,al                   ;
  mov     al, byte ptr [bp+8]    ; Load function number (0-7)
  or      bl,al                   ;
  mov     dh, PCI_CFG_WRITE_BYTE  ;   special cycle "port"
  mov     dl, byte ptr [bp+10]    ; Load register number
  mov     al, byte ptr [bp+12]    ; Load data to be write
  call    pciCfgCycle             ;
  mov     byte ptr [bp-2], al     ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     al, byte ptr [bp-2]     ; Save byte into al
  HEAD_END
_Write_pci_byte   endp

;==================================================================================
;Routine name : write_pci_word
;Purpose      : write a word to pci register
;==================================================================================
_Write_pci_word   proc    near
  HEAD_BG
	cli

  mov     al, byte ptr [bp+4]     ; Load bus number (0-255)
  mov     bh,al                   ;
  mov     al, byte ptr [bp+6]     ; Load device number (0-31)
  shl     al,3                    ;
  mov     bl,al                   ;
  mov     al, byte ptr [bp+8]    ; Load function number (0-7)
  or      bl,al                   ;
  mov     dh, PCI_CFG_WRITE_WORD  ;   special cycle "port"
  mov     dl, byte ptr [bp+10]    ; Load register number
  mov     ax, word ptr [bp+12]    ; Load data to be write
  call    pciCfgCycle             ;
  mov     word ptr [bp-2], ax     ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     ax, word ptr [bp-2]     ; Save byte into al
  HEAD_END
_Write_pci_word   endp

;==================================================================================
;Routine name : write_pci_dword
;Purpose      : write a dword to pci register
;==================================================================================
_Write_pci_dword   proc    near
  HEAD_BG
	cli

  mov     al, byte ptr [bp+4]     ; Load bus number (0-255)
  mov     bh,al                   ;
  mov     al, byte ptr [bp+5]     ; Load device number (0-31)
  shl     al,3                    ;
  mov     bl,al                   ;
  mov     al, byte ptr [bp+8]    ; Load function number (0-7)
  or      bl,al                   ;
  mov     dh, PCI_CFG_WRITE_DWORD ;   special cycle "port"
  mov     dl, byte ptr [bp+10]    ; Load register number
  mov     eax, dword ptr [bp+12]  ; Load data to be write
  call    pciCfgCycle             ;
  mov     dword ptr [bp-4], eax   ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     ax, word ptr [bp-4]     ; Save low word into ax
  mov     dx, word ptr [bp-2]     ; Save high word into dx
  HEAD_END
_Write_pci_dword   endp

;==================================================================================
;Routine name : read_pci_byte
;Purpose      : read a byte from pci register
;==================================================================================
_Read_pci_byte   proc    near
  HEAD_BG
  cli

  mov     al, byte ptr [bp+4]     ; Load bus number (0-255)
  mov     bh,al                   ;
  mov     al, byte ptr [bp+6]     ; Load device number (0-31)
  shl     al,3                    ;
  mov     bl,al                   ;
  mov     al, byte ptr [bp+8]    ; Load function number (0-7)
  or      bl,al                   ;
  mov     dh, PCI_CFG_READ_BYTE   ;   special cycle "port"
  mov     dl, byte ptr [bp+10]    ; Load register number
  call    pciCfgCycle             ;
  mov     byte ptr [bp-2], al     ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     al, byte ptr [bp-2]     ; Save byte into al
  HEAD_END
_Read_pci_byte   endp

;==================================================================================
;Routine name : read_pci_word
;Purpose      : read a word from pci register
;==================================================================================
_Read_pci_word   proc    near
  HEAD_BG
	cli

  mov     al, byte ptr [bp+4]     ; Load bus number (0-255)
  mov     bh,al                   ;
  mov     al, byte ptr [bp+6]     ; Load device number (0-31)
  shl     al,3                    ;
  mov     bl,al                   ;
  mov     al, byte ptr [bp+8]    ; Load function number (0-7)
  or      bl,al                   ;
  mov     dh, PCI_CFG_READ_WORD   ;   special cycle "port"
  mov     dl, byte ptr [bp+10]    ; Load register number
  call    pciCfgCycle             ;
  mov     word ptr [bp-2], ax     ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     ax, word ptr [bp-2]     ; Save byte into al
  HEAD_END
_Read_pci_word   endp


;==================================================================================
;
;==================================================================================

_Read_pci_dword   proc    near
  HEAD_BG
	cli

  mov     al, byte ptr [bp+4]     ; Load bus number (0-255)
  mov     bh,al                   ;
  mov     al, byte ptr [bp+6]     ; Load device number (0-31)
  shl     al,3                    ;
  mov     bl,al                   ;
  mov     al, byte ptr [bp+8]    ; Load function number (0-7)
  or      bl,al                   ;
  mov     dh, PCI_CFG_READ_DWORD  ;   special cycle "port"
  mov     dl, byte ptr [bp+10]    ; Load register number
  call    pciCfgCycle             ;
  mov     dword ptr [bp-4], eax   ; Save the results
  RESTORE_REGISTERS               ; Restore all registers
  mov     ax, word ptr [bp-4]     ; Save low word into ax
  mov     dx, word ptr [bp-2]     ; Save high word into dx
  HEAD_END

_Read_pci_dword    endp

;==================================================================================
;
;==================================================================================

pciCfgCycle proc near
  ; Validate configuration cycle type in DH
  xchg    eax, ebx                   ; Get PCI_FCN_ADDR into AX for setup
                                     ; Save possible write value in EBX
  ; Construct CFG_ADDR in EAX

  ror     eax, 8                     ; Move PFA into EAX[7:0,31:24]
  mov     ah, 80h                    ; Set up CFG_DATA enable flag
  rol     eax, 16                    ; Slide everything into EAX[31:8]
  mov     al, dl                     ; Add register number to EAX[7:0]
  and     al, 0FCh                   ; Make it a dword register

  ; Save stuff in ECX and EDX[31:16]

  shld    ecx, edx, 10h              ; Save CX in ECX[31:16], EDX[31:16] in CX,
  shl     edx, 10h                   ;   and DX in EDX[31:16]

  cli                                ;? Lights out
  
  mov     dx, CFG_ADDR_PORT          ; Put CFG_ADDR out on the wire
  out     dx, eax                    ; must be a DWORD operation

  shl     eax, 8                     ; Save PCI_FCN_ADDR in EAX[31:16]

  ; Construct CFG_DATA port for requested register number

  shr     edx, 10h                   ; Clone access type( CFG cycle type ) to AH and
  mov     ax, dx                     ;   register number to AL
  shl     edx, 10h

  mov     dx, CFG_DATA_PORT          ; Set up CFG_DATA port base
  and     al, 3                      ; Strip off register number[1:0]
  add     dl, al                     ;   and add to CFG_DATA port base
                                     ;   for dword/word/byte alignment access

  shr     ax, 8                      ; Move access type to AL (from AH)
  xchg    eax, ebx                   ; Retrieve possible value to write

  cmp     bl, PCI_CFG_READ_BYTE
  je      SHORT PCI_CFG_READ_8

  cmp     bl, PCI_CFG_READ_WORD
  je      SHORT PCI_CFG_READ_16

  cmp     bl, PCI_CFG_READ_DWORD
  je      SHORT PCI_CFG_READ_32

  cmp     bl, PCI_CFG_WRITE_BYTE
  je      SHORT PCI_CFG_WRITE_8

  cmp     bl, PCI_CFG_WRITE_WORD
  je      SHORT PCI_CFG_WRITE_16

  jmp     SHORT PCI_CFG_WRITE_32


PCI_CFG_READ_8:
  in      al, dx
  jmp     SHORT PCI_CFG_OUT

PCI_CFG_READ_16:
  in      ax, dx
  jmp     SHORT PCI_CFG_OUT

PCI_CFG_READ_32:
  in      eax, dx
  jmp     SHORT PCI_CFG_OUT

PCI_CFG_WRITE_8:
  out     dx, al
  jmp     SHORT PCI_CFG_OUT

PCI_CFG_WRITE_16:
  out     dx, ax
  jmp     SHORT PCI_CFG_OUT

PCI_CFG_WRITE_32:
  out     dx, eax

PCI_CFG_OUT:
  shr     ebx, 10h                     ; Restore PCI_FCN_ADDR to BX
  shrd    edx, ecx, 10h                ; Restore original EDX[31:16],
                                             ;   and DX
  shr     ecx, 10h                     ; Restore original CX

  ret
pciCfgCycle endp

;==================================================================================

_TEXT      ends
end
