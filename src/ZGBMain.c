#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = STATE_MENU;

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == STATE_GAME) {
		if(U_LESS_THAN(255 - (UINT16)*tile_ptr, N_SPRITE_TYPES)) {
			*tile = 0;
			return 255 - (UINT16)*tile_ptr;
		}
		else if(*tile_ptr == 4)
			*tile = 0;
		else
			*tile = *tile_ptr;
	}

	return 255u;
}