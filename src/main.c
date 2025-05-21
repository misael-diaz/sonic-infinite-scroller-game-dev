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
#include <X11/Xutil.h>
#include <string.h>
#include <errno.h>
#include <png.h>

void load(
		void **cmp,
		void **png,
		png_image * const imp,
		char const * const fileNamePNG
)
{
	void *colormap = NULL;
	imp->version = PNG_IMAGE_VERSION;
	png_byte *bufp = NULL;
	if (png_image_begin_read_from_file(imp, fileNamePNG)) {
		imp->format = PNG_FORMAT_BGRA;
		bufp = malloc(PNG_IMAGE_SIZE(*imp));
		if (!bufp) {
			fprintf(stderr, "load: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		colormap = malloc(PNG_IMAGE_COLORMAP_SIZE(*imp));
		memset(colormap, 0, PNG_IMAGE_COLORMAP_SIZE(*imp));
		if (!colormap) {
			free(bufp);
			fprintf(stderr, "load: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (!png_image_finish_read(imp, NULL, bufp, 0, colormap)) {
			fprintf(stderr, "load: %s\n", imp->message);
			free(bufp);
			free(colormap);
			png_image_free(imp);
			exit(EXIT_FAILURE);
		}
		if (!png_image_write_to_file(imp, "/tmp/tmp.png", 0, bufp, 0, colormap)) {
			fprintf(stderr, "load: %s\n", imp->message);
			free(bufp);
			free(colormap);
			png_image_free(imp);
			exit(EXIT_FAILURE);
		}
	}
	fprintf(stdout, "load: loaded-png: %s\n", fileNamePNG);
	*cmp = colormap;
	*png = bufp;
}

int main(void)
{
	//char const * const pngfile = "public/graphics/sonic.png";
	char const * const pngfile = "public/graphics/bg.png";
	png_image img = {};
	void *png = NULL;
	void *map = NULL;
	load(&map, &png, &img, pngfile);
	size_t const bytes_map = PNG_IMAGE_COLORMAP_SIZE(img);
	size_t const bytes_png = PNG_IMAGE_SIZE(img);
	Display *display = XOpenDisplay(NULL);
	if (!display) {
		fprintf(stderr, "%s\n", "main: XOpenDisplayError");
		free(map);
		free(png);
		map = NULL;
		png = NULL;
		exit(EXIT_FAILURE);
	}

	int screen = XDefaultScreen(display);
	fprintf(stdout, "main: using screen %d\n", screen);
	Visual *visual = XDefaultVisual(display, screen);
	if (!visual) {
		fprintf(stderr, "%s\n", "main: XDefaultVisualError");
		free(map);
		free(png);
		XCloseDisplay(display);
		display = NULL;
		map = NULL;
		png = NULL;
		exit(EXIT_FAILURE);
	}

	int numVisuals = 0;
	VisualID visualID = XVisualIDFromVisual(visual);
	XVisualInfo tmpXVisualInfo = {
		.visualid = visualID
	};
	XVisualInfo *visualInfo = XGetVisualInfo(
			display,
			VisualIDMask,
			&tmpXVisualInfo,
			&numVisuals
	);
	if (!visualInfo) {
		fprintf(stderr, "%s\n", "main: XGetVisualInfoError");
		free(map);
		free(png);
		XFree(visualInfo);
		XCloseDisplay(display);
		display = NULL;
		map = NULL;
		png = NULL;
		exit(EXIT_FAILURE);
	}

	int const windowXPos = 0;
	int const windowYPos = 0;
	int const windowWidth = img.width;
	int const windowHeight = img.height;
	int const windowBorderWidth = 0;
	unsigned long const windowBorder = 0;
	unsigned long const windowBackground = 0;
	Window window = XCreateSimpleWindow(
			display,
			XRootWindow(display, screen),
			windowXPos,
			windowYPos,
			windowWidth,
			windowHeight,
			windowBorderWidth,
			windowBorder,
			windowBackground
	);
	XStoreName(display, window, "SonicInfiniteScroller");

	int const graphicsContextFlags = GCGraphicsExposures;
	XGCValues graphicsContextValues = {
		.graphics_exposures = 1,
	};
	GC gc = XCreateGC(
			display,
			window,
			graphicsContextFlags,
			&graphicsContextValues
	);

	XSelectInput(display, window, ExposureMask);
	XMapWindow(display, window);

	XEvent ev = {};
	XWindowEvent(display, window, ExposureMask, &ev);

	int const offset = 0;
	int const bitmap_pad = 32;
	int const bytes_per_line = (img.width * sizeof(int));
	XImage *framebuffer = XCreateImage(
			display,
			visual,
			visualInfo->depth,
			ZPixmap,
			offset,
			png,
			img.width,
			img.height,
			bitmap_pad,
			bytes_per_line
	);

	if (!framebuffer) {
		fprintf(stderr, "%s\n", "main: XCreateImageError");
		free(map);
		free(png);
		XFree(visualInfo);
		XCloseDisplay(display);
		display = NULL;
		map = NULL;
		png = NULL;
		exit(EXIT_FAILURE);
	}

	XPutImage(
			display,
			window,
			gc,
			framebuffer,
			0,
			0,
			0,
			0,
			img.width,
			img.height
	);

	char c;
	fprintf(stdout, "%s\n", "main: press any key to continue");
	fread(&c, sizeof(c), 1, stdin);

	XDestroyImage(framebuffer);
	XFreeGC(display, gc);
	XFree(visualInfo);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
	free(map);
	visual = NULL;
	framebuffer = NULL;
	visualInfo = NULL;
	display = NULL;
	map = NULL;
	return 0;
}
