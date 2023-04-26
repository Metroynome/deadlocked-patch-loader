#include <tamtypes.h>
#include <kernel.h>
#include <libdlsp/string.h>
#include <libdlsp/stdio.h>
#include <libdlsp/graphics.h>
#include <libdlsp/ui.h>
#include <libdlsp/dl.h>

/*
uiShowPopup Possibilities
203EB918
203F0294
203FA810
204531E8
20457538
2048B708
2048B728
2048D1D8
2048D200
2048D220
*/

#define EngineAddr 0x80047010

extern void codes;
extern u32 size_codes;

extern void exceptiondisplay;
extern u32 size_exceptiondisplay;

u32 HookAddr = 0x800001A0;
u32 HookValue = (((int)EngineAddr << 4) >> 6) + 0x08000000;

// Set /Codes/ Directory address'
u32 kAddr_Codes = 0x80050000;
u32 eeAddr_Codes = 0x000F0000;

// Set Exception Handler address'
u32 kAddr_ExceptionDisplay = 0x80079000;
u32 eeAddr_ExceptionDisplay = 0x000c8000;

int EnabledChaosMod = 0;
int IsCirclePressed = 0;

u32 Engine[] = {
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
	0x3C018004,
	0x34217010,
	0x8C38FFFC,
	0x8C39FFF8,
	0xAF38FFFC,
	0x8F390000,
	0x13200006,
	0x00000000,
	0x13000038,
	0x00000000,
	0x0C011C58,
	0x00000000,
	0x10000008,
	0x8C24FFEC,
	0x8C25FFE4,
	0x0C011C75,
	0x8C26FFE8,
	0x8C24FFF8,
	0x8C25FFF0,
	0x0C011C75,
	0x8C26FFF4,
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
	0x03400008,
	0x27BD0200,
	0x3C0B0013,
	0x356B8DFC,
	0x3C0C0803,
	0x358CC000,
	0x8D6D0000,
	0x11A00004,
	0x00000000,
	0x11AC0002,
	0x00000000,
	0xAD6C0000,
	0x03E00008,
	0x00000000,
	0x3C0B0013,
	0x356B8DFC,
	0x3C0C03E0,
	0x358C0008,
	0x8D6D0000,
	0x11A0FFF8,
	0x00000000,
	0x11AC0007,
	0x00000000,
	0xAD6C0000,
	0x3C0B8000,
	0x356B01A0,
	0x3C0C0340,
	0x358C0008,
	0xAD6C0000,
	0x08011C38,
	0x00000000,
	0x0080402D,
	0x2CC20020,
	0x1440001c,
	0x0100182D,
	0x00A81025,
	0x3042000F,
	0x54400019,
	0x24C6FFFF,
	0x0100382D,
	0x78A30000,
	0x24C6FFE0,
	0x24A50010,
	0x2CC40020,
	0x7CE30000,
	0x24E70010,
	0x78A20000,
	0x24A50010,
	0x7CE20000,
	0x1080fff6,
	0x24E70010,
	0x2CC20008,
	0x14400009,
	0x00E0182D,
	0xDCA30000,
	0x24C6FFF8,
	0x24A50008,
	0x2CC20008,
	0xFCE30000,
	0x1040fffa,
	0x24E70008,
	0x00E0182D,
	0x24C6FFFF,
	0x2402FFFF,
	0x10C20007,
	0x0040202D,
	0x90A20000,
	0x24C6FFFF,
	0x24A50001,
	0xA0620000,
	0x14C4fffb,
	0x24630001,
	0x03E00008,
	0x0100102D,

};

void HookKernel(int EnableDisable)
{
	DI();
	ee_kmode_enter();
		// copy Engline into EngineAddr
		memcpy((u32*)(int)EngineAddr, Engine, sizeof(Engine));

		// Handle Codes.bin
		// memset size of codes -0x1000 because the first 0x1000 bytes of codes is not needed.
		memset((u32*)kAddr_Codes, 0, (size_codes - 0x1000));
		// Copy codes starting at offset +0x1000 to the end into kAddr_Codes
		memcpy((u8*)kAddr_Codes, (u8*)(&codes + 0x1000), (size_codes - 0x1000));
		// Set kAddr_Codes Pointer for Engine.
		*(u32*)((int)EngineAddr - 0x10) = kAddr_Codes;
		// set size_codes information for Engine.
		*(u32*)((int)EngineAddr - 0xc) = (size_codes - 0x1000);
		// Set eeAddr_Codes Pointer for Engine.
		*(u32*)((int)EngineAddr - 0x8) = eeAddr_Codes;
		// EnableDisable variable used in Engine.
		*(u32*)((int)EngineAddr - 0x4) = EnableDisable;

		// Handle Exception Display
		// Copy Exception Display to kernel
		memcpy((u8*)kAddr_ExceptionDisplay, (u8*)(&exceptiondisplay), size_exceptiondisplay);
		// Set Kernel Exception Handler Pointer for Engine.
		*(u32*)((int)EngineAddr - 0x1c) = kAddr_ExceptionDisplay;
		// Set size_exceptiondisplay information for Engine.
		*(u32*)((int)EngineAddr - 0x18) = size_exceptiondisplay;
		// Set EE Exception Handler Pointer for Engine
		*(u32*)((int)EngineAddr - 0x14) = eeAddr_ExceptionDisplay;

		*(u32*)HookAddr = HookValue;
	ee_kmode_exit();
	EI();
}

void OnMultiplayerMenu(void)
{
	// If Mod is Enabled
	if (EnabledChaosMod == 1)
	{
		// Disable "Online Play" Option
		*(u32*)0x0136237C = 3;
		// Disable "Local Play" Option
		*(u32*)0x013623DC = 3;
		gfxScreenSpaceText(SCREEN_WIDTH * 0.3, SCREEN_HEIGHT * 0.855, 1, 1, 0x80FFFFFF, "Press \x11 to Disable Mod", -1, 4);
	}
	// if Mod is Disabled
	else if (EnabledChaosMod == 0)
	{
		// Enable "Online Play" Option
		*(u32*)0x0136237C = 4;
		// Enable "Local Play" Option
		*(u32*)0x013623DC = 4;
		gfxScreenSpaceText(SCREEN_WIDTH * 0.3, SCREEN_HEIGHT * 0.855, 1, 1, 0x80FFFFFF, "Press \x11 to Enable Mod", -1, 4);
	}

	// if circle is pressed
	// Enable
	if ((*(u16*)0x001EE682 == 0xdfff) && (EnabledChaosMod == 0) && (IsCirclePressed == 0))
	{
		// Disable Mod Check
		EnabledChaosMod = 1;
		// Switch IsCirclePressed to true so it doesn't cycle.
		IsCirclePressed = 1;	
		// Enable Through Engine
		HookKernel(1);
	}
	// Disable
	else if ((*(u16*)0x001EE682 == 0xdfff) && (EnabledChaosMod == 1) && (IsCirclePressed == 0))
	{
		// Enabled Mod Check
		EnabledChaosMod = 0;
		// Switch IsCirclePressed to true so it doesn't cycle.
		IsCirclePressed = 1;
		// Disable through Engine
		HookKernel(0);
	}
	// Reset IsCirclePressed
	else if (*(u16*)0x001EE682 != 0xdfff)
	{
		IsCirclePressed = 0;
	}
}

int main(void)
{
	// Call this first
	dlPreUpdate();

	// Patch.bin hook: 0x00138DD0
	// run original jal that patch.bin hook took over
	((void (*)(void))0x001270C0)();

	// if Music is not Loaded, stop.
	if (*(u32*)0x001CF85C != 0x000F8D29)
		return -1;

	// Check to see if on Multiplayer Menu.  If not, don't run anything else.
	if (uiGetActivePointer() != uiGetPointer(UI_MENU_ID_ONLINE_LOCAL_EDIT_PROFILE_MENU))
		return -1;

	// Grab Current status of Mod.
	EnabledChaosMod = *(u32*)0x000EFFFC;



	// if (isInMenus())
	// {
	// 	// from DL patch hook, Black Screens loading into multiplayer.
	// 	// if (*(u32*)0x00594CBC == 0)
	// 	// 	*(u32*)0x00594CB8 = 0x0C000000 | ((u32)(&OnMultiplayerMenu) / 4);

	// 	// Hook Display Text
	// 	if (*(u32*)0x0061E1B4 == 0x03e00008)
	// 		*(u32*)0x0061E1B4 = 0x08000000 | ((u32)(&OnMultiplayerMenu) / 4);
	// }

	if (*(u32*)0x0061E1B4 == 0x03e00008)
		*(u32*)0x0061E1B4 = 0x08000000 | ((u32)(&OnMultiplayerMenu) / 4);

	// Call this last
	dlPostUpdate();

	return 0;
}
