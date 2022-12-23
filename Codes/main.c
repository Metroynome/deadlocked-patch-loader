#include <tamtypes.h>
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

int _InfiniteHealthMoonjump_Init = 0;

void InfiniteHealthMoonjump()
{
	// Handle On/Off Button Press
	void * PlayerPointer = (void*)(*(u32*)0x001eeb70);
	if (PlayerPointer == 0)
		return;
	
	Player * player = (Player*)((u32)PlayerPointer - 0x2FEC);
	PadButtonStatus * pad = playerGetPad(player);
	if ((pad->btns & (PAD_R3 | PAD_R2)) == 0){
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
	player->Health = PLAYER_MAX_HEALTH;
	// if X is pressed, lower gravity.
	if ((pad->btns & PAD_CROSS) == 0){
		*(float*)(PlayerPointer - 0x2EB4) = 0.125;
	}
}

void RunCodes()
{
	dlPreUpdate();
	InfiniteHealthMoonjump();
	dlPostUpdate();
}

int main(void)
{
	printf("use your inside codes!\n");

	return 0;
}
