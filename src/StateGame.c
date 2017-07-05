#pragma bank 2
#include "StateGame.h"
UINT8 bank_STATE_GAME = 2;

#include "../res/src/font.h"
#include "../res/src/window.h"
#include "../res/src/level_complete.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Math.h"
#include "Palette.h"
#include "string.h"
#include "Palette.h"
#include "Keys.h"

#include "../res/src/tiles.h"
#include "../res/src/maplevel1.h"
#include "../res/src/maplevellobo.h"
#include "../res/src/maplevelpajaro.h"
#include "../res/src/maplevelpuzzlesencilloylobo.h"
#include "../res/src/maplevelsubida.h"
#include "../res/src/maplevelpinchosabajo.h"
#include "../res/src/maplevelplataformashorizontal.h"
#include "../res/src/maplevelplataformaslobopajaro.h"

typedef struct LevelInfo {
	UINT16 w;
	UINT16 h;
	UINT8* map;
	UINT8 bank;
};
#define LEVEL(A, BANK) A##Width, A##Height, A, BANK
const struct LevelInfo levels[] = {
	{LEVEL(maplevel1,                     3)},
	{LEVEL(maplevellobo,                  3)},
	{LEVEL(maplevelpajaro,                3)},
	{LEVEL(maplevelpuzzlesencilloylobo,   3)},
	{LEVEL(maplevelsubida,                3)},
	{LEVEL(maplevelpinchosabajo,          5)},
	{LEVEL(maplevelplataformashorizontal, 5)},
	{LEVEL(maplevelplataformaslobopajaro, 5)},
};

UINT8 collisions[] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 0};

UINT8 current_level = 0;

INT16 countdown;
INT8 countdown_tick;
extern UINT16 lifes_y[];

extern struct Sprite* friendsheep_sprite;
extern struct Sprite* player_sprite;
UINT16 level_complete_time;
typedef enum {
	PLAYING,
	LEVEL_COMPLETE,
} GameState;
GameState game_state;

extern UINT8 n_sprite_types;
void Start_STATE_GAME() {
	UINT8 i;
	UINT16 start_x, start_y;
	const struct LevelInfo* level = &levels[current_level];

	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

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
	DPRINT(6, 0, " DEBUG ");
	PRINT_POS(0, 1);
	Printf("Level %d", (UINT16)(current_level + 1));
	
	ScrollFindTile(level->w, level->map, level->bank, 4, 0, 0, level->w, level->h, &start_x, &start_y);
	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, start_x << 3, (start_y - 1) << 3);

	InitScrollTiles(0, 128, tiles, 3);
	InitScroll(level->w, level->h, level->map, collisions, 0, level->bank);
	SHOW_BKG;

	countdown = 1024;
	countdown_tick = -1; //Force first update

	lifes_y[0] = 0; //reset lifes y array
	
	friendsheep_sprite = 0;
	game_state = PLAYING;
}

#define END_Y 85
#define END_X 20
const UINT8 pals[] = {PAL_DEF(0, 1, 2, 3), PAL_DEF(0, 0, 0, 0)};
UINT8 current_pal;
INT8 pal_tick;
void Update_STATE_GAME() {
	struct Sprite* spr;
	UINT8 i;

	switch(game_state) {
		case PLAYING:
			//Timer update
			/*countdown_tick -= 1 << delta_time;
			if(U_LESS_THAN(countdown_tick, 0)) {
				countdown_tick += 60;
				countdown --;
				PRINT_POS(0, 1);
				Printf("t: %u ", countdown);
			}*/

			pal_tick -= 1 << delta_time;
			if(U_LESS_THAN(pal_tick, 0)) {
				pal_tick += 3;

				current_pal ++;
				OBP1_REG = pals[current_pal % 2];
			}

			if(friendsheep_sprite != 0) {
				game_state = LEVEL_COMPLETE;
				scroll_target = 0;
				level_complete_time = 0;
				SPRITEMANAGER_ITERATE(i, spr) {
					if(spr->type != SPRITE_PLAYER && spr->type != SPRITE_FRIENDSHEEP && spr->type != SPRITE_POP) {
						SpriteManagerRemove(i);
					}
				}
			}

#ifndef NDEBUG
			if(KEY_TICKED(J_SELECT)) {
				current_level ++;
				SetState(STATE_GAME);
			}
#endif
			break;

		case LEVEL_COMPLETE:
			level_complete_time += 1;

			       if(level_complete_time ==  10) {BGP_REG = PAL_DEF(0, 0, 1, 2);
			} else if(level_complete_time ==  20) {BGP_REG = PAL_DEF(0, 0, 0, 1);
			} else if(level_complete_time ==  30) {BGP_REG = PAL_DEF(0, 0, 0, 0); HIDE_WIN;
			} else if(level_complete_time ==  80) {
				player_sprite->x = player_sprite->x - scroll_x; friendsheep_sprite->x = friendsheep_sprite->x - scroll_x;
				player_sprite->y = player_sprite->y - scroll_y; friendsheep_sprite->y = friendsheep_sprite->y - scroll_y;
				InitScroll(level_completeWidth, level_completeHeight, level_complete, 0, 0, 3);
			} else if(level_complete_time ==  90) {BGP_REG = PAL_DEF(0, 0, 0, 1);
			} else if(level_complete_time == 100) {BGP_REG = PAL_DEF(0, 0, 1, 2);
			} else if(level_complete_time == 110) {BGP_REG = PAL_DEF(0, 1, 2, 3);
			} else if(level_complete_time == 120) {
				print_target = PRINT_BKG;
				PRINT(3, 6, "LEVEL COMPLETE!");
			} else if(level_complete_time > 130) {
					if(previous_keys && !keys) {
						current_level ++;
						SetState(STATE_GAME);
					}
			}
			

			if(player_sprite->x != scroll_x + (144 - END_X))
				player_sprite->x += (player_sprite->x > scroll_x + (144 - END_X)) ? -1 : 1;

			if(player_sprite->y != scroll_y + END_Y)
				player_sprite->y += (player_sprite->y > scroll_y + END_Y) ? -1 : 1;

			if(friendsheep_sprite->x != scroll_x + END_X)
				friendsheep_sprite->x += (friendsheep_sprite->x > scroll_x + END_X) ? -1 : 1;

			if(friendsheep_sprite->y != scroll_y + END_Y)
				friendsheep_sprite->y += (friendsheep_sprite->y > scroll_y + END_Y) ? -1 : 1;

			break;
	}
}