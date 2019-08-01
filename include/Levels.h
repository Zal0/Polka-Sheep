#ifndef LEVELS_H
#define LEVELS_H

#include "main.h"

typedef struct LevelInfo {
	UINT16 w;
	UINT16 h;
	struct MapInfo* map;
};

#endif