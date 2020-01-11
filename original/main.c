/*	$NetBSD: main.c,v 1.21 2004/11/05 21:30:32 dsl Exp $	*/

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

int main(int, char **);

//extern const char	*Scorefile;
extern int	Max_per_uid;

int
main(ac, av)
	int	ac;
	char	**av;
{
	const char	*sp;
	bool	bad_arg;

	/* Revoke setgid privileges */
	setregid(getgid(), getgid());

	Num_games = 1;
	if (ac > 1) {
		bad_arg = FALSE;
		for (++av; ac > 1 && *av[0]; av++, ac--)
			if (av[0][0] == '-')
				for (sp = &av[0][1]; *sp; sp++)
					switch (*sp) {
					  case 'A':
						Auto_bot = TRUE;
						break;
					  case 'a':
						Start_level = 4;
						break;
					  case 'n':
						Num_games++;
						break;
					  case 'j':
						Jump = TRUE;
						break;
					  case 't':
						Teleport = TRUE;
						break;
					  
					  default:
						fprintf(stderr, "robots: unknown option: %c\n", *sp);
						bad_arg = TRUE;
						break;
					}
		if (bad_arg) {
			exit(1);
			/* NOTREACHED */
		}
	}

	initscr();
	signal(SIGINT, quit);
	cbreak();
	noecho();
	nonl();
	if (LINES != Y_SIZE || COLS != X_SIZE) {
		if (LINES < Y_SIZE || COLS < X_SIZE) {
			endwin();
			printf("Need at least a %dx%d screen\n",
			    Y_SIZE, X_SIZE);
			exit(1);
		}
		delwin(stdscr);
		stdscr = newwin(Y_SIZE, X_SIZE, 0, 0);
	}

        init_rand();
	do {
		while (Num_games--) {
			init_field();
			for (Level = Start_level; !Dead; Level++) {
				make_level();
				play_level();
				if (Auto_bot)
					sleep(1);
			}
			move(My_pos.y, My_pos.x);
			printw("AARRrrgghhhh....");
			refresh();
			if (Auto_bot)
				sleep(1);
			if (Auto_bot)
				sleep(1);
			refresh();
		}
		Num_games = 1;
	} while (!Auto_bot && another());
	quit(0);
	/* NOTREACHED */
	return(0);
}

/*
 * quit:
 *	Leave the program elegantly.
 */
void
quit(dummy)
	int dummy __attribute__((__unused__));
{
	endwin();
	exit(0);
	/* NOTREACHED */
}

/*
 * another:
 *	See if another game is desired
 */
bool
another()
{
	int	y;

	if (query("Another game?")) {
		for (y = 1; y <= Y_SIZE; y++) {
			move(y, 1);
			clrtoeol();
		}
		refresh();
		return TRUE;
	}
	return FALSE;
}
