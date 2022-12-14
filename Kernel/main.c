#include <tamtypes.h>
#include <kernel.h>
#include <libdl/dl.h>
#include <libdl/player.h>
#include <libdl/pad.h>
#include <libdl/game.h>
#include <libdl/string.h>
#include <libdl/stdio.h>
#include <libdl/gamesettings.h>
#include <libdl/graphics.h>
#include <libdl/ui.h>
#include <libdl/math.h>
#include <libdl/math3d.h>
#include <libdl/hud.h>
#include <libdl/music.h>
#include <libdl/weapon.h>
#include <libdl/team.h>

#define EngineAddr 0x80047010

u32 HookAddr = 0x800001A0;
u32 HookValue = (((int)EngineAddr << 4) >> 6) + 0x08000000;
u32 CodesAddr = 0x80050000;

u32 Engine[] = { 
	0x27BDFFE0,
	0x7FBF0000,
	0x7FA20010,
	0x0C011C0C,
	0x00000000,
	0x7BA20010,
	0x03400008,
	0x27BD0020,
	0x27BDFE00,
	0x7FA10000,
	0x7FA20010,
	0x7FA30020,
	0x7FA40030,
	0x7FA50040,
	0x7FA60050,
	0x7FA70060,
	0x7FA80070,
	0x7FA90080,
	0x7FAA0090,
	0x7FAB00A0,
	0x7FAC00B0,
	0x7FAD00C0,
	0x7FAE00D0,
	0x7FAF00E0,
	0x7FB000F0,
	0x7FB10100,
	0x7FB20110,
	0x7FB30120,
	0x7FB40130,
	0x7FB50140,
	0x7FB60150,
	0x7FB70160,
	0x7FB80170,
	0x7FB90180,
	0x7FBA0190,
	0x7FBB01A0,
	0x7FBE01B0,
	0x7FBC01C0,
	0x7FBF01D0,
	0x3C010015,
	0x374179A0,
	0x0020F809,
	0x00000000,
	0x7BA10000,
	0x7BA20010,
	0x7BA30020,
	0x7BA40030,
	0x7BA50040,
	0x7BA60050,
	0x7BA70060,
	0x7BA80070,
	0x7BA90080,
	0x7BAA0090,
	0x7BAB00A0,
	0x7BAC00B0,
	0x7BAD00C0,
	0x7BAE00D0,
	0x7BAF00E0,
	0x7BB000F0,
	0x7BB10100,
	0x7BB20110,
	0x7BB30120,
	0x7BB40130,
	0x7BB50140,
	0x7BB60150,
	0x7BB70160,
	0x7BB80170,
	0x7BB90180,
	0x7BBA0190,
	0x7BBB01A0,
	0x7BBE01B0,
	0x7BBC01C0,
	0x7BBF01D0,
	0x03E00008,
	0x27BD0200,

};

void HookKernel()
{

	DI();
	ee_kmode_enter();
		memcpy((u32*)(int)EngineAddr, Engine, sizeof(Engine));
		// memset((u32*)CodesAddr, 0, 0x0000EFFC);	
		memcpy((u32*)CodesAddr, (u32*)0x01E00000, 0x0000EFFC);
		memcpy((u32*)0x000F0000, (u32*)CodesAddr, 0x0000EFFC);
		// memcpy((u32*)(CodesAddr + 8), (u32*)0x000F0000, code_len);
		*(u32*)((int)EngineAddr - 0x10) = CodesAddr;
		*(u32*)HookAddr = HookValue;
	ee_kmode_exit();
	EI();

	*(u32*)0x00138DD0 = 0x0c000000 | ((u32)(0x000F0000) >> 2);
}

int main(void)
{
	// if Music is not Loaded, stop.
	if (*(u32*)0x001CF85C != 0x000F8D29)
		return -1;

	// Patch.bin hook: 0x00138DD0
	// run original jal that patch.bin hook took over
	// Still needs to be changed.  Disable vSync disables mod-menu.
	((void (*)(void))0x001270C0)();

	HookKernel();

	return 0;
}
