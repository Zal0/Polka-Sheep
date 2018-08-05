#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES         \
_STATE(STATE_GAME)     \
_STATE(STATE_MENU)     \
_STATE(STATE_GAMEOVER) \
_STATE(STATE_GAMEEND)  \
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SPRITE_PLAYER,      player,      3, FRAME_16x16, 12) \
_SPRITE_DMG(SPRITE_CROSSHAIR,   crossair,    3, FRAME_8x16,   1) \
_SPRITE_DMG(SPRITE_BIRD,        bird,        3, FRAME_16x16,  3) \
_SPRITE_DMG(SPRITE_WOLF,        wolf,        3, FRAME_16x16,  4) \
_SPRITE_DMG(SPRITE_POLKAMAN,    polkaman,    3, FRAME_16x16,  6) \
_SPRITE_DMG(SPRITE_LIFE,        life,        3, FRAME_8x16,   2) \
_SPRITE_DMG(SPRITE_PLATFORM,    platform,    3, FRAME_16x16,  1) \
_SPRITE_DMG(SPRITE_BUBBLE,      bubble,      3, FRAME_16x16,  2) \
_SPRITE_DMG(SPRITE_POP,         pop,         3, FRAME_16x16,  2) \
_SPRITE_DMG(SPRITE_FRIENDSHEEP, friendsheep, 3, FRAME_16x16,  2) \
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif