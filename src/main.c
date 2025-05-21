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
#include <string.h>
#include <errno.h>
#include <png.h>

void *load (char const * const fileNamePNG)
{
	png_image img = {
		.version = PNG_IMAGE_VERSION,
		.format = PNG_FORMAT_RGBA
	};
	png_byte *bufp = NULL;
	if (png_image_begin_read_from_file(&img, fileNamePNG)) {
		img.format = PNG_FORMAT_RGBA;
		bufp = malloc(PNG_IMAGE_SIZE(img));
		if (!bufp) {
			fprintf(stderr, "load: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (!png_image_finish_read(&img, NULL, bufp, 0, NULL)) {
			fprintf(stderr, "load: %s\n", img.message);
			png_image_free(&img);
			free(bufp);
			exit(EXIT_FAILURE);
		}
	}
	fprintf(stdout, "load: loaded-png: %s\n", fileNamePNG);
	return bufp;
}

int main(void)
{
	char const * const background = "../public/graphics/chemical-bg.png";
	char const * const bg = background;
	void *png = load(bg);
	Display *display = XOpenDisplay(NULL);
	if (!display) {
		fprintf(stderr, "%s\n", "main: XOpenDisplayError");
		free(png);
		exit(EXIT_FAILURE);
	}
	int screen = XDefaultScreen(display);
	fprintf(stdout, "main: using screen %d\n", screen);
	XCloseDisplay(display);
	free(png);
	display = NULL;
	png = NULL;
	return 0;
}
