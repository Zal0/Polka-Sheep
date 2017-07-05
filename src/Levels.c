#pragma bank 2
#include "StateGame.h"

#include "../res/src/maplevel1.h"
#include "../res/src/maplevellobo.h"
#include "../res/src/maplevelpajaro.h"
#include "../res/src/maplevelpuzzlesencilloylobo.h"
#include "../res/src/maplevelsubida.h"
#include "../res/src/maplevelpinchosabajo.h"
#include "../res/src/maplevelplataformashorizontal.h"
#include "../res/src/maplevelplataformaslobopajaro.h"

#define LEVEL(A, BANK) A##Width, A##Height, A, BANK
const struct LevelInfo levels[] = {
	{LEVEL(maplevel1,                     3)},
	{LEVEL(maplevellobo,                  3)},
	{LEVEL(maplevelpajaro,                3)},
	{LEVEL(maplevelpuzzlesencilloylobo,   3)},
	{LEVEL(maplevelsubida,                3)},
	{LEVEL(maplevelpinchosabajo,          5)},
	{LEVEL(maplevelplataformashorizontal, 5)},
	{LEVEL(maplevelplataformaslobopajaro, 5)},
};

UINT8 current_level = 0;