/*
Deadlocked-Chaos Mod Engine
Created by Agent Moose
*/
address $00047010

_init:
addiu sp, sp, $FE00
sq at, $0000(sp)
sq v0, $0010(sp)
sq v1, $0020(sp)
sq a0, $0030(sp)
sq a1, $0040(sp)
sq a2, $0050(sp)
sq a3, $0060(sp)
sq t0, $0070(sp)
sq t1, $0080(sp)
sq t2, $0090(sp)
sq t3, $00a0(sp)
sq t4, $00b0(sp)
sq t5, $00c0(sp)
sq t6, $00d0(sp)
sq t7, $00e0(sp)
sq s0, $00f0(sp)
sq s1, $0100(sp)
sq s2, $0110(sp)
sq s3, $0120(sp)
sq s4, $0130(sp)
sq s5, $0140(sp)
sq s6, $0150(sp)
sq s7, $0160(sp)
sq t8, $0170(sp)
sq t9, $0180(sp)
sq k0, $0190(sp)
sq k1, $01a0(sp)
sq fp, $01b0(sp)
sq gp, $01c0(sp)
sq ra, $01d0(sp)

setreg at, $80047010

lw t8, $fffc(at) // Load EnableDisable Variable.
lw t9, $fff8(at) // Load Destination Pointer
sw t8, $fffc(t9) // Save EnableDisable Variable to Destination
lw t9, $0000(t9) // Load Destination Data
// Check to see if data is zero, if not, continue
beq t9, zero, :_doMemCpy
nop

jal :_do_hook
nop
beq zero, zero, :_end

_doMemCpy:
//Exception Handler
lw a0, $ffec(at) // eeAddr_ExceptionHandler (dest)
lw a1, $ffe4(at) // kAddr_ExceptionHandler (src)
jal :_memcpy
lw a2, $ffe8(at) // size_ExceptionHandler (size)

// Codes
lw a0, $fff8(at) // eeAddr_Codes (dest)
lw a1, $fff0(at) // kAddr_Codes (src)
jal :_memcpy
lw a2, $fff4(at) // size_codes (size)

_end:
lq at, $0000(sp)
lq v0, $0010(sp)
lq v1, $0020(sp)
lq a0, $0030(sp)
lq a1, $0040(sp)
lq a2, $0050(sp)
lq a3, $0060(sp)
lq t0, $0070(sp)
lq t1, $0080(sp)
lq t2, $0090(sp)
lq t3, $00a0(sp)
lq t4, $00b0(sp)
lq t5, $00c0(sp)
lq t6, $00d0(sp)
lq t7, $00e0(sp)
lq s0, $00f0(sp)
lq s1, $0100(sp)
lq s2, $0110(sp)
lq s3, $0120(sp)
lq s4, $0130(sp)
lq s5, $0140(sp)
lq s6, $0150(sp)
lq s7, $0160(sp)
lq t8, $0170(sp)
lq t9, $0180(sp)
lq k0, $0190(sp)
lq k1, $01a0(sp)
lq fp, $01b0(sp)
lq gp, $01c0(sp)
lq ra, $01d0(sp)
jr k0
addiu sp, sp, $0200

_do_hook:
setreg t3, $00138DFC // Hook
setreg t4, $0803c000 // New Value
lw t5, $0000(t3)
// if hook equals zero, jump to exit.
beq t5, zero, :_exit_do_hook
nop
// if hook already equals needed value, jump to exit.
beq t5, t4, :_exit_do_hook
nop
// if not, save new value into hook.
sw t4, $0000(t3)
_exit_do_hook:
jr ra
nop

// Taken from Deadlocked Assembly
_memcpy:
daddu t0, a0, zero
sltiu v0, a2, $0020
bne v0, zero, $1c
daddu v1, t0, zero
or v0, a1, t0
andi v0, v0, $000f
bnel v0, zero, $19
addiu a2, a2, $ffff
daddu a3, t0, zero
lq v1, $0000(a1)
addiu a2, a2, $ffe0
addiu a1, a1, $0010
sltiu a0, a2, $0020
sq v1, $0000(a3)
addiu a3, a3, $0010
lq v0, $0000(a1)
addiu a1, a1, $0010
sq v0, $0000(a3)
beq a0, zero, $fff6
addiu a3, a3, $0010
sltiu v0, a2, $0008
bne v0, zero, $9
daddu v1, a3, zero
ld v1, $0000(a1)
addiu a2, a2, $fff8
addiu a1, a1, $0008
sltiu v0, a2, $0008
sd v1, $0000(a3)
beq v0, zero, $fffa
addiu a3, a3, $0008
daddu v1, a3, zero
addiu a2, a2, $ffff
addiu v0, zero, $ffff
beq a2, v0, $7
daddu a0, v0, zero
lbu v0, $0000(a1)
addiu a2, a2, $ffff
addiu a1, a1, $0001
sb v0, $0000(v1)
bne a2, a0, $fffb
addiu v1, v1, $0001
jr ra
daddu v0, t0, zero

