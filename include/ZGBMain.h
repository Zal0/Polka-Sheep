#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES         \
_STATE(STATE_GAME)     \
_STATE(STATE_MENU)     \
_STATE(STATE_GAMEOVER) \
_STATE(STATE_GAMEEND)  \
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SPRITE_PLAYER,      player     ) \
_SPRITE_DMG(SPRITE_CROSSHAIR,   crossair   ) \
_SPRITE_DMG(SPRITE_BIRD,        bird       ) \
_SPRITE_DMG(SPRITE_WOLF,        wolf       ) \
_SPRITE_DMG(SPRITE_POLKAMAN,    polkaman   ) \
_SPRITE_DMG(SPRITE_LIFE,        life       ) \
_SPRITE_DMG(SPRITE_PLATFORM,    platform   ) \
_SPRITE_DMG(SPRITE_BUBBLE,      bubble     ) \
_SPRITE_DMG(SPRITE_POP,         pop        ) \
_SPRITE_DMG(SPRITE_FRIENDSHEEP, friendsheep) \
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif