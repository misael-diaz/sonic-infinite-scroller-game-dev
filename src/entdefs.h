#ifndef SONIC_INFINITE_SCROLLER_GAME_DEV_ENTDEFS_H
#define SONIC_INFINITE_SCROLLER_GAME_DEV_ENTDEFS_H

#include "gmdefs.h"

#define EN_MAXNUMOF_ENT 5
#define EN_CAMERA_ID 0
#define EN_SONIC_ID 1
#define EN_PLATFORM_BETA_ID 2
#define EN_PLATFORM_ZETA_ID 3
#define EN_ENEMY_MOTOBUG_ID 4

#define EN_ENVIEW_NUMFACES 4

/* if a property is set to this that means that it has no meaning for that entity */

#define EN_IGNORE_PROPERTY 0

/*

E: East,  aligned with the screen +x-axis
N: Nort,  aligned with the screen +y-axis
W: West,  aligned with the screen -x-axis
S: South, aligned with the screen -y-axis

*/

#define EN_ENVIEW_E 0
#define EN_ENVIEW_N 1
#define EN_ENVIEW_W 2
#define EN_ENVIEW_S 3

#define EN_ANIMATIONS_COUNT 2
#define EN_AFRAME_COUNT 8

#define EN_CAMERA_DEFAULT_AN 0
#define EN_CAMERA_DEFAULT_AF 0

#define EN_SONIC_RUN_AN 0
#define EN_SONIC_SPIN_AN 1
#define EN_SONIC_DEFAULT_AF 0

#define EN_PLATFORM_DEFAULT_AN 0
#define EN_PLATFORM_DEFAULT_AF 0

#define EN_ENEMY_MOTOBUG_DEFAULT_AN 0
#define EN_ENEMY_MOTOBUG_DEFAULT_AF 0
#define EN_ENEMY_MOTOBUG_RUN_AN 0
#define EN_ENEMY_MOTOBUG_EXPLODE_AN 1

#define EN_PLATFORM_AFRAME_COUNT 1
#define EN_SONIC_AFRAME_COUNT EN_AFRAME_COUNT
#define EN_SONIC_ANIMATIONS_COUNT EN_ANIMATIONS_COUNT
#define EN_ENEMY_MOTOBUG_ANIMATIONS_COUNT EN_ANIMATIONS_COUNT
#define EN_ENEMY_MOTOBUG_AFRAME_COUNT 5 
_Static_assert(EN_SONIC_AFRAME_COUNT == EN_AFRAME_COUNT, "UXAframeCountError");

#define EN_SONIC_RUN_FRAME_NAME "run"
#define EN_SONIC_SPIN_FRAME_NAME "spin"
#define EN_PLATFORM_FRAME_NAME "scroll"
#define EN_ENEMY_MOTOBUG_RUN_FRAME_NAME "bobbing"
#define EN_ENEMY_MOTOBUG_EXPLODE_FRAME_NAME "exploding"
#define EN_CAMERA_FRAME_NAME "hover"

#endif

/*

sonic-infinite-scroller-game-dev                                 May 23, 2025

author: @misael-diaz
source: src/endefs.h

Copyright (C) 2025 Misael Diaz-Maldonado

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 2 only of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/
