/*

sonic-infinite-scroller-game-dev                                          May 23, 2025

author: @misael-diaz
source: src/entity.c

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
#include <time.h>
#include <math.h>
#include "graphic.h"
#include "video.h"
#include "entity.h"

#define MIN(x, y) ((x) < (y))? (x) : (y)
#define MAX(x, y) ((x) > (y))? (x) : (y)

static float en_clamp(
		float const val,
		float const min,
		float const max
)
{
	float _min = min;
	float _max = max;
	if (max < min) {
		_max = min;
		_min = max;
	}
	float ret = val;
	if (_min > val) {
		ret = _min;
	} else if (_max < val) {
		ret = _max;
	}
	return ret;
}

static void en_tag_entity(struct game * const g)
{
	int count = 0;
	for (int i = 0; i != EN_MAXNUMOF_ENT; ++i) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		if (EN_CAMERA_ID == i) {
			ent->tag = EN_CAMERA_TAG;
			ent->id = EN_CAMERA_ID;
			++count;
		} else if (EN_SONIC_ID == i) {
			ent->tag = EN_SONIC_TAG;
			ent->id = EN_SONIC_ID;
			++count;
		} else if (EN_PLATFORM_BETA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_BETA_ID;
			++count;
		} else if (EN_PLATFORM_ZETA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_ZETA_ID;
			++count;
		} else if (EN_ENEMY_MOTOBUG_ALPHA_ID == i) {
			ent->tag = EN_ENEMY_TAG;
			ent->id = EN_ENEMY_MOTOBUG_ALPHA_ID;
			++count;
		} else if (EN_ENEMY_MOTOBUG_GAMMA_ID == i) {
			ent->tag = EN_ENEMY_TAG;
			ent->id = EN_ENEMY_MOTOBUG_GAMMA_ID;
			++count;
		} else if (EN_ENEMY_MOTOBUG_DELTA_ID == i) {
			ent->tag = EN_ENEMY_TAG;
			ent->id = EN_ENEMY_MOTOBUG_DELTA_ID;
			++count;
		} else if (EN_ENEMY_MOTOBUG_THETA_ID == i) {
			ent->tag = EN_ENEMY_TAG;
			ent->id = EN_ENEMY_MOTOBUG_THETA_ID;
			++count;
		} else if (EN_ENEMY_MOTOBUG_KAPPA_ID == i) {
			ent->tag = EN_ENEMY_TAG;
			ent->id = EN_ENEMY_MOTOBUG_KAPPA_ID;
			++count;
		}
	}
	if (EN_MAXNUMOF_ENT != count) {
		fprintf(stderr, "%s\n", "en_tag_entity: UXUnhandledEntitiesError");
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
}

static void en_load_graphic(struct game * const g)
{
	int count = 0;
	for (int i = 0; i != EN_MAXNUMOF_ENT; ++i) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		struct graphic * const graphicp = &ent->graphic;
		if (EN_CAMERA_TAG == ent->tag) {
			memset(&ent->graphic, 0, sizeof(ent->graphic));
			ent->graphic.name = GAME_CAMERA_NOGRAPHIC_FP;
			ent->graphic.data = NULL;
			ent->graphic.loaded = !GAME_LOADED_GRAPHIC;
			ent->graphic.binded = !GAME_LOADED_GRAPHIC;
			++count;
		} else if (EN_SONIC_TAG == ent->tag) {
			graphicp->name = GAME_SONIC_GRAPHIC_FP;
			if (GAME_ERROR_RC == graph_load_graphic(graphicp)) {
				fprintf(stderr,
					"%s\n",
					"en_load_graphic: UXLoadGraphicError");
				goto handle_err;
			}
			++count;
		} else if (EN_PLATFORM_TAG == ent->tag) {
			graphicp->name = GAME_PLATFORM_GRAPHIC_FP;
			if (GAME_ERROR_RC == graph_load_graphic(graphicp)) {
				fprintf(stderr,
					"%s\n",
					"en_load_graphic: UXLoadGraphicError");
				goto handle_err;
			}
			++count;
		} else if (EN_ENEMY_TAG == ent->tag) {
			graphicp->name = GAME_ENEMY_MOTOBUG_GRAPHIC_FP;
			if (GAME_ERROR_RC == graph_load_graphic(graphicp)) {
				fprintf(stderr,
					"%s\n",
					"en_load_graphic: UXLoadGraphicError");
				goto handle_err;
			}
			++count;
		}
	}
	if (EN_MAXNUMOF_ENT != count) {
		fprintf(stderr, "%s\n", "en_load_graphic: UXUnhandledEntitiesError");
		goto handle_err;
	}
	return;
handle_err:
	{
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
}

// we set this for completeness, might be useful for debugging sessions
static void en_init_camera_aframes(struct game * const g)
{
	struct entity * const entities = g->ents;
	struct entity * const camera = &entities[EN_CAMERA_ID];
	struct animation * const animations = camera->animations;
	int const width_camera = GAME_CAMERA_WIDTH;
	int const height_camera = GAME_CAMERA_HEIGHT;
	for (int animno = 0; animno != EN_ANIMATIONS_COUNT; ++animno) {
		for (int aframeno = 0; aframeno != EN_AFRAME_COUNT; ++aframeno) {
			animations[animno].aframes[aframeno].id = aframeno;
			animations[animno].aframes[aframeno].xof = 0;
			animations[animno].aframes[aframeno].yof = 0;
			animations[animno].aframes[aframeno].width = width_camera;
			animations[animno].aframes[aframeno].height = height_camera;
		}
		animations[animno].tickcount_aframe_sequence = EN_AFRAME_COUNT;
		animations[animno].tickcount_aframe = 1;
		animations[animno].name = EN_CAMERA_FRAME_NAME;
		animations[animno].count = 1;
		animations[animno].id = animno;
	}
}

static void en_init_sonic_aframes(struct game * const g)
{
	struct entity * const entities = g->ents;
	struct entity * const sonic = &entities[EN_SONIC_ID];
	struct animation * const animations = sonic->animations;
	for (int i = 0; i != EN_SONIC_ANIMATIONS_COUNT; ++i) {
		int const animation_id = i;
		for (int j = 0; j != EN_SONIC_AFRAME_COUNT; ++j) {
			int const frame_id = j;
			int const id = frame_id;
			int const xof = frame_id * (sonic->graphic.info.width >> 3);
			int const yof = animation_id * (sonic->graphic.info.height >> 1);
			int const width = (sonic->graphic.info.width >> 3);
			int const height = (sonic->graphic.info.height >> 1);
			animations[animation_id].aframes[frame_id].id = id;
			animations[animation_id].aframes[frame_id].xof = xof;
			animations[animation_id].aframes[frame_id].yof = yof;
			animations[animation_id].aframes[frame_id].width = width;
			animations[animation_id].aframes[frame_id].height = height;
		}
		if (EN_SONIC_RUN_AN == animation_id) {
			float const duration = (
				GAME_SONIC_RUN_ANIMATION_DURATION *
				GAME_FRAMERATE_HZ
			);
			int const iduration = duration;
			int const icount = (
				(iduration / EN_AFRAME_COUNT) +
				(iduration % EN_AFRAME_COUNT)
			);
			int const tickcount = (icount)? icount : 1;
			int const tickcount_aframe = tickcount;
			int const tickcount_aframe_sequence = (
				tickcount_aframe * EN_AFRAME_COUNT
			);
			int const tas = tickcount_aframe_sequence;
			animations[animation_id].name = EN_SONIC_RUN_FRAME_NAME;
			animations[animation_id].tickcount_aframe = tickcount_aframe;
			animations[animation_id].tickcount_aframe_sequence = tas;
		} else if (EN_SONIC_SPIN_AN == animation_id) {
			float const duration = (
				GAME_SONIC_SPIN_ANIMATION_DURATION *
				GAME_FRAMERATE_HZ
			);
			int const iduration = duration;
			int const icount = (
				(iduration / EN_AFRAME_COUNT) +
				(iduration % EN_AFRAME_COUNT)
			);
			int const tickcount = (icount)? icount : 1;
			int const tickcount_aframe = tickcount;
			int const tickcount_aframe_sequence = (
				tickcount_aframe * EN_AFRAME_COUNT
			);
			int const tas = tickcount_aframe_sequence;
			animations[animation_id].name = EN_SONIC_SPIN_FRAME_NAME;
			animations[animation_id].tickcount_aframe = tickcount_aframe;
			animations[animation_id].tickcount_aframe_sequence = tas;
		} else {
			fprintf(stderr, "%s\n", "UXUnhandledAnimationError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
		animations[animation_id].count = EN_SONIC_AFRAME_COUNT;
		animations[animation_id].id = animation_id;
	}
}

// we set everything for completeness even if we just need a subset of the platform data
static void en_init_platform_aframes(
		struct game * const g,
		int const id_platform
)
{
	struct entity * const entities = g->ents;
	struct entity * const platform = &entities[id_platform];
	struct animation * const animations = platform->animations;
	int const width_platform = platform->graphic.info.width;
	int const height_platform = platform->graphic.info.height;
	for (int animno = 0; animno != EN_ANIMATIONS_COUNT; ++animno) {
		for (int aframeno = 0; aframeno != EN_AFRAME_COUNT; ++aframeno) {
			animations[animno].aframes[aframeno].id = aframeno;
			animations[animno].aframes[aframeno].xof = 0;
			animations[animno].aframes[aframeno].yof = 0;
			animations[animno].aframes[aframeno].width = width_platform;
			animations[animno].aframes[aframeno].height = height_platform;
		}
		animations[animno].tickcount_aframe_sequence = EN_PLATFORM_AFRAME_COUNT;
		animations[animno].tickcount_aframe = EN_PLATFORM_AFRAME_COUNT;
		animations[animno].name = EN_PLATFORM_FRAME_NAME;
		animations[animno].count = EN_PLATFORM_AFRAME_COUNT;
		animations[animno].id = animno;
	}
}

static void en_init_enemy_motobug_aframes(
		struct game * const g,
		int const id_enemy
)
{
	struct entity * const entities = g->ents;
	struct entity * const enemy = &entities[id_enemy];
	struct animation * const animations = enemy->animations;
	int const numaframes = EN_ENEMY_MOTOBUG_AFRAME_COUNT;
	int const width = (enemy->graphic.info.width / numaframes);
	int const height = (enemy->graphic.info.height >> 1);
	memset(enemy->animations, 0, sizeof(enemy->animations));
	for (int i = 0; i != EN_ENEMY_MOTOBUG_ANIMATIONS_COUNT; ++i) {
		int const animation_id = i;
		for (int j = 0; j != EN_ENEMY_MOTOBUG_AFRAME_COUNT; ++j) {
			int const frame_id = j;
			int const id = frame_id;
			int const xof = frame_id * width;
			int const yof = animation_id * height;
			animations[animation_id].aframes[frame_id].id = id;
			animations[animation_id].aframes[frame_id].xof = xof;
			animations[animation_id].aframes[frame_id].yof = yof;
			animations[animation_id].aframes[frame_id].width = width;
			animations[animation_id].aframes[frame_id].height = height;
		}
		if (EN_ENEMY_MOTOBUG_RUN_AN == animation_id) {
			float const duration = (
				GAME_ENEMY_MOTOBUG_RUN_ANIMATION_DURATION *
				GAME_FRAMERATE_HZ
			);
			int const iduration = duration;
			int const icount = (
				(iduration / EN_ENEMY_MOTOBUG_AFRAME_COUNT) +
				(iduration % EN_ENEMY_MOTOBUG_AFRAME_COUNT)
			);
			int const tickcount = (icount)? icount : 1;
			int const tickcount_aframe = tickcount;
			int const tickcount_aframe_sequence = (
				tickcount_aframe * EN_ENEMY_MOTOBUG_AFRAME_COUNT
			);
			int const tas = tickcount_aframe_sequence;
			animations[animation_id].name = EN_ENEMY_MOTOBUG_RUN_FRAME_NAME;
			animations[animation_id].tickcount_aframe = tickcount_aframe;
			animations[animation_id].tickcount_aframe_sequence = tas;
		} else if (EN_ENEMY_MOTOBUG_EXPLODE_AN == animation_id) {
			float const duration = (
				GAME_ENEMY_MOTOBUG_EXPLODE_ANIMATION_DURATION *
				GAME_FRAMERATE_HZ
			);
			int const iduration = duration;
			int const icount = (
				(iduration / EN_ENEMY_MOTOBUG_AFRAME_COUNT) +
				(iduration % EN_ENEMY_MOTOBUG_AFRAME_COUNT)
			);
			int const tickcount = (icount)? icount : 1;
			int const tickcount_aframe = tickcount;
			int const tickcount_aframe_sequence = (
				tickcount_aframe * EN_ENEMY_MOTOBUG_AFRAME_COUNT
			);
			int const tas = tickcount_aframe_sequence;
			animations[animation_id].name = (
				EN_ENEMY_MOTOBUG_EXPLODE_FRAME_NAME
			);
			animations[animation_id].tickcount_aframe = tickcount_aframe;
			animations[animation_id].tickcount_aframe_sequence = tas;
		} else {
			fprintf(stderr, "%s\n", "UXUnhandledAnimationError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
		animations[animation_id].count = EN_ENEMY_MOTOBUG_AFRAME_COUNT;
		animations[animation_id].id = animation_id;
	}
}

static void en_init_aframes(struct game * const g)
{
	en_init_camera_aframes(g);
	en_init_sonic_aframes(g);
	en_init_platform_aframes(g, EN_PLATFORM_BETA_ID);
	en_init_platform_aframes(g, EN_PLATFORM_ZETA_ID);
	en_init_enemy_motobug_aframes(g, EN_ENEMY_MOTOBUG_ALPHA_ID);
	en_init_enemy_motobug_aframes(g, EN_ENEMY_MOTOBUG_GAMMA_ID);
	en_init_enemy_motobug_aframes(g, EN_ENEMY_MOTOBUG_DELTA_ID);
	en_init_enemy_motobug_aframes(g, EN_ENEMY_MOTOBUG_THETA_ID);
	en_init_enemy_motobug_aframes(g, EN_ENEMY_MOTOBUG_KAPPA_ID);
}

static void en_init_entity_framebuffer(
		struct game * const g,
		int const id
)
{
	struct entity * const entities = g->ents;
	struct entity * const ent = &entities[id];
	if (!ent->graphic.data || !ent->graphic.loaded) {
		// handles entities that have no graphic such as the camera
		ent->graphic.binded = !GAME_BINDED_GRAPHIC;
		return;
	}
	int const offset = 0;
	int const bitmap_pad = 32;
	int const bytes_per_line = (ent->graphic.info.width * sizeof(int));
	ent->framebuffer = XCreateImage(
			g->display,
			g->visual,
			g->screen_depth,
			ZPixmap,
			offset,
			(void*) ent->graphic.data,
			ent->graphic.info.width,
			ent->graphic.info.height,
			bitmap_pad,
			bytes_per_line
	);
	if (!ent->framebuffer) {
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	ent->graphic.binded = GAME_BINDED_GRAPHIC;
}

static void en_init_framebuffers(struct game * const g)
{
	en_init_entity_framebuffer(g, EN_CAMERA_ID);
	en_init_entity_framebuffer(g, EN_SONIC_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_BETA_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_ZETA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_ALPHA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_GAMMA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_DELTA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_THETA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_KAPPA_ID);
}

static void en_set_view(
		struct game * const g,
		int const id
)
{
	struct entity const * const camera = &g->ents[EN_CAMERA_ID];
	struct entity * const ent = &g->ents[id];
	ent->view.xrel = ent->xpos - camera->xpos;
	ent->view.yrel = ent->ypos - camera->ypos;

	float const xmin = (0.5f * (-(GAME_CAMERA_VIEW_WIDTH)));
	float const xmax = (0.5f * (+(GAME_CAMERA_VIEW_WIDTH)));
	float const ymin = (0.5f * (-(GAME_CAMERA_VIEW_HEIGHT)));
	float const ymax = (0.5f * (+(GAME_CAMERA_VIEW_HEIGHT)));
	ent->view.xedg = (
			ent->view.xrel +
			(0.5f * ent->width) * ent->view.N[EN_ENVIEW_W].x
	);
	ent->view.yedg = (
			ent->view.yrel +
			(0.5f * ent->height) * ent->view.N[EN_ENVIEW_S].y
	);
	if ((xmin > (ent->view.xedg + ent->width)) || (xmax < ent->view.xedg)) {
		ent->view.xedg = 0;
		ent->view.yedg = 0;
		ent->view.xscr = 0;
		ent->view.yscr = 0;
		ent->view.xoff = 0;
		ent->view.yoff = 0;
		ent->view.width = 0;
		ent->view.height = 0;
		return;
	}
	if ((ymin > (ent->view.yedg + ent->height)) || (ymax < ent->view.yedg)) {
		ent->view.xedg = 0;
		ent->view.yedg = 0;
		ent->view.xscr = 0;
		ent->view.yscr = 0;
		ent->view.xoff = 0;
		ent->view.yoff = 0;
		ent->view.width = 0;
		ent->view.height = 0;
		return;
	}

	if (
		(xmin > (ent->view.xedg + ent->width)) ||
		(xmax < ent->view.xedg) ||
		(ymin > (ent->view.yedg + ent->height)) ||
		(xmax < ent->view.yedg)
	   ) {
		fprintf(stderr, "%s\n", "en_set_view: ImplCameraViewBoundsError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	if (xmin > ent->view.xedg) {
		ent->view.xoff = xmin - ent->view.xedg;
		if (xmax > (ent->view.xedg + ent->width)) {
			ent->view.width = ent->width - ent->view.xoff;
		} else {
			ent->view.width = GAME_CAMERA_VIEW_WIDTH;
		}
	} else {
		ent->view.xoff = 0;
		if (xmax > (ent->view.xedg + ent->width)) {
			ent->view.width = ent->width;
		} else {
			ent->view.width = xmax - ent->view.xedg;
		}
	}

	if (ymin > ent->view.yedg) {
		ent->view.yoff = ymin - ent->view.yedg;
		if (ymax > (ent->view.yedg + ent->height)) {
			ent->view.height = ent->height - ent->view.yoff;
		} else {
			ent->view.height = GAME_CAMERA_VIEW_HEIGHT;
		}
	} else {
		ent->view.yoff = 0;
		if (ymax > (ent->view.yedg + ent->height)) {
			ent->view.height = ent->height;
		} else {
			ent->view.height = ymax - ent->view.yedg;
		}
	}

	ent->view.xedg = en_clamp(ent->view.xedg, xmin, xmax);
	ent->view.yedg = en_clamp(ent->view.yedg, ymin, ymax);
	ent->view.xscr = ent->view.xedg + ent->view.xref;
	ent->view.yscr = ent->view.yedg + ent->view.yref;
	if ((EN_ENEMY_TAG == ent->tag) || (EN_SONIC_TAG == ent->tag)) {
		int const animno = ent->animno;
		int const aframecur = ent->animations[animno].aframecur;
		ent->view.xoff += ent->animations[animno].aframes[aframecur].xof;
		ent->view.yoff += ent->animations[animno].aframes[aframecur].yof;
	}
}

static void en_init_view(
		struct game * const g,
		int const id
)
{
	struct entity * const ent = &g->ents[id];
	ent->view.N[EN_ENVIEW_E].x = 1;
	ent->view.N[EN_ENVIEW_E].y = 0;
	ent->view.N[EN_ENVIEW_N].x = 0;
	ent->view.N[EN_ENVIEW_N].y = 1;
	ent->view.N[EN_ENVIEW_W].x =-1;
	ent->view.N[EN_ENVIEW_W].y = 0;
	ent->view.N[EN_ENVIEW_S].x = 0;
	ent->view.N[EN_ENVIEW_S].y =-1;
	en_set_view(g, id);
}

static void en_init_camera(struct game * const g)
{
	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	struct entity * const camera = &g->ents[EN_CAMERA_ID];
	camera->xpos = (0.5f * width_game_window);
	camera->ypos = (0.5f * height_game_window);
	camera->xold = GAME_CAMERA_XVEL;
	camera->yold = GAME_CAMERA_YVEL;
	camera->xvel = GAME_CAMERA_XVEL;
	camera->yvel = GAME_CAMERA_YVEL;
	camera->xv00 = GAME_CAMERA_XVEL;
	camera->yv00 = GAME_CAMERA_YVEL;
	camera->xmax = EN_IGNORE_PROPERTY;
	camera->ymax = EN_IGNORE_PROPERTY;
	camera->width = camera->animations[0].aframes[0].width;
	camera->height = camera->animations[0].aframes[0].height;
	camera->reff = 0.5f * (0.5f * (camera->width + camera->height));
	camera->visible = !GAME_CAMERA_VISIBLE;
	camera->falling = EN_IGNORE_PROPERTY;
	camera->contact = EN_IGNORE_PROPERTY;
	camera->hitting = EN_IGNORE_PROPERTY;
	camera->explode = EN_IGNORE_PROPERTY;
	camera->frameno = EN_CAMERA_DEFAULT_AF;
	camera->animno = EN_CAMERA_DEFAULT_AN;
	camera->tickno = EN_IGNORE_PROPERTY;
	camera->view.N[EN_ENVIEW_E].x = 1;
	camera->view.N[EN_ENVIEW_E].y = 0;
	camera->view.N[EN_ENVIEW_N].x = 0;
	camera->view.N[EN_ENVIEW_N].y = 1;
	camera->view.N[EN_ENVIEW_W].x =-1;
	camera->view.N[EN_ENVIEW_W].y = 0;
	camera->view.N[EN_ENVIEW_S].x = 0;
	camera->view.N[EN_ENVIEW_S].y =-1;
	camera->view.xref = (0.5f * width_game_window);
	camera->view.yref = (0.5f * height_game_window);
	camera->view.xrel = 0;
	camera->view.yrel = 0;
	camera->view.xedg = (
		camera->view.xrel +
		(0.5f * camera->width) * camera->view.N[EN_ENVIEW_W].x
	);
	camera->view.yedg = (
		camera->view.yrel +
		(0.5f * camera->height) * camera->view.N[EN_ENVIEW_S].y
	);
	camera->view.xscr = camera->view.xedg + camera->view.xref;
	camera->view.yscr = camera->view.yedg + camera->view.yref;
	camera->xscr = camera->view.xscr;
	camera->yscr = camera->view.yscr;
	camera->view.xoff = 0;
	camera->view.yoff = 0;
	if (GAME_CAMERA_VISIBLE == camera->visible) {
		camera->view.width = camera->width;
		camera->view.height = camera->height;
	} else {
		camera->view.width = 0;
		camera->view.height = 0;
	}
}

static void en_init_sonic(struct game * const g)
{
	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	struct entity const * const beta_platform = &g->ents[EN_PLATFORM_BETA_ID];
	struct entity * const sonic = &g->ents[EN_SONIC_ID];
	sonic->xold = EN_IGNORE_PROPERTY;
	sonic->xvel = GAME_SONIC_XVEL;
	sonic->yvel = GAME_SONIC_YVEL;
	sonic->xv00 = GAME_SONIC_XVEL;
	sonic->yv00 = GAME_SONIC_YVEL;
	sonic->xscr = EN_IGNORE_PROPERTY;
	sonic->yscr = EN_IGNORE_PROPERTY;
	sonic->xmax = EN_IGNORE_PROPERTY;
	sonic->ymax = EN_IGNORE_PROPERTY;
	sonic->width = sonic->animations[0].aframes[0].width;
	sonic->height = sonic->animations[0].aframes[0].height;
	sonic->reff = 0.5f * (0.5f * (sonic->width + sonic->height));
	sonic->visible = EN_IGNORE_PROPERTY;
	sonic->falling = !GAME_ENTITY_FALLING;
	sonic->contact = GAME_PLATFORM_CONTACT;
	sonic->hitting = !GAME_ENEMY_HITTING;
	sonic->explode = EN_IGNORE_PROPERTY;
	sonic->frameno = EN_SONIC_DEFAULT_AF;
	sonic->animno = EN_SONIC_RUN_AN;
	sonic->tickno = 0;
	sonic->view.xref = (0.5f * width_game_window);
	sonic->view.yref = (0.5f * height_game_window);
	sonic->xpos = beta_platform->xpos;
	sonic->ypos = (
		beta_platform->ypos -
		(0.5f * beta_platform->height) -
		(0.5f * sonic->height)
	);
	sonic->yold = sonic->ypos;
	en_init_view(g, sonic->id);
}

static void en_init_platform(
		struct game * const g,
		int const id_platform
)
{
	if (
		(EN_PLATFORM_BETA_ID != id_platform) &&
		(EN_PLATFORM_ZETA_ID != id_platform)
	   ) {
		fprintf(stderr, "%s\n", "en_init_platform: InvalidPlatformIdError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	struct entity * const platform = &g->ents[id_platform];
	if (id_platform != platform->id) {
		fprintf(stderr, "%s\n", "en_init_enemy: MismatchEnemyIdError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	struct entity * const camera = &g->ents[EN_CAMERA_ID];
	platform->xold = EN_IGNORE_PROPERTY;
	platform->yold = EN_IGNORE_PROPERTY;
	platform->xvel = GAME_PLATFORM_XVEL;
	platform->yvel = GAME_PLATFORM_YVEL;
	platform->xv00 = EN_IGNORE_PROPERTY;
	platform->yv00 = EN_IGNORE_PROPERTY;
	platform->xscr = EN_IGNORE_PROPERTY;
	platform->yscr = EN_IGNORE_PROPERTY;
	platform->xmax = EN_IGNORE_PROPERTY;
	platform->ymax = EN_IGNORE_PROPERTY;
	platform->width = platform->animations[0].aframes[0].width;
	platform->height = platform->animations[0].aframes[0].height;
	platform->reff = EN_IGNORE_PROPERTY;
	platform->visible = EN_IGNORE_PROPERTY;
	platform->falling = EN_IGNORE_PROPERTY;
	platform->contact = EN_IGNORE_PROPERTY;
	platform->hitting = EN_IGNORE_PROPERTY;
	platform->explode = EN_IGNORE_PROPERTY;
	platform->frameno = EN_PLATFORM_DEFAULT_AF;
	platform->animno = EN_PLATFORM_DEFAULT_AN;
	platform->tickno = EN_IGNORE_PROPERTY;
	platform->view.xref = (0.5f * width_game_window);
	platform->view.yref = (0.5f * height_game_window);
	if (EN_PLATFORM_BETA_ID == id_platform) {
		platform->xpos = camera->xpos + GAME_PLATFORM_XREL;
		platform->ypos = (
				camera->ypos +
				GAME_PLATFORM_YREL
		);
	} else if (EN_PLATFORM_ZETA_ID == id_platform) {
		platform->xpos = (
				camera->xpos +
				platform->width +
				GAME_PLATFORM_XREL
		);
		platform->ypos = (
				camera->ypos +
				GAME_PLATFORM_YREL +
				GAME_PLATFORM_SHIFT_YPOS
		);
	}
	en_init_view(g, platform->id);
}

static void en_init_enemy(
		struct game * const g,
		int const id_enemy
)
{
	if (
		(EN_ENEMY_MOTOBUG_ALPHA_ID != id_enemy) &&
		(EN_ENEMY_MOTOBUG_GAMMA_ID != id_enemy) &&
		(EN_ENEMY_MOTOBUG_DELTA_ID != id_enemy) &&
		(EN_ENEMY_MOTOBUG_THETA_ID != id_enemy) &&
		(EN_ENEMY_MOTOBUG_KAPPA_ID != id_enemy)
	   ) {
		fprintf(stderr, "%s\n", "en_init_enemy: InvalidEnemyIdError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	struct entity * const enemy = &g->ents[id_enemy];
	if (id_enemy != enemy->id) {
		fprintf(stderr, "%s\n", "en_init_enemy: MismatchEnemyIdError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	struct entity const * const zeta_platform = &g->ents[EN_PLATFORM_ZETA_ID];
	enemy->xold = EN_IGNORE_PROPERTY;
	enemy->xvel = GAME_ENEMY_MOTOBUG_XVEL;
	enemy->yvel = GAME_ENEMY_MOTOBUG_YVEL;
	enemy->xv00 = GAME_ENEMY_MOTOBUG_XVEL;
	enemy->yv00 = GAME_ENEMY_MOTOBUG_YVEL;
	enemy->xscr = EN_IGNORE_PROPERTY;
	enemy->yscr = EN_IGNORE_PROPERTY;
	enemy->xmax = EN_IGNORE_PROPERTY;
	enemy->ymax = EN_IGNORE_PROPERTY;
	enemy->width = enemy->animations[0].aframes[0].width;
	enemy->height = enemy->animations[0].aframes[0].height;
	enemy->reff = 0.5f * (0.5f * (enemy->width + enemy->height));
	enemy->visible = EN_IGNORE_PROPERTY;
	enemy->falling = EN_IGNORE_PROPERTY;
	enemy->contact = GAME_PLATFORM_CONTACT;
	enemy->hitting = EN_IGNORE_PROPERTY;
	enemy->explode = !GAME_ENEMY_EXPLODE;
	enemy->frameno = EN_ENEMY_MOTOBUG_DEFAULT_AF;
	enemy->animno = EN_ENEMY_MOTOBUG_DEFAULT_AN;
	enemy->tickno = EN_IGNORE_PROPERTY;
	enemy->view.xref = (0.5f * width_game_window);
	enemy->view.yref = (0.5f * height_game_window);
	enemy->xpos = zeta_platform->xpos + enemy->id * 2.0f * enemy->width;
	enemy->ypos = (
		zeta_platform->ypos -
		(0.5f * zeta_platform->height) -
		(0.5f * enemy->height)
	);
	enemy->yold = enemy->ypos;
	en_init_view(g, enemy->id);
}

void en_init(struct game * const g)
{
	int count = 0;
	if ((0 >= g->entno) || (EN_MAXNUMOF_ENT < g->entno)) {
		fprintf(stderr, "%s\n", "en_init: InvalidEntityCount");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	en_tag_entity(g);
	en_load_graphic(g);
	en_init_aframes(g);
	for (int i = 0; i != EN_MAXNUMOF_ENT; ++i) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		if (!ent->graphic.data && (EN_CAMERA_TAG != ent->tag)) {
			fprintf(stderr, "%s\n", "en_init: UXNoGraphicsDataEntityError\n");
			goto handle_err;
		}
		if (EN_CAMERA_TAG == ent->tag) {
			en_init_camera(g);
			++count;
		} else if (EN_SONIC_TAG == ent->tag) {
			en_init_sonic(g);
			++count;
		} else if (EN_PLATFORM_TAG == ent->tag) {
			en_init_platform(g, i);
			++count;
		} else if (EN_ENEMY_TAG == ent->tag) {
			en_init_enemy(g, i);
			++count;
		}
	}
	if (EN_MAXNUMOF_ENT != count) {
		fprintf(stderr, "%s\n", "en_init: UXUnhandledEntitiesError");
		goto handle_err;
	}
	en_init_framebuffers(g);
	return;
handle_err:
	{
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
}

static void en_update_animation(
		struct game * const g,
		int const id_entity,
		int const animno
)
{
	struct entity * const ent = &g->ents[id_entity];
	struct animation const * const anims = ent->animations;
	struct animation const * const an = &anims[animno];
	if ((EN_ENEMY_TAG == ent->tag) && (GAME_ENEMY_EXPLODE == ent->explode)) {
		int const ticks = (g->frameno - ent->frameno);
		int aframecur = 0;
		if (an->tickcount_aframe_sequence <= ticks) {
			aframecur = (an->count - 1);
		} else {
			aframecur = (ticks / an->tickcount_aframe);
		}
		ent->animations[animno].aframecur = aframecur;
		return;
	}
	int const rem = g->frameno % an->tickcount_aframe_sequence;
	int const aframecur = (rem / an->tickcount_aframe);
	ent->animations[animno].aframecur = aframecur;
	ent->animno = animno;
}

static void en_update_camera(struct game * const g)
{
	float const time_step = GAME_PERIOD_SEC;
	struct entity * const entities = g->ents;
	struct entity * const ent = &entities[EN_CAMERA_ID];
	struct entity * const sonic = &entities[EN_SONIC_ID];
	struct entity const * const beta_platform = &entities[EN_PLATFORM_BETA_ID];
	struct entity const * const zeta_platform = &entities[EN_PLATFORM_ZETA_ID];
	float const beacon_ypos = (
			sonic->ypos -
			(0.5f * sonic->height) -
			(ent->height)
	);
	float const base = (
			(1.0f * sonic->height)
	);
	float const dist = ((ent->ypos - beacon_ypos) / base);
	float const d2 = (dist * dist);
	float const r = (ent->ypos - sonic->ypos);
	float const r2 = (r * r);
	float const overlap = 0.5f * (ent->height + sonic->height);
	float const overlap2 = overlap * overlap;
	float yvel = 0;
	if (((1.5f * overlap2) >= r2) && (overlap2 < r2)) {
		if (0 > sonic->view.yrel) {
			yvel = -(d2 * GAME_CAMERA_CATCHUP_YVEL);
		} else {
			yvel = (d2 * GAME_CAMERA_CATCHUP_YVEL);
		}
	} else if (((1.5f * overlap2) < r2)) {
		yvel = 1.005f * sonic->yvel;
	} else {
		yvel = 0;
	}
	ent->yvel = yvel;
	ent->xpos += (time_step * ent->xvel);
	ent->ypos += (time_step * ent->yvel);
}

static int en_map_platform(
		struct game * const g,
		int const id
)
{
	int platform_id = EN_PLATFORM_BETA_ID;
	struct entity const * const platform = &g->ents[platform_id];
	struct entity const * const ent = &g->ents[id];
	if (
		((platform->xpos - 0.5f * platform->width) > ent->xpos) ||
		((platform->xpos + 0.5f * platform->width) <= ent->xpos)
	   ) {
		platform_id = EN_PLATFORM_ZETA_ID;
	}
	return platform_id;
}

static void en_check_falling(
		struct game * const gp,
		int const platform_id,
		int const id
)
{
	struct entity const * const platform = &gp->ents[platform_id];
	struct entity * const ent = &gp->ents[id];
	ent->frameno = 0;
	ent->tickno = 0;
	ent->yv00 = 0;
	ent->yvel = 0;
	ent->yold = 0;
	float const contact = (
			platform->ypos - 0.5f * platform->height
	);
	if (contact != (ent->ypos + 0.5f * ent->height)) {
		ent->contact = !GAME_PLATFORM_CONTACT;
		ent->falling = GAME_ENTITY_FALLING;
		ent->frameno = gp->frameno;
		ent->tickno = 1;
		ent->yv00 = 0;
		ent->yvel = 0;
		ent->yold = ent->ypos;
		if (EN_SONIC_TAG == ent->tag) {
			ent->animno = EN_SONIC_SPIN_AN;
		}
	}
}

static void en_apply_gravity(
		struct game * const gp,
		int const platform_id,
		int const id
)
{
	struct entity const * const platform = &gp->ents[platform_id];
	struct entity * const ent = &gp->ents[id];
	float const game_period = GAME_PERIOD_SEC;
	float const time = (
			(gp->frameno - ent->frameno) * game_period
	);
	float const t = time;
	float const g = GAME_GRAVITY_ACCELERATION;
	float const floor = (
			platform->ypos -
			(0.5f * platform->height) -
			(0.5f * ent->height)
	);
	ent->yvel = (ent->yv00 + g * t);
	ent->ypos = (
			ent->yold +
			(ent->yv00 * t) +
			(0.5f * g * t * t)
	);
	ent->ypos = MIN(ent->ypos, floor);
	if (floor == ent->ypos) {
		if (EN_SONIC_TAG == ent->tag) {
			ent->animno = EN_SONIC_RUN_AN;
			ent->hitting = !GAME_ENEMY_HITTING;
		}
		ent->falling = !GAME_ENTITY_FALLING;
		ent->contact = GAME_PLATFORM_CONTACT;
		ent->yvel = 0;
		ent->yv00 = 0;
		ent->frameno = 0;
		ent->tickno = 0;
	} else {
		if (EN_SONIC_TAG == ent->tag) {
			if (GAME_ENEMY_HITTING == ent->hitting) {
				if (0 < ent->yvel) {
					ent->hitting = !GAME_ENEMY_HITTING;
				}
			}
		}
		ent->tickno++;
	}
}

static void en_enemy_hitting(struct game * const g)
{
	struct entity * const sonic = &g->ents[EN_SONIC_ID];
	for (int id = EN_ENEMY_MOTOBUG_ALPHA_ID; id <= EN_ENEMY_MOTOBUG_KAPPA_ID; ++id) {
		struct entity const * const enemy = &g->ents[id];
		float const contact = (sonic->reff + enemy->reff);
		float const contact2 = (contact * contact);
		float const dx = sonic->xpos - enemy->xpos;
		float const dy = sonic->ypos - enemy->ypos;
		float const r2 = (dx * dx) + (dy * dy);
		if (
			(contact2 >= r2) &&
			(enemy->ypos > sonic->ypos) &&
			(0 < sonic->yvel)
		   ) {
			sonic->hitting = GAME_ENEMY_HITTING;
			sonic->yold = sonic->ypos;
			sonic->yv00 = -(sonic->yvel);
			sonic->frameno = g->frameno;
			sonic->tickno = 1;
			break;
		}
	}
}

static void en_update_sonic(struct game * const g)
{
	float const time_step = GAME_PERIOD_SEC;
	struct entity * const entities = g->ents;
	struct entity * const ent = &entities[EN_SONIC_ID];
	int const platform_id = en_map_platform(g, ent->id);
	struct entity const * platform = &entities[platform_id];
	int animno = ent->animno;

	if ((!GAME_ENEMY_HITTING) == ent->hitting) {
		en_enemy_hitting(g);
	}

	if (GAME_PLATFORM_CONTACT == ent->contact) {
		en_check_falling(g, platform_id, ent->id);
	} else {
		ent->animno = EN_SONIC_SPIN_AN;
		if (!ent->tickno) {
			ent->frameno = g->frameno;
			ent->yv00 = -((float)GAME_SONIC_JUMP_VEL);
			ent->yold = ent->ypos;
			ent->tickno++;
		} else {
			en_apply_gravity(g, platform_id, ent->id);
		}
	}
	ent->xpos += (time_step * ent->xvel);
	en_update_animation(g, ent->id, ent->animno);
	en_set_view(g, ent->id);
}

static void en_update_platform(
		struct game * const g,
		int const id_platform
)
{
	struct entity * const entities = g->ents;
	struct entity const * const camera = &entities[EN_CAMERA_ID];
	struct entity * const ent = &entities[id_platform];
	float const xmin = (
		camera->xpos +
		0.5f * (-(GAME_CAMERA_VIEW_WIDTH))
	);
	if (xmin >= (ent->xpos + (0.5f * ent->width))) {
		ent->xpos += (2.0f * ent->width);
		ent->ypos += GAME_PLATFORM_SHIFT_YPOS;
	}
	en_set_view(g, ent->id);
}

static void en_update_enemy(
		struct game * const g,
		int const id_enemy
)
{
	struct entity * const ent = &g->ents[id_enemy];
	struct entity const * const camera = &g->ents[EN_CAMERA_ID];
	struct entity const * const sonic = &g->ents[EN_SONIC_ID];
	float const time_step = GAME_PERIOD_SEC;
	int const platform_id = en_map_platform(g, ent->id);
	struct entity const * const platform = &g->ents[platform_id];
	float const dx = sonic->xpos - ent->xpos;
	float const dy = sonic->ypos - ent->ypos;
	float const r2 = (dx * dx) + (dy * dy);
	float const contact = (sonic->reff + ent->reff);
	float const contact2 = (contact * contact);
	float const xmin = (camera->xpos + (0.5f * (-(GAME_CAMERA_VIEW_WIDTH))));
	if (contact2 >= r2) {
		if ((!GAME_ENEMY_EXPLODE) == ent->explode) {
			ent->explode = GAME_ENEMY_EXPLODE;
			ent->animno = EN_ENEMY_MOTOBUG_EXPLODE_AN;
			ent->frameno = g->frameno;
		}
	}

	if ((!GAME_ENEMY_EXPLODE) == ent->explode) {
		if (GAME_PLATFORM_CONTACT == ent->contact) {
			en_check_falling(g, platform_id, ent->id);
		} else {
			en_apply_gravity(g, platform_id, ent->id);
		}
	}

	if (xmin >= ent->xpos) {
		ent->xpos += (2.0f * platform->width);
		ent->ypos += GAME_PLATFORM_SHIFT_YPOS;
		ent->explode = !GAME_ENEMY_EXPLODE;
		ent->animno = EN_ENEMY_MOTOBUG_RUN_AN;
		ent->frameno = 0;
	}
	ent->xpos += (time_step * ent->xvel);
	en_update_animation(g, ent->id, ent->animno);
	en_set_view(g, ent->id);
}

void en_update(struct game * const g)
{
	float const time_step = GAME_PERIOD_SEC;
	if (GAME_CAMERA_VIEW_MODE == g->mode) {
		struct entity * const camera = &g->ents[EN_CAMERA_ID];
		camera->xpos += (time_step * camera->xvel);
		camera->ypos += (time_step * camera->yvel);
		camera->xvel = 0;
		camera->yvel = 0;
		for (int i = (EN_CAMERA_ID + 1); i != EN_MAXNUMOF_ENT; ++i) {
			struct entity * const ent = &g->ents[i];
			en_set_view(g, ent->id);
		}
		return;
	}
	for (int i = 0; i != g->entno; ++i) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		if (EN_CAMERA_TAG == ent->tag) {
			en_update_camera(g);
		} else if (EN_SONIC_TAG == ent->tag) {
			en_update_sonic(g);
		} else if (EN_PLATFORM_TAG == ent->tag) {
			int const id_platform = i;
			en_update_platform(g, id_platform);
		} else if (EN_ENEMY_TAG == ent->tag) {
			int const id_enemy = i;
			en_update_enemy(g, id_enemy);
		}
	}
}
