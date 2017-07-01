#pragma bank 2
#include "SpritePlayer.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Keys.h"

const UINT8 sin[] = {
	128,131,134,137,140,143,146,149,
	152,156,159,162,165,168,171,174,
	176,179,182,185,188,191,193,196,
	199,201,204,206,209,211,213,216,
	218,220,222,224,226,228,230,232,
	234,235,237,239,240,242,243,244,
	246,247,248,249,250,251,251,252,
	253,253,254,254,254,255,255,255,
	255,255,255,255,254,254,253,253,
	252,252,251,250,249,248,247,246,
	245,244,242,241,239,238,236,235,
	233,231,229,227,225,223,221,219,
	217,215,212,210,207,205,202,200,
	197,195,192,189,186,184,181,178,
	175,172,169,166,163,160,157,154,
	151,148,145,142,138,135,132,129,
	126,123,120,117,113,110,107,104,
	101,98,95,92,89,86,83,80,
	77,74,71,69,66,63,60,58,
	55,53,50,48,45,43,40,38,
	36,34,32,30,28,26,24,22,
	20,19,17,16,14,13,11,10,
	9,8,7,6,5,4,3,3,
	2,2,1,1,0,0,0,0,
	0,0,0,1,1,1,2,2,
	3,4,4,5,6,7,8,9,
	11,12,13,15,16,18,20,21,
	23,25,27,29,31,33,35,37,
	39,42,44,46,49,51,54,56,
	59,62,64,67,70,73,76,79,
	81,84,87,90,93,96,99,103,
	106,109,112,115,118,121,124,128
};

#define SIN(A) (sin[0xFF & A] - 128)
#define COS(A) (sin[0xFF & (A - 64)] - 128)

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

void ChangeState(SheepState next);
void Start_SPRITE_PLAYER() {
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
			crossHair = SpriteManagerAdd(SPRITE_CROSSHAIR, THIS->x, THIS->y);
			break;
	}
}

void Update_SPRITE_PLAYER() {
	switch(sheep_state) {
		case AIMING:
			sheepAng += 2 << delta_time;
			crossHair->x = THIS->x - 4 + 8 + (SIN(sheepAng) >> 3); //-4 to center the cross, +8 to center in the sprite
			crossHair->y = THIS->y - 4 + 8 + (COS(sheepAng) >> 3);

			if(KEY_TICKED(J_A)) {
				ChangeState(FLYING);
			}

			if(KEY_PRESSED(J_LEFT)) {
				THIS->x --;
			}
			if(KEY_PRESSED(J_RIGHT)) {
				THIS->x ++;
			}
			break;

		case FLYING:
			accum_x.w += SIN(sheepAng) << 2;
			accum_y.w += COS(sheepAng) << 2;
			if(TranslateSprite(THIS, accum_x.b.h, accum_y.b.h)) {
				ChangeState(AIMING);
			}
			accum_x.b.h = 0;
			accum_y.b.h = 0;
			break;
	}
}

void Destroy_SPRITE_PLAYER() {
}