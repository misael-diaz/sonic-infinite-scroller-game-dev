/*

sonic-infinite-scroller-game-dev                       May 21, 2025

author: @misael-diaz
source: src/graphic.c

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
#include <X11/Xutil.h>
#include "graphic.h"

// References:
// see man libpng for a detailed description of the libpng API and also read
// `/usr/share/doc/libpng-dev/example.c', this should exist in your system if the libpng
// installation was performed with a package manager like apt, rpm, pacman, etc.
int graph_load_graphic(struct graphic * const graphicp)
{
	void * const background = NULL;
	void * const colormap = NULL;
	// our graphics conform to the default row-stride (top-down pixel arrangement)
	int const default_row_stride = 0;
	// we don't need to perform 8-bit conversion because our graphics conform to it
	int const none = 0;
	int const default_conversion = none;
	int rc = GAME_ERROR_RC;
	graphicp->loaded = !GAME_LOADED_GRAPHIC;
	graphicp->binded = !GAME_BINDED_GRAPHIC;
	graphicp->info.version = PNG_IMAGE_VERSION;
	graphicp->data = NULL;
	if (png_image_begin_read_from_file(&graphicp->info, graphicp->name)) {
		// selected format has been chosen according to my screen hardware specs 
		graphicp->info.format = PNG_FORMAT_BGRA;
		graphicp->data = malloc(PNG_IMAGE_SIZE(graphicp->info));
		if (!graphicp->data) {
			fprintf(stderr, "graph_load_graphic: %s\n", strerror(errno));
			png_image_free(&graphicp->info);
			return rc;
		}
		if (
			!png_image_finish_read(
				&graphicp->info,
				background,
				graphicp->data,
				default_row_stride,
				colormap
			)
		   ) {
			fprintf(stderr,
				"graph_load_graphic: %s\n",
				graphicp->info.message);
			graph_unload_graphic(graphicp);
			return rc;
		}
		// sometimes it's useful to look at the output in the system scratch space
		if (
			!png_image_write_to_file(
				&graphicp->info,
				"/tmp/tmp.png",
				default_conversion,
				graphicp->data,
				default_row_stride,
				colormap	
			)
		   ) {
			fprintf(stderr,
				"graph_load_graphic: %s\n",
				graphicp->info.message);
			graph_unload_graphic(graphicp);
			return rc;
		}
	} else {
		fprintf(stdout,
			"graph_load_graphic: error: %s\n",
			graphicp->info.message);
		return rc;
	}
	fprintf(stdout, "graph_load_graphic: loaded: %s\n", graphicp->name);
	graphicp->loaded = GAME_LOADED_GRAPHIC;
	rc = !GAME_ERROR_RC;
	return rc;
}

// do not call this utility on a graphic that has been associated with a Xlib framebuffer
// because XDestroyImage() already frees the graphic's data; unless you nullify the
// graphics data yourself calling this utility is OK. Note that calling png_image_free()
// is optional unless an error has occurred while reading the PNG file. The main use of
// this utility, is to free graphic memory buffers on errors that happen before calling
// XCreateImage (that's when the graphic becomes associated with Xlib).
void graph_unload_graphic(struct graphic * const graphicp)
{
	if (!graphicp->data) {
		return;
	}
	if (graphicp->binded) {
		fprintf(stderr,
			"%s%s%s\n",
			"graph_unload_graphic: WARNING: "
			"graphic: ",
			graphicp->name,
			" is binded to a Xlib framebuffer, "
			"call XDestroyImage() instead");
		return;
	}
	free(graphicp->data);
	png_image_free(&graphicp->info);
	graphicp->data = NULL;
}

// frees graphics (presumed) unassociated with a framebuffer
void graph_unloadall_graphics(struct game * const g)
{
	struct entity * const ents = g->ents;
	for (int i = 0; i != EN_ENT_MAX; ++i) {
		struct entity * const ent = &ents[i];
		if (!ent->framebuffer) {
			graph_unload_graphic(&ent->graphic);
		} else {
			if (GAME_BINDED_GRAPHIC == ent->graphic.binded) {
				XDestroyImage(ent->framebuffer);
				ent->framebuffer = NULL;
			} else {
				fprintf(stderr,
					"%s %s %s\n",
					"graph_unloadall_graphics: WARNING: graphic:",
					ent->graphic.name,
					"AllocatedFrameBufferButNotBindedError");
			}
		}
	}
}

// check that the screen is wider than a single platform
void graph_check_platform_dims(struct game * const g)
{
	struct entity const * const ents = g->ents;
	struct entity const * const beta_platform = &ents[EN_PLATFORM_BETA_ID];
	struct entity const * const zeta_platform = &ents[EN_PLATFORM_ZETA_ID];
	if (
		(!g->init) ||
		(!g->display) ||
		(!g->screen) ||
		(!g->visual) ||
		(!g->screen_width) ||
		(!g->screen_height) ||
		(!beta_platform->graphic.data) ||
		(!zeta_platform->graphic.data) ||
		((!GAME_LOADED_GRAPHIC) == beta_platform->graphic.loaded) ||
		((!GAME_LOADED_GRAPHIC) == zeta_platform->graphic.loaded)
	   ) {
		fprintf(stderr, "%s\n", "graph_check_platform_dims: UXError");
		exit(EXIT_FAILURE);
	}

	if (!beta_platform->graphic.name || !zeta_platform->graphic.name) {
		fprintf(stderr,
			"%s\n",
			"graph_check_platform_dims: UXGraphicResourceError");
		exit(EXIT_FAILURE);
	}

	if (strcmp(beta_platform->graphic.name, zeta_platform->graphic.name)) {
		fprintf(stderr,
			"%s\n",
			"graph_check_platform_dims: UXGraphicResourceMismatchError");
		exit(EXIT_FAILURE);
	}

	if (beta_platform->graphic.info.width != zeta_platform->graphic.info.width) {
		fprintf(stderr,
			"%s\n",
			"graph_check_platform_dims: UXWidthPlatformError");
		exit(EXIT_FAILURE);
	}

	// we expect our code to work when the screen is as wide as the platform
	if (((int) beta_platform->graphic.info.width) > g->screen_width) {
		fprintf(stderr,
			"%s\n",
			"graph_check_platform_dims: UXScreenWidthLoBoundError");
		exit(EXIT_FAILURE);
	}

	// we are OK with the (probable) empty/void region after the platform
}
