#ifndef SONIC_INFINITE_SCROLLER_GAME_DEV_ENTYPE_H
#define SONIC_INFINITE_SCROLLER_GAME_DEV_ENTYPE_H

#include <X11/Xlib.h>
#include "entdefs.h"
#include "graphictype.h"
#include "animationtype.h"

/* entity tags */

enum entag {
	EN_CAMERA_TAG,
	EN_LVLMAP_TAG,
	EN_GOAL_TAG,
	EN_SONIC_TAG,
	EN_ENEMY_TAG,
	EN_PLATFORM_TAG,
	EN_MAXNUMOF_TAG
};

enum enid {
	EN_CAMERA_ID,
	EN_LVLMAP_ID,
	EN_PLATFORM_BETA_ID,
	EN_PLATFORM_ZETA_ID,
	EN_PLATFORM_IOTA_ID,
	EN_PLATFORM_TAU_ID,
	EN_PLATFORM_PHI_ID,
	EN_PLATFORM_CHI_ID,
	EN_PLATFORM_ETA_ID,
	EN_PLATFORM_RHO_ID,
	EN_PLATFORM_PSI_ID,
	EN_PLATFORM_EPSILON_ID,
	EN_PLATFORM_LAMBDA_ID,
	EN_PLATFORM_OMICRON_ID,
	EN_PLATFORM_SIGMA_ID,
	EN_PLATFORM_UPSILON_ID,
	EN_PLATFORM_MU_ID,
	EN_PLATFORM_NU_ID,
	EN_PLATFORM_PI_ID,
	EN_PLATFORM_XI_ID,
	EN_PLATFORM_OMEGA_ID,
	EN_PLATFORM_ALPHA_ID,
	EN_ENEMY_MOTOBUG_ALPHA_ID,
	EN_ENEMY_MOTOBUG_GAMMA_ID,
	EN_ENEMY_MOTOBUG_DELTA_ID,
	EN_ENEMY_MOTOBUG_THETA_ID,
	EN_ENEMY_MOTOBUG_KAPPA_ID,
	EN_SONIC_ID,
	EN_GOAL_ID,
	EN_MAXNUMOF_ENT,
	EN_WARP_PLATFORM_ETA_ID = EN_PLATFORM_ETA_ID,
	EN_WARP_PLATFORM_RHO_ID = EN_PLATFORM_RHO_ID,
	EN_SKY_PLATFORM_PSI_ID = EN_PLATFORM_PSI_ID,
	EN_SKY_PLATFORM_EPSILON_ID = EN_PLATFORM_EPSILON_ID,
	EN_SKY_PLATFORM_LAMBDA_ID = EN_PLATFORM_LAMBDA_ID,
	EN_SKY_PLATFORM_OMICRON_ID = EN_PLATFORM_OMICRON_ID,
	EN_SKY_PLATFORM_SIGMA_ID = EN_PLATFORM_SIGMA_ID,
	EN_SKY_PLATFORM_UPSILON_ID = EN_PLATFORM_UPSILON_ID,
	EN_SKY_PLATFORM_MU_ID = EN_PLATFORM_MU_ID,
	EN_SKY_PLATFORM_NU_ID = EN_PLATFORM_NU_ID,
	EN_SKY_PLATFORM_PI_ID = EN_PLATFORM_PI_ID,
	EN_SKY_PLATFORM_XI_ID = EN_PLATFORM_XI_ID,
	EN_SKY_PLATFORM_OMEGA_ID = EN_PLATFORM_OMEGA_ID,
	EN_SKY_PLATFORM_ALPHA_ID = EN_PLATFORM_ALPHA_ID,
	EN_MAXNUMOF_PLATFORMS = (EN_ENEMY_MOTOBUG_ALPHA_ID - EN_PLATFORM_BETA_ID),
	EN_MAXNUMOF_ENEMIES = (EN_SONIC_ID - EN_ENEMY_MOTOBUG_ALPHA_ID)
};

struct vector {
	float x;
	float y;
};

/*

struct enview:
Think of an `enview struct' to be a rectangle that encloses an entity, the enview has
four faces and a unit normal vector for each face (just like rectangles).

We pass the coordinates and dimensions of the `enview struct' to Xlib drawing functions,
and so their meanings are tied to the parameter list of Xlib drawing functions.

The coordinates `xref' and `yref' define the center of the screen in pixels (all coords
and dimensions are in pixels) and once set we don't change them because they are fixed.
The coordinates `xrel', `yrel' and `xedg', `yedg' are defined with relative to the camera,
where `xrel', `yrel' define the relative-position vector that points towards the center
of the entity, and `xedg', `yedg' define the relative-position vector that points to the
left-top edge (from our viewing perspective) of the entity. The coordinates `xscr' and
`yscr' also define the position of the left-top edge of the entity but with respect to
the screen reference frame (not the camera). The values for `xoff', `yoff', `width', and
`height' determine the visible region of the entity (what's not visible is simply beyond
the viewing range of the camera); these are the parameters that we pass to Xlib functions
for drawing entities.

*/

struct enview {
	struct vector N[EN_ENVIEW_NUMFACES];
	float xref;
	float yref;
	float xrel;
	float yrel;
	float xedg;
	float yedg;
	float xscr;
	float yscr;
	float xoff;
	float yoff;
	float width;
	float height;
};

/*animations can share graphics this is why they are not nested in the animation struct*/
struct entity {
	enum entag tag;
	enum enid id;
	struct graphic graphic;
	struct animation animations[EN_ANIMATIONS_COUNT];
	struct enview view;
	struct enview mapview;
	XImage *framebuffer;
	float xpos;
	float ypos;
	float xold;
	float yold;
	float ymin;
	float ymax;
	float xvel;
	float yvel;
	float xv00;
	float yv00;
	float xscr;
	float yscr;
	float xmap;
	float ymap;
	float wmap;
	float hmap;
	float reff;
	float xvcol;
	float yvcol;
	float width;
	float height;
	int visible;
	int falling;
	int contact;
	int clamped;
	int hitting;
	int explode;
	int frameid;
	int platfno;
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
