#pragma bank 2
#include "SpriteWolf.h"
UINT8 bank_SPRITE_WOLF = 2;

#include "../res/src/Wolf.h"
#include "SpriteManager.h"
#include "Scroll.h"

UINT8 anim_walking[] = {2, 0, 1};
UINT8 anim_laughing[] = {2, 2, 3};

extern INT16 inmunity;

struct SpriteWolfData {
	INT16 laughing;
	fixed wolf_x_accum;
};

void Start_SPRITE_WOLF() {
	struct SpriteWolfData* data = (struct SpriteWolfData*)THIS->custom_data;
	data->laughing = 0;
	data->wolf_x_accum.w = 0;

	SetSpriteAnim(THIS, anim_walking, 20u);

	THIS->coll_x += 4;
	THIS->coll_w -= 8;
	THIS->lim_x = 160u;
	THIS->lim_y = 160u;
}

void Update_SPRITE_WOLF() {
	struct SpriteWolfData* data = (struct SpriteWolfData*)THIS->custom_data;
	if(data->laughing) {
		data->laughing -= 1 << delta_time;
		if(data->laughing < 1) {
			data->laughing = 0;
			SetSpriteAnim(THIS, anim_walking, 20u);
		}
	} else {
		data->wolf_x_accum.w += 150;
		if(data->wolf_x_accum.b.h != 0) {
			if(THIS->flags & OAM_VERTICAL_FLAG) {
				//moving left
				if(TranslateSprite(THIS, -data->wolf_x_accum.b.h, 0)) {
					THIS->flags = 0u;
				} else	if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x) >> 3), (THIS->y >> 3) + 2u)]) {
					THIS->flags = 0u;
				}
			} else {
				//moving right
				if(TranslateSprite(THIS, data->wolf_x_accum.b.h, 0)) {
					THIS->flags |= OAM_VERTICAL_FLAG;
				} else if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)]) {
					THIS->flags |= OAM_VERTICAL_FLAG;
				}
			}
			data->wolf_x_accum.b.h = 0;
		}

		if(CheckCollision(THIS, scroll_target)) {
			data->laughing = 100;
			SetSpriteAnim(THIS, anim_laughing, 10);
		}
	}
}

void Destroy_SPRITE_WOLF() {
}