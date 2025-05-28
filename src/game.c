/*

sonic-infinite-scroller-game-dev                             May 23, 2025

author: @misael-diaz
source: src/game.c

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
#include "input.h"
#include "system.h"
#include "entity.h"
#include "video.h"
#include "game.h"

void g_loop(struct game * const g)
{
	struct timespec time_game_start = {};
	struct timespec time_stat_start = {};
	struct timespec time_frame_start = {};
	struct timespec time_game_end = {};
	struct timespec time_stat_end = {};
	struct timespec time_frame_current = {};
	clockid_t clockid = CLOCK_MONOTONIC;
	int const frame_stat_count_max = 64;
	float etime = 0;
	float fps = 0;
	int frame_stat_count = 0;
	clock_gettime(clockid, &time_game_start);
	time_stat_start = time_game_start;
	while (1) {
		clock_gettime(clockid, &time_frame_start);
		if (g->abort) {
			fprintf(stderr, "%s\n", g->error);
			break;
		}
		vid_draw_gw(g);
		if (in_handle_input(g)) {
			break;
		}
		en_update(g);
		++frame_stat_count;
		clock_gettime(clockid, &time_frame_current);
		sys_delay(clockid, &time_frame_current);
		if (frame_stat_count_max == frame_stat_count) {
			clock_gettime(clockid, &time_stat_end);
			etime = sys_etime(&time_stat_end, &time_stat_start);
			fps = (frame_stat_count_max / etime);
			fprintf(stdout, "g_loop: fps: %f\n", fps);
			frame_stat_count = 0;
			time_stat_start = time_stat_end;
		}
	}
	clock_gettime(clockid, &time_game_end);
	etime = sys_etime(&time_game_end, &time_game_start);
	fprintf(stdout, "g_loop: game-duration: %f sec\n", etime);
}

void g_pause(struct game const * const g)
{
	char c = 0;
	fprintf(stdout, "g_pause: Press Any Key To Continue\n");
	fread(&c, sizeof(c), 1, stdin);
}

