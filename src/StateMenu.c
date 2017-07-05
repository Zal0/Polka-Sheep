#pragma bank 2
#include "StateMenu.h"
UINT8 bank_STATE_MENU = 2;

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/screen_start.h"
#include "../res/src/screen_start_tileset.h"

extern const unsigned char * const polka_start_mod_Data[];
extern UINT8 current_level;
void Start_STATE_MENU() {
	SetPalette(BG_PALETTE, 0, 8, bgPALMenu, bank_STATE_MENU);

	InitScrollTiles(0, 256, screen_start_tileset, 3);
	InitScroll(screen_startWidth, screen_startHeight, screen_start, 0, 0, 3);
	SHOW_BKG;
	HIDE_WIN;

	PlayMusic(polka_start_mod_Data, 4, 0);
}

extern const UINT8 max_energy;
extern UINT8 current_energy;
void Update_STATE_MENU() {
	if(previous_keys && !keys) {
#ifdef NDEBUG
		current_level = 0;
#endif 
		current_energy = max_energy;
		SetState(STATE_GAME);
	}
}