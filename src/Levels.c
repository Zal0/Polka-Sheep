#pragma bank 2
#include "Levels.h"
#include "main.h"

IMPORT_MAP(maplevel1);
IMPORT_MAP(maplevellobo);
IMPORT_MAP(maplevelpajaro);
IMPORT_MAP(maplevelpuzzlesencilloylobo);
IMPORT_MAP(maplevelsubida);
IMPORT_MAP(maplevelpinchosabajo);
IMPORT_MAP(maplevelplataformashorizontal);
IMPORT_MAP(maplevelplataformaslobopajaro);
IMPORT_MAP(maplevelsubidapajaritos);
IMPORT_MAP(maplevelescondrijo);
IMPORT_MAP(mapleveldospisos);
IMPORT_MAP(maplevelsubidapro);
IMPORT_MAP(maplevelsubidapinchos);

#define BANKED_MAP(MAP) {BANK(MAP), &MAP}

const struct MapInfoBanked levels[] = {
	BANKED_MAP(maplevel1),
	BANKED_MAP(maplevellobo),
	BANKED_MAP(maplevelpuzzlesencilloylobo),
	BANKED_MAP(maplevelpajaro),
	BANKED_MAP(maplevelsubida),
	BANKED_MAP(maplevelplataformashorizontal),
	BANKED_MAP(maplevelpinchosabajo),
	BANKED_MAP(maplevelplataformaslobopajaro),
	BANKED_MAP(maplevelsubidapinchos),
	BANKED_MAP(maplevelsubidapajaritos),
	BANKED_MAP(maplevelescondrijo),
	BANKED_MAP(mapleveldospisos),
	BANKED_MAP(maplevelsubidapro),
};

UINT8 current_level = 0;
const UINT8 num_levels = 13;