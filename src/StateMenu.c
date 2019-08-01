#pragma bank 2
#include "main.h"
UINT8 bank_STATE_MENU = 2;

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

extern struct TilesInfo screen_start_tiles;
extern struct MapInfo screen_start;

extern const unsigned char * const polka_start_mod_Data[];
extern UINT8 current_level;
void Start_STATE_MENU() {
	InitScrollTiles(0, &screen_start_tiles);
	InitScroll(&screen_start, 0, 0);
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