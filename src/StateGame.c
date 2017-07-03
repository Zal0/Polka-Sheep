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
#include "Math.h"
#include "Palette.h"
#include "string.h"

UINT8 collisions[] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 0};

INT16 countdown;
INT8 countdown_tick;
extern UINT16 lifes_y[];

extern UINT8 n_sprite_types;
void Start_STATE_GAME() {
	UINT8 i;
	UINT16 start_x, start_y;

	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;
	
	ScrollFindTile(mapWidth, map, 3, 4, 0, 0, mapWidth, mapHeight, &start_x, &start_y);
	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, start_x << 3, (start_y - 1) << 3);

	InitScrollTiles(0, 19, tiles, 3);
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
#else
	INIT_CONSOLE(font, 3, 2);
#endif

	countdown = 1024;
	countdown_tick = -1; //Force first update

	lifes_y[0] = 0; //reset lifes y array
}

const UINT8 pals[] = {PAL_DEF(0, 1, 2, 3), PAL_DEF(0, 0, 0, 0)};
UINT8 current_pal;
INT8 pal_tick;
void Update_STATE_GAME() {
	//Timer update
	countdown_tick -= 1 << delta_time;
	if(U_LESS_THAN(countdown_tick, 0)) {
		countdown_tick += 60;
		countdown --;
		PRINT_POS(0, 1);
		Printf("t: %u ", countdown);
	}

	pal_tick -= 1 << delta_time;
	if(U_LESS_THAN(pal_tick, 0)) {
		pal_tick += 3;

		current_pal ++;
		OBP1_REG = pals[current_pal % 2];
	}
}