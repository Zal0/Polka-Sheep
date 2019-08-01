#pragma bank 2
#include "Levels.h"

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

#define LEVEL(A) A##Width, A##Height, &A
const struct LevelInfo levels[] = {
	{LEVEL(maplevel1)},
	{LEVEL(maplevellobo)},
	{LEVEL(maplevelpuzzlesencilloylobo)},
	{LEVEL(maplevelpajaro)},
	{LEVEL(maplevelsubida)},
	{LEVEL(maplevelplataformashorizontal)},
	{LEVEL(maplevelpinchosabajo)},
	{LEVEL(maplevelplataformaslobopajaro)},
	{LEVEL(maplevelsubidapinchos)},
	{LEVEL(maplevelsubidapajaritos)},
	{LEVEL(maplevelescondrijo)},
	{LEVEL(mapleveldospisos)},
	{LEVEL(maplevelsubidapro)},
};

UINT8 current_level = 0;
const UINT8 num_levels = 13;