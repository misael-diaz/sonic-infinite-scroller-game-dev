#ifndef SONIC_INFINITE_SCROLLER_GAME_DEV_GRAPHIC_TYPE_H
#define SONIC_INFINITE_SCROLLER_GAME_DEV_GRAPHIC_TYPE_H

#include <png.h>

struct graphic {
	char const *name;
	png_byte *data;
	png_image info;
	int loaded;
	int binded;
};

#endif

/*

sonic-infinite-scroller-game-dev                                 May 23, 2025

author: @misael-diaz
source: src/graphictype.h

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
