#pragma bank 2
#include "SpriteBubble.h"
UINT8 bank_SPRITE_BUBBLE = 2;

#include "SpriteManager.h"

UINT8 anim_idle_bubble[] = {8, 0, 0, 0, 1, 0, 0, 0, 0};

void Start_SPRITE_BUBBLE() {
	SetSpriteAnim(THIS, anim_idle_bubble, 6);
}

void Update_SPRITE_BUBBLE() {
}

void Destroy_SPRITE_BUBBLE() {
}