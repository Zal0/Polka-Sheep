#pragma bank 2
#include "StateGame.h"
UINT8 bank_STATE_GAME = 2;

#include "..\res\src\font.h"
#include "..\res\src\tiles.h"
#include "..\res\src\map.h"
#include "..\res\src\window.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"

UINT8 collisions[] = {6, 0};



extern UINT8 n_sprite_types;
void Start_STATE_GAME() {
	UINT8 i;
	UINT16 start_x, start_y;

	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;
	
	ScrollFindTile(mapWidth, map, 4, 6, 0, 0, mapWidth, mapHeight, &start_x, &start_y);
	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, start_x << 3, start_y << 3);

	InitScrollTiles(0, 7, tiles, 3);
	InitScroll(mapWidth, mapHeight, map, collisions, 0, 3);
	SHOW_BKG;

#ifdef NDEBUG
	print_target = PRINT_WIN;\
	print_x = 0;\
	print_y = 0;\
	font_idx = 255 - 45;\
	InitScrollTiles(255 - 45, 45, font, 3);\
	WX_REG = 7;\
  WY_REG = (144 - (2 << 3));\
	scroll_h_border = 2 << 3;\
	SHOW_WIN;
	InitWindow(0, 0, 20, 3, window, 3, 0);
	PRINT(1, 1, "PIZZA PIZZA PIZZA PIZZA");
#else
	INIT_CONSOLE(font, 3, 2);
#endif
}

void Update_STATE_GAME() {
}