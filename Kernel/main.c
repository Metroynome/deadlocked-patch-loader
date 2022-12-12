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

u32 Engine[11] = { 
	0x27BDFFE0,
	0x7FBF0000,
	0x7FA20010,
	// 0x0C014000, // jal to jump to codes
	0x00000000,
	0x3C028000,
	0x34420234,
	0x7BBF0000,
	0x13E20003,
	0x7BA20010,
	0x03400008,
	0x27BD0020,

};

void HookKernel()
{

	DI();
	ee_kmode_enter();
		memcpy((u32*)(int)EngineAddr, Engine, sizeof(Engine));
		// memset((u32*)CodesAddr, 0x10, 0x0000EFFC);	
		memcpy((u32*)(CodesAddr + 8), (u32*)0x01E00000, 20);
		// memcpy((u32*)0x000F0000, (u32*)CodesAddr, 61440);
		// memcpy((u32*)(CodesAddr + 8), (u32*)0x000F0000, code_len);
		*(u32*)((int)EngineAddr - 0x18) = (CodesAddr + 0x10); 
		*(u32*)((int)EngineAddr - 0x10) = (CodesAddr + 0x10);
		*(u32*)HookAddr = HookValue;
	ee_kmode_exit();
	EI();
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
