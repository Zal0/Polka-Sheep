#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"

UINT8 anim_pop_idle[] = {4, 0, 1, 1, 1};

void Start_SpritePop() {
	SetSpriteAnim(THIS, anim_pop_idle, 7);
}

void Update_SpritePop() {
	if(THIS->anim_frame == 2) {
		SpriteManagerRemove(THIS_IDX);
	}
}

void Destroy_SpritePop() {
}