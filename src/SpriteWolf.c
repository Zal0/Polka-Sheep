#pragma bank 2
#include "SpriteWolf.h"
UINT8 bank_SPRITE_WOLF = 2;

#include "../res/src/Wolf.h"
#include "SpriteManager.h"
#include "Scroll.h"

UINT8 anim_walking[] = {2, 0, 1};
UINT8 anim_laughing[] = {2, 2, 3};

void Start_SPRITE_WOLF() {
	SetSpriteAnim(THIS, anim_walking, 20u);

	THIS->coll_x += 4;
	THIS->coll_w -= 8;
	THIS->lim_x = 160u;
	THIS->lim_y = 160u;
}

void Update_SPRITE_WOLF() {
	if(THIS->flags & OAM_VERTICAL_FLAG) {
		//moving left
		if(TranslateSprite(THIS, -1, 0)) {
			THIS->flags = 0u;
		} else	if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x) >> 3), (THIS->y >> 3) + 2u)]) {
			THIS->flags = 0u;
		}
	} else {
		//moving right
		if(TranslateSprite(THIS, +1, 0)) {
			THIS->flags |= OAM_VERTICAL_FLAG;
		} else if(!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)]) {
			THIS->flags |= OAM_VERTICAL_FLAG;
		}
	}
}

void Destroy_SPRITE_WOLF() {
}