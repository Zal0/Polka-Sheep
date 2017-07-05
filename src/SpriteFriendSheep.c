#pragma bank 2
#include "SpriteFRIENDSHEEP.h"
UINT8 bank_SPRITE_FRIENDSHEEP = 2;

#include "SpriteManager.h"
UINT8 anim_friendsheep_idle[] = {2, 0, 1};
struct Sprite* friendsheep_sprite = 0;

void Start_SPRITE_FRIENDSHEEP() {
	friendsheep_sprite = THIS;
	SetSpriteAnim(THIS, anim_friendsheep_idle, 4);
}

void Update_SPRITE_FRIENDSHEEP() {
}

void Destroy_SPRITE_FRIENDSHEEP() {
}