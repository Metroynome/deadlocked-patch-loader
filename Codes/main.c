#include <tamtypes.h>
#include <libdlsp/dl.h>
#include <libdlsp/player.h>
#include <libdlsp/pad.h>
#include <libdlsp/game.h>
#include <libdlsp/stdio.h>
#include <libdlsp/map.h>
#include <libdlsp/graphics.h>
#include <libdlsp/ui.h>

#define IS_PROGRESSIVE_SCAN				(*(int*)0x0021DE6C)
#define EXCEPTION_DISPLAY_ADDR			(0x000C8000)

int hasInstalledExceptionHandler = 0;

int _InfiniteHealthMoonjump_Init = 0;
int _Test = 0;
int _ShowText = 0;

void InfiniteHealthMoonjump(void)
{
	// Handle On/Off Button Press
	void * PlayerPointer = (void*)(*(u32*)0x001eeb70);
	if (PlayerPointer == 0)
		return;
	
	Player * player = (Player*)((u32)PlayerPointer - 0x2FEC);
	PadButtonStatus * pad = playerGetPad(player);
	if ((pad->btns & (PAD_R3 | PAD_R2)) == 0)
	{
		_InfiniteHealthMoonjump_Init = 1;
	}
	else if ((pad->btns & (PAD_L3)) == 0)
	{
		_InfiniteHealthMoonjump_Init = 0;
	}

	// Handle On/Off
	if(!_InfiniteHealthMoonjump_Init)
		return;

	// Player Health is always max.
	player->Health = player->MaxHealth;
	// if X is pressed, lower gravity.
	if ((pad->btns & PAD_CROSS) == 0)
	{
		*(float*)(PlayerPointer - 0x2EB4) = 0.125;
	}
}

void Test(void)
{
	void * PlayerPointer = (void*)(*(u32*)0x001eeb70);
	if (PlayerPointer == 0)
		return;

	Player * player = (Player*)((u32)PlayerPointer - 0x2FEC);
	PadButtonStatus * pad = playerGetPad(player);
	if ((pad->btns & PAD_UP) == 0 && _Test == 0)
	{
		_Test = 1;
		_ShowText = !_ShowText;
		// uiPrintAmmoPickup(0, 0x2D34);
		uiShowHelpPopup(0, "Message me, Kenobi.  UwU", -1);
		// mapResetMission();
	}
	else if ((pad->btns & PAD_UP) != 0 && _Test == 1)
	{
		_Test = 0;
	}

	// if (_ShowText == 1)
		// uiShowHelpPopup(0, "GENERAL KENOBI >:(", 7);
		// gfxScreenSpaceText(SCREEN_WIDTH * 0.3, SCREEN_HEIGHT * 0.855, 1, 1, 0x80FFFFFF, "TEST YOUR MOTHER FOR HUGS", -1, 4);
}

void MainMenu(void)
{
	if (mapGetActiveMission() != -1)
		return;

	gfxScreenSpaceText(SCREEN_WIDTH * 0.3, SCREEN_HEIGHT * 0.855, 1, 1, 0x80FFFFFF, "Main Menu! Woah!", -1, 4);
}

void RunCodes()
{
	if (isInGame())
	{
		InfiniteHealthMoonjump();
		Test();
	}
	else if (isInMenus())
	{
		MainMenu();
	}
}

int main(void)
{
	// Call this first
	dlPreUpdate();

	// if EnableDisable Variable is 0, Mod is disabled.
	if (*(u32*)0x000EFFFC == 0 || *(u32*)0x001CF85C == 0x000F8D29)
		return -1;

	// Exception Display
	if (*(u32*)EXCEPTION_DISPLAY_ADDR != 0)
	{
		if (!hasInstalledExceptionHandler)
		{
			((void (*)(void))EXCEPTION_DISPLAY_ADDR)();
			hasInstalledExceptionHandler = 1;
		}
		
		// change display to match progressive scan resolution
		if (IS_PROGRESSIVE_SCAN)
		{
			*(u16*)(EXCEPTION_DISPLAY_ADDR + 0x9F4) = 0x0083;
			*(u16*)(EXCEPTION_DISPLAY_ADDR + 0x9F8) = 0x210E;
		}
		else
		{
			*(u16*)(EXCEPTION_DISPLAY_ADDR + 0x9F4) = 0x0183;
			*(u16*)(EXCEPTION_DISPLAY_ADDR + 0x9F8) = 0x2278;
		}
	}

	RunCodes();

	// Call this last
	dlPostUpdate();

	return 0;
}
