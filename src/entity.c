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
#include <time.h>
#include <math.h>
#include "graphic.h"
#include "video.h"
#include "entity.h"

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
	for (int i = 0; i != EN_MAXNUMOF_ENT; ++i, ++count) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		if (EN_SONIC_ID == i) {
			ent->tag = EN_SONIC_TAG;
			ent->id = EN_SONIC_ID;
		} else if (EN_PLATFORM_BETA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_BETA_ID;
		} else if (EN_PLATFORM_ZETA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_ZETA_ID;
		}
	}
	if (EN_MAXNUMOF_ENT != count) {
		fprintf(stderr, "%s\n", "en_load_graphic: UXUnhandledEntitiesError");
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
}

static void en_load_graphic(struct game * const g)
{
	int count = 0;
	for (int i = 0; i != EN_MAXNUMOF_ENT; ++i, ++count) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		if (EN_SONIC_ID == i) {
			ent->tag = EN_SONIC_TAG;
			ent->id = EN_SONIC_ID;
		} else if (EN_PLATFORM_BETA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_BETA_ID;
		} else if (EN_PLATFORM_ZETA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_ZETA_ID;
		}
	}
	if (EN_MAXNUMOF_ENT != count) {
		fprintf(stderr, "%s\n", "en_load_graphic: UXUnhandledEntitiesError");
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	count = 0;
	for (int i = 0; i != EN_MAXNUMOF_ENT; ++i, ++count) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		struct graphic * const graphicp = &ent->graphic;
		if (EN_SONIC_TAG == ent->tag) {
			graphicp->name = GAME_SONIC_GRAPHIC_FP;
			if (GAME_ERROR_RC == graph_load_graphic(graphicp)) {
				fprintf(stderr,
					"%s\n",
					"en_load_graphic: UXLoadGraphicError");
				goto handle_err;
			}
		} else if (EN_PLATFORM_TAG == ent->tag) {
			graphicp->name = GAME_PLATFORM_GRAPHIC_FP;
			if (GAME_ERROR_RC == graph_load_graphic(graphicp)) {
				fprintf(stderr,
					"%s\n",
					"en_load_graphic: UXLoadGraphicError");
				goto handle_err;
			}
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

void en_init_aframes(struct game * const g)
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

void en_init_framebuffers(struct game * const g)
{
	struct entity * const entities = g->ents;
	struct entity * const sonic = &entities[EN_SONIC_ID];
	int const offset = 0;
	int const bitmap_pad = 32;
	int const bytes_per_line = (sonic->graphic.info.width * sizeof(int));
	sonic->framebuffer = XCreateImage(
			g->display,
			g->visual,
			g->screen_depth,
			ZPixmap,
			offset,
			(void*) sonic->graphic.data,
			sonic->graphic.info.width,
			sonic->graphic.info.height,
			bitmap_pad,
			bytes_per_line
	);
	if (!sonic->framebuffer) {
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	sonic->graphic.binded = GAME_BINDED_GRAPHIC;
}

void en_init(struct game * const g)
{
	if ((0 >= g->entno) || (EN_MAXNUMOF_ENT < g->entno)) {
		fprintf(stderr, "%s\n", "en_init: InvalidEntityCount");
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	en_tag_entity(g);
	en_load_graphic(g);
	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	for (int i = 0; i != EN_MAXNUMOF_ENT; ++i) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		if (!ent->graphic.data) {
			fprintf(stderr, "%s\n", "en_init: UXNoGraphicsDataEntityError\n");
			goto handle_err;
		}
		if (EN_SONIC_TAG == ent->tag) {
			ent->tag = EN_SONIC_TAG;
			ent->id = i;
			ent->xpos = (0.5f * width_game_window);
			ent->ypos = (0.5f * height_game_window);
			ent->xvel = 0;
			ent->yvel = 0;
			ent->xmin = 0;
			ent->ymin = 0;
			ent->xmax = (width_game_window - ent->graphic.info.width);
			ent->ymax = (height_game_window - ent->graphic.info.height);
			ent->animno = EN_SONIC_RUN_AN;
		} else if (EN_PLATFORM_TAG == ent->tag) {
			if (EN_PLATFORM_BETA_ID == i) {
				ent->xpos = 0;
			} else if (EN_PLATFORM_ZETA_ID == i) {
				ent->xpos = ent->graphic.info.width;
			}
			ent->tag = EN_PLATFORM_TAG;
			ent->id = i;
			ent->ypos = (0.5 * height_game_window);
			ent->xvel = 0;
			ent->yvel = 0;
			ent->xmin = -ent->graphic.info.width;
			ent->ymin = 0;
			ent->xmax = (width_game_window + ent->graphic.info.width);
			ent->ymax = (height_game_window - ent->graphic.info.height);
		}
	}
	en_init_aframes(g);
	en_init_framebuffers(g);
	return;
handle_err:
	{
		for (int i = 0; i != EN_MAXNUMOF_ENT; ++i) {
			struct entity * const entities = g->ents;
			struct entity * const ent = &entities[i];
			struct graphic * const graphicp = &ent->graphic;
			graph_unload_graphic(graphicp);
		}
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
}

// TODO: clamping platform coords is not compatible with the infinite scrolling gameplay;
//       you need to define a visible region for the platforms
void en_update(struct game * const g)
{
	float const time_step = GAME_PERIOD_SEC;
	for (int i = 0; i != g->entno; ++i) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		if (ent->xvel || ent->yvel) {
			fprintf(stderr, "%s\n", "en_update: NotImplError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
		if (EN_SONIC_TAG == ent->tag) {
			int const animno = ent->animno;
			struct animation const * const an = &ent->animations[animno];
			int const rem = (g->frameno % an->tickcount_aframe_sequence);
			int const aframecur = (rem / an->tickcount_aframe);
			ent->animations[animno].aframecur = aframecur;
		} else if (EN_PLATFORM_TAG == ent->tag) {
			ent->xpos += (time_step * ent->xvel);
			ent->ypos += (time_step * ent->yvel);
		}
	}
}
