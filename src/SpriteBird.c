#include "Banks/SetAutoBank.h"
#include "main.h"

#include "ZGBMain.h"
#include "SpriteManager.h" 
#include "Keys.h"
#include "Trig.h"
#include "Scroll.h"

UINT8 anim_flying[] = {3, 0, 1, 2};

struct SpriteBirdData {
	INT8 ang;
};

void Start_SpriteBird() {
	struct  SpriteBirdData* data = (struct  SpriteBirdData*) THIS->custom_data;
	data->ang = (scroll_target->x < THIS->x) ? 128 :0;

	THIS->lim_x = 64;
	SetSpriteAnim(THIS, anim_flying, 13);
}

void Update_SpriteBird() {
	struct  SpriteBirdData* data = (struct  SpriteBirdData*) THIS->custom_data;
	INT16 prev_x = THIS->x;
	
	THIS->x -= (INT8)(SIN(data->ang) >> 2);
	data->ang += 1 << delta_time;
	THIS->x += (INT8)(SIN(data->ang) >> 2);

	if(THIS->x > prev_x) {
		THIS->mirror = NO_MIRROR;
	} else if(THIS->x != prev_x) {
		THIS->mirror = V_MIRROR;
	}
}

void Destroy_SpriteBird() {
}