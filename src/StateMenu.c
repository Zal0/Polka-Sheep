#include "Banks/SetAutoBank.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Music.h"

IMPORT_MAP(screen_start);

DECLARE_MUSIC(polka_start);

extern UINT8 current_level;
void START() {
	LoadMap(0, 0, 0, BANK(screen_start), &screen_start);
	HIDE_WIN;

	PlayMusic(polka_start, 0);
}

extern const UINT8 max_energy;
extern UINT8 current_energy;
void UPDATE() {
	if(previous_keys && !keys) {
#ifdef NDEBUG
		current_level = 0;
#endif 
		current_energy = max_energy;
		SetState(StateGame);
	}
}