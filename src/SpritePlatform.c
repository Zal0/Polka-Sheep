#pragma bank 2
#include "SpritePlatform.h"
UINT8 bank_SPRITE_PLATFORM = 2;

#include "SpriteManager.h"
#include "Scroll.h"
#include "Print.h"
#include "Math.h"

#include "Print.h"

#define START_TILE 19u

struct PlatformCustomData {
	INT8 vx, vy;
	INT8 frame_accum;
};

void Start_SPRITE_PLATFORM() {
	UINT16 tile_x = THIS->x >> 3;
	UINT16 tile_y = THIS->y >> 3;
	UINT16 tile;

	struct PlatformCustomData* data = (struct PlatformCustomData*)THIS->custom_data;
	data->frame_accum = 0;

	tile = GetScrollTile(tile_x + 1, tile_y + 1);
	if(U_LESS_THAN(START_TILE - 1 , tile) && U_LESS_THAN(tile, START_TILE + 6)) {
		data->vy = -1;
		data->vx =  0;
		THIS->x += 4;
	} else {
		tile = GetScrollTile(tile_x - 1, tile_y + 1);
		if(U_LESS_THAN(START_TILE - 1 , tile) && U_LESS_THAN(tile, START_TILE + 6)) {
			data->vy = 1;
			data->vx = 0;
			THIS->x -= 12;
		} else {
			tile = GetScrollTile(tile_x, tile_y + 2);
			if(U_LESS_THAN(START_TILE - 1 , tile) && U_LESS_THAN(tile, START_TILE + 6)) {
				data->vy =  0;
				data->vx = -1;
				THIS->y += 12;
			} else {
				tile = GetScrollTile(tile_x, tile_y);
				if(U_LESS_THAN(START_TILE - 1 , tile) && U_LESS_THAN(tile, START_TILE + 6)) {
					data->vy = 0;
					data->vx = 1;
					THIS->y -= 4;
				}
			}
		}
	}

	THIS->coll_y = 5;
	THIS->coll_h = 6;
	THIS->lim_x = 100u;
	THIS->lim_y = 100u;
}

extern struct Sprite* player_parent;

void Update_SPRITE_PLATFORM() {
	struct PlatformCustomData* data = (struct PlatformCustomData*)THIS->custom_data;
	struct Sprite* sprite = THIS;
	UINT8 offset_x = 8;
	UINT8 offset_y = 8;
	UINT8 tile;
	UINT16 old_x, old_y;

	data->frame_accum += 8;
	old_x = sprite->x;
	old_y = sprite->y;
	while((data->frame_accum >> 4) > 1) {
		data->frame_accum -= 1 << 4;
	
		sprite->x += (INT16)data->vx;
		sprite->y += (INT16)data->vy;

		if(data->vy != 0 && (0x7 & (sprite->y + offset_y)) == 4) {
			tile = GetScrollTile((sprite->x + offset_x) >> 3, (sprite->y + offset_y) >> 3);
			switch(tile) {
				case START_TILE + 2:
				case START_TILE + 3:
					data->vx = -1;
					data->vy = 0;
					break;

				case START_TILE + 4:
				case START_TILE + 5:
					data->vx = 1;
					data->vy = 0;
					break;
			}
		}else if(data->vx != 0 && (0x7 & (sprite->x + offset_x)) == 4) {
			tile = GetScrollTile((sprite->x + offset_x) >> 3, (sprite->y + offset_y) >> 3);
			switch(tile) {
				case START_TILE + 2:
				case START_TILE + 4:
					data->vx = 0;
					data->vy = 1;
					break;

				case START_TILE + 3:
				case START_TILE + 5:
					data->vx =  0;
					data->vy = -1;
					break;
			}
		}
	}

	if(player_parent == THIS) {
		scroll_target->x += sprite->x - old_x;
		scroll_target->y += sprite->y - old_y;
		RefreshScroll();
	}
}

void Destroy_SPRITE_PLATFORM() {
}