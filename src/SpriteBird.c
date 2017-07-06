#pragma bank 2
#include "SpriteBird.h"
UINT8 bank_SPRITE_BIRD = 2;

#include "ZGBMain.h"
#include "SpriteManager.h" 
#include "Keys.h"
#include "Trig.h"
#include "Scroll.h"

UINT8 anim_flying[] = {3, 0, 1, 2};

struct SpriteBirdData {
	INT8 ang;
};

void Start_SPRITE_BIRD() {
	struct  SpriteBirdData* data = (struct  SpriteBirdData*) THIS->custom_data;
	data->ang = (scroll_target->x < THIS->x) ? 128 :0;

	THIS->lim_x = 64;
	SetSpriteAnim(THIS, anim_flying, 13);
}

void Update_SPRITE_BIRD() {
	struct  SpriteBirdData* data = (struct  SpriteBirdData*) THIS->custom_data;
	INT16 prev_x = THIS->x;
	
	THIS->x -= (INT8)(SIN(data->ang) >> 2);
	data->ang += 1 << delta_time;
	THIS->x += (INT8)(SIN(data->ang) >> 2);

	if(THIS->x > prev_x) {
		THIS->flags = 0;
	} else if(THIS->x != prev_x) {
		THIS->flags = OAM_VERTICAL_FLAG;
	}
}

void Destroy_SPRITE_BIRD() {
}