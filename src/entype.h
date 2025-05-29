#ifndef SONIC_INFINITE_SCROLLER_GAME_DEV_ENTYPE_H
#define SONIC_INFINITE_SCROLLER_GAME_DEV_ENTYPE_H

#include <X11/Xlib.h>
#include "entdefs.h"
#include "graphictype.h"
#include "animationtype.h"

/* entity tags */

enum entag {
	EN_SONIC_TAG,
	EN_ENEMY_TAG,
	EN_PLATFORM_TAG,
	EN_MAXNUMOF_TAG
};

// animations can share graphics this is why they are not nested in the animation struct
struct entity {
	enum entag tag;
	int id;
	struct graphic graphic;
	struct animation animations[EN_ANIMATIONS_COUNT];
	XImage *framebuffer;
	float xpos;
	float ypos;
	float xoff;
	float yoff;
	float xvis;
	float yvis;
	float xvel;
	float yvel;
	float xmin;
	float ymin;
	float xmax;
	float ymax;
	float width;
	float height;
	int contact;
	int frameno;
	int animno;
	int tickno;
};

#endif

/*

sonic-infinite-scroller-game-dev                                 May 23, 2025

author: @misael-diaz
source: src/entype.h

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
