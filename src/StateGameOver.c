#pragma bank 2
#include "main.h"
UINT8 bank_STATE_GAMEOVER = 2;

#include "ZGBMain.h"
#include "Keys.h"

#include "wolf_gameover.h"
#include "wolf_gameover_tileset.h"
#include "../res/src/font.h"

#include "Scroll.h"
#include "Print.h"

extern const unsigned char * const polka_lose_mod_Data[];
void Start_STATE_GAMEOVER() {
	InitScrollTilesLEGACY(0, 256, wolf_gameover_tileset, 4);
	InitScroll(wolf_gameoverWidth, wolf_gameoverHeight, wolf_gameover, 0, 0, 4);
	SHOW_BKG;
	HIDE_WIN;

	INIT_FONT(font, PRINT_BKG);
	PRINT(5, 1, "GAME OVER");

	PlayMusic(polka_lose_mod_Data, 4, 0);
}

void Update_STATE_GAMEOVER() {
	if(previous_keys && !keys) {
		SetState(STATE_MENU);
	}
}

