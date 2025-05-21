/*

sonic-infinite-scroller-game-dev                       May 21, 2025

author: @misael-diaz
source: src/main.c

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

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

int main(void)
{
	Display *display = XOpenDisplay(NULL);
	if (!display) {
		fprintf(stderr, "%s\n", "main: XOpenDisplayError");
		exit(EXIT_FAILURE);
	}
	int screen = XDefaultScreen(display);
	fprintf(stdout, "main: using screen %d\n", screen);
	XCloseDisplay(display);
	display = NULL;
	return 0;
}
