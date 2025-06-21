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
#include "system.h"
#include "graphic.h"
#include "video.h"
#include "entity.h"

#define MIN(x, y) ((x) < (y))? (x) : (y)
#define MAX(x, y) ((x) > (y))? (x) : (y)

static int en_compare_platforms(
		struct entity const * const platform_1,
		struct entity const * const platform_2
)
{
	int const x1 = platform_1->xpos;
	int const y1 = platform_1->ypos;
	int const x2 = platform_2->xpos;
	int const y2 = platform_2->ypos;
	if (x1 != x2) {
		return (x1 - x2);
	} else {
		return (y1 - y2);
	}
}

static void en_sort_platforms(struct game * const g)
{
	int * const ids = g->platform_ids;
	int const numel = EN_PLATFORM_MAX;
	// loop-invariant: the elements in the arange [0, i) are sorted
	for (int i = 0; i != numel; ++i) {
		int loc = (i - 1);
		int const id_platform = ids[i];
		struct entity const * const in = &g->ents[id_platform];
		while ((0 <= loc) && (0 < en_compare_platforms(&g->ents[ids[loc]], in))) {
			ids[loc + 1] = ids[loc];
			--loc;
		}
		ids[loc + 1] = id_platform;
	}

	for (int i = 0; i != numel; ++i) {
		int const id_platform = g->platform_ids[i];
		struct entity const * const platform = &g->ents[id_platform];
		if (EN_PLATFORM_TAG != platform->tag) {
			fprintf(stderr,
				"%s\n",
				"en_sort_platforms: "
				"ImplPlatformEntityError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i != (numel - 1); ++i) {
		int const id_platform = g->platform_ids[i];
		int const id_next_platform = g->platform_ids[i + 1];
		struct entity const * const platform = &g->ents[id_platform];
		struct entity const * const next_platform = &g->ents[id_next_platform];
		if (
			(0 < en_compare_platforms(platform, next_platform)) ||
			(0 == en_compare_platforms(platform, next_platform))
		   ) {
			fprintf(stderr,
				"%s\n",
				"en_sort_platforms: "
				"ImplPlatformSortingError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i != numel; ++i) {
		int const platfno = i;
		int const id_platform = g->platform_ids[platfno];
		struct entity * const platform = &g->ents[id_platform];
		platform->platfno = platfno;
	}

	g->sorted_platforms = GAME_SORTED_PLATFORMS;
}

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
		} else if (EN_LVLMAP_ID == i) {
			ent->tag = EN_LVLMAP_TAG;
			ent->id = EN_LVLMAP_ID;
			++count;
		} else if (EN_BLOCK_BETA_ID == i) {
			ent->tag = EN_BLOCK_TAG;
			ent->id = EN_BLOCK_BETA_ID;
			++count;
		} else if (EN_BLOCK_ZETA_ID == i) {
			ent->tag = EN_BLOCK_TAG;
			ent->id = EN_BLOCK_ZETA_ID;
			++count;
		} else if (EN_GOAL_ID == i) {
			ent->tag = EN_GOAL_TAG;
			ent->id = EN_GOAL_ID;
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
		} else if (EN_PLATFORM_IOTA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_IOTA_ID;
			++count;
		} else if (EN_PLATFORM_ETA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_ETA_ID;
			++count;
		} else if (EN_PLATFORM_RHO_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_RHO_ID;
			++count;
		} else if (EN_PLATFORM_TAU_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_TAU_ID;
			++count;
		} else if (EN_PLATFORM_PHI_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_PHI_ID;
			++count;
		} else if (EN_PLATFORM_CHI_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_CHI_ID;
			++count;
		} else if (EN_PLATFORM_PSI_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_PSI_ID;
			++count;
		} else if (EN_PLATFORM_EPSILON_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_EPSILON_ID;
			++count;
		} else if (EN_PLATFORM_LAMBDA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_LAMBDA_ID;
			++count;
		} else if (EN_PLATFORM_OMICRON_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_OMICRON_ID;
			++count;
		} else if (EN_PLATFORM_SIGMA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_SIGMA_ID;
			++count;
		} else if (EN_PLATFORM_UPSILON_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_UPSILON_ID;
			++count;
		} else if (EN_PLATFORM_MU_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_MU_ID;
			++count;
		} else if (EN_PLATFORM_NU_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_NU_ID;
			++count;
		} else if (EN_PLATFORM_PI_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_PI_ID;
			++count;
		} else if (EN_PLATFORM_XI_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_XI_ID;
			++count;
		} else if (EN_PLATFORM_OMEGA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_OMEGA_ID;
			++count;
		} else if (EN_PLATFORM_ALPHA_ID == i) {
			ent->tag = EN_PLATFORM_TAG;
			ent->id = EN_PLATFORM_ALPHA_ID;
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
			struct entity * const camera = ent;
			memset(&camera->graphic, 0, sizeof(camera->graphic));
			camera->graphic.name = GAME_ENTITY_NOGRAPHIC_FP;
			camera->graphic.data = NULL;
			camera->graphic.loaded = !GAME_LOADED_GRAPHIC;
			camera->graphic.binded = !GAME_BINDED_GRAPHIC;
			++count;
		} else if (EN_LVLMAP_TAG == ent->tag) {
			struct entity * const lvlmap = ent;
			memset(&lvlmap->graphic, 0, sizeof(lvlmap->graphic));
			lvlmap->graphic.name = GAME_ENTITY_NOGRAPHIC_FP;
			lvlmap->graphic.data = NULL;
			lvlmap->graphic.loaded = !GAME_LOADED_GRAPHIC;
			lvlmap->graphic.binded = !GAME_BINDED_GRAPHIC;
			++count;
		} else if (EN_BLOCK_TAG == ent->tag) {
			struct entity * const block = ent;
			memset(&block->graphic, 0, sizeof(block->graphic));
			block->graphic.name = GAME_ENTITY_NOGRAPHIC_FP;
			block->graphic.data = NULL;
			block->graphic.loaded = !GAME_LOADED_GRAPHIC;
			block->graphic.binded = !GAME_BINDED_GRAPHIC;
			++count;
		} else if (EN_GOAL_TAG == ent->tag) {
			graphicp->name = GAME_GOAL_GRAPHIC_FP;
			if (GAME_ERROR_RC == graph_load_graphic(graphicp)) {
				fprintf(stderr,
					"%s\n",
					"en_load_graphic: UXLoadGraphicError");
				goto handle_err;
			}
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

static void en_init_lvlmap_aframes(struct game * const g)
{
	struct entity * const entities = g->ents;
	struct entity * const lvlmap = &entities[EN_LVLMAP_ID];
	struct animation * const animations = lvlmap->animations;
	int const width_lvlmap = GAME_LVLMAP_WIDTH;
	int const height_lvlmap = GAME_LVLMAP_HEIGHT;
	for (int animno = 0; animno != EN_ANIMATIONS_COUNT; ++animno) {
		for (int aframeno = 0; aframeno != EN_AFRAME_COUNT; ++aframeno) {
			animations[animno].aframes[aframeno].id = aframeno;
			animations[animno].aframes[aframeno].xof = 0;
			animations[animno].aframes[aframeno].yof = 0;
			animations[animno].aframes[aframeno].width = width_lvlmap;
			animations[animno].aframes[aframeno].height = height_lvlmap;
		}
		animations[animno].tickcount_aframe_sequence = EN_AFRAME_COUNT;
		animations[animno].tickcount_aframe = 1;
		animations[animno].name = EN_LVLMAP_FRAME_NAME;
		animations[animno].count = 1;
		animations[animno].id = animno;
	}
}

static void en_init_block_aframes(
		struct game * const g,
		int const id_block
)
{
	struct entity * const entities = g->ents;
	struct entity * const block = &entities[id_block];
	struct animation * const animations = block->animations;
	int const width_block = GAME_BLOCK_WIDTH;
	int const height_block = GAME_BLOCK_HEIGHT;
	for (int animno = 0; animno != EN_ANIMATIONS_COUNT; ++animno) {
		for (int aframeno = 0; aframeno != EN_AFRAME_COUNT; ++aframeno) {
			animations[animno].aframes[aframeno].id = aframeno;
			animations[animno].aframes[aframeno].xof = 0;
			animations[animno].aframes[aframeno].yof = 0;
			animations[animno].aframes[aframeno].width = width_block;
			animations[animno].aframes[aframeno].height = height_block;
		}
		animations[animno].tickcount_aframe_sequence = EN_AFRAME_COUNT;
		animations[animno].tickcount_aframe = 1;
		animations[animno].name = EN_BLOCK_FRAME_NAME;
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

static void en_init_goal_aframes(struct game * const g)
{
	struct entity * const goal = &g->ents[EN_GOAL_ID];
	struct animation * const animations = goal->animations;
	int const width_goal = goal->graphic.info.width;
	int const height_goal = goal->graphic.info.height;
	for (int animno = 0; animno != EN_ANIMATIONS_COUNT; ++animno) {
		for (int aframeno = 0; aframeno != EN_AFRAME_COUNT; ++aframeno) {
			animations[animno].aframes[aframeno].id = aframeno;
			animations[animno].aframes[aframeno].xof = 0;
			animations[animno].aframes[aframeno].yof = 0;
			animations[animno].aframes[aframeno].width = width_goal;
			animations[animno].aframes[aframeno].height = height_goal;
		}
		animations[animno].tickcount_aframe_sequence = EN_GOAL_AFRAME_COUNT;
		animations[animno].tickcount_aframe = EN_GOAL_AFRAME_COUNT;
		animations[animno].name = EN_GOAL_FRAME_NAME;
		animations[animno].count = EN_GOAL_AFRAME_COUNT;
		animations[animno].id = animno;
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
	en_init_lvlmap_aframes(g);
	en_init_goal_aframes(g);
	en_init_sonic_aframes(g);
	en_init_platform_aframes(g, EN_PLATFORM_BETA_ID);
	en_init_platform_aframes(g, EN_PLATFORM_ZETA_ID);
	en_init_platform_aframes(g, EN_PLATFORM_IOTA_ID);
	en_init_platform_aframes(g, EN_PLATFORM_ETA_ID);
	en_init_platform_aframes(g, EN_PLATFORM_RHO_ID);
	en_init_platform_aframes(g, EN_PLATFORM_TAU_ID);
	en_init_platform_aframes(g, EN_PLATFORM_PHI_ID);
	en_init_platform_aframes(g, EN_PLATFORM_CHI_ID);
	en_init_platform_aframes(g, EN_PLATFORM_PSI_ID);
	en_init_platform_aframes(g, EN_PLATFORM_EPSILON_ID);
	en_init_platform_aframes(g, EN_PLATFORM_LAMBDA_ID);
	en_init_platform_aframes(g, EN_PLATFORM_OMICRON_ID);
	en_init_platform_aframes(g, EN_PLATFORM_SIGMA_ID);
	en_init_platform_aframes(g, EN_PLATFORM_UPSILON_ID);
	en_init_platform_aframes(g, EN_PLATFORM_MU_ID);
	en_init_platform_aframes(g, EN_PLATFORM_NU_ID);
	en_init_platform_aframes(g, EN_PLATFORM_PI_ID);
	en_init_platform_aframes(g, EN_PLATFORM_XI_ID);
	en_init_platform_aframes(g, EN_PLATFORM_OMEGA_ID);
	en_init_platform_aframes(g, EN_PLATFORM_ALPHA_ID);
	en_init_block_aframes(g, EN_BLOCK_BETA_ID);
	en_init_block_aframes(g, EN_BLOCK_ZETA_ID);
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
	en_init_entity_framebuffer(g, EN_LVLMAP_ID);
	en_init_entity_framebuffer(g, EN_GOAL_ID);
	en_init_entity_framebuffer(g, EN_SONIC_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_BETA_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_ZETA_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_IOTA_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_ETA_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_RHO_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_TAU_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_PHI_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_CHI_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_PSI_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_EPSILON_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_LAMBDA_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_OMICRON_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_SIGMA_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_UPSILON_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_MU_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_NU_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_PI_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_XI_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_OMEGA_ID);
	en_init_entity_framebuffer(g, EN_PLATFORM_ALPHA_ID);
	en_init_entity_framebuffer(g, EN_BLOCK_BETA_ID);
	en_init_entity_framebuffer(g, EN_BLOCK_ZETA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_ALPHA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_GAMMA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_DELTA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_THETA_ID);
	en_init_entity_framebuffer(g, EN_ENEMY_MOTOBUG_KAPPA_ID);
}

static void en_set_view(
		struct game * const g,
		struct enview * const view,
		float const width,
		float const height,
		float const xmin,
		float const xmax,
		float const ymin,
		float const ymax
)
{
	float const window_height = (ymax - ymin);
	float const window_width = (xmax - xmin);
	view->xedg = (
			view->xrel +
			(0.5f * width) * view->N[EN_ENVIEW_W].x
	);
	view->yedg = (
			view->yrel +
			(0.5f * height) * view->N[EN_ENVIEW_S].y
	);
	if ((xmin > (view->xedg + width)) || (xmax < view->xedg)) {
		view->xedg = 0;
		view->yedg = 0;
		view->xscr = 0;
		view->yscr = 0;
		view->xoff = 0;
		view->yoff = 0;
		view->width = 0;
		view->height = 0;
		return;
	}
	if ((ymin > (view->yedg + height)) || (ymax < view->yedg)) {
		view->xedg = 0;
		view->yedg = 0;
		view->xscr = 0;
		view->yscr = 0;
		view->xoff = 0;
		view->yoff = 0;
		view->width = 0;
		view->height = 0;
		return;
	}

	if (
		(xmin > (view->xedg + width)) ||
		(xmax < view->xedg) ||
		(ymin > (view->yedg + height)) ||
		(ymax < view->yedg)
	   ) {
		fprintf(stderr, "%s\n", "en_set_view: ImplCameraViewBoundsError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	if (xmin > view->xedg) {
		view->xoff = xmin - view->xedg;
		if (xmax > (view->xedg + width)) {
			view->width = width - view->xoff;
		} else {
			view->width = window_width;
		}
	} else {
		view->xoff = 0;
		if (xmax > (view->xedg + width)) {
			view->width = width;
		} else {
			view->width = xmax - view->xedg;
		}
	}

	if (ymin > view->yedg) {
		view->yoff = ymin - view->yedg;
		if (ymax > (view->yedg + height)) {
			view->height = height - view->yoff;
		} else {
			view->height = window_height;
		}
	} else {
		view->yoff = 0;
		if (ymax > (view->yedg + height)) {
			view->height = height;
		} else {
			view->height = ymax - view->yedg;
		}
	}

	view->xedg = en_clamp(view->xedg, xmin, xmax);
	view->yedg = en_clamp(view->yedg, ymin, ymax);
	view->xscr = view->xedg + view->xref;
	view->yscr = view->yedg + view->yref;
}

static void en_set_screenview(
		struct game * const g,
		int const id
)
{
	float const xmin = (0.5f * (-(GAME_CAMERA_VIEW_WIDTH)));
	float const xmax = (0.5f * (+(GAME_CAMERA_VIEW_WIDTH)));
	float const ymin = (0.5f * (-(GAME_CAMERA_VIEW_HEIGHT)));
	float const ymax = (0.5f * (+(GAME_CAMERA_VIEW_HEIGHT)));
	struct entity const * const camera = &g->ents[EN_CAMERA_ID];
	struct entity * const ent = &g->ents[id];
	struct enview * const view = &ent->view;
	float const width = ent->width;
	float const height = ent->height;
	ent->view.xrel = ent->xpos - camera->xpos;
	ent->view.yrel = ent->ypos - camera->ypos;
	en_set_view(
			g,
			view,
			width,
			height,
			xmin,
			xmax,
			ymin,
			ymax
		   );
	if ((EN_ENEMY_TAG == ent->tag) || (EN_SONIC_TAG == ent->tag)) {
		int const animno = ent->animno;
		int const aframecur = ent->animations[animno].aframecur;
		ent->view.xoff += ent->animations[animno].aframes[aframecur].xof;
		ent->view.yoff += ent->animations[animno].aframes[aframecur].yof;
	}
}

static void en_set_mapview(
		struct game * const g,
		int const id
)
{
	float const xmin = (0.5f * (-(GAME_LVLMAP_VIEW_WIDTH)));
	float const xmax = (0.5f * (+(GAME_LVLMAP_VIEW_WIDTH)));
	float const ymin = (0.5f * (-(GAME_LVLMAP_VIEW_HEIGHT)));
	float const ymax = (0.5f * (+(GAME_LVLMAP_VIEW_HEIGHT)));
	struct entity * const ent = &g->ents[id];
	struct enview * const mapview = &ent->mapview;
	float const width = ent->wmap;
	float const height = ent->hmap;
	ent->mapview.xrel = ent->xmap - ent->mapview.xref;
	ent->mapview.yrel = ent->ymap - ent->mapview.yref;
	en_set_view(
			g,
			mapview,
			width,
			height,
			xmin,
			xmax,
			ymin,
			ymax
		   );
}

static void en_init_norm(
		struct enview * const view
)
{
	view->N[EN_ENVIEW_E].x = 1;
	view->N[EN_ENVIEW_E].y = 0;
	view->N[EN_ENVIEW_N].x = 0;
	view->N[EN_ENVIEW_N].y = 1;
	view->N[EN_ENVIEW_W].x =-1;
	view->N[EN_ENVIEW_W].y = 0;
	view->N[EN_ENVIEW_S].x = 0;
	view->N[EN_ENVIEW_S].y =-1;
}

static void en_init_view(
		struct game * const g,
		int const id
)
{
	struct entity * const ent = &g->ents[id];
	en_init_norm(&ent->view);
	en_init_norm(&ent->mapview);
	en_set_screenview(g, id);
	if (
		(EN_PLATFORM_TAG == ent->tag) ||
		(EN_SONIC_TAG == ent->tag) ||
		(EN_GOAL_TAG == ent->tag)
	   ) {
		en_set_mapview(g, id);
	}
}

static void en_init_camera(struct game * const g)
{
	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	struct entity * const camera = &g->ents[EN_CAMERA_ID];
	camera->name = EN_CAMERA_NM;
	camera->xpos = (0.5f * width_game_window);
	camera->ypos = (0.5f * height_game_window);
	camera->xold = GAME_CAMERA_XVEL;
	camera->yold = GAME_CAMERA_YVEL;
	camera->ymin = GAME_CAMERA_YVEL;
	camera->ymax = GAME_CAMERA_YVEL;
	camera->xvel = GAME_CAMERA_XVEL;
	camera->yvel = GAME_CAMERA_YVEL;
	camera->xv00 = GAME_CAMERA_XVEL;
	camera->yv00 = GAME_CAMERA_YVEL;
	camera->xmap = EN_IGNORE_PROPERTY;
	camera->ymap = EN_IGNORE_PROPERTY;
	camera->wmap = EN_IGNORE_PROPERTY;
	camera->hmap = EN_IGNORE_PROPERTY;
	camera->xvcol = EN_IGNORE_PROPERTY;
	camera->yvcol = EN_IGNORE_PROPERTY;
	camera->width = camera->animations[0].aframes[0].width;
	camera->height = camera->animations[0].aframes[0].height;
	camera->reff = 0.5f * (0.5f * (camera->width + camera->height));
	camera->flags = 0;
	camera->frameid = EN_IGNORE_PROPERTY;
	camera->platfno = EN_IGNORE_PROPERTY;
	camera->blockno = EN_IGNORE_PROPERTY;
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
	if (camera->flags & EN_INVISIBLE_FLAG) {
		camera->view.width = 0;
		camera->view.height = 0;
	} else {
		camera->view.width = camera->width;
		camera->view.height = camera->height;
	}
}

static void en_init_lvlmap(struct game * const g)
{
	struct entity * const lvlmap = &g->ents[EN_LVLMAP_ID];
	lvlmap->name = EN_LVLMAP_NM;
	lvlmap->xpos = EN_IGNORE_PROPERTY;
	lvlmap->ypos = EN_IGNORE_PROPERTY;
	lvlmap->xold = EN_IGNORE_PROPERTY;
	lvlmap->yold = EN_IGNORE_PROPERTY;
	lvlmap->xvel = EN_IGNORE_PROPERTY;
	lvlmap->yvel = EN_IGNORE_PROPERTY;
	lvlmap->xv00 = EN_IGNORE_PROPERTY;
	lvlmap->yv00 = EN_IGNORE_PROPERTY;
	lvlmap->xscr = EN_IGNORE_PROPERTY;
	lvlmap->yscr = EN_IGNORE_PROPERTY;
	lvlmap->xmap = EN_IGNORE_PROPERTY;
	lvlmap->ymap = EN_IGNORE_PROPERTY;
	lvlmap->wmap = EN_IGNORE_PROPERTY;
	lvlmap->hmap = EN_IGNORE_PROPERTY;
	lvlmap->xvcol = EN_IGNORE_PROPERTY;
	lvlmap->yvcol = EN_IGNORE_PROPERTY;
	lvlmap->width = lvlmap->animations[0].aframes[0].width;
	lvlmap->height = lvlmap->animations[0].aframes[0].height;
	lvlmap->reff = EN_IGNORE_PROPERTY;
	lvlmap->flags = 0;
	lvlmap->frameid = EN_IGNORE_PROPERTY;
	lvlmap->platfno = EN_IGNORE_PROPERTY;
	lvlmap->blockno = EN_IGNORE_PROPERTY;
	lvlmap->frameno = EN_LVLMAP_DEFAULT_AF;
	lvlmap->animno = EN_LVLMAP_DEFAULT_AN;
	lvlmap->tickno = EN_IGNORE_PROPERTY;
	lvlmap->mapview.xref = 0.5f * GAME_LVLMAP_VIEW_WIDTH;
	lvlmap->mapview.yref = 0.5f * GAME_LVLMAP_VIEW_HEIGHT;
	lvlmap->mapview.xrel = 0;
	lvlmap->mapview.yrel = 0;
	lvlmap->mapview.xedg = -0.5f * GAME_LVLMAP_VIEW_WIDTH;
	lvlmap->mapview.yedg = -0.5f * GAME_LVLMAP_VIEW_HEIGHT;
	lvlmap->mapview.xscr = 0;
	lvlmap->mapview.yscr = 0;
	lvlmap->mapview.xoff = 0;
	lvlmap->mapview.yoff = 0;
	lvlmap->mapview.width = GAME_LVLMAP_VIEW_WIDTH;
	lvlmap->mapview.height = GAME_LVLMAP_VIEW_HEIGHT;
}

static void en_init_goal(struct game * const g)
{
	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	float const width_levelmap_window = GAME_LVLMAP_VIEW_WIDTH;
	float const height_levelmap_window = GAME_LVLMAP_VIEW_HEIGHT;
	if (
		(GAME_CAMERA_VIEW_WIDTH != g->screen_width) ||
		(GAME_CAMERA_VIEW_HEIGHT != g->screen_height)
	   ) {
		fprintf(stderr, "%s\n", "en_init_goal: UXScreenDimsError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	struct entity const * const alpha_platform = &g->ents[EN_PLATFORM_ALPHA_ID];
	struct entity * const goal = &g->ents[EN_GOAL_ID];
	goal->name = EN_GOAL_NM;
	goal->xold = EN_IGNORE_PROPERTY;
	goal->yold = EN_IGNORE_PROPERTY;
	goal->xvel = EN_IGNORE_PROPERTY;
	goal->yvel = EN_IGNORE_PROPERTY;
	goal->xv00 = EN_IGNORE_PROPERTY;
	goal->yv00 = EN_IGNORE_PROPERTY;
	goal->xmap = alpha_platform->xmap;
	goal->ymap = alpha_platform->ymap;
	goal->wmap = GAME_LVLMAP_GOAL_WIDTH;
	goal->hmap = GAME_LVLMAP_GOAL_HEIGHT;
	goal->xscr = EN_IGNORE_PROPERTY;
	goal->yscr = EN_IGNORE_PROPERTY;
	goal->reff = EN_IGNORE_PROPERTY;
	goal->width = goal->animations[0].aframes[0].width;
	goal->height = goal->animations[0].aframes[0].height;
	goal->xpos = alpha_platform->xpos;
	goal->ypos = (
		alpha_platform->ypos -
		(0.5f * alpha_platform->height) -
		(0.5f * goal->height)
	);
	goal->flags = EN_FLOOR_FLAG;
	goal->frameid = EN_IGNORE_PROPERTY;
	goal->platfno = EN_IGNORE_PROPERTY;
	goal->blockno = EN_IGNORE_PROPERTY;
	goal->frameno = EN_GOAL_DEFAULT_AF;
	goal->animno = EN_GOAL_DEFAULT_AN;
	goal->tickno = EN_IGNORE_PROPERTY;
	goal->view.xref = (0.5f * width_game_window);
	goal->view.yref = (0.5f * height_game_window);
	goal->view.width = goal->width;
	goal->view.height = goal->height;
	goal->mapview.xref = (0.5f * width_levelmap_window);
	goal->mapview.yref = (0.5f * height_levelmap_window);
	goal->mapview.width = goal->wmap;
	goal->mapview.height = goal->hmap;
	en_init_view(g, goal->id);
}

static void en_init_sonic(struct game * const g)
{
	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	float const width_levelmap_window = GAME_LVLMAP_VIEW_WIDTH;
	float const height_levelmap_window = GAME_LVLMAP_VIEW_HEIGHT;
	if (
		(GAME_CAMERA_VIEW_WIDTH != g->screen_width) ||
		(GAME_CAMERA_VIEW_HEIGHT != g->screen_height)
	   ) {
		fprintf(stderr, "%s\n", "en_init_sonic: UXScreenDimsError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	struct entity const * const beta_platform = &g->ents[EN_PLATFORM_BETA_ID];
	struct entity * const sonic = &g->ents[EN_SONIC_ID];
	sonic->name = EN_SONIC_NM;
	sonic->xold = EN_IGNORE_PROPERTY;
	sonic->ymin = 0;
	sonic->ymax = EN_IGNORE_PROPERTY;
	sonic->wmap = GAME_LVLMAP_SONIC_WIDTH;
	sonic->hmap = GAME_LVLMAP_SONIC_HEIGHT;
	sonic->xvel = GAME_SONIC_XVEL;
	sonic->yvel = GAME_SONIC_YVEL;
	sonic->xv00 = GAME_SONIC_XVEL;
	sonic->yv00 = GAME_SONIC_YVEL;
	sonic->xscr = EN_IGNORE_PROPERTY;
	sonic->yscr = EN_IGNORE_PROPERTY;
	sonic->xvcol = EN_IGNORE_PROPERTY;
	sonic->yvcol = 0;
	sonic->width = sonic->animations[0].aframes[0].width;
	sonic->height = sonic->animations[0].aframes[0].height;
	sonic->reff = 0.5f * (0.5f * (sonic->width + sonic->height));
	sonic->flags = EN_FLOOR_FLAG;
	sonic->frameid = EN_IGNORE_PROPERTY;
	sonic->platfno = EN_IGNORE_PROPERTY;
	sonic->blockno = 0;
	sonic->frameno = EN_SONIC_DEFAULT_AF;
	sonic->animno = EN_SONIC_RUN_AN;
	sonic->tickno = 0;
	sonic->view.xref = (0.5f * width_game_window);
	sonic->view.yref = (0.5f * height_game_window);
	sonic->view.width = sonic->width;
	sonic->view.height = sonic->height;
	sonic->mapview.xref = (0.5f * width_levelmap_window);
	sonic->mapview.yref = (0.5f * height_levelmap_window);
	sonic->mapview.width = sonic->wmap;
	sonic->mapview.height = sonic->hmap;
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
		enum enid const id_platform
)
{
	if (
		(EN_PLATFORM_BETA_ID    != id_platform) &&
		(EN_PLATFORM_ZETA_ID    != id_platform) &&
		(EN_PLATFORM_IOTA_ID    != id_platform) &&
		(EN_PLATFORM_ETA_ID     != id_platform) &&
		(EN_PLATFORM_RHO_ID     != id_platform) &&
		(EN_PLATFORM_TAU_ID     != id_platform) &&
		(EN_PLATFORM_PHI_ID     != id_platform) &&
		(EN_PLATFORM_CHI_ID     != id_platform) &&
		(EN_PLATFORM_PSI_ID     != id_platform) &&
		(EN_PLATFORM_EPSILON_ID != id_platform) &&
		(EN_PLATFORM_LAMBDA_ID  != id_platform) &&
		(EN_PLATFORM_OMICRON_ID != id_platform) &&
		(EN_PLATFORM_SIGMA_ID   != id_platform) &&
		(EN_PLATFORM_UPSILON_ID != id_platform) &&
		(EN_PLATFORM_MU_ID      != id_platform) &&
		(EN_PLATFORM_NU_ID      != id_platform) &&
		(EN_PLATFORM_PI_ID      != id_platform) &&
		(EN_PLATFORM_XI_ID      != id_platform) &&
		(EN_PLATFORM_OMEGA_ID   != id_platform) &&
		(EN_PLATFORM_ALPHA_ID   != id_platform)
	   ) {
		fprintf(stderr, "%s\n", "en_init_platform: InvalidPlatformIdError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	struct entity * const platform = &g->ents[id_platform];
	if (id_platform != platform->id) {
		fprintf(stderr, "%s\n", "en_init_platform: MismatchPlatformIdError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	if (
		(GAME_CAMERA_VIEW_WIDTH != g->screen_width) ||
		(GAME_CAMERA_VIEW_HEIGHT != g->screen_height)
	   ) {
		fprintf(stderr, "%s\n", "en_init_platform: UXScreenDimsError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	float const width_levelmap_window = GAME_LVLMAP_VIEW_WIDTH;
	float const height_levelmap_window = GAME_LVLMAP_VIEW_HEIGHT;
	struct entity * const camera = &g->ents[EN_CAMERA_ID];
	struct entity const * const beta_platform = &g->ents[EN_PLATFORM_BETA_ID];
	struct entity const * const zeta_platform = &g->ents[EN_PLATFORM_ZETA_ID];
	struct entity const * const iota_platform = &g->ents[EN_PLATFORM_IOTA_ID];
	struct entity const * const tau_platform = &g->ents[EN_PLATFORM_TAU_ID];
	struct entity const * const chi_platform = &g->ents[EN_PLATFORM_CHI_ID];
	platform->xold = EN_IGNORE_PROPERTY;
	platform->yold = EN_IGNORE_PROPERTY;
	platform->ymin = EN_IGNORE_PROPERTY;
	platform->ymax = EN_IGNORE_PROPERTY;
	platform->xvel = GAME_PLATFORM_XVEL;
	platform->yvel = GAME_PLATFORM_YVEL;
	platform->xv00 = EN_IGNORE_PROPERTY;
	platform->yv00 = EN_IGNORE_PROPERTY;
	platform->xscr = EN_IGNORE_PROPERTY;
	platform->yscr = EN_IGNORE_PROPERTY;
	platform->xvcol = EN_IGNORE_PROPERTY;
	platform->yvcol = EN_IGNORE_PROPERTY;
	platform->width = platform->animations[0].aframes[0].width;
	platform->height = platform->animations[0].aframes[0].height;
	platform->wmap = GAME_LVLMAP_PLATFORM_WIDTH;
	platform->hmap = GAME_LVLMAP_PLATFORM_HEIGHT;
	platform->reff = EN_IGNORE_PROPERTY;
	platform->flags = 0;
	platform->frameid = EN_IGNORE_PROPERTY;
	platform->platfno = 0;
	platform->blockno = 0;
	platform->frameno = EN_PLATFORM_DEFAULT_AF;
	platform->animno = EN_PLATFORM_DEFAULT_AN;
	platform->tickno = EN_IGNORE_PROPERTY;
	platform->view.xref = (0.5f * width_game_window);
	platform->view.yref = (0.5f * height_game_window);
	platform->view.width = platform->width;
	platform->view.height = platform->height;
	platform->mapview.xref = (0.5f * width_levelmap_window);
	platform->mapview.yref = (0.5f * height_levelmap_window);
	platform->mapview.width = platform->wmap;
	platform->mapview.height = platform->hmap;
	if (EN_PLATFORM_BETA_ID == id_platform) {
		platform->name = EN_PLATFORM_BETA_NM;
		platform->xpos = camera->xpos + GAME_PLATFORM_XREL;
		platform->ypos = (
				camera->ypos +
				GAME_PLATFORM_YREL
		);
		platform->xmap = (
				(0.5f * platform->wmap) +
				(id_platform - EN_PLATFORM_BETA_ID) * platform->wmap
		);
		platform->ymap = (
				height_levelmap_window -
				(0.5f * platform->hmap)
		);
	} else if (EN_PLATFORM_ZETA_ID == id_platform) {
		platform->name = EN_PLATFORM_ZETA_NM;
		platform->xpos = (
				camera->xpos +
				platform->width +
				GAME_PLATFORM_XREL
		);
		platform->ypos = (
				camera->ypos +
				GAME_PLATFORM_YREL
		);
		platform->xmap = (
				(0.5f * platform->wmap) +
				(id_platform - EN_PLATFORM_BETA_ID) * platform->wmap
		);
		platform->ymap = (
				height_levelmap_window -
				(0.5f * platform->hmap)
		);
	} else if (EN_PLATFORM_IOTA_ID == id_platform) {
		platform->name = EN_PLATFORM_IOTA_NM;
		platform->xpos = (
				camera->xpos +
				(2.0f * platform->width) +
				GAME_PLATFORM_XREL
		);
		platform->ypos = (
				camera->ypos +
				GAME_PLATFORM_YREL
		);
		platform->xmap = (
				(0.5f * platform->wmap) +
				(id_platform - EN_PLATFORM_BETA_ID) * platform->wmap
		);
		platform->ymap = (
				height_levelmap_window -
				(0.5f * platform->hmap)
		);
	} else if (EN_PLATFORM_ETA_ID == id_platform) {
		platform->name = EN_PLATFORM_ETA_NM;
		platform->xpos = beta_platform->xpos;
		platform->ypos = (
				beta_platform->ypos -
				(4.0f * platform->height)
		);
		platform->xmap = beta_platform->xmap;
		platform->ymap = (
				beta_platform->ymap -
				GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_PLATFORM_RHO_ID == id_platform) {
		platform->name = EN_PLATFORM_RHO_NM;
		platform->xpos = chi_platform->xpos;
		platform->ypos = (
				chi_platform->ypos -
				(4.0f * platform->height)
		);
		platform->xmap = chi_platform->xmap;
		platform->ymap = (
				chi_platform->ymap -
				GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_PLATFORM_TAU_ID == id_platform) {
		platform->name = EN_PLATFORM_TAU_NM;
		platform->xpos = (
				camera->xpos +
				(3.0f * platform->width) +
				GAME_PLATFORM_XREL
		);
		platform->ypos = (
				camera->ypos +
				GAME_PLATFORM_YREL
		);
		platform->xmap = (
				(0.5f * platform->wmap) +
				(id_platform - EN_PLATFORM_BETA_ID) * platform->wmap
		);
		platform->ymap = (
				height_levelmap_window -
				(0.5f * platform->hmap)
		);
	} else if (EN_PLATFORM_PHI_ID == id_platform) {
		platform->name = EN_PLATFORM_PHI_NM;
		platform->xpos = (
				camera->xpos +
				(4.0f * platform->width) +
				GAME_PLATFORM_XREL
		);
		platform->ypos = (
				camera->ypos +
				GAME_PLATFORM_YREL
		);
		platform->xmap = (
				(0.5f * platform->wmap) +
				(id_platform - EN_PLATFORM_BETA_ID) * platform->wmap
		);
		platform->ymap = (
				height_levelmap_window -
				(0.5f * platform->hmap)
		);
	} else if (EN_PLATFORM_CHI_ID == id_platform) {
		platform->name = EN_PLATFORM_CHI_NM;
		platform->xpos = (
				camera->xpos +
				(5.0f * platform->width) +
				GAME_PLATFORM_XREL
		);
		platform->ypos = (
				camera->ypos +
				GAME_PLATFORM_YREL
		);
		platform->xmap = (
				(0.5f * platform->wmap) +
				(id_platform - EN_PLATFORM_BETA_ID) * platform->wmap
		);
		platform->ymap = (
				height_levelmap_window -
				(0.5f * platform->hmap)
		);
	} else if (EN_SKY_PLATFORM_PSI_ID == id_platform) {
		platform->name = EN_PLATFORM_PSI_NM;
		platform->xpos = beta_platform->xpos;
		platform->ypos = (
				beta_platform->ypos -
				(10.0f * platform->height) -
				GAME_PLATFORM_SHIFT_YPOS
		);
		platform->xmap = beta_platform->xmap;
		platform->ymap = (
			beta_platform->ymap -
			2.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_EPSILON_ID == id_platform) {
		platform->name = EN_PLATFORM_EPSILON_NM;
		platform->xpos = zeta_platform->xpos;
		platform->ypos = (
				zeta_platform->ypos -
				(18.0f * platform->height) -
				GAME_PLATFORM_SHIFT_YPOS
		);
		platform->xmap = zeta_platform->xmap;
		platform->ymap = (
			zeta_platform->ymap -
			3.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_LAMBDA_ID == id_platform) {
		platform->name = EN_PLATFORM_LAMBDA_NM;
		platform->xpos = tau_platform->xpos;
		platform->ypos = (
				tau_platform->ypos -
				(22.0f * platform->height) -
				GAME_PLATFORM_SHIFT_YPOS
		);
		platform->xmap = tau_platform->xmap;
		platform->ymap = (
			tau_platform->ymap -
			4.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_OMICRON_ID == id_platform) {
		platform->name = EN_PLATFORM_OMICRON_NM;
		platform->xpos = chi_platform->xpos;
		platform->ypos = (
				chi_platform->ypos -
				(26.0f * platform->height) -
				GAME_PLATFORM_SHIFT_YPOS
		);
		platform->xmap = chi_platform->xmap;
		platform->ymap = (
			chi_platform->ymap -
			5.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_SIGMA_ID == id_platform) {
		platform->name = EN_PLATFORM_SIGMA_NM;
		platform->xpos = beta_platform->xpos;
		platform->ypos = (
				beta_platform->ypos -
				(4.0f * platform->height) -
				(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
		platform->xmap = beta_platform->xmap;
		platform->ymap = (
			beta_platform->ymap -
			6.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_UPSILON_ID == id_platform) {
		platform->name = EN_PLATFORM_UPSILON_NM;
		platform->xpos = zeta_platform->xpos;
		platform->ypos = (
				zeta_platform->ypos -
				(4.0f * platform->height) -
				(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
		platform->xmap = zeta_platform->xmap;
		platform->ymap = (
			zeta_platform->ymap -
			6.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_MU_ID == id_platform) {
		platform->name = EN_PLATFORM_MU_NM;
		platform->xpos = iota_platform->xpos;
		platform->ypos = (
				iota_platform->ypos -
				(4.0f * platform->height) -
				(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
		platform->xmap = iota_platform->xmap;
		platform->ymap = (
			iota_platform->ymap -
			6.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_NU_ID == id_platform) {
		platform->name = EN_PLATFORM_NU_NM;
		platform->xpos = tau_platform->xpos;
		platform->ypos = (
				tau_platform->ypos -
				(4.0f * platform->height) -
				(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
		platform->xmap = tau_platform->xmap;
		platform->ymap = (
			tau_platform->ymap -
			6.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_PI_ID == id_platform) {
		platform->name = EN_PLATFORM_PI_NM;
		platform->xpos = chi_platform->xpos;
		platform->ypos = (
				chi_platform->ypos -
				(4.0f * platform->height) -
				(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
		platform->xmap = chi_platform->xmap;
		platform->ymap = (
			chi_platform->ymap -
			6.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_XI_ID == id_platform) {
		platform->name = EN_PLATFORM_XI_NM;
		platform->xpos = iota_platform->xpos;
		platform->ypos = (
				iota_platform->ypos -
				(10.0f * platform->height) -
				(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
		platform->xmap = iota_platform->xmap;
		platform->ymap = (
			iota_platform->ymap -
			7.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_OMEGA_ID == id_platform) {
		platform->name = EN_PLATFORM_OMEGA_NM;
		platform->xpos = beta_platform->xpos;
		platform->ypos = (
				beta_platform->ypos -
				(4.0f * platform->height) -
				(4.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
		platform->xmap = beta_platform->xmap;
		platform->ymap = (
			beta_platform->ymap -
			9.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	} else if (EN_SKY_PLATFORM_ALPHA_ID == id_platform) {
		platform->name = EN_PLATFORM_ALPHA_NM;
		platform->xpos = iota_platform->xpos;
		platform->ypos = (
				iota_platform->ypos -
				(4.0f * platform->height) -
				(4.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
		platform->xmap = iota_platform->xmap;
		platform->ymap = (
			iota_platform->ymap -
			9.0f * GAME_LVLMAP_PLATFORM_VSPACE
		);
	}
	en_init_view(g, platform->id);
}

static void en_check_platform_list(struct game * const g)
{
	int platforms[EN_PLATFORM_MAX];
	_Static_assert(
		(EN_PLATFORM_MAX * sizeof(int) == sizeof(platforms)),
		"en_check_lists: UXArraySizeError"
	);
	_Static_assert(
		EN_PLATFORM_START_ID == EN_PLATFORM_BETA_ID,
		"en_check_lists: UXPlatformStartIdError"
	);
	memset(platforms, 0xff, sizeof(platforms));
	for(int i = 0; i != EN_PLATFORM_MAX; ++i) {
		if (!g->platform_ids[i]) {
			fprintf(stderr, "%s\n", "en_check_lists: UnsetPlatformIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i != EN_PLATFORM_MAX; ++i) {
		enum enid const id_platform = g->platform_ids[i];
		struct entity * const platform = &g->ents[id_platform];
		if (EN_PLATFORM_TAG != platform->tag) {
			fprintf(stderr, "%s\n", "en_check_lists: PlatformTagError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		} else if (
				(EN_PLATFORM_START_ID > id_platform) ||
				(EN_PLATFORM_END_ID <= id_platform)
			  ) {
			fprintf(stderr, "%s\n", "en_check_lists: InvalidPlatformIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		} else if (id_platform != platform->id) {
			fprintf(stderr, "%s\n", "en_check_lists: PlatformIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}

	for(int platfno = 0; platfno != EN_PLATFORM_MAX; ++platfno) {
		int const id_platform = g->platform_ids[platfno];
		platforms[platfno] = id_platform;
	}

	for(int platfno = 0; platfno != EN_PLATFORM_MAX; ++platfno) {
		if (-1 == platforms[platfno]) {
			fprintf(stderr,
				"%s\n",
				"en_check_lists: DuplicatePlatformIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}
}

static void en_check_block_list(struct game * const g)
{
	int blocks[EN_BLOCK_MAX];
	_Static_assert(
		(EN_BLOCK_MAX * sizeof(int) == sizeof(blocks)),
		"en_check_lists: UXArraySizeError"
	);
	_Static_assert(
		EN_BLOCK_START_ID == EN_BLOCK_BETA_ID,
		"en_check_lists: UXBlockStartIdError"
	);
	memset(blocks, 0xff, sizeof(blocks));
	for(int i = 0; i != EN_BLOCK_MAX; ++i) {
		if (!g->block_ids[i]) {
			fprintf(stderr, "%s\n", "en_check_lists: UnsetBlockIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i != EN_BLOCK_MAX; ++i) {
		enum enid const id_block = g->block_ids[i];
		struct entity * const block = &g->ents[id_block];
		if (EN_BLOCK_TAG != block->tag) {
			fprintf(stderr, "%s\n", "en_check_lists: BlockTagError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		} else if (
				(EN_BLOCK_START_ID > id_block) ||
				(EN_BLOCK_END_ID <= id_block)
			  ) {
			fprintf(stderr, "%s\n", "en_check_lists: InvalidBlockIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		} else if (id_block != block->id) {
			fprintf(stderr, "%s\n", "en_check_lists: BlockIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}

	for(int blockno = 0; blockno != EN_BLOCK_MAX; ++blockno) {
		enum enid const id_block = g->block_ids[blockno];
		struct entity * const block = &g->ents[id_block];
		if (id_block != block->id) {
			fprintf(stderr, "%s\n", "en_check_lists: BlockIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
		}
		blocks[blockno] = id_block;
	}

	for(int blockno = 0; blockno != EN_BLOCK_MAX; ++blockno) {
		if (-1 == blocks[blockno]) {
			fprintf(stderr,
				"%s\n",
				"en_check_lists: DuplicateBlockIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}
}

static void en_check_enemy_list(struct game * const g)
{
	int enemys[EN_ENEMY_MAX];
	_Static_assert(
		(EN_ENEMY_MAX * sizeof(typeof(*enemys)) == sizeof(enemys)),
		"en_check_lists: UXArraySizeError"
	);
	_Static_assert(
		EN_ENEMY_START_ID == EN_ENEMY_MOTOBUG_ALPHA_ID,
		"en_check_lists: UXEnemyStartIdError"
	);
	memset(enemys, 0xff, sizeof(enemys));
	for(int i = 0; i != EN_ENEMY_MAX; ++i) {
		if (!g->enemy_ids[i]) {
			fprintf(stderr, "%s\n", "en_check_lists: UnsetEnemyIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i != EN_ENEMY_MAX; ++i) {
		if (
			(EN_ENEMY_START_ID > g->enemy_ids[i]) ||
			((EN_ENEMY_START_ID + EN_ENEMY_MAX) <= g->enemy_ids[i])
		   ) {
			fprintf(stderr, "%s\n", "en_check_lists: InvalidEnemyIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i != EN_ENEMY_MAX; ++i) {
		enum enid const id_enemy = g->enemy_ids[i];
		struct entity * const enemy = &g->ents[id_enemy];
		if (EN_ENEMY_TAG != enemy->tag) {
			fprintf(stderr, "%s\n", "en_check_lists: EnemyTagError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		} else if (
			(EN_ENEMY_START_ID > enemy->id) ||
			(EN_ENEMY_END_ID <= enemy->id)
			) {
			fprintf(stderr, "%s\n", "en_check_lists: InvalidEnemyIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		} else if (id_enemy != enemy->id) {
			fprintf(stderr, "%s\n", "en_check_lists: EnemyIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}

	for(int enemyno = 0; enemyno != EN_ENEMY_MAX; ++enemyno) {
		int const id_enemy = g->enemy_ids[enemyno];
		enemys[enemyno] = id_enemy;
	}

	for(int enemyno = 0; enemyno != EN_ENEMY_MAX; ++enemyno) {
		if (-1 == enemys[enemyno]) {
			fprintf(stderr,
				"%s\n",
				"en_check_lists: DuplicateEnemyIdError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}
}

static void en_check_lists(struct game * const g)
{
	en_check_platform_list(g);
	en_check_block_list(g);
	en_check_enemy_list(g);
}

static void en_check_names(struct game * const g)
{
	for(int i = 0; i != EN_MAXNUMOF_ENT; ++i) {
		if (!g->ent_names[i]) {
			fprintf(stderr, "%s\n", "en_check_names: NullEntityNameError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}
}

static void en_init_block(
		struct game * const g,
		enum enid const id_block
)
{
	if (
		(EN_BLOCK_BETA_ID != id_block) &&
		(EN_BLOCK_ZETA_ID != id_block)
	   ) {
		fprintf(stderr, "%s\n", "en_init_block: InvalidBlockIdError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	struct entity * const block = &g->ents[id_block];
	if (id_block != block->id) {
		fprintf(stderr, "%s\n", "en_init_block: MismatchBlockIdError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}

	if (
		(GAME_CAMERA_VIEW_WIDTH != g->screen_width) ||
		(GAME_CAMERA_VIEW_HEIGHT != g->screen_height)
	   ) {
		fprintf(stderr, "%s\n", "en_init_block: UXScreenDimsError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	float const width_game_window = g->screen_width;
	float const height_game_window = g->screen_height;
	struct entity * const beta_platform = &g->ents[EN_PLATFORM_BETA_ID];
	struct entity * const zeta_platform = &g->ents[EN_PLATFORM_ZETA_ID];
	struct enview * const mapview = &block->mapview;
	if (beta_platform->width < block->width) {
		fprintf(stderr, "%s\n", "en_init_block: BlockWidthError");
		goto handle_err;
	}
	block->xold = EN_IGNORE_PROPERTY;
	block->yold = EN_IGNORE_PROPERTY;
	block->ymin = EN_IGNORE_PROPERTY;
	block->ymax = EN_IGNORE_PROPERTY;
	block->xvel = GAME_BLOCK_XVEL;
	block->yvel = GAME_BLOCK_YVEL;
	block->xv00 = EN_IGNORE_PROPERTY;
	block->yv00 = EN_IGNORE_PROPERTY;
	block->xscr = EN_IGNORE_PROPERTY;
	block->yscr = EN_IGNORE_PROPERTY;
	block->xmap = EN_IGNORE_PROPERTY;
	block->ymap = EN_IGNORE_PROPERTY;
	block->wmap = EN_IGNORE_PROPERTY;
	block->hmap = EN_IGNORE_PROPERTY;
	block->xvcol = EN_IGNORE_PROPERTY;
	block->yvcol = EN_IGNORE_PROPERTY;
	block->width = GAME_BLOCK_WIDTH;
	block->height = GAME_BLOCK_HEIGHT;
	block->reff = 0.5f * (block->width + block->height);
	block->frameid = EN_IGNORE_PROPERTY;
	block->frameno = EN_BLOCK_DEFAULT_AF;
	block->animno = EN_BLOCK_DEFAULT_AN;
	block->tickno = EN_IGNORE_PROPERTY;
	block->view.xref = (0.5f * width_game_window);
	block->view.yref = (0.5f * height_game_window);
	block->view.width = block->width;
	block->view.height = block->height;
	memset(mapview, 0, sizeof(*mapview));
	if (EN_BLOCK_BETA_ID == id_block) {
		beta_platform->blockno = EN_BLOCK_BETA_ID;
		block->flags = 0;
		block->name = EN_BLOCK_BETA_NM;
		block->platfno = EN_PLATFORM_BETA_ID;
		block->blockno = EN_BLOCK_BETA_ID;
		block->xpos = beta_platform->xpos;
		block->ypos = (
				beta_platform->ypos -
				(0.5f * beta_platform->height) -
				(2.5f * block->height)
		);
	} else if (EN_BLOCK_ZETA_ID == id_block) {
		zeta_platform->blockno = EN_BLOCK_ZETA_ID;
		block->flags = EN_FLOOR_FLAG;
		block->name = EN_BLOCK_ZETA_NM;
		block->platfno = EN_PLATFORM_ZETA_ID;
		block->blockno = EN_BLOCK_ZETA_ID;
		block->xpos = zeta_platform->xpos;
		block->ypos = (
				zeta_platform->ypos -
				(0.5f * zeta_platform->height) -
				(0.5f * block->height)
		);
	}
	en_init_view(g, block->id);
	return;
handle_err:
	{
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
}

static void en_init_enemy(
		struct game * const g,
		enum enid const id_enemy
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
	struct entity const * const warp_platform = &g->ents[EN_WARP_PLATFORM_RHO_ID];
	if (EN_ENEMY_MOTOBUG_ALPHA_ID == enemy->id) {
		enemy->name = EN_ENEMY_MOTOBUG_ALPHA_NM;
	} else if (EN_ENEMY_MOTOBUG_GAMMA_ID == enemy->id) {
		enemy->name = EN_ENEMY_MOTOBUG_GAMMA_NM;
	} else if (EN_ENEMY_MOTOBUG_DELTA_ID == enemy->id) {
		enemy->name = EN_ENEMY_MOTOBUG_DELTA_NM;
	} else if (EN_ENEMY_MOTOBUG_THETA_ID == enemy->id) {
		enemy->name = EN_ENEMY_MOTOBUG_THETA_NM;
	} else if (EN_ENEMY_MOTOBUG_KAPPA_ID == enemy->id) {
		enemy->name = EN_ENEMY_MOTOBUG_KAPPA_NM;
	}
	enemy->xold = EN_IGNORE_PROPERTY;
	enemy->ymin = EN_IGNORE_PROPERTY;
	enemy->ymax = EN_IGNORE_PROPERTY;
	enemy->xvel = -sys_random(
		GAME_ENEMY_MOTOBUG_MIN_XVEL,
		GAME_ENEMY_MOTOBUG_MAX_XVEL
	);
	enemy->yvel = GAME_ENEMY_MOTOBUG_YVEL;
	enemy->xv00 = enemy->xvel;
	enemy->yv00 = enemy->yvel;
	enemy->xscr = EN_IGNORE_PROPERTY;
	enemy->yscr = EN_IGNORE_PROPERTY;
	enemy->xmap = EN_IGNORE_PROPERTY;
	enemy->ymap = EN_IGNORE_PROPERTY;
	enemy->wmap = EN_IGNORE_PROPERTY;
	enemy->hmap = EN_IGNORE_PROPERTY;
	enemy->xvcol = EN_IGNORE_PROPERTY;
	enemy->yvcol = EN_IGNORE_PROPERTY;
	enemy->width = enemy->animations[0].aframes[0].width;
	enemy->height = enemy->animations[0].aframes[0].height;
	enemy->reff = 0.5f * (0.5f * (enemy->width + enemy->height));
	enemy->flags = EN_FLOOR_FLAG;
	enemy->frameid = g->frameno;
	enemy->platfno = EN_WARP_PLATFORM_RHO_ID;
	enemy->blockno = EN_IGNORE_PROPERTY;
	enemy->frameno = EN_ENEMY_MOTOBUG_DEFAULT_AF;
	enemy->animno = EN_ENEMY_MOTOBUG_DEFAULT_AN;
	enemy->tickno = EN_IGNORE_PROPERTY;
	enemy->view.xref = (0.5f * width_game_window);
	enemy->view.yref = (0.5f * height_game_window);
	enemy->view.width = enemy->width;
	enemy->view.height = enemy->height;
	enemy->mapview.xref = EN_IGNORE_PROPERTY;
	enemy->mapview.yref = EN_IGNORE_PROPERTY;
	enemy->mapview.width = EN_IGNORE_PROPERTY;
	enemy->mapview.height = EN_IGNORE_PROPERTY;
	enemy->xpos = (
			warp_platform->xpos -
			(0.5f * warp_platform->width) +
			((enemy->id - EN_ENEMY_MOTOBUG_ALPHA_ID) * 1.5f * enemy->width)
	);
	enemy->ypos = (
		warp_platform->ypos -
		(0.5f * warp_platform->height) -
		(0.5f * enemy->height)
	);
	enemy->yold = enemy->ypos;
	en_init_view(g, enemy->id);
}

static void en_check_overlap(struct game * const g)
{
	for (int i = 0; i != (EN_MAXNUMOF_ENT - 1); ++i) {
		struct entity const * const ent = &g->ents[i];
		if (EN_CAMERA_TAG == ent->tag) {
			continue;
		}
		for (int j = (i + 1); j != EN_MAXNUMOF_ENT; ++j) {
			struct entity const * const other = &g->ents[j];
			float const contact = 0.5f * (ent->width + other->width);
			float const contact2 = (contact * contact);
			float const dx = (ent->xpos - other->xpos);
			float const dx2 = (dx * dx);
			if (contact2 > dx2) {
				float const dy = (ent->ypos - other->ypos);
				float const dy2 = (dy * dy);
				float const contact = (
					0.5f * (ent->height + other->height)
				);
				float const contact2 = (contact * contact);
				if (contact2 > dy2) {
					fprintf(stderr, "entity: %s\n", ent->name);
					fprintf(stderr, "entity: %s\n", other->name);
					fprintf(stderr,
						"%s\n",
						"en_check_overlap: EntityOverlapError");
					graph_unloadall_graphics(g);
					vid_close_gw(g);
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}

void en_init(struct game * const g)
{
	int count = 0;
	int platform_count = 0;
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
		if (
			(!ent->graphic.data) &&
			(EN_CAMERA_TAG != ent->tag) &&
			(EN_LVLMAP_TAG != ent->tag) &&
			(EN_BLOCK_TAG  != ent->tag)
		   ) {
			fprintf(stderr, "%s\n", "en_init: UXNoGraphicsDataEntityError\n");
			goto handle_err;
		}
		if (EN_CAMERA_TAG == ent->tag) {
			en_init_camera(g);
			++count;
		} else if (EN_LVLMAP_TAG == ent->tag) {
			en_init_lvlmap(g);
			++count;
		} else if (EN_GOAL_TAG == ent->tag) {
			en_init_goal(g);
			++count;
		} else if (EN_SONIC_TAG == ent->tag) {
			en_init_sonic(g);
			++count;
		} else if (EN_PLATFORM_TAG == ent->tag) {
			en_init_platform(g, i);
			++count;
			++platform_count;
		} else if (EN_BLOCK_TAG == ent->tag) {
			en_init_block(g, i);
			++count;
		} else if (EN_ENEMY_TAG == ent->tag) {
			en_init_enemy(g, i);
			++count;
		}
	}
	if ((EN_MAXNUMOF_ENT != count) || (EN_PLATFORM_MAX != platform_count)) {
		fprintf(stderr, "%s\n", "en_init: UXUnhandledEntitiesError");
		goto handle_err;
	}
	en_init_framebuffers(g);
	en_check_names(g);
	en_check_lists(g);
	en_check_overlap(g);
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
	if ((EN_ENEMY_TAG == ent->tag) && (ent->flags & EN_EXPLODING_FLAG)) {
		struct entity * const enemy = ent;
		int const ticks = (g->frameno - enemy->frameid);
		int aframecur = 0;
		if (an->tickcount_aframe_sequence <= ticks) {
			aframecur = (an->count - 1);
		} else {
			aframecur = (ticks / an->tickcount_aframe);
		}
		enemy->animations[animno].aframecur = aframecur;
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
	struct entity * const camera = &entities[EN_CAMERA_ID];
	struct entity * const sonic = &entities[EN_SONIC_ID];
	float const gc = GAME_GRAVITY_ACCELERATION;
	float const t = GAME_PERIOD_SEC;
	float const beacon_ypos = (
			sonic->ypos
	);
	float const base = (
			(0.5f * sonic->height)
	);
	float const dist = ((camera->ypos - beacon_ypos) / base);
	float const d2 = (dist * dist);
	float const r = (camera->ypos - sonic->ypos);
	float const r2 = (r * r);
	float const overlap = 0.5f * (camera->height + sonic->height);
	float const overlap2 = overlap * overlap;
	float const screen_height = GAME_CAMERA_VIEW_HEIGHT;
	float const screen_height2 = (screen_height * screen_height);
	float yvel = 0;
	if (!(sonic->flags & EN_PLATFORM_CONTACT_FLAG)) {
		yvel = 0.995f * (sonic->yvel + gc * t);
	} else if ((overlap2 < r2) && (screen_height2 >= r2)) {
		if (0 > sonic->view.yrel) {
			yvel = -(d2 * GAME_CAMERA_CATCHUP_YVEL);
		} else {
			yvel = (d2 * GAME_CAMERA_CATCHUP_YVEL);
		}
	} else if (screen_height2 < r2) {
		if (sonic->flags & EN_PLATFORM_CONTACT_FLAG) {
			camera->ypos = sonic->ypos;
		}
	} else {
		yvel = 0;
	}
	camera->yvel = yvel;
	camera->xvel = sonic->xvel;
	camera->xpos += (time_step * camera->xvel);
	camera->ypos += (time_step * camera->yvel);
}

// for the purposes of mapping we are okay if the entity overlaps the platform
static int en_map_platform(
		struct game * const g,
		int const entid
)
{
	if ((!GAME_SORTED_PLATFORMS) == g->sorted_platforms) {
		fprintf(stderr, "%s\n", "en_map_platform: ImplGameLogicError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	struct entity const * const ent = &g->ents[entid];
	int id_platform = -1;
	for (int i = 0; i != EN_PLATFORM_MAX; ++i) {
		int const id = g->platform_ids[i];
		struct entity const * const platform = &g->ents[id];
		if (
			((platform->xpos - 0.5f * platform->width) <= ent->xpos) &&
			((platform->xpos + 0.5f * platform->width) > ent->xpos) &&
			((platform->ypos + 0.5f * platform->height) >= ent->ypos)
		   ) {
			id_platform = id;
			break;
		}
	}
	if (-1 == id_platform) {
		fprintf(stderr, "%s\n", "en_map_platform: UXPlatformMappingError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	return id_platform;
}

static int en_check_overlapped(
		struct game * const g,
		int const block_id,
		int const id
)
{
	int rc = -1;
	struct entity const * const block = &g->ents[block_id];
	struct entity const * const ent = &g->ents[id];
	if (EN_BLOCK_TAG != block->tag) {
		fprintf(stderr, "%s\n", "en_check_rc: UXBlockTagError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	float const dx = (ent->xpos - block->xpos);
	float const dx2 = (dx * dx);
	float const contact = 0.5f * (ent->width + block->width);
	float const contact2 = (contact * contact);
	if (contact2 > dx2) {
		float const dy = (ent->ypos - block->ypos);
		float const dy2 = (dy * dy);
		float const contact = 0.5f * (ent->height + block->height);
		float const contact2 = (contact * contact);
		if (contact2 > dy2) {
			rc = EN_OVERLAP_FLAG;
		} else {
			if (0 > dy) {
				rc = EN_ABOVE_FLAG;
			} else {
				rc = EN_BELOW_FLAG;
			}
		}
	} else {
		if (0 > dx) {
			rc = EN_LEFT_FLAG;
		} else {
			rc = EN_RIGHT_FLAG;
		}
	}
	if (-1 == rc) {
		fprintf(stderr, "%s\n", "en_check_rc: ImplError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
	return rc;
}

static void en_check_blocked(
		struct game * const g,
		int const platform_id,
		int const id
)
{
	struct entity const * const platform = &g->ents[platform_id];
	struct entity * const ent = &g->ents[id];
	if (!platform->blockno) {
		return;
	}
	int const blockno = platform->blockno;
	struct entity const * const block = &g->ents[blockno];
	float const dx = (ent->xpos - block->xpos);
	if (EN_OVERLAP_FLAG == en_check_overlapped(g, block->id, ent->id)) {
		if (EN_ENEMY_TAG == ent->tag) {
			ent->xvel = -(ent->xvel);
		} else if (EN_SONIC_TAG == ent->tag) {
			ent->flags |= EN_BLOCKED_FLAG;
			ent->blockno = blockno;
			ent->xv00 = ent->xvel;
			ent->xvel = 0;
			if (0 > dx) {
				if (0 >= ent->xv00) {
					fprintf(stderr,
						"%s\n",
						"en_check_blocked: "
						"ImplBlockingError");
					graph_unloadall_graphics(g);
					vid_close_gw(g);
					exit(EXIT_FAILURE);
				}
				ent->xpos = (
						block->xpos -
						(0.5f * block->width) -
						(0.5f * ent->width)
					    );
			} else {
				if (0 <= ent->xv00) {
					fprintf(stderr,
						"%s\n",
						"en_check_blocked: "
						"ImplBlockingError");
					graph_unloadall_graphics(g);
					vid_close_gw(g);
					exit(EXIT_FAILURE);
				}
				ent->xpos = (
						block->xpos +
						(0.5f * block->width) +
						(0.5f * ent->width)
					    );
			}
		} else {
			fprintf(stderr, "%s\n", "en_check_blocked: ImplError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
	}
}

static void en_check_falling(
		struct game * const g,
		int const platform_id,
		int const id
)
{
	struct entity const * const platform = &g->ents[platform_id];
	struct entity * const ent = &g->ents[id];
	ent->frameno = 0;
	ent->tickno = 0;
	ent->yv00 = 0;
	ent->yvel = 0;
	ent->yold = 0;
	float const contact = (
			platform->ypos - 0.5f * platform->height
	);
	if (contact != (ent->ypos + 0.5f * ent->height)) {
		ent->flags ^= EN_FLOOR_FLAG;
		ent->flags |= EN_FALLING_FLAG;
		ent->frameno = g->frameno;
		ent->tickno = 1;
		ent->yv00 = 0;
		ent->yvel = 0;
		ent->yold = ent->ypos;
		if (EN_SONIC_TAG == ent->tag) {
			struct entity * const sonic = ent;
			sonic->animno = EN_SONIC_SPIN_AN;
		}
	}
}

static void en_apply_gravity(
		struct game * const g,
		int const platform_id,
		int const id
)
{
	struct entity const * const platform = &g->ents[platform_id];
	struct entity * const ent = &g->ents[id];
	float const game_period = GAME_PERIOD_SEC;
	float const time = (
			(g->frameno - ent->frameno) * game_period
	);
	float const t = time;
	float const gc = GAME_GRAVITY_ACCELERATION;
	float const floor = (
			platform->ypos -
			(0.5f * platform->height) -
			(0.5f * ent->height)
	);
	ent->yvel = (ent->yv00 + gc * t);
	ent->ypos = (
			ent->yold +
			(ent->yv00 * t) +
			(0.5f * gc * t * t)
	);
	if (ent->flags & EN_CEILING_FLAG) {
		ent->ypos = en_clamp(ent->ypos, ent->ymin, floor);
		int const id = ent->platfno;
		struct entity const * const ceiling_platform = &g->ents[id];
		if (
				(platform->xpos != ceiling_platform->xpos) ||
				(ent->flags & EN_SPRINGING_FLAG)
		   ) {
			ent->flags ^= EN_CEILING_FLAG;
			ent->flags &= (~EN_SPRINGING_FLAG);
			ent->flags |= EN_FALLING_FLAG;
			ent->frameno = g->frameno;
			ent->tickno = 1;
			ent->yold = ent->ymin;
			ent->ymin = 0;
			ent->yvel = -ent->yvcol;
			ent->yv00 = -ent->yvcol;
		}
	} else if (platform->platfno) {
		int const platfno = platform->platfno;
		int const id = g->platform_ids[platfno - 1];
		struct entity const * const ceiling_platform = &g->ents[id];
		if (platform->xpos == ceiling_platform->xpos) {
			int const ceiling = (
				ceiling_platform->ypos +
				0.5f * ceiling_platform->height +
				0.5f * ent->height
			) + 1;
			ent->ypos = en_clamp(ent->ypos, floor, ceiling);
			if (ceiling == ent->ypos) {
				ent->flags |= EN_CEILING_FLAG;
				ent->platfno = id;
				ent->yvcol = ent->yvel;
				ent->ymin = ceiling;
			}
		} else {
			ent->ypos = MIN(ent->ypos, floor);
		}
	} else {
		ent->ypos = MIN(ent->ypos, floor);
	}
	if (floor == ent->ypos) {
		if (EN_SONIC_TAG == ent->tag) {
			struct entity * const sonic = ent;
			sonic->animno = EN_SONIC_RUN_AN;
		}
		ent->flags ^= EN_FLOOR_FLAG;
		if ((EN_SONIC_TAG == ent->tag) && (!(ent->flags & EN_BLOCKED_FLAG))) {
			struct entity * const sonic = ent;
			if (!sonic->blockno) {
				ent->xvel = ent->xv00;
			}
		}
		ent->ymin = 0;
		ent->yvel = 0;
		ent->yv00 = 0;
		ent->frameno = 0;
		ent->tickno = 0;
	} else {
		if (EN_SONIC_TAG == ent->tag) {
			struct entity * const sonic = ent;
			if (sonic->flags & EN_HITTING_FLAG) {
				if (0 < sonic->yvel) {
					sonic->flags ^= EN_HITTING_FLAG;
				}
			}
		}
		ent->tickno++;
	}
}

static void en_check_hitting(struct game * const g)
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
			(enemy->flags & EN_EXPLODING_FLAG) &&
			(!enemy->tickno) &&
			(0 < sonic->yvel)
		   ) {
			sonic->flags |= EN_HITTING_FLAG;
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
	struct entity * const sonic = &entities[EN_SONIC_ID];
	int const platform_id = en_map_platform(g, sonic->id);
	struct entity const * const platform = &g->ents[platform_id];
	sonic->xmap = platform->xmap;
	sonic->ymap = platform->ymap;

	if (!(sonic->flags & EN_HITTING_FLAG)) {
		en_check_hitting(g);
	}

	if (!(sonic->flags & EN_BLOCKED_FLAG)) {
		en_check_blocked(g, platform_id, sonic->id);
	}

	if (sonic->flags & EN_FLOOR_FLAG) {
		en_check_falling(g, platform_id, sonic->id);
	} else {
		sonic->animno = EN_SONIC_SPIN_AN;
		if (!sonic->tickno) {
			sonic->flags &= (~EN_SPRINGING_FLAG);
			sonic->frameno = g->frameno;
			sonic->yv00 = -((float)GAME_SONIC_JUMP_VEL);
			sonic->yold = sonic->ypos;
			sonic->tickno++;
		} else {
			en_apply_gravity(g, platform_id, sonic->id);
		}
	}
	sonic->xpos += (time_step * sonic->xvel);
	en_update_animation(g, sonic->id, sonic->animno);
	en_set_screenview(g, sonic->id);
	en_set_mapview(g, sonic->id);
}

static void en_update_platform(
		struct game * const g,
		int const id_platform
)
{
	struct entity * const entities = g->ents;
	struct entity const * const sonic = &entities[EN_SONIC_ID];
	struct entity const * const beta_platform = &entities[EN_PLATFORM_BETA_ID];
	struct entity const * const zeta_platform = &entities[EN_PLATFORM_ZETA_ID];
	struct entity const * const iota_platform = &entities[EN_PLATFORM_IOTA_ID];
	struct entity const * const tau_platform = &entities[EN_PLATFORM_TAU_ID];
	struct entity const * const chi_platform = &entities[EN_PLATFORM_CHI_ID];
	struct entity * const platform = &entities[id_platform];
	float const xmin = (
		sonic->xpos +
		0.5f * (-(GAME_CAMERA_VIEW_WIDTH))
	);
	if (xmin >= (platform->xpos + (0.5f * platform->width))) {
		platform->xpos += (6.0f * platform->width);
		platform->ypos += GAME_PLATFORM_SHIFT_YPOS;
	}
	if (EN_WARP_PLATFORM_ETA_ID == platform->id) {
		platform->xpos = beta_platform->xpos;
		platform->ypos = beta_platform->ypos - (4.0f * platform->height);
	} else if (EN_WARP_PLATFORM_RHO_ID == platform->id) {
		platform->xpos = chi_platform->xpos;
		platform->ypos = chi_platform->ypos - (4.0f * platform->height);
	} else if (EN_SKY_PLATFORM_PSI_ID == platform->id) {
		platform->xpos = beta_platform->xpos;
		platform->ypos = (
			beta_platform->ypos -
			(10.0f * platform->height) -
			GAME_PLATFORM_SHIFT_YPOS
		);
	} else if (EN_SKY_PLATFORM_EPSILON_ID == platform->id) {
		platform->xpos = zeta_platform->xpos;
		platform->ypos = (
			zeta_platform->ypos -
			(18.0f * platform->height) -
			GAME_PLATFORM_SHIFT_YPOS
		);
	} else if (EN_SKY_PLATFORM_LAMBDA_ID == platform->id) {
		platform->xpos = tau_platform->xpos;
		platform->ypos = (
			tau_platform->ypos -
			(22.0f * platform->height) -
			GAME_PLATFORM_SHIFT_YPOS
		);
	} else if (EN_SKY_PLATFORM_OMICRON_ID == platform->id) {
		platform->xpos = chi_platform->xpos;
		platform->ypos = (
			chi_platform->ypos -
			(26.0f * platform->height) -
			GAME_PLATFORM_SHIFT_YPOS
		);
	} else if (EN_SKY_PLATFORM_SIGMA_ID == platform->id) {
		platform->xpos = beta_platform->xpos;
		platform->ypos = (
			beta_platform->ypos -
			(4.0f * platform->height) -
			(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
	} else if (EN_SKY_PLATFORM_UPSILON_ID == platform->id) {
		platform->xpos = zeta_platform->xpos;
		platform->ypos = (
			zeta_platform->ypos -
			(4.0f * platform->height) -
			(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
	} else if (EN_SKY_PLATFORM_MU_ID == platform->id) {
		platform->xpos = iota_platform->xpos;
		platform->ypos = (
			iota_platform->ypos -
			(4.0f * platform->height) -
			(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
	} else if (EN_SKY_PLATFORM_NU_ID == platform->id) {
		platform->xpos = tau_platform->xpos;
		platform->ypos = (
			tau_platform->ypos -
			(4.0f * platform->height) -
			(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
	} else if (EN_SKY_PLATFORM_PI_ID == platform->id) {
		platform->xpos = chi_platform->xpos;
		platform->ypos = (
			chi_platform->ypos -
			(4.0f * platform->height) -
			(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
	} else if (EN_SKY_PLATFORM_XI_ID == platform->id) {
		platform->xpos = iota_platform->xpos;
		platform->ypos = (
			iota_platform->ypos -
			(10.0f * platform->height) -
			(3.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
	} else if (EN_SKY_PLATFORM_OMEGA_ID == platform->id) {
		platform->xpos = beta_platform->xpos;
		platform->ypos = (
			beta_platform->ypos -
			(4.0f * platform->height) -
			(4.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
	} else if (EN_SKY_PLATFORM_ALPHA_ID == platform->id) {
		platform->xpos = iota_platform->xpos;
		platform->ypos = (
			iota_platform->ypos -
			(4.0f * platform->height) -
			(4.0f * GAME_PLATFORM_SHIFT_YPOS)
		);
	}
	en_set_screenview(g, platform->id);
}

static void en_update_block(
		struct game * const g,
		int const id_block
)
{
	struct entity const * const beta_platform = &g->ents[EN_PLATFORM_BETA_ID];
	struct entity const * const zeta_platform = &g->ents[EN_PLATFORM_ZETA_ID];
	struct entity * const block = &g->ents[id_block];
	if (EN_BLOCK_BETA_ID == block->id) {
		block->xpos = beta_platform->xpos;
		block->ypos = (
				beta_platform->ypos -
				(0.5f * beta_platform->height) -
				(3.5f * block->height)
		);
	} else if (EN_BLOCK_ZETA_ID == block->id) {
		block->xpos = zeta_platform->xpos;
		block->ypos = (
				zeta_platform->ypos -
				(0.5f * zeta_platform->height) -
				(0.5f * block->height)
		);
	}
	en_set_screenview(g, block->id);
}

static void en_check_notwarp_platform(
		struct game * const g,
		int const id_platform
)
{
	struct entity const * const platform = &g->ents[id_platform];
	if (EN_PLATFORM_TAG != platform->tag) {
		fprintf(stderr,
			"%s\n",
			"en_check_notwarp_platform: "
			"UXLeveledPlatformTagError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	} else if (
			(EN_WARP_PLATFORM_ETA_ID == platform->id) ||
			(EN_WARP_PLATFORM_RHO_ID == platform->id)
		  ) {
		fprintf(stderr,
			"%s\n",
			"en_check_notwarp_platform: "
			"UXLeveledPlatformIdError");
		graph_unloadall_graphics(g);
		vid_close_gw(g);
		exit(EXIT_FAILURE);
	}
}

static void en_update_enemy(
		struct game * const g,
		int const id_enemy
)
{
	struct entity * const enemy = &g->ents[id_enemy];
	struct entity const * const sonic = &g->ents[EN_SONIC_ID];
	float const time_step = GAME_PERIOD_SEC;
	struct entity const * warp_platform = NULL;
	float const dx = sonic->xpos - enemy->xpos;
	float const dy = sonic->ypos - enemy->ypos;
	float const r2 = (dx * dx) + (dy * dy);
	float const contact = (sonic->reff + enemy->reff);
	float const contact2 = (contact * contact);
	float const xmin = (sonic->xpos + (0.5f * (-(GAME_CAMERA_VIEW_WIDTH))));
	if (contact2 >= r2) {
		if (!(enemy->flags & EN_EXPLODING_FLAG)) {
			enemy->flags ^= EN_EXPLODING_FLAG;
			enemy->animno = EN_ENEMY_MOTOBUG_EXPLODE_AN;
			enemy->frameid = g->frameno;
			enemy->tickno = 0;
			enemy->xvel = 0;
		}
	}

	if (xmin >= enemy->xpos) {
		if (EN_WARP_PLATFORM_ETA_ID == enemy->platfno) {
			warp_platform = &g->ents[EN_WARP_PLATFORM_RHO_ID];
			enemy->xvel = -sys_random(
				GAME_ENEMY_MOTOBUG_MIN_XVEL,
				GAME_ENEMY_MOTOBUG_MAX_XVEL
			);
			enemy->platfno = EN_WARP_PLATFORM_RHO_ID;
		} else {
			warp_platform = &g->ents[EN_WARP_PLATFORM_ETA_ID];
			enemy->xvel = sys_random(
				GAME_ENEMY_MOTOBUG_MIN_XVEL,
				GAME_ENEMY_MOTOBUG_MAX_XVEL
			);
			enemy->platfno = EN_WARP_PLATFORM_ETA_ID;
		}
		enemy->xpos = (
			warp_platform->xpos -
			(0.5f * warp_platform->width) +
			((enemy->id - EN_ENEMY_MOTOBUG_ALPHA_ID) * 1.5f * enemy->width)
		);
		enemy->ypos = (
				warp_platform->ypos -
				(0.5f * warp_platform->height) -
				(0.5f * enemy->height)
		);
		enemy->flags = EN_FLOOR_FLAG;
		enemy->animno = EN_ENEMY_MOTOBUG_RUN_AN;
		enemy->frameid = 0;
		enemy->frameno = 0;
	} else {
		int min = EN_IGNORE_PROPERTY;
		int max = EN_IGNORE_PROPERTY;
		int const platform_id = en_map_platform(g, enemy->id);
		struct entity const * platform = &g->ents[platform_id];
		int const platform_next_id = g->platform_ids[(platform->platfno) + 1];
		if (enemy->flags & EN_EXPLODING_FLAG) {
			if (g->frameno != enemy->frameid) {
				enemy->tickno++;
			}
		} else {
			if (enemy->flags & EN_FLOOR_FLAG) {
				en_check_falling(g, platform_id, enemy->id);
			} else {
				en_apply_gravity(g, platform_id, enemy->id);
			}
		}

		int id = EN_IGNORE_PROPERTY;
		if (
			(platform_id == EN_WARP_PLATFORM_ETA_ID) ||
			(platform_id == EN_WARP_PLATFORM_RHO_ID)
		   ) {
			id = platform_next_id;
		} else {
			id = platform_id;
		}
		platform = &g->ents[id];
		if (EN_PLATFORM_TAG != platform->tag) {
			fprintf(stderr, "%s\n", "en_update_enemy: UXPlatformTagError");
			graph_unloadall_graphics(g);
			vid_close_gw(g);
			exit(EXIT_FAILURE);
		}
		if (0 > enemy->xvel) {
			max = ((platform->xpos + 0.5f * platform->width) - 1);
			for (int i = platform->platfno; i >= 0; --i) {
				int const id_platform = g->platform_ids[i];
				struct entity const * const other = &g->ents[id_platform];
				if (platform->ypos == other->ypos) {
					id = id_platform;
				}
			}
			platform = &g->ents[id];
			en_check_notwarp_platform(g, id);
			min = (platform->xpos - 0.5f * platform->width);
		} else {
			min = (platform->xpos - 0.5f * platform->width);
			for (int i = platform->platfno; i != EN_PLATFORM_MAX; ++i) {
				int const id_platform = g->platform_ids[i];
				struct entity const * const other = &g->ents[id_platform];
				if (platform->ypos == other->ypos) {
					id = id_platform;
				}
			}
			platform = &g->ents[id];
			en_check_notwarp_platform(g, id);
			max = ((platform->xpos + 0.5f * platform->width) - 1);
		}

		if (!(enemy->flags & EN_BLOCKED_FLAG)) {
			en_check_blocked(g, platform_id, enemy->id);
		}

		enemy->xpos += (time_step * enemy->xvel);
		enemy->xpos = en_clamp(
			enemy->xpos,
			min,
			max
		);
		if ((min == enemy->xpos) || (max == enemy->xpos)) {
			enemy->xvel = -(enemy->xvel);
		}
	}
	en_update_animation(g, enemy->id, enemy->animno);
	en_set_screenview(g, enemy->id);
}

static void en_update_goal(struct game * const g)
{
	struct entity * const goal = &g->ents[EN_GOAL_ID];
	struct entity * const platform = &g->ents[EN_PLATFORM_ALPHA_ID];
	goal->xpos = platform->xpos;
	goal->ypos = (
		platform->ypos -
		(0.5f * platform->height) -
		(0.5f * goal->height)
	);
	en_set_screenview(g, goal->id);
}

static void en_late_update_camera(struct game * const g)
{
	struct entity * const camera = &g->ents[EN_CAMERA_ID];
	struct entity const * const sonic = &g->ents[EN_SONIC_ID];
	if (EN_BLOCKED_FLAG == (sonic->flags & EN_BLOCKED_FLAG)) {
		camera->xpos = sonic->xpos;
		camera->xvel = sonic->xvel;
	}
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
			en_set_screenview(g, ent->id);
		}
		return;
	}
	en_sort_platforms(g);
	for (int i = 0; i != g->entno; ++i) {
		struct entity * const entities = g->ents;
		struct entity * const ent = &entities[i];
		if (EN_CAMERA_TAG == ent->tag) {
			en_update_camera(g);
		} else if (EN_SONIC_TAG == ent->tag) {
			en_update_sonic(g);
		} else if (EN_GOAL_TAG == ent->tag) {
			en_update_goal(g);
		} else if (EN_PLATFORM_TAG == ent->tag) {
			int const id_platform = i;
			en_update_platform(g, id_platform);
		} else if (EN_BLOCK_TAG == ent->tag) {
			int const id_block = i;
			en_update_block(g, id_block);
		} else if (EN_ENEMY_TAG == ent->tag) {
			int const id_enemy = i;
			en_update_enemy(g, id_enemy);
		}
	}
	en_late_update_camera(g);
}
