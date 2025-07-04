#ifndef SONIC_INFINITE_SCROLLER_GAME_DEV_ENTDEFS_H
#define SONIC_INFINITE_SCROLLER_GAME_DEV_ENTDEFS_H

#include "gmdefs.h"

#define EN_ENVIEW_NUMFACES 4

/* if a property is set to this that means that it has no meaning for that entity */

#define EN_IGNORE_PROPERTY 0

/*

E: East,  aligned with the screen +x-axis
N: Nort,  aligned with the screen +y-axis
W: West,  aligned with the screen -x-axis
S: South, aligned with the screen -y-axis

*/

#define EN_ENVIEW_E 0
#define EN_ENVIEW_N 1
#define EN_ENVIEW_W 2
#define EN_ENVIEW_S 3

#define EN_ANIMATIONS_COUNT 2
#define EN_AFRAME_COUNT 8

#define EN_CAMERA_DEFAULT_AN 0
#define EN_CAMERA_DEFAULT_AF 0

#define EN_LVLMAP_DEFAULT_AN 0
#define EN_LVLMAP_DEFAULT_AF 0

#define EN_GOAL_DEFAULT_AN 0
#define EN_GOAL_DEFAULT_AF 0

#define EN_SONIC_RUN_AN 0
#define EN_SONIC_SPIN_AN 1
#define EN_SONIC_DEFAULT_AF 0

#define EN_PLATFORM_DEFAULT_AN 0
#define EN_PLATFORM_DEFAULT_AF 0

#define EN_BLOCK_DEFAULT_AN 0
#define EN_BLOCK_DEFAULT_AF 0

#define EN_ENEMY_MOTOBUG_DEFAULT_AN 0
#define EN_ENEMY_MOTOBUG_DEFAULT_AF 0
#define EN_ENEMY_MOTOBUG_RUN_AN 0
#define EN_ENEMY_MOTOBUG_EXPLODE_AN 1

#define EN_GOAL_AFRAME_COUNT 1
#define EN_PLATFORM_AFRAME_COUNT 1
#define EN_SONIC_AFRAME_COUNT EN_AFRAME_COUNT
#define EN_SONIC_ANIMATIONS_COUNT EN_ANIMATIONS_COUNT
#define EN_ENEMY_MOTOBUG_ANIMATIONS_COUNT EN_ANIMATIONS_COUNT
#define EN_ENEMY_MOTOBUG_AFRAME_COUNT 5 
_Static_assert(EN_SONIC_AFRAME_COUNT == EN_AFRAME_COUNT, "UXAframeCountError");

#define EN_SONIC_RUN_FRAME_NAME "run"
#define EN_SONIC_SPIN_FRAME_NAME "spin"
#define EN_BLOCK_FRAME_NAME "block"
#define EN_GOAL_FRAME_NAME "goal"
#define EN_PLATFORM_FRAME_NAME "scroll"
#define EN_ENEMY_MOTOBUG_RUN_FRAME_NAME "bobbing"
#define EN_ENEMY_MOTOBUG_EXPLODE_FRAME_NAME "exploding"
#define EN_LVLMAP_FRAME_NAME "display"
#define EN_CAMERA_FRAME_NAME "hover"

#define EN_CAMERA_NM "camera"
#define EN_LVLMAP_NM "map"
#define EN_PLATFORM_BETA_NM "platform_beta"
#define EN_PLATFORM_ZETA_NM "platform_zeta"
#define EN_PLATFORM_IOTA_NM "platform_iota"
#define EN_PLATFORM_TAU_NM "platform_tau"
#define EN_PLATFORM_PHI_NM "platform_phi"
#define EN_PLATFORM_CHI_NM "platform_chi"
#define EN_PLATFORM_ETA_NM "platform_eta"
#define EN_PLATFORM_RHO_NM "platform_rho"
#define EN_PLATFORM_PSI_NM "platform_psi"
#define EN_PLATFORM_EPSILON_NM "platform_epsilon"
#define EN_PLATFORM_LAMBDA_NM "platform_lambda"
#define EN_PLATFORM_OMICRON_NM "platform_omicron"
#define EN_PLATFORM_SIGMA_NM "platform_sigma"
#define EN_PLATFORM_UPSILON_NM "platform_upsilon"
#define EN_PLATFORM_MU_NM "platform_mu"
#define EN_PLATFORM_NU_NM "platform_nu"
#define EN_PLATFORM_PI_NM "platform_pi"
#define EN_PLATFORM_XI_NM "platform_xi"
#define EN_PLATFORM_OMEGA_NM "platform_omega"
#define EN_PLATFORM_ALPHA_NM "platform_alpha"
#define EN_BLOCK_ETA_NM "block_eta"
#define EN_BLOCK_IOTA_NM "block_iota"
#define EN_BLOCK_PHI_NM "block_phi"
#define EN_BLOCK_TAU_NM "block_tau"
#define EN_BLOCK_OMICRON_NM "block_omicron"
#define EN_BLOCK_ZETA_NM "block_zeta"
#define EN_ENEMY_MOTOBUG_ALPHA_NM "enemy_motobug_alpha"
#define EN_ENEMY_MOTOBUG_GAMMA_NM "enemy_motobug_gamma"
#define EN_ENEMY_MOTOBUG_DELTA_NM "enemy_motobug_delta"
#define EN_ENEMY_MOTOBUG_THETA_NM "enemy_motobug_theta"
#define EN_ENEMY_MOTOBUG_KAPPA_NM "enemy_motobug_kappa"
#define EN_GOAL_NM "goal"
#define EN_SONIC_NM "sonic"

#endif

/*

sonic-infinite-scroller-game-dev                                 May 23, 2025

author: @misael-diaz
source: src/endefs.h

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
