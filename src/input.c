/*

sonic-infinite-scroller-game-dev                                 May 23, 2025

author: @misael-diaz
source: src/input.c

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
#include <X11/keysym.h>
#include "graphic.h"
#include "video.h"
#include "input.h"

#define KBD_ESC XKeysymToKeycode(dpy, XK_Escape)
#define KBD_LEFT XKeysymToKeycode(dpy, XK_Left)
#define KBD_RIGHT XKeysymToKeycode(dpy, XK_Right)
#define KBD_DOWN XKeysymToKeycode(dpy, XK_Down)
#define KBD_UP XKeysymToKeycode(dpy, XK_Up)
#define KBD_TAB XKeysymToKeycode(dpy, XK_Tab)
#define KBD_M XKeysymToKeycode(dpy, XK_M)
#define KBD_B XKeysymToKeycode(dpy, XK_B)
#define KBD_E XKeysymToKeycode(dpy, XK_E)
#define KBD_P XKeysymToKeycode(dpy, XK_P)

// Window Manager Protocol Message Handling Resource:
// https://tronche.com/gui/x/xlib/events/client-communication/client-message.html
int in_handle_input(struct game * const g)
{
	int rc = 0;
	XEvent ev = {};
	Display *dpy = g->display;
	struct entity * const camera = &g->ents[EN_CAMERA_ID];
	struct entity * const sonic = &g->ents[EN_SONIC_ID];
	char const * const msg_close_req = "in_handle_input: closing-game-window";
	char const * const msg_unhandled_req = (
			"in_handle_input: WARNING unhandled-request"
	);
	long const close_request_long = g->protocols[GAME_DELETE_WINDOW_ID];
	short const close_request_short = g->protocols[GAME_DELETE_WINDOW_ID];
	char const close_request_char = g->protocols[GAME_DELETE_WINDOW_ID];
	while (XPending(g->display)) {
		XNextEvent(g->display, &ev);
		if (ClientMessage == ev.type) {
			if (g->protocols[GAME_PROTOCOL_ID] == ev.xclient.message_type) {
				if (32 == ev.xclient.format) {
					if (close_request_long == ev.xclient.data.l[0]) {
						fprintf(stdout, "%s\n", msg_close_req);
						rc = 1;
						break;
					} else {
						fprintf(stdout,
							"%s\n",
							msg_unhandled_req);
						rc = 0;
						break;
					}
				} else if (16 == ev.xclient.format) {
					if (close_request_short == ev.xclient.data.s[0]) {
						fprintf(stdout, "%s\n", msg_close_req);
						rc = 1;
						break;
					} else {
						fprintf(stdout,
							"%s\n",
							msg_unhandled_req);
						rc = 0;
						break;
					}
				} else if (8 == ev.xclient.format) {
					if (close_request_char == ev.xclient.data.b[0]) {
						fprintf(stdout, "%s\n", msg_close_req);
						rc = 1;
						break;
					} else {
						fprintf(stdout,
							"%s\n",
							msg_unhandled_req);
						rc = 0;
						break;
					}
				} else {
					fprintf(stdout, "%s\n", msg_unhandled_req);
					rc = 0;
					break;
				}
			} else {
				fprintf(stdout, "%s\n", msg_unhandled_req);
				rc = 0;
				break;
			}
		} else if (KeyPress == ev.type) {
			if (KBD_ESC == ev.xkey.keycode) {
				rc = 1;
				break;
			} else if (KBD_LEFT == ev.xkey.keycode) {
				if (GAME_VIEW_MODE == g->mode) {
					camera->xvel = -GAME_CAMERA_HOVER_XVEL;
				} else if (GAME_AUTO_MODE == g->mode) {
					if (EN_CAMERA_ID == camera->entno) {
						camera->xvel = -GAME_CAMERA_HOVER_XVEL;
					} else {
						camera->entno = EN_CAMERA_ID;
						camera->xvel = -GAME_CAMERA_HOVER_XVEL;
						camera->yvel = 0;
					}
				}
				rc = 0;
				break;
			} else if (KBD_RIGHT == ev.xkey.keycode) {
				if (GAME_VIEW_MODE == g->mode) {
					camera->xvel = GAME_CAMERA_HOVER_XVEL;
				} else if (GAME_AUTO_MODE == g->mode) {
					if (EN_CAMERA_ID == camera->entno) {
						camera->xvel = GAME_CAMERA_HOVER_XVEL;
					} else {
						camera->entno = EN_CAMERA_ID;
						camera->xvel = GAME_CAMERA_HOVER_XVEL;
						camera->yvel = 0;
					}
				} else {
					sonic->animno = EN_SONIC_RUN_AN;
				}
				rc = 0;
				break;
			} else if (KBD_DOWN == ev.xkey.keycode) {
				if (GAME_VIEW_MODE == g->mode) {
					camera->yvel = GAME_CAMERA_HOVER_YVEL;
				} else if (GAME_AUTO_MODE == g->mode) {
					if (EN_CAMERA_ID == camera->entno) {
						camera->yvel = GAME_CAMERA_HOVER_YVEL;
					} else {
						camera->entno = EN_CAMERA_ID;
						camera->xvel = 0;
						camera->yvel = GAME_CAMERA_HOVER_YVEL;
					}
				} else {
					sonic->animno = EN_SONIC_SPIN_AN;
				}
				rc = 0;
				break;
			} else if (KBD_UP == ev.xkey.keycode) {
				if (GAME_VIEW_MODE == g->mode) {
					camera->yvel = -GAME_CAMERA_HOVER_YVEL;
				} else if (GAME_AUTO_MODE == g->mode) {
					if (EN_CAMERA_ID == camera->entno) {
						camera->yvel = -GAME_CAMERA_HOVER_YVEL;
					} else {
						camera->entno = EN_CAMERA_ID;
						camera->xvel = 0;
						camera->yvel = -GAME_CAMERA_HOVER_YVEL;
					}
				}
				rc = 0;
				break;
			} else if (KBD_TAB == ev.xkey.keycode) {
				if (GAME_GAME_MODE == g->mode) {
					sonic->flags &= (~EN_FLOOR_FLAG);
					sonic->flags |= EN_SPRINGING_FLAG;
				}
				rc = 0;
				break;
			} else if (KBD_E == ev.xkey.keycode) {
				if (GAME_VIEW_MODE == g->mode) {
					int const enemyno = g->enemyno;
					int const id = g->enemy_ids[enemyno];
					struct entity const * const enemy = &g->ents[id];
					camera->xpos = enemy->xpos;
					camera->ypos = enemy->ypos;
					g->enemyno++;
					if (EN_ENEMY_MAX == g->enemyno) {
						g->enemyno = 0;
					}
				} else if (GAME_AUTO_MODE == g->mode) {
					int const enemyno = g->enemyno;
					int const entno = g->enemy_ids[enemyno];
					camera->entno = entno;
					g->enemyno++;
					if (EN_ENEMY_MAX == g->enemyno) {
						g->enemyno = 0;
					}
				}
				rc = 0;
				break;
			} else if (KBD_P == ev.xkey.keycode) {
				if (GAME_VIEW_MODE == g->mode) {
					int const platformno = g->platformno;
					int const id = g->platform_ids[platformno];
					struct entity const * const ents = g->ents;
					struct entity const * const platform = &ents[id];
					camera->xpos = platform->xpos;
					camera->ypos = platform->ypos;
					fprintf(stdout, "platform-id: %d\n", id);
					fprintf(stdout, "x: %f\t", platform->xpos);
					fprintf(stdout, "y: %f\n", platform->ypos);
					g->platformno++;
					if (EN_PLATFORM_MAX == g->platformno) {
						g->platformno = 0;
					}
				}
				rc = 0;
				break;
			} else if (KBD_M == ev.xkey.keycode) {
				if (GAME_GAME_MODE == g->mode) {
					g->oldframeno = g->frameno;
					camera->xold = camera->xpos;
					camera->yold = camera->ypos;
					camera->xv00 = camera->xvel;
					camera->yv00 = camera->yvel;
					camera->xscr = camera->view.xscr;
					camera->yscr = camera->view.yscr;
					camera->width = camera->view.width;
					camera->height = camera->view.height;
					camera->xvel = 0;
					camera->yvel = 0;
					camera->entno = EN_SONIC_ID;
				} else if (GAME_VIEW_MODE == g->mode) {
					g->frameno = g->oldframeno;
					camera->xpos = camera->xold;
					camera->ypos = camera->yold;
					camera->xvel = camera->xv00;
					camera->yvel = camera->yv00;
					camera->view.xscr = camera->xscr;
					camera->view.yscr = camera->yscr;
					camera->view.width = camera->width;
					camera->view.height = camera->height;
					camera->entno = EN_CAMERA_ID;
				} else if (GAME_AUTO_MODE == g->mode) {
					camera->entno = EN_SONIC_ID;
				} else {
					fprintf(stderr,
						"%s\n",
						"in_handle_input: UXGameModeError");
					graph_unloadall_graphics(g);
					vid_close_gw(g);
					exit(EXIT_FAILURE);
				}
				g->modeno++;
				if (GAME_MODE_MAX <= g->modeno) {
					g->modeno = 0;
				}
				g->mode = g->modes[g->modeno];
				rc = 0;
				break;
			} else if (KBD_B == ev.xkey.keycode) {
				if (GAME_VIEW_MODE == g->mode) {
					camera->xpos = camera->xold;
					camera->ypos = camera->yold;
					camera->xvel = camera->xv00;
					camera->yvel = camera->yv00;
					camera->view.xscr = camera->xscr;
					camera->view.yscr = camera->yscr;
					camera->view.width = camera->width;
					camera->view.height = camera->height;
				}
				rc = 0;
				break;
			} else {
				rc = 0;
				break;
			}
		} else if (KeyRelease == ev.type) {
			if (KBD_LEFT == ev.xkey.keycode) {
				rc = 0;
				break;
			} else if (KBD_RIGHT == ev.xkey.keycode) {
				rc = 0;
				break;
			} else if (KBD_DOWN == ev.xkey.keycode) {
				rc = 0;
				break;
			} else if (KBD_UP == ev.xkey.keycode) {
				rc = 0;
				break;
			} else if (KBD_TAB == ev.xkey.keycode) {
				rc = 0;
				break;
			} else if (KBD_M == ev.xkey.keycode) {
				rc = 0;
				break;
			} else {
				rc = 0;
				break;
			}
		} else {
			rc = 0;
			break;
		}
	}
	if (GAME_GAME_MODE == g->mode) {
		XSync(g->display, True);
	}
	return rc;
}

