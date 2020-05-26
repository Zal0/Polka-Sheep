#include "Banks/SetBank2.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

extern struct TilesInfo screen_start_tiles;
extern struct MapInfo screen_start;

extern const unsigned char * const polka_start_mod_Data[];
extern UINT8 current_level;
void Start_StateMenu() {
	InitScrollTiles(0, &screen_start_tiles);
	InitScroll(&screen_start, 0, 0);
	SHOW_BKG;
	HIDE_WIN;

	PlayMusic(polka_start_mod_Data, 4, 0);
}

extern const UINT8 max_energy;
extern UINT8 current_energy;
void Update_StateMenu() {
	if(previous_keys && !keys) {
#ifdef NDEBUG
		current_level = 0;
#endif 
		current_energy = max_energy;
		SetState(StateGame);
	}
}