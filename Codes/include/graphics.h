#include <tamtypes.h>

#ifndef _CODES_GRAPHICS_H_
#define _CODES_GRAPHICS_H_

#define SCREEN_WIDTH	(512)
#define SCREEN_HEIGHT	(416)


int gfxScreenSpaceText(float x, float y, float scaleX, float scaleY, u32 color, const char * string, int length, int alignment);

#endif // _CODES_GRAPHICS_H_
