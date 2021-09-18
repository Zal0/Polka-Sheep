#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"
#include "Trig.h"

UINT8 anim_idle_bubble[] = {8, 0, 0, 0, 1, 0, 0, 0, 0};

typedef struct {
	UINT16 x;
	UINT16 y;
	UINT8 sin;
} CUSTOM_DATA;

void START() {
	CUSTOM_DATA* data = (CUSTOM_DATA*) THIS->custom_data;
	data->x = THIS->x;
	data->y = THIS->y;
	data->sin = 0;

	SetSpriteAnim(THIS, anim_idle_bubble, 6);
}

void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*) THIS->custom_data;

	THIS->x = data->x;
	THIS->y = data->y;

	data->sin += 1 << delta_time;
	THIS->x += SIN(data->sin) >> 7;
	THIS->y += COS(data->sin << 1) >> 6;
}

void DESTROY() {
}