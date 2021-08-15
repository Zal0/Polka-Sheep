#ifndef LEVELS_H
#define LEVELS_H

#include <gb/gb.h>
#include "MapInfo.h"

struct MapInfoBanked {
	UINT8 bank;
	struct MapInfo* map;
};

#endif