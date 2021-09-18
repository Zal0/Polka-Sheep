#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"
#include "Vector.h"

DECLARE_VECTOR(lifes_y, 5);

UINT8 anim_idle_life[] = {4, 0, 0, 0, 1};

void START() {
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

void UPDATE() {
}

void DESTROY() {
}