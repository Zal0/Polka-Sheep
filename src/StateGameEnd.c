#include "Banks/SetAutoBank.h"
#include "main.h"

#include "ZGBMain.h"
#include "Keys.h"

#include "Scroll.h"
#include "Print.h"

IMPORT_MAP(ending);
IMPORT_TILES(font);

UINT8 game_over_state;

void START() {
	InitScroll(BANK(ending), &ending, 0, 0);
	HIDE_WIN;

	INIT_FONT(font, PRINT_BKG);

	PRINT(1, 1, "CONGRATULATIONS!!!");
	game_over_state = 0;
}

void UPDATE() {
	if(previous_keys && !keys) {
		switch(game_over_state) {
			case 0:
				PRINT(9, 15, "Thanks for");
				PRINT(12, 16, "playing");
				break;

			default:
				SetState(StateMenu);
		}
		game_over_state ++;
	}
}

