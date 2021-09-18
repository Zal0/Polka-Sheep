#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"
UINT8 anim_friendsheep_idle[] = {2, 0, 1};
Sprite* friendsheep_sprite = 0;

void START() {
	friendsheep_sprite = THIS;
	SetSpriteAnim(THIS, anim_friendsheep_idle, 4);
}

void UPDATE() {
}

void DESTROY() {
}