#pragma bank 2
#include "SpritePlayer.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "Trig.h"
#include "Print.h"
#include "Math.h"
#include "Vector.h"

extern const INT8 gravity;

UINT8 anim_idle[]   = {2, 0, 1};
UINT8 anim_flying_r[] = {8, 2, 3, 4, 5, 6, 7, 8, 9};
UINT8 anim_flying_l[] = {8, 9, 8, 7, 6, 5, 4, 3, 2};

struct Sprite* crossHair;
UINT8 sheepAngStart = 64;
UINT8 sheepAngOffset = 0;
INT8 sheepIncr = 1;

extern UINT8 lifes_y[];

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

extern const UINT8 max_energy;
UINT8 current_energy;

extern const INT8 inmunity_time;
INT16 inmunity = 0;


const UINT8 HEART_TILE = 1;
const UINT8 EMPTY_HEART_TILE = 2;
void RefreshLife() {
	UINT8 i;

	for(i = 0; i != current_energy; ++i) {
		set_win_tiles(10 + i, 1, 1, 1, &HEART_TILE);
	}
	for(; i != max_energy; ++i) {
		set_win_tiles(10 + i, 1, 1, 1, &EMPTY_HEART_TILE);
	}
}

void ChangeState(SheepState next);
void Start_SPRITE_PLAYER() {
	THIS->lim_y = 255;
	THIS->coll_x = 5;
	THIS->coll_w -= 10;
	THIS->coll_y = 8;
	THIS->coll_h = 8;

	sheep_state = NONE;
	ChangeState(AIMING);

	current_energy = max_energy;
	RefreshLife();

	sheepAngStart = 192;
	sheepAngOffset = 64;
	sheepIncr = 2;
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
			crossHair = SpriteManagerAdd(SPRITE_CROSSHAIR, THIS->x, THIS->y);
			SetSpriteAnim(THIS, anim_idle, 5);
			break;

		case FLYING:
			SetSpriteAnim(THIS, speed_x > 0 ? anim_flying_r : anim_flying_l, 25);
			break;
	}
}

void Hit() {
	if(inmunity == 0) {
			current_energy--;
			RefreshLife();
			if(current_energy == 0) {
				SetState(STATE_GAME);
			} else {
				THIS->flags = 1 << 4;
				inmunity = inmunity_time;
			}
	}
}

void Update_SPRITE_PLAYER() {
	UINT16 expected_x;
	UINT16 expected_y;
	UINT8 coll_tile;
	UINT8 i;
	struct Sprite* spr;
	UINT8 sheepAng;

	switch(sheep_state) {
		case AIMING:
			sheepAngOffset += sheepIncr << delta_time;
			if(sheepIncr == 2 && sheepAngOffset > 128) {
				sheepIncr = -2;
				sheepAngOffset = 127;
			}
			if(sheepIncr == -2 && (0x80 & sheepAngOffset)) {
				sheepIncr = 2;
				sheepAngOffset = 0;
			}
			sheepAng = sheepAngStart + sheepAngOffset;

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
			
			if(speed_y < 1024) {
				speed_y += gravity;
			}
			
			expected_x = (THIS->x + (INT8)accum_x.b.h);
			expected_y = (THIS->y + (INT8)accum_y.b.h);
			coll_tile = TranslateSprite(THIS, accum_x.b.h, accum_y.b.h);
			if(coll_tile) {
				if(coll_tile == 18) {
					Hit();
				}

				if(expected_y > THIS->y || (coll_tile > 6 && coll_tile < 18)) {
					
					//Adjust crosshair
					sheepAngOffset = 64;
					if(expected_x != THIS->x) {
						if(expected_x > THIS->x) {
							sheepAngStart = 128;
							sheepIncr = 2;
						} else {
							sheepAngStart = 0;
							sheepIncr = -2;
						}
					} else if(expected_y != THIS->y) { 
						if(expected_y > THIS->y) {
							sheepAngStart = 192;
							
							//Look on the current direction
							if(speed_x > 0) {
								sheepAngOffset = 128;
							} else {
								sheepAngOffset = 0;
							}

						} else if(expected_y < THIS->y) {
							sheepAngStart = 64;
						}
					}
					

					ChangeState(AIMING);
				} else {
					if(speed_y < 0 && (expected_y != THIS->y)) {
						speed_y = 0;
					}
				}
			}
			accum_x.b.h = 0;
			accum_y.b.h = 0;
			break;
	}

	if(inmunity == 0) {
		SPRITEMANAGER_ITERATE(i, spr) {
			if(CheckCollision(THIS, spr)) {
				if(spr->type == SPRITE_BIRD || spr->type == SPRITE_WOLF) {
					Hit();
				} else if(spr->type == SPRITE_LIFE) {
					SpriteManagerRemove(i);

					VectorAdd(lifes_y, spr->y >> 3);

					if(current_energy != max_energy) {
						current_energy++;
						RefreshLife();
					}
				}
			}
		}
	} else {
		inmunity -= (1 << delta_time);
		if(inmunity < 1) {
			inmunity = 0;
			THIS->flags = 0;

			if(sheep_state == AIMING && sheepAngStart == 192) {
				if(TranslateSprite(THIS, 0, 1) == 18) {
					Hit();
				}
			}
		}
	}
}

void Destroy_SPRITE_PLAYER() {
}