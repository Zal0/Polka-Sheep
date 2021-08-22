#include "Banks/SetAutoBank.h"
#include "main.h"

IMPORT_TILES(font);
IMPORT_MAP(window);
IMPORT_TILES(tiles);
IMPORT_MAP(level_complete);

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Math.h"
#include "Palette.h"
#include "string.h"
#include "Keys.h"
#include "gb/cgb.h"
#include "Music.h"

IMPORT_MAP(maplevel1);
IMPORT_MAP(maplevellobo);
IMPORT_MAP(maplevelpajaro);
IMPORT_MAP(maplevelpuzzlesencilloylobo);
IMPORT_MAP(maplevelsubida);
IMPORT_MAP(maplevelpinchosabajo);
IMPORT_MAP(maplevelplataformashorizontal);
IMPORT_MAP(maplevelplataformaslobopajaro);
IMPORT_MAP(maplevelsubidapajaritos);
IMPORT_MAP(maplevelescondrijo);
IMPORT_MAP(mapleveldospisos);
IMPORT_MAP(maplevelsubidapro);
IMPORT_MAP(maplevelsubidapinchos);

#define BANKED_MAP(MAP) {BANK(MAP), &MAP}

struct MapInfoBanked {
	UINT8 bank;
	struct MapInfo* map;
};

const struct MapInfoBanked levels[] = {
	BANKED_MAP(maplevel1),
	BANKED_MAP(maplevellobo),
	BANKED_MAP(maplevelpuzzlesencilloylobo),
	BANKED_MAP(maplevelpajaro),
	BANKED_MAP(maplevelsubida),
	BANKED_MAP(maplevelplataformashorizontal),
	BANKED_MAP(maplevelpinchosabajo),
	BANKED_MAP(maplevelplataformaslobopajaro),
	BANKED_MAP(maplevelsubidapinchos),
	BANKED_MAP(maplevelsubidapajaritos),
	BANKED_MAP(maplevelescondrijo),
	BANKED_MAP(mapleveldospisos),
	BANKED_MAP(maplevelsubidapro),
};

UINT8 current_level = 0;
const UINT8 num_levels = 13;

UINT8 collisions[] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 0};

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

DECLARE_MUSIC(polka_level1);
DECLARE_MUSIC(polka_win);

void Start_StateGame() {
	UINT8 i;
	UINT16 start_x, start_y;
	const struct MapInfoBanked* level = &levels[current_level];
	UINT8 level_w, level_h;

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

#ifdef CGB
	//TODO: ensure the Player has its own palette for the blinking effect when hit
	if(_cpu == CGB_TYPE) {
		spritePalsOffset[SpritePlayer] = 1;
	}
#endif
	
	INIT_FONT(font, PRINT_WIN);
	WX_REG = 7;
	WY_REG = 128;
	scroll_h_border = 2 << 3;
	InitWindow(0, 0, BANK(window), &window);
	SHOW_WIN;
	PRINT_POS(0, 1);
	Printf("Level %d", (UINT16)(current_level + 1));

	DPRINT(6, 0, " DEBUG ");
	
	GetMapSize(level->bank, level->map, &level_w, &level_h);
	ScrollFindTile(level->bank, level->map, 4, 0, 0, level_w, level_h, &start_x, &start_y);
	scroll_target = SpriteManagerAdd(SpritePlayer, start_x << 3, ((start_y - 1) << 3) + 8);

	InitScrollTiles(0, &tiles);
	InitScroll(level->bank, level->map, collisions, 0);
	SHOW_BKG;

	countdown = 1024;
	countdown_tick = -1; //Force first update

	lifes_y[0] = 0; //reset lifes y array
	
	friendsheep_sprite = 0;
	game_state = PLAYING;

	PlayMusic(polka_level1, 1);
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
}

#define END_Y 85
#define END_X 20

UWORD UpdateColorGame(UINT8 i, UWORD col) {
	return RGB2(PAL_RED(col) | DespRight(0x1F, 5 - i), PAL_GREEN(col) | DespRight(0x1F, 5 - i), PAL_BLUE(col) | DespRight(0x1F, 5 - i));
}

extern UWORD ZGB_Fading_BPal[32];
extern UWORD ZGB_Fading_SPal[32];
void FadeStepColorGame(UINT8 i) {
	UINT8 pal, c;
	UWORD palette[4];
	UWORD* col = ZGB_Fading_BPal;

	for(pal = 0; pal < 8; pal ++) {
		for(c = 0; c < 4; ++c, ++col) {
				palette[c] = UpdateColorGame(i, *col);
		};
		set_bkg_palette(pal, 1, palette);
	}
	delay(20);
}

void SetGBFade(UINT8 i) {
#ifdef CGB
	if(_cpu == CGB_TYPE) {
		FadeStepColorGame((i << 1) < 5 ? i << 1 : 5);
	} else
#endif
		BGP_REG = PAL_DEF(0, 1, 2, 3) << (i << 1);
}

void Update_StateGame() {
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

			if(friendsheep_sprite != 0) {
				game_state = LEVEL_COMPLETE;
				scroll_target = 0;
				level_complete_time = 0;
				SPRITEMANAGER_ITERATE(i, spr) {
					if(spr->type != SpritePlayer && spr->type != SpriteFriendSheep && spr->type != SpritePop) {
						SpriteManagerRemove(i);
					}
				}
				PlayMusic(polka_win, 0);
			}

#ifndef NDEBUG
			if(KEY_TICKED(J_SELECT)) {
				current_level ++;
				SetState(StateGame);
			}
#endif
			break;

		case LEVEL_COMPLETE:
			level_complete_time += 1;

			       if(level_complete_time ==  10) {SetGBFade(1);
			} else if(level_complete_time ==  20) {SetGBFade(2);
			} else if(level_complete_time ==  30) {SetGBFade(3); HIDE_WIN;
			} else if(level_complete_time ==  80) {
				player_sprite->x = player_sprite->x - scroll_x; friendsheep_sprite->x = friendsheep_sprite->x - scroll_x;
				player_sprite->y = player_sprite->y - scroll_y; friendsheep_sprite->y = friendsheep_sprite->y - scroll_y;
				InitScroll(BANK(level_complete), &level_complete, 0, 0);
			} else if(level_complete_time ==  90) {SetGBFade(2);
			} else if(level_complete_time == 100) {SetGBFade(1);
			} else if(level_complete_time == 110) {SetGBFade(0);
			} else if(level_complete_time == 120) {
				print_target = PRINT_BKG;
				PRINT(3, 6, "LEVEL COMPLETE!");
			} else if(level_complete_time > 130) {
					if(previous_keys && !keys) {
						current_level ++;
						SetState(current_level == num_levels ? StateGameEnd : StateGame);
					}
			}
			

			if(player_sprite->x != scroll_x + (150 - END_X))
				player_sprite->x += U_LESS_THAN(player_sprite->x, scroll_x + (150 - END_X)) ? 1 : -1;

			if(player_sprite->y != scroll_y + END_Y)
				player_sprite->y += U_LESS_THAN(player_sprite->y, scroll_y + END_Y) ? 1 : -1;

			if(friendsheep_sprite->x != scroll_x + END_X)
				friendsheep_sprite->x += U_LESS_THAN(friendsheep_sprite->x, scroll_x + END_X) ? 1 : -1;

			if(friendsheep_sprite->y != scroll_y + END_Y)
				friendsheep_sprite->y += U_LESS_THAN(friendsheep_sprite->y, scroll_y + END_Y) ? 1 : -1;

			break;
	}
}