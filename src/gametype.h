#ifndef SONIC_INFINITE_SCROLLER_GAME_DEV_GAMETYPE_H
#define SONIC_INFINITE_SCROLLER_GAME_DEV_GAMETYPE_H

#include <X11/Xlib.h>
#include "entype.h"

enum gmode {
	GAME_GAME_MODE,
	GAME_VIEW_MODE,
	GAME_AUTO_MODE,
	GAME_MODE_MAX,
};
_Static_assert(0 == GAME_GAME_MODE, "GameGameModeError");
_Static_assert(1 == GAME_VIEW_MODE, "GameViewModeError");
_Static_assert(2 == GAME_AUTO_MODE, "GameAutoModeError");

struct game {
	struct entity ents[EN_ENT_MAX];
	int platform_ids[EN_PLATFORM_MAX];
	int enemy_ids[EN_ENEMY_MAX];
	int block_ids[EN_BLOCK_MAX];
	int modes[GAME_MODE_MAX];
	char const * const ent_names[EN_ENT_MAX];
	char *supported_protocols[GAME_SUPPORTED_PROTOCOLS_NUM];
	Atom protocols[GAME_SUPPORTED_PROTOCOLS_NUM];
	char const *error;
	Display *display;
	Window window;
	Screen *screen;
	Visual *visual;
	XImage *framebuffers[EN_ENT_MAX];
	Colormap colormap;
	XColor red;
	XColor green;
	XColor blue;
	XColor gray;
	GC gc;
	int screen_width;
	int screen_height;
	int screen_depth;
	int protocolno;
	int sorted_platforms;
	int oldframeno;
	int platformno;
	int enemyno;
	int screeno;
	int frameno;
	int entno;
	int modeno;
	int mode;
	int init;
};

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
