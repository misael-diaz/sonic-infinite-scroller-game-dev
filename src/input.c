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
#include "input.h"

#define KBD_ESC XKeysymToKeycode(dpy, XK_Escape)
#define KBD_LEFT XKeysymToKeycode(dpy, XK_Left)
#define KBD_RIGHT XKeysymToKeycode(dpy, XK_Right)
#define KBD_DOWN XKeysymToKeycode(dpy, XK_Down)
#define KBD_UP XKeysymToKeycode(dpy, XK_Up)
#define KBD_TAB XKeysymToKeycode(dpy, XK_Tab)

// Window Manager Protocol Message Handling Resource:
// https://tronche.com/gui/x/xlib/events/client-communication/client-message.html
int in_handle_input(struct game * const g)
{
	int rc = 0;
	XEvent ev = {};
	Display *dpy = g->display;
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
					}
				} else if (16 == ev.xclient.format) {
					if (close_request_short == ev.xclient.data.s[0]) {
						fprintf(stdout, "%s\n", msg_close_req);
						rc = 1;
						break;
					}
				} else if (8 == ev.xclient.format) {
					if (close_request_char == ev.xclient.data.b[0]) {
						fprintf(stdout, "%s\n", msg_close_req);
						rc = 1;
						break;
					}
				} else {
					fprintf(stdout, "%s\n", msg_unhandled_req);
					rc = 0;
					break;
				}
			}
		} else if (KeyPress == ev.type) {
			if (KBD_ESC == ev.xkey.keycode) {
				rc = 1;
				break;
			} else if (KBD_LEFT == ev.xkey.keycode) {
				fprintf(stdout, "%s\n", "left-key pressed");
				rc = 0;
				break;
			} else if (KBD_RIGHT == ev.xkey.keycode) {
				struct entity * const sonic = &g->ents[EN_SONIC_ID];
				sonic->animno = EN_SONIC_RUN_AN;
				fprintf(stdout, "%s\n", "right-key pressed");
				rc = 0;
				break;
			} else if (KBD_DOWN == ev.xkey.keycode) {
				struct entity * const sonic = &g->ents[EN_SONIC_ID];
				sonic->animno = EN_SONIC_SPIN_AN;
				fprintf(stdout, "%s\n", "down-key pressed");
				rc = 0;
				break;
			} else if (KBD_UP == ev.xkey.keycode) {
				fprintf(stdout, "%s\n", "up-key pressed");
				rc = 0;
				break;
			} else if (KBD_TAB == ev.xkey.keycode) {
				struct entity * const sonic = &g->ents[EN_SONIC_ID];
				sonic->contact = !GAME_PLATFORM_CONTACT;
				fprintf(stdout, "%s\n", "spacebar-key pressed");
				rc = 0;
				break;
			}
		} else if (KeyRelease == ev.type) {
			if (KBD_LEFT == ev.xkey.keycode) {
				fprintf(stdout, "%s\n", "left-key released");
				rc = 0;
				break;
			} else if (KBD_RIGHT == ev.xkey.keycode) {
				fprintf(stdout, "%s\n", "right-key released");
				rc = 0;
				break;
			} else if (KBD_DOWN == ev.xkey.keycode) {
				fprintf(stdout, "%s\n", "down-key released");
				rc = 0;
				break;
			} else if (KBD_UP == ev.xkey.keycode) {
				fprintf(stdout, "%s\n", "up-key released");
				rc = 0;
				break;
			} else if (KBD_TAB == ev.xkey.keycode) {
				fprintf(stdout, "%s\n", "spacebar-key released");
				rc = 0;
				break;
			}
		}
	}
	return rc;
}

