#pragma bank 2
#include <gb/gb.h>
#include "MapInfo.h"

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

const struct MapInfo* levels[] = {
	&maplevel1,
	&maplevellobo,
	&maplevelpuzzlesencilloylobo,
	&maplevelpajaro,
	&maplevelsubida,
	&maplevelplataformashorizontal,
	&maplevelpinchosabajo,
	&maplevelplataformaslobopajaro,
	&maplevelsubidapinchos,
	&maplevelsubidapajaritos,
	&maplevelescondrijo,
	&mapleveldospisos,
	&maplevelsubidapro,
};

UINT8 current_level = 0;
const UINT8 num_levels = 13;