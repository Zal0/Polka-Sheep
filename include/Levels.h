#ifndef LEVELS_H
#define LEVELS_H

#include "main.h"

typedef struct LevelInfo {
	UINT16 w;
	UINT16 h;
	UINT8* map;
	UINT8 bank;
};

#endif