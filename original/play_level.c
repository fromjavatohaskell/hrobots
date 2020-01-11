/*	$NetBSD: play_level.c,v 1.6 2003/08/07 09:37:37 agc Exp $	*/

/*
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>

# include	"robots.h"

/*
 * play_level:
 *	Let the player play the current level
 */
void
play_level()
{
	COORD	*cp;

	wmove(stdscr, My_pos.y, My_pos.x);
	waddch(stdscr,PLAYER);
	wrefresh(stdscr);
	for (cp = Robots; cp < &Robots[MAXROBOTS]; cp++) {
		if (cp->y < 0)
			continue;
		wmove(stdscr, cp->y, cp->x);
		waddch(stdscr,ROBOT);
	}
	wrefresh(stdscr);
	flush_in();
	while (!Dead && Num_robots > 0) {
		wmove(stdscr, My_pos.y, My_pos.x);
		wrefresh(stdscr);
		get_move();
		if (Field[My_pos.y][My_pos.x] != 0)
			Dead = TRUE;
		if (!Dead)
			move_robots();
	}
}
