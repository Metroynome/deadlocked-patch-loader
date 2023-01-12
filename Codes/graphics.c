#include "include/graphics.h"
#include "include/interop.h"

// widthFunc is above drawTestFuncion  (Offset is: +0x2F0)
VariableAddress_t vaGetTextWidthFunc = {
	.Battledome = 0x0055E4D0,
	.Catacrom = 0x00510BF8,
	.Sarathos = 0x00510FD0,
	.Kronos = 0x00535410,
	.Shaar = 0x00508C40,
	.Valix = 0x004FA638,
	.Orxon = 0x00511E48,
	.Torval = 0x0051CC40,
	.Stygia = 0x00509CA8,
	.Maraxus = 0x005231E8,
	.GhostStation = 0x0051C040,
	.DreadZoneInterior = 0x0052DA00
	// .StartMenu = 0x00454780
};

VariableAddress_t vaDrawTextFunc = {
	.Battledome = 0x0055E7C0,
	.Catacrom = 0x00510EE8,
	.Sarathos = 0x005112C0,
	.Kronos = 0x00535700,
	.Shaar = 0x00508F30,
	.Valix = 0x004FA928,
	.Orxon = 0x00512138,
	.Torval = 0x0051CF30,
	.Stygia = 0x00509F98,
	.Maraxus = 0x005234D8,
	.GhostStation = 0x0051C330,
	.DreadZoneInterior = 0x0052DCF0
	// .StartMenu = 0x00454A70
};

int internal_drawFunc(u32,const char*,long,u64,u64,u64,float,float,float,float,float,float);

int gfxScreenSpaceText(float x, float y, float scaleX, float scaleY, u32 color, const char * string, int length, int alignment)
{
	internal_drawFunc(color, string, length, alignment, 0, 0x80000000, x, y, scaleX, scaleY, 0, 0);
	return x + gfxGetFontWidth(string, length, scaleX);
}
