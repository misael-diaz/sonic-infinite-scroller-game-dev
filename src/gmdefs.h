#ifndef SONIC_INFINITE_SCROLLER_GAME_DEV_GAME_DEFS_H
#define SONIC_INFINITE_SCROLLER_GAME_DEV_GAME_DEFS_H

#define GAME_FRAMERATE_HZ 60.0f
#define GAME_PERIOD_SEC (1.0f / GAME_FRAMERATE_HZ)
#define GAME_PERIOD_NS ((1.0e9f * (1.0f / GAME_FRAMERATE_HZ)))

#define GAME_ERROR_RC 1

#define GAME_INITED_GW 1

#define GAME_LOADED_GRAPHIC 1
#define GAME_BINDED_GRAPHIC 1

#define GAME_CAMERA_VIEW_WIDTH 2560
#define GAME_CAMERA_VIEW_HEIGHT 1440

#define GAME_CAMERA_WIDTH 32
#define GAME_CAMERA_HEIGHT 32

#define GAME_CAMERA_VISIBLE 1
#define GAME_CAMERA_NOGRAPHIC_FP "nographic"
#define GAME_SONIC_GRAPHIC_FP "public/graphics/sonic.png"
#define GAME_PLATFORM_GRAPHIC_FP "public/graphics/platform.png"
#define GAME_ENEMY_MOTOBUG_GRAPHIC_FP "public/graphics/motobug.png"

#define GAME_SONIC_RUN_ANIMATION_DURATION 0.0625f
#define GAME_SONIC_SPIN_ANIMATION_DURATION 0.03125f
#define GAME_ENEMY_MOTOBUG_RUN_ANIMATION_DURATION 0.125f
#define GAME_ENEMY_MOTOBUG_EXPLODE_ANIMATION_DURATION 0.5f

#define GAME_SONIC_XVEL 1000
#define GAME_SONIC_YVEL 0
#define GAME_CAMERA_XVEL GAME_SONIC_XVEL
#define GAME_CAMERA_YVEL GAME_SONIC_YVEL
#define GAME_CAMERA_CATCHUP_YVEL 200
#define GAME_PLATFORM_XVEL 0
#define GAME_PLATFORM_YVEL 0
#define GAME_ENEMY_MOTOBUG_XVEL 0
#define GAME_ENEMY_MOTOBUG_YVEL 0

#define GAME_PLATFORM_SHIFT_YPOS 2400

#define GAME_SONIC_JUMP_VEL 2300

/* if set sonic is in contact with a platform (has no meaning for other entities) */

#define GAME_SONIC_FALLING 1
#define GAME_PLATFORM_CONTACT 1
#define GAME_ENEMY_EXPLODE 1

#define GAME_GRAVITY_ACCELERATION 4000

#define GAME_SUPPORTED_PROTOCOLS_NUM 2
#define GAME_PROTOCOL_ID 0
#define GAME_DELETE_WINDOW_ID 1
#define GAME_PROTOCOL_NM "WM_PROTOCOLS"
#define GAME_DELETE_WINDOW_NM "WM_DELETE_WINDOW"
_Static_assert(8 == sizeof(long), "UXLongIntSizeError");

#endif

/*

sonic-infinite-scroller-game-dev                                 May 23, 2025

author: @misael-diaz
source: src/game.h

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
