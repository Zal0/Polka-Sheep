#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES        \
_STATE(StateGame)     \
_STATE(StateMenu)     \
_STATE(StateGameOver) \
_STATE(StateGameEnd)  \
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer,      player     ) \
_SPRITE_DMG(SpriteCrosshair,   crossair   ) \
_SPRITE_DMG(SpriteBird,        bird       ) \
_SPRITE_DMG(SpriteWolf,        wolf       ) \
_SPRITE_DMG(SpritePolkaMan,    polkaman   ) \
_SPRITE_DMG(SpriteLife,        life       ) \
_SPRITE_DMG(SpritePlatform,    platform   ) \
_SPRITE_DMG(SpriteBubble,      bubble     ) \
_SPRITE_DMG(SpritePop,         pop        ) \
_SPRITE_DMG(SpriteFriendSheep, friendsheep) \
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif