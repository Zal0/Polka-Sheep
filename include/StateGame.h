#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "main.h"

typedef struct LevelInfo {
	UINT16 w;
	UINT16 h;
	UINT8* map;
	UINT8 bank;
};

DECLARE_STATE(STATE_GAME);

#endif