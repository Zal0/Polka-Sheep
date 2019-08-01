#pragma bank 2
#include "main.h"
UINT8 bank_STATE_GAMEEND = 2;

#include "ZGBMain.h"
#include "Keys.h"

#include "../res/src/font.h"

#include "Scroll.h"
#include "Print.h"

extern struct TilesInfo ending_tiles;
extern struct MapInfo ending;

UINT8 game_over_state;

void Start_STATE_GAMEEND() {
	InitScrollTiles(0, &ending_tiles);
	InitScroll(&ending, 0, 0);
	SHOW_BKG;
	HIDE_WIN;

	INIT_FONT(font, PRINT_BKG);

	PRINT(1, 1, "CONGRATULATIONS!!!");
	game_over_state = 0;
}

void Update_STATE_GAMEEND() {
	if(previous_keys && !keys) {
		switch(game_over_state) {
			case 0:
				PRINT(9, 15, "Thanks for");
				PRINT(12, 16, "playing");
				break;

			default:
				SetState(STATE_MENU);
		}
		game_over_state ++;
	}
}

