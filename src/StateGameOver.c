#include "Banks/SetAutoBank.h"
#include "main.h"

#include "ZGBMain.h"
#include "Keys.h"

#include "Scroll.h"
#include "Print.h"
#include "Music.h"

IMPORT_TILES(font);
IMPORT_MAP(wolf_gameover);

DECLARE_MUSIC(polka_lose);

void START() {
	InitScroll(BANK(wolf_gameover), &wolf_gameover, 0, 0);
	HIDE_WIN;

	INIT_FONT(font, PRINT_BKG);
	PRINT(5, 1, "GAME OVER");

	PlayMusic(polka_lose, 0);
}

void UPDATE() {
	if(previous_keys && !keys) {
		SetState(StateMenu);
	}
}

