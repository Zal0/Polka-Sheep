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
#include "../res/src/maplevelsubidapajaritos.h"
#include "../res/src/maplevelescondrijo.h"
#include "../res/src/mapleveldospisos.h"
#include "../res/src/maplevelsubidapro.h"
#include "../res/src/maplevelsubidapinchos.h"

#define LEVEL(A, BANK) A##Width, A##Height, A, BANK
const struct LevelInfo levels[] = {
	{LEVEL(maplevel1,                     3)},
	{LEVEL(maplevellobo,                  3)},
	{LEVEL(maplevelpuzzlesencilloylobo,   3)},
	{LEVEL(maplevelpajaro,                3)},
	{LEVEL(maplevelsubida,                3)},
	{LEVEL(maplevelplataformashorizontal, 5)},
	{LEVEL(maplevelpinchosabajo,          5)},
	{LEVEL(maplevelplataformaslobopajaro, 5)},
	{LEVEL(maplevelsubidapinchos,		  5)},
	{LEVEL(maplevelsubidapajaritos,       5)},
	{LEVEL(maplevelescondrijo,		      5)},
	{LEVEL(mapleveldospisos,		      5)},
	{LEVEL(maplevelsubidapro,		      5)},
};

UINT8 current_level = 0;
const UINT8 num_levels = 13;