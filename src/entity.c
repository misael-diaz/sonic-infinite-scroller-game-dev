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
		animations[animno].tickcount_aframe_sequence = EN_AFRAME_COUNT;
		animations[animno].tickcount_aframe = 1;
		animations[animno].name = EN_PLATFORM_FRAME_NAME;
		animations[animno].count = 1;
		animations[animno].id = animno;
	}
}

static void en_init_aframes(struct game * const g)
{
	en_init_sonic_aframes(g);
	en_init_platform_aframes(g, EN_PLATFORM_BETA_ID);
	en_init_platform_aframes(g, EN_PLATFORM_ZETA_ID);
}

static void en_init_entity_framebuffer(
		struct game * const g,
		int const id
)
{
	struct entity * const entities = g->ents;
	struct entity * const ent = &entities[id];
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
	en_init_entity_framebuffer(g, EN_SONIC_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_BETA_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_ZETA_ID);
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
	en_init_aframes(g);
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
			ent->xvis = ent->xpos;
			ent->yvis = ent->ypos;
			ent->xvel = 0;
			ent->yvel = 0;
			ent->xmin = 0;
			ent->ymin = 0;
			ent->xmax = (width_game_window - ent->graphic.info.width);
			ent->ymax = (height_game_window - ent->graphic.info.height);
			ent->width = ent->animations[0].aframes[0].width;
			ent->height = ent->animations[0].aframes[0].height;
			ent->animno = EN_SONIC_RUN_AN;
		} else if (EN_PLATFORM_TAG == ent->tag) {
			struct entity * const sonic = &entities[EN_SONIC_ID];
			ent->tag = EN_PLATFORM_TAG;
			ent->id = i;
			ent->xvel = -GAME_PLATFORM_VEL;
			ent->yvel = 0;
			ent->xmin = -((float) ent->graphic.info.width);
			ent->ymin = 0;
			ent->xmax = ent->graphic.info.width;
			ent->ymax = (height_game_window - ent->graphic.info.height);
			ent->height = ent->animations[0].aframes[0].height;
			if (EN_PLATFORM_BETA_ID == i) {
				ent->xpos = 0;
				ent->xoff = 0;
				ent->xvis = 0;
				ent->width = ent->animations[0].aframes[0].width;
			} else if (EN_PLATFORM_ZETA_ID == i) {
				ent->xpos = ent->xmax;
				ent->xoff = 0;
				ent->xvis = ent->xmax;
				ent->width = 0;
			}
			ent->yoff = 0;
			ent->ypos = (
					sonic->ypos +
					sonic->height
			);
			ent->yvis = ent->ypos;
		}
	}
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

void en_update(struct game * const g)
{
	float const time_step = GAME_PERIOD_SEC;
	for (int i = 0; i != g->entno; ++i) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		if (EN_SONIC_TAG == ent->tag) {
			int const animno = ent->animno;
			struct animation const * const an = &ent->animations[animno];
			int const rem = (g->frameno % an->tickcount_aframe_sequence);
			int const aframecur = (rem / an->tickcount_aframe);
			ent->animations[animno].aframecur = aframecur;
		} else if (EN_PLATFORM_TAG == ent->tag) {
			ent->xpos += (time_step * ent->xvel);
			if (0 > ent->xpos) {
				ent->xvis = 0;
				ent->xoff = -ent->xpos;
				ent->width = (ent->graphic.info.width + ent->xpos);
			} else {
				ent->xvis = ent->xpos;
				ent->xoff = 0;
				ent->width = (ent->graphic.info.width - ent->xpos);
			}
			ent->xpos = en_clamp(ent->xpos, ent->xmin, ent->xmax);
			if (ent->xmin == ent->xpos) {
				ent->xpos = ent->xmax;
				ent->xvis = ent->xmax;
				ent->xoff = 0;
				ent->width = 0;
			}
		}
	}
}
