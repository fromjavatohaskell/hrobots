/*	$NetBSD: move.c,v 1.12 2004/08/27 09:07:08 christos Exp $	*/

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
#include "robots.h"

# define	ESC	'\033'

/*
 * get_move:
 *	Get and execute a move from the player
 */
void
get_move()
{
	int		c;

	if (Waiting)
		return;

	for (;;) {
		if (Running)
			c = Run_ch;
		else if (Count != 0)
			c = Cnt_move;
		else {
over:
			c = getchar();
			if (isdigit(c)) {
				Count = (c - '0');
				while (isdigit(c = getchar()))
					Count = Count * 10 + (c - '0');
				if (c == ESC)
					goto over;
				Cnt_move = c;
				if (Count)
					leaveok(stdscr, TRUE);
			}
		}

		switch (c) {
		  case ' ':
		  case '.':
			if (do_move(0, 0))
				goto ret;
			break;
		  case 'y':
			if (do_move(-1, -1))
				goto ret;
			break;
		  case 'k':
			if (do_move(-1, 0))
				goto ret;
			break;
		  case 'u':
			if (do_move(-1, 1))
				goto ret;
			break;
		  case 'h':
			if (do_move(0, -1))
				goto ret;
			break;
		  case 'l':
			if (do_move(0, 1))
				goto ret;
			break;
		  case 'b':
			if (do_move(1, -1))
				goto ret;
			break;
		  case 'j':
			if (do_move(1, 0))
				goto ret;
			break;
		  case 'n':
			if (do_move(1, 1))
				goto ret;
			break;
		  case 'Y': case 'U': case 'H': case 'J':
		  case 'K': case 'L': case 'B': case 'N':
		  case '>':
			Running = TRUE;
			if (c == '>')
				Run_ch = ' ';
			else
				Run_ch = tolower(c);
			leaveok(stdscr, TRUE);
			break;
		  case 'q':
		  case 'Q':
			if (query("Really quit?"))
				quit(0);
			wrefresh(stdscr);
			break;
		  case 'w':
		  case 'W':
			Waiting = TRUE;
			leaveok(stdscr, TRUE);
			goto ret;
		  case 't':
		  case 'T':
			Running = FALSE;
			mvwaddch(stdscr, My_pos.y, My_pos.x, ' ');
			My_pos = *rnd_pos();
			telmsg(1);
			wrefresh(stdscr);
			sleep(1);
			telmsg(0);
			mvwaddch(stdscr, My_pos.y, My_pos.x, PLAYER);
			leaveok(stdscr, FALSE);
			wrefresh(stdscr);
			flush_in();
			goto ret;
		  case CTRL('L'):
			wrefresh(stdscr);
			break;
		  case EOF:
			break;
		  default:
			putchar(CTRL('G'));
			reset_count();
			fflush(stdout);
			break;
		}
	}
ret:
	if (Count > 0)
		if (--Count == 0)
			leaveok(stdscr, FALSE);
}

/*
 * must_telep:
 *	Must I teleport; i.e., is there anywhere I can move without
 * being eaten?
 */
bool
must_telep()
{
	int		x, y;
	static COORD	newpos;

	for (y = -1; y <= 1; y++) {
		newpos.y = My_pos.y + y;
		if (newpos.y <= 0 || newpos.y >= Y_FIELDSIZE)
			continue;
		for (x = -1; x <= 1; x++) {
			newpos.x = My_pos.x + x;
			if (newpos.x <= 0 || newpos.x >= X_FIELDSIZE)
				continue;
			if (Field[newpos.y][newpos.x] > 0)
				continue;
			if (!eaten(&newpos))
				return FALSE;
		}
	}
	return TRUE;
}

/*
 * do_move:
 *	Execute a move
 */
bool
do_move(dy, dx)
	int	dy, dx;
{
	static COORD	newpos;

	newpos.y = My_pos.y + dy;
	newpos.x = My_pos.x + dx;
	if (newpos.y <= 0 || newpos.y >= Y_FIELDSIZE ||
	    newpos.x <= 0 || newpos.x >= X_FIELDSIZE ||
	    Field[newpos.y][newpos.x] > 0 || eaten(&newpos)) {
		if (Running) {
			Running = FALSE;
			leaveok(stdscr, FALSE);
			wmove(stdscr, My_pos.y, My_pos.x);
			wrefresh(stdscr);
		}
		else {
			putchar(CTRL('G'));
			reset_count();
		}
		return FALSE;
	}
	else if (dy == 0 && dx == 0)
		return TRUE;
	mvwaddch(stdscr, My_pos.y, My_pos.x, ' ');
	My_pos = newpos;
	mvwaddch(stdscr, My_pos.y, My_pos.x, PLAYER);
	wrefresh(stdscr);
	return TRUE;
}

/*
 * eaten:
 *	Player would get eaten at this place
 */
bool
eaten(pos)
	const COORD	*pos;
{
	int	x, y;

	for (y = pos->y - 1; y <= pos->y + 1; y++) {
		if (y <= 0 || y >= Y_FIELDSIZE)
			continue;
		for (x = pos->x - 1; x <= pos->x + 1; x++) {
			if (x <= 0 || x >= X_FIELDSIZE)
				continue;
			if (Field[y][x] == 1)
				return TRUE;
		}
	}
	return FALSE;
}

/*
 * reset_count:
 *	Reset the count variables
 */
void
reset_count()
{
	Count = 0;
	Running = FALSE;
	leaveok(stdscr, FALSE);
	wrefresh(stdscr);
}
