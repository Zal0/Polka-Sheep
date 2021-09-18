#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"
#include "Scroll.h"

UINT8 anim_walking[] = {2, 0, 1};
UINT8 anim_laughing[] = {2, 2, 3};

extern INT16 inmunity;

typedef struct {
	INT16 laughing;
	fixed wolf_x_accum;
} CUSTOM_DATA;

void START() {
	CUSTOM_DATA* data = (CUSTOM_DATA*) THIS->custom_data;
	data->laughing = 0;
	data->wolf_x_accum.w = 0;

	SetSpriteAnim(THIS, anim_walking, 20u);

	THIS->lim_x = 160u;
	THIS->lim_y = 160u;
}

void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*) THIS->custom_data;
	if(data->laughing) {
		data->laughing -= 1 << delta_time;
		if(data->laughing < 1) {
			data->laughing = 0;
			SetSpriteAnim(THIS, anim_walking, 20u);
		}
	} else {
		data->wolf_x_accum.w += 150 << delta_time;
		if(data->wolf_x_accum.b.h != 0) {
			if(THIS->mirror == V_MIRROR) {
				//moving left
				if(TranslateSprite(THIS, -data->wolf_x_accum.b.h, 0)) {
					THIS->mirror = NO_MIRROR;
				} else	if(!scroll_collisions[GetScrollTile((THIS->x >> 3), (THIS->y >> 3) + 2u)]) {
					THIS->mirror = NO_MIRROR;
				}
			} else {
				//moving right
				if(TranslateSprite(THIS, data->wolf_x_accum.b.h, 0)) {
					THIS->mirror = V_MIRROR;
				} else if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)]) {
					THIS->mirror = V_MIRROR;
				}
			}
			data->wolf_x_accum.b.h = 0;
		}

		//Moved to SpritePlayer to improve performance
		//if(CheckCollision(THIS, scroll_target)) {
		//	data->laughing = 100;
		//	SetSpriteAnim(THIS, anim_laughing, 10);
		//}
	}
}

void DESTROY() {
}