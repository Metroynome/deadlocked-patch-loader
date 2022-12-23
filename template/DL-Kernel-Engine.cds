/*
NetCheat Engine
Written by Dnawrkshp
Heavily Modified by Agent Moose
*/
address $00047010

_init:
addiu sp, sp, $FFE0
sq ra, $0000(sp)
sq v0, $0010(sp)

setreg at, :_init
lw a1, $fff0(at) // KernelCodesAddr (src)
lw a0, $fff8(at) // NonKernelCodesAddr (dest)
lw a2, $fffc(at) // size_codes (size)

jal :_memcpy
nop

/*
lui t8, $001f
lw at, $eb70(t8)
beq at, zero, :_end
nop
*/

setreg t3, $001274ac
setreg t4, $0803c000
beq t3, t4 :_end
nop
sw t4, $0000(t3)

_end:
lq v0, $0010(sp)
jr k0
addiu sp, sp, $0020


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
