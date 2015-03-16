	title  E820_ASM.asm
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
public  _Int_E820



_TEXT	segment public use16 'code'
	assume  cs: _TEXT

_Int_E820	proc    NEAR

	HEAD_BG
	
	mov	ebx, dword ptr [bp+4]	; EBX data
	mov	ax, word ptr [bp+8]	; seg
	mov	es, ax			;
	mov	ax, word ptr [bp+10]	; offset
	mov	di, ax			;
	mov	ecx, dword ptr [bp+12]	; buf size
	mov	edx,534d4150h		; 'SMAP'
	mov	eax,0e820h
	int	15h
	jnc	Int_ck
	mov	ebx,0ffffffffh
	jmp	Int_ok
Int_ck:
	push	ebx
	mov	ebx,534d4150h
	cmp	eax,ebx
	pop	ebx
	je	Int_ok
	mov	ebx,0ffffffffh
Int_ok:
	mov	eax,ebx
	mov     dword ptr [bp-4], eax   ; Save the results
	RESTORE_REGISTERS               ; Restore all registers
	mov     ax, word ptr [bp-4]     ; Save low word into ax
	mov     dx, word ptr [bp-2]     ; Save high word into dx;
	HEAD_END

_Int_E820             endp



_TEXT      ends
end
