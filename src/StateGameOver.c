#include "Banks/SetBank2.h"
#include "main.h"

#include "ZGBMain.h"
#include "Keys.h"

#include "../res/src/font.h"

#include "Scroll.h"
#include "Print.h"

extern struct TilesInfo wolf_gameover_tiles;
extern struct MapInfo wolf_gameover;

extern const unsigned char * const polka_lose_mod_Data[];
void Start_StateGameOver() {
	InitScrollTiles(0, &wolf_gameover_tiles);
	InitScroll(&wolf_gameover, 0, 0);
	SHOW_BKG;
	HIDE_WIN;

	INIT_FONT(font, PRINT_BKG);
	PRINT(5, 1, "GAME OVER");

	PlayMusic(polka_lose_mod_Data, 4, 0);
}

void Update_StateGameOver() {
	if(previous_keys && !keys) {
		SetState(StateMenu);
	}
}

