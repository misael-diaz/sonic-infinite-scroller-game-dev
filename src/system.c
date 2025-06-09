/*

sonic-infinite-scroller-game-dev                                          May 23, 2025

author: @misael-diaz
source: src/system.c

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

#include <stdlib.h>
#include <time.h>
#include "gmdefs.h"
#include "system.h"

void sys_init_random(void)
{
	long const t = time(NULL);
	long const mask = ((1L << 32) - 1L);
	long const lo = (t & mask);
	long const hi = ((t >> 32) & mask);
	unsigned int const seed = (hi ^ lo);
	unsigned int const s = (seed)? seed : (mask >> 1);
	srandom(s);
}

float sys_random(
		float const min,
		float const max
)
{
	float _min = 0;
	float _max = 0;
	if (max > min) {
		_min = min;
		_max = max;
	} else {
		_min = max;
		_max = min;
	}
	float const rand_max_inv = (1.0 / RAND_MAX);
	float const r = _min + (_max - _min) * (random() * rand_max_inv);
	return r;
}

float sys_etime(
		struct timespec const * const tep,
		struct timespec const * const tsp
)
{
	float const delta_sec = (tep->tv_sec - tsp->tv_sec);
	float const delta_nsec = (tep->tv_nsec - tsp->tv_nsec);
	float elapsed_time = (delta_sec + (1.0e-9 * delta_nsec));
	return elapsed_time;
}

void sys_delay(
		clockid_t const clockid,
		struct timespec const * const time
)
{
	time_t const sec = time->tv_sec;
	long const nsec = (time->tv_nsec + GAME_PERIOD_NS);
	struct timespec ts_walltime;
	struct timespec *twp = &ts_walltime;
	if (nsec > 999999999L) {
		twp->tv_sec = (1 + sec);
		twp->tv_nsec = (nsec % 999999999L);
	} else {
		twp->tv_sec = sec;
		twp->tv_nsec = nsec;
	}
	int const flags = TIMER_ABSTIME;
	clock_nanosleep(clockid, flags, twp, NULL);
}
