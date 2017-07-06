#pragma bank 1
#include "ZGBMain.h"
UINT8 init_bank = 1;


#include "StateGame.h"
#include "StateMenu.h"
#include "StateGameOver.h"
#include "StateGameEnd.h"

#include "SpritePlayer.h"
#include "SpriteBird.h"
#include "SpriteCrosshair.h"
#include "SpriteWolf.h"
#include "SpritePolkaman.h"
#include "SpriteLife.h"
#include "SpritePlatform.h"
#include "SpriteBubble.h"
#include "SpritePop.h"
#include "SpriteFriendSheep.h"

#include "../res/src/player.h"
#include "../res/src/bird.h"
#include "../res/src/crossair.h"
#include "../res/src/wolf.h"
#include "../res/src/polkaman.h"
#include "../res/src/life.h"
#include "../res/src/platform.h"
#include "../res/src/bubble.h"
#include "../res/src/pop.h"
#include "../res/src/friendsheep.h"

UINT8 next_state = STATE_MENU;//STATE_GAME;

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	INIT_STATE(STATE_GAME);
	INIT_STATE(STATE_MENU);
	INIT_STATE(STATE_GAMEOVER);
	INIT_STATE(STATE_GAMEEND);
}

void InitSprites() {
	INIT_SPRITE(SPRITE_PLAYER, player, 3, FRAME_16x16, 12);
	INIT_SPRITE(SPRITE_CROSSHAIR, crossair, 3, FRAME_8x16, 1);
	INIT_SPRITE(SPRITE_BIRD, bird, 3, FRAME_16x16, 3);
	INIT_SPRITE(SPRITE_WOLF, wolf, 3, FRAME_16x16, 4);
	INIT_SPRITE(SPRITE_POLKAMAN, polkaman, 3, FRAME_16x16, 6);
	INIT_SPRITE(SPRITE_LIFE, life, 3, FRAME_8x16, 2);
	INIT_SPRITE(SPRITE_PLATFORM, platform, 3, FRAME_16x16, 1);

	INIT_SPRITE(SPRITE_BUBBLE, bubble, 3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_POP, pop, 3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_FRIENDSHEEP, friendsheep, 3, FRAME_16x16, 2);
}