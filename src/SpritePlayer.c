#pragma bank 2
#include "SpritePlayer.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "Trig.h"

extern INT8 gravity;

UINT8 anim_idle[]   = {2, 0, 1};
UINT8 anim_flying_r[] = {8, 2, 3, 4, 5, 6, 7, 8, 9};
UINT8 anim_flying_l[] = {8, 9, 8, 7, 6, 5, 4, 3, 2};

struct Sprite* crossHair;
UINT8 sheepAng;
typedef enum {
	AIMING,
	FLYING, 
	NONE
} SheepState;
SheepState sheep_state;
fixed accum_x;
fixed accum_y;
INT16 speed_x;
INT16 speed_y;

void ChangeState(SheepState next);
void Start_SPRITE_PLAYER() {
	THIS->lim_y = 255;
	THIS->coll_x = 5;
	THIS->coll_w -= 10;
	THIS->coll_y = 8;
	THIS->coll_h = 8;

	sheep_state = NONE;
	ChangeState(AIMING);
}

void ChangeState(SheepState next) {
	switch (sheep_state) {
		case AIMING:
			SpriteManagerRemoveSprite(crossHair);
			break;
	}

	sheep_state = next;

	switch (next) {
		case AIMING:
			sheepAng = speed_x > 0 ? 64 : -64;
			crossHair = SpriteManagerAdd(SPRITE_CROSSHAIR, THIS->x, THIS->y);
			SetSpriteAnim(THIS, anim_idle, 5);
			break;

		case FLYING:
			SetSpriteAnim(THIS, speed_x > 0 ? anim_flying_r : anim_flying_l, 25);
			break;
	}
}

void Update_SPRITE_PLAYER() {
	UINT16 prev_x;
	UINT16 prev_y;
	UINT8 coll_tile;
	switch(sheep_state) {
		case AIMING:
			sheepAng += (speed_x > 0 ? -2 : 2) << delta_time;
			crossHair->x = THIS->x - 4 + 8 + (SIN(sheepAng) >> 3); //-4 to center the cross, +8 to center in the sprite
			crossHair->y = THIS->y - 4 + 8 + (COS(sheepAng) >> 3);

			if(KEY_TICKED(J_A)) {
				speed_x = SIN(sheepAng) << 2;
				speed_y = COS(sheepAng) << 3;
				ChangeState(FLYING);
			}

#ifndef NDEBUG
			if(KEY_PRESSED(J_LEFT)) {
				TranslateSprite(THIS, -1, 0);
			}
			if(KEY_PRESSED(J_RIGHT)) {
				TranslateSprite(THIS, 1, 0);
			}
			if(KEY_PRESSED(J_UP)) {
				TranslateSprite(THIS, 0, -1);
			}
			if(KEY_PRESSED(J_DOWN)) {
				TranslateSprite(THIS, 0, 1);
			}
#endif
			break;

		case FLYING:
			accum_x.w += speed_x;
			accum_y.w += speed_y;
			
			speed_y += gravity;
			
			prev_x = THIS->x;
			prev_y = THIS->y;
			coll_tile = TranslateSprite(THIS, accum_x.b.h, accum_y.b.h);
			if(coll_tile) {
				if((prev_y + (INT8)accum_y.b.h) > THIS->y || (coll_tile > 6 && coll_tile < 15)) {
					if((prev_x + (INT8)accum_x.b.h) != THIS->x) {
						speed_x = -speed_x;
					}

					ChangeState(AIMING);
				} 
			}
			accum_x.b.h = 0;
			accum_y.b.h = 0;
			break;
	}
}

void Destroy_SPRITE_PLAYER() {
}