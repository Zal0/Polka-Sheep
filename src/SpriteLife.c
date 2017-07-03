#pragma bank 2
#include "SpriteLife.h"
UINT8 bank_SPRITE_LIFE = 2;

#include "SpriteManager.h"
#include "Vector.h"

DECLARE_VECTOR(lifes_y, 5);

UINT8 anim_idle_life[] = {4, 0, 0, 0, 1};

void Start_SPRITE_LIFE() {
	UINT8 i;
	UINT8 elem;

	THIS->coll_h = 8;
	
	IterateVector(lifes_y, i, elem) {
		if(elem == (THIS->y >> 3)) {
			SpriteManagerRemove(THIS_IDX);
		}
	}

	SetSpriteAnim(THIS, anim_idle_life, 10);
}

void Update_SPRITE_LIFE() {
}

void Destroy_SPRITE_LIFE() {
}