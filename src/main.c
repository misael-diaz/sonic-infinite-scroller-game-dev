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
#include <string.h>
#include <errno.h>
#include "system.h"
#include "input.h"
#include "video.h"
#include "entity.h"
#include "graphic.h"
#include "game.h"

int main(void)
{
	struct game g = {
		.ents = {},
		.platform_ids = {
			EN_PLATFORM_BETA_ID,
			EN_PLATFORM_ZETA_ID,
			EN_PLATFORM_IOTA_ID,
			EN_PLATFORM_ETA_ID,
			EN_PLATFORM_RHO_ID,
			EN_PLATFORM_TAU_ID,
			EN_PLATFORM_PHI_ID,
			EN_PLATFORM_CHI_ID,
			EN_PLATFORM_PSI_ID,
			EN_PLATFORM_EPSILON_ID,
			EN_PLATFORM_LAMBDA_ID,
			EN_PLATFORM_OMICRON_ID,
			EN_PLATFORM_SIGMA_ID,
			EN_PLATFORM_UPSILON_ID,
			EN_PLATFORM_MU_ID,
			EN_PLATFORM_NU_ID,
			EN_PLATFORM_PI_ID,
			EN_PLATFORM_XI_ID,
			EN_PLATFORM_OMEGA_ID,
			EN_PLATFORM_ALPHA_ID
		},
		.enemy_ids = {
			EN_ENEMY_MOTOBUG_ALPHA_ID,
			EN_ENEMY_MOTOBUG_GAMMA_ID,
			EN_ENEMY_MOTOBUG_DELTA_ID,
			EN_ENEMY_MOTOBUG_THETA_ID,
			EN_ENEMY_MOTOBUG_KAPPA_ID
		},
		.block_ids = {
			EN_BLOCK_ETA_ID,
			EN_BLOCK_IOTA_ID,
			EN_BLOCK_PHI_ID,
			EN_BLOCK_TAU_ID,
			EN_BLOCK_OMICRON_ID,
			EN_BLOCK_ZETA_ID
		},
		.modes = {
			GAME_GAME_MODE,
			GAME_VIEW_MODE,
			GAME_AUTO_MODE
		},
		.ent_names = {
			[EN_CAMERA_ID] = EN_CAMERA_NM,
			[EN_LVLMAP_ID] = EN_LVLMAP_NM,
			[EN_PLATFORM_BETA_ID] = EN_PLATFORM_BETA_NM,
			[EN_PLATFORM_ZETA_ID] = EN_PLATFORM_ZETA_NM,
			[EN_PLATFORM_IOTA_ID] = EN_PLATFORM_IOTA_NM,
			[EN_PLATFORM_TAU_ID] = EN_PLATFORM_TAU_NM,
			[EN_PLATFORM_PHI_ID] = EN_PLATFORM_PHI_NM,
			[EN_PLATFORM_CHI_ID] = EN_PLATFORM_CHI_NM,
			[EN_PLATFORM_ETA_ID] = EN_PLATFORM_ETA_NM,
			[EN_PLATFORM_RHO_ID] = EN_PLATFORM_RHO_NM,
			[EN_PLATFORM_PSI_ID] = EN_PLATFORM_PSI_NM,
			[EN_PLATFORM_EPSILON_ID] = EN_PLATFORM_EPSILON_NM,
			[EN_PLATFORM_LAMBDA_ID] = EN_PLATFORM_LAMBDA_NM,
			[EN_PLATFORM_OMICRON_ID] = EN_PLATFORM_OMICRON_NM,
			[EN_PLATFORM_SIGMA_ID] = EN_PLATFORM_SIGMA_NM,
			[EN_PLATFORM_UPSILON_ID] = EN_PLATFORM_UPSILON_NM,
			[EN_PLATFORM_MU_ID] = EN_PLATFORM_MU_NM,
			[EN_PLATFORM_NU_ID] = EN_PLATFORM_NU_NM,
			[EN_PLATFORM_PI_ID] = EN_PLATFORM_PI_NM,
			[EN_PLATFORM_XI_ID] = EN_PLATFORM_XI_NM,
			[EN_PLATFORM_OMEGA_ID] = EN_PLATFORM_OMEGA_NM,
			[EN_PLATFORM_ALPHA_ID] = EN_PLATFORM_ALPHA_NM,
			[EN_BLOCK_ETA_ID] = EN_BLOCK_ETA_NM,
			[EN_BLOCK_IOTA_ID] = EN_BLOCK_IOTA_NM,
			[EN_BLOCK_PHI_ID] = EN_BLOCK_PHI_NM,
			[EN_BLOCK_TAU_ID] = EN_BLOCK_TAU_NM,
			[EN_BLOCK_OMICRON_ID] = EN_BLOCK_OMICRON_NM,
			[EN_BLOCK_ZETA_ID] = EN_BLOCK_ZETA_NM,
			[EN_ENEMY_MOTOBUG_ALPHA_ID] = EN_ENEMY_MOTOBUG_ALPHA_NM,
			[EN_ENEMY_MOTOBUG_GAMMA_ID] = EN_ENEMY_MOTOBUG_GAMMA_NM,
			[EN_ENEMY_MOTOBUG_DELTA_ID] = EN_ENEMY_MOTOBUG_DELTA_NM,
			[EN_ENEMY_MOTOBUG_THETA_ID] = EN_ENEMY_MOTOBUG_THETA_NM,
			[EN_ENEMY_MOTOBUG_KAPPA_ID] = EN_ENEMY_MOTOBUG_KAPPA_NM,
			[EN_GOAL_ID] = EN_GOAL_NM,
			[EN_SONIC_ID] = EN_SONIC_NM
		},
		.supported_protocols = {
			GAME_PROTOCOL_NM,
			GAME_DELETE_WINDOW_NM,
		},
		.protocols = {},
		.display = NULL,
		.window = 0,
		.screen = NULL,
		.visual = NULL,
		.colormap = 0,
		.red = {},
		.green = {},
		.blue = {},
		.gray = {},
		.gc = 0,
		.screen_width = 0,
		.screen_height = 0,
		.screen_depth = 0,
		.protocolno = GAME_SUPPORTED_PROTOCOLS_NUM,
		.sorted_platforms = !GAME_SORTED_PLATFORMS,
		.oldframeno = 0,
		.platformno = 0,
		.enemyno = 0,
		.screeno = 0,
		.frameno = 0,
		.entno = EN_ENT_MAX,
		.modeno = 0,
		.mode = GAME_GAME_MODE,
		.init = !GAME_INITED_GW
	};
	sys_init_random();
	vid_init_gw(&g);
	vid_info_gw(&g);
	vid_check_gw(&g);
	en_init(&g);
	g_loop(&g);
	g_pause(&g);
	graph_unloadall_graphics(&g);
	vid_close_gw(&g);
	return 0;
}
