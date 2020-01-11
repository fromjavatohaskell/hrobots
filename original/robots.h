/*	$NetBSD: robots.h,v 1.18 2004/01/27 20:30:30 jsm Exp $	*/

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
 *
 *	@(#)robots.h	8.1 (Berkeley) 5/31/93
 */

# include	<ctype.h>
# include       <stdbool.h>
# include       <ncurses.h>
# include	<signal.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>
# include	<termios.h>
# include	<unistd.h>

/*
 * miscellaneous constants
 */

# define	Y_FIELDSIZE	23
# define	X_FIELDSIZE	60
# define	Y_SIZE		24
# define	X_SIZE		80
# define	MAXLEVELS	4
# define	MAXROBOTS	(MAXLEVELS * 10)
# define	Y_PROMPT	(Y_FIELDSIZE - 1)
# define	X_PROMPT	(X_FIELDSIZE + 2)

/*
 * characters on screen
 */

# define	ROBOT	'+'
# define	HEAP	'*'
# define	PLAYER	'@'

/*
 * type definitions
 */

typedef struct {
	int	y, x;
} COORD;

/*
 * global variables
 */

extern bool	Dead, Running, Waiting;

extern char	Cnt_move, Field[Y_FIELDSIZE][X_FIELDSIZE], Run_ch;

extern int	Count, Level, Num_robots, Num_scrap;

extern COORD	Max, Min, My_pos, Robots[], Scrap[];

/*
 * functions types
 */

bool	another(void);
bool	do_move(int, int);
void    teleport(void);
bool	eaten(const COORD *);
void	flush_in(void);
void	get_move(void);
void	init_field(void);
void	make_level(void);
void	move_robots(void);
void	play_level(void);
int	query(const char *);
void	quit(int) __attribute__((__noreturn__));
void	reset_count(void);
COORD  *rnd_pos(void);
void    init_rand(void);
int	sign(int);
void	telmsg(int);
