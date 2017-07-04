#pragma bank 2
#include "SpriteBubble.h"
UINT8 bank_SPRITE_BUBBLE = 2;

#include "SpriteManager.h"
#include "Trig.h"

UINT8 anim_idle_bubble[] = {8, 0, 0, 0, 1, 0, 0, 0, 0};

struct SpriteBubbleData {
	UINT16 x;
	UINT16 y;
	UINT8 sin;
};

void Start_SPRITE_BUBBLE() {
	struct SpriteBubbleData* data = (struct SpriteBubbleData*)THIS->custom_data;
	data->x = THIS->x;
	data->y = THIS->y;

	SetSpriteAnim(THIS, anim_idle_bubble, 6);
}

void Update_SPRITE_BUBBLE() {
	struct SpriteBubbleData* data = (struct SpriteBubbleData*)THIS->custom_data;

	THIS->x = data->x;
	THIS->y = data->y;

	data->sin += 1 << delta_time;
	THIS->x += SIN(data->sin) >> 7;
	THIS->y += COS(data->sin << 1) >> 6;
}

void Destroy_SPRITE_BUBBLE() {
}