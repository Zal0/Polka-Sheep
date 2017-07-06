#pragma bank 2
#include "StateGameEnd.h"
UINT8 bank_STATE_GAMEEND = 2;

#include "ZGBMain.h"
#include "Keys.h"

#include "../res/src/ending.h"
#include "../res/src/ending_tileset.h"
#include "../res/src/font.h"

#include "Scroll.h"
#include "Print.h"

void Start_STATE_GAMEEND() {
	InitScrollTiles(0, 256, ending_tileset, 3);
	InitScroll(endingWidth, endingHeight, ending, 0, 0, 3);
	SHOW_BKG;
	HIDE_WIN;

	INIT_FONT(font, 3, PRINT_BKG);
	PRINT(1, 8, "CONGRATULATIONS!!!");

	PRINT(5, 12, "Thanks for");
	PRINT(6, 13, "playing");
}

void Update_STATE_GAMEEND() {
	if(previous_keys && !keys) {
		SetState(STATE_MENU);
	}
}

