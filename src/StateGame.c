#pragma bank 2
#include "StateGame.h"
UINT8 bank_STATE_GAME = 2;

#include "..\res\src\font.h"
#include "..\res\src\tiles.h"
#include "..\res\src\map.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"

UINT8 collisions[] = {1, 0};

extern UINT8 n_sprite_types;
void Start_STATE_GAME() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 50, 50);

	InitScrollTiles(0, 8, tiles, 3);
	InitScroll(mapWidth, mapHeight, map, collisions, 0, 3);
	SHOW_BKG;

	INIT_CONSOLE(font, 3, 2);
}

void Update_STATE_GAME() {
}