#define GAME_MAP_ID                         (0x0021DE10)

// fixed address function
#define FUNCTION(name, address) \
	.set	push;		        \
	.set	noreorder;	        \
	.section	.text.##name,"ax",@progbits; \
	.align 2;		            \
	.globl	name;		        \
	.type	name,@function;	    \
	.ent	name,0;		        \
name:	j address;              \
	nop;			            \
	.end	name;		        \
	.size	name,.-name;	    \
	.set	pop;

// variable address function
#define VARIABLE_FUNCTION(name, variable_address_struct) \
	.set	push;		        				\
	.set	noreorder;	        		\
	.section	.text.##name,"ax",@progbits; \
	.align 2;		            			\
	.globl	name;		        			\
	.type	name,@function;	    		\
	.ent	name,0;		        			\
	.extern variable_address_struct; \
name:														\
		addiu $sp, $sp, -0x40;			\
		sq $ra, 0x00($sp);					\
		sq $a0, 0x10($sp);					\
		sq $a1, 0x20($sp);					\
		sq $s0, 0x30($sp);					\
		la $a0, variable_address_struct; \
		la $a1, ##name##_return;				\
		j __LocalGetAddress;        \
		nop;			            			\
##name##_return:										\
		beq $zero, $v0, ##name##_exit;	\
		nop;												\
		lq $a1, 0x20($sp);					\
		jalr $v1;										\
		lq $a0, 0x10($sp);					\
##name##_exit:											\
		lq $ra, 0x00($sp);					\
		lq $s0, 0x30($sp);					\
		jr $ra;											\
		addiu $sp, $sp, 0x40;				\
	.end	name;		        				\
	.size	name,.-name;	   			 	\
	.set	pop;

//
__LocalGetAddress_offsets:
	// Starting Address: 000F0408 + Offset = Function Pointer
	// MISSING_00 = -1
	// BATTLEDOME = +0
    // CATACROM = +4
	// MISSING_03 = -1
    // SARATHOS = +8
    // KRONOS = +12
    // SHAAR = +16
    // VALIX = +20
	// MISSING_09 = -1
    // ORXON = +24
    // TORVAL = +28
    // STYGIA = +32
	// MISSING_12 = -1
    // MARAXUS = +36,
    // GHOST_STATION = +40,
    // DREADZONE_INTERIOR = +44
	.byte -1,0,4,-1,8,12,16,20,24,-1,28,32,-1,36,40,44;

// 
	.set	push;
	.set	noreorder;
	.section	.text.##__LocalGetAddress,"ax",@progbits;
	.align 2;
	.globl	__LocalGetAddress;
	.type	__LocalGetAddress,@function;
	.ent	__LocalGetAddress,0;
__LocalGetAddress:
	// return address by map
	lw $v0, GAME_MAP_ID;

	// load offset into VariableAddress struct by map id
	la $v1, __LocalGetAddress_offsets;
	addu $v1, $v0;
	lb $v1, 0($v1);

	// load address from struct
	addu $a0, $v1;
	lw $v1, 0($a0);

	// return to calling function
__LocalGetAddress_exit:
	jr $a1;
	nop;
	.end	__LocalGetAddress;
	.size	__LocalGetAddress,.-__LocalGetAddress;
	.set	pop;

// 
	.set	push;
	.set	noreorder;
	.section	.text.##GetAddress,"ax",@progbits;
	.align 2;
	.globl	GetAddress;
	.type	GetAddress,@function;
	.ent	GetAddress,0;
GetAddress:
	// return address by map
	lw $v0, GAME_MAP_ID;

	// load offset into VariableAddress struct by map id
	la $v1, __LocalGetAddress_offsets;
	addu $v1, $v0;
	lb $v1, 0($v1);

	// load address from struct
	addu $a0, $v1;
	lw $v1, 0($a0);

	// return to calling function
GetAddress_exit:
	jr $ra;
	nop;
	.end	GetAddress;
	.size	GetAddress,.-GetAddress;
	.set	pop;

VARIABLE_FUNCTION(internal_drawFunc, vaDrawTextFunc)
VARIABLE_FUNCTION(gfxGetFontWidth, vaGetTextWidthFunc)