#pragma bank 2
#include "SpritePOP.h"
UINT8 bank_SPRITE_POP = 2;

#include "SpriteManager.h"

UINT8 anim_pop_idle[] = {4, 0, 1, 1, 1};

void Start_SPRITE_POP() {
	SetSpriteAnim(THIS, anim_pop_idle, 7);
}

void Update_SPRITE_POP() {
	if(THIS->current_frame == 2) {
		SpriteManagerRemove(THIS_IDX);
	}
}

void Destroy_SPRITE_POP() {
}