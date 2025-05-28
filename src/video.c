/*

sonic-infinite-scroller-game-dev                       May 21, 2025

author: @misael-diaz
source: src/video.c

Game Window GW
Frame Buffer FB

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
#include <string.h>
#include <errno.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "video.h"

void vid_init_gw(struct game * const g)
{
	g->init = !GAME_INITED_GW;
	g->display = XOpenDisplay(NULL);
	if (!g->display) {
		fprintf(stderr, "%s\n", "vid_info_gw: XOpenDisplayError");
		exit(EXIT_FAILURE);
	}
	XEvent ev = {};
	int const x = 0;
	int const y = 0;
	int const border_width = 0;
	unsigned int io_window_class = InputOutput;
	g->screeno = DefaultScreen(g->display);
	g->screen = DefaultScreenOfDisplay(g->display);
	XSetWindowAttributes attributes_window = {
		.background_pixel = BlackPixel(g->display, g->screeno),
		.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask
	};
	g->visual = DefaultVisual(g->display, g->screeno);
	g->screen_width = WidthOfScreen(g->screen);
	g->screen_height = HeightOfScreen(g->screen);
	g->screen_depth = DefaultDepthOfScreen(g->screen);
	g->window = XCreateWindow(
			g->display,
			DefaultRootWindow(g->display),
			x,
			y,
			g->screen_width,
			g->screen_height,
			border_width,
			g->screen_depth,
			io_window_class,
			g->visual,
			CWBackPixel | CWEventMask,
			&attributes_window
	);

	g->colormap = DefaultColormap(g->display, g->screeno);
	XColor screen_red = {};
	XColor screen_green = {};
	XColor screen_blue = {};
	XColor screen_gray = {};
	XAllocNamedColor(
			g->display,
			g->colormap,
			"red",
			&screen_red,
			&g->red
	);
	XAllocNamedColor(
			g->display,
			g->colormap,
			"green",
			&screen_green,
			&g->green
	);
	XAllocNamedColor(
			g->display,
			g->colormap,
			"blue",
			&screen_blue,
			&g->blue
	);
	XAllocNamedColor(
			g->display,
			g->colormap,
			"gray",
			&screen_gray,
			&g->gray
	);

	g->gc = DefaultGC(g->display, g->screeno);
	XSetGraphicsExposures(g->display, g->gc, True);
	XStoreName(g->display, g->window, "GNU/Linux-Xlib-Game-Dev");
	XSizeHints hints = {
		.flags = PMinSize | PMaxSize,
		.min_width = g->screen_width,
		.max_width = g->screen_width,
		.min_height = g->screen_height,
		.max_height = g->screen_height,
	};
	XSetWMNormalHints(g->display, g->window, &hints);
	Status stat = XInternAtoms(g->display,
			g->supported_protocols,
			g->protocolno,
			True,
			g->protocols
	);
	if (!stat) {
		fprintf(stderr, "%s\n", "vid_info_gw: XIntermAtomsError");
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	XSetWMProtocols(g->display, g->window, g->protocols, g->protocolno);
	XMapWindow(g->display, g->window);
	XWindowEvent(g->display, g->window, ExposureMask, &ev);
	g->init = GAME_INITED_GW;
}

void vid_info_gw(struct game const * const g)
{
	int const image_byte_order = ImageByteOrder(g->display);
	int const bitmap_bit_order = BitmapBitOrder(g->display);
	fprintf(stdout, "vid_init_gw: XProtocolVersion: %d\n", ProtocolVersion(g->display));
	fprintf(stdout, "vid_init_gw: fd: %d\n", ConnectionNumber(g->display));
	fprintf(stdout, "vid_init_gw: screen: %d\n", g->screeno);
	fprintf(stdout, "vid_init_gw: screen-count: %d\n", ScreenCount(g->display));
	fprintf(stdout, "vid_init_gw: depth: %d\n", DisplayPlanes(g->display, g->screeno));
	fprintf(stdout, "vid_init_gw: default-depth: %d\n", g->screen_depth);
	if (LSBFirst == image_byte_order) {
		fprintf(stdout, "%s\n", "vid_init_gw: image_byte_order: LSBFirst");
	} else {
		fprintf(stdout, "%s\n", "vid_init_gw: image_byte_order: MSBFirst");
	}
	if (LSBFirst == bitmap_bit_order) {
		fprintf(stdout, "%s\n", "vid_init_gw: bitmap_bit_order: LSBFirst");
	} else {
		fprintf(stdout, "%s\n", "vid_init_gw: bitmap_bit_order: MSBFirst");
	}
	fprintf(stdout, "vid_init_gw: bitmap_pad: %d\n", BitmapPad(g->display));
	fprintf(stdout, "vid_init_gw: width: %d\n", DisplayWidth(g->display, g->screeno));
	fprintf(stdout, "vid_init_gw: height: %d\n", DisplayHeight(g->display, g->screeno));
	fprintf(stdout, "vid_init_gw: screen-width: %d\n", g->screen_width);
	fprintf(stdout, "vid_init_gw: screen-height: %d\n", g->screen_height);
	fprintf(stdout, "vid_init_gw: cells: %d\n", CellsOfScreen(g->screen));
	fprintf(stdout, "vid_init_gw: planes: %d\n", PlanesOfScreen(g->screen));
	fprintf(stdout, "vid_init_gw: max-num-colormaps: %d\n", MaxCmapsOfScreen(g->screen));
	fprintf(stdout, "vid_init_gw: min-num-colormaps: %d\n", MinCmapsOfScreen(g->screen));

}

void vid_draw_gw(struct game const * const g)
{
	XClearWindow(g->display, g->window);
	for (int i = 0; i != g->entno; ++i) {
		struct entity const * const entities = g->ents;
		struct entity const * const ent = &entities[i];
		if (EN_SONIC_TAG == ent->tag) {
			XPutImage(
					g->display,
					g->window,
					g->gc,
					ent->framebuffer,
					ent->animations[0].aframes[0].xof,
					ent->animations[0].aframes[0].yof,
					ent->xpos,
					ent->ypos,
					ent->animations[0].aframes[0].width,
					ent->animations[0].aframes[0].height
				 );
		} 
	}
	XFlush(g->display);
}

void vid_close_gw(struct game * const g)
{
	XDestroyWindow(g->display, g->window);
	XCloseDisplay(g->display);
	g->display = NULL;
}

/*
void vid_write_fb(
		struct game * const g,
		struct image const * const img
)
{
	int const offset = 0;
	XImage *framebuffer = XCreateImage(
			g->display,
			g->visual,
			g->depth,
			ZPixmap,
			offset,
			data_img,
			img->png.width,
			img->png.height,
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
}
*/
