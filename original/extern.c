// Modified version Copyright (c) 2020 https://github.com/fromjavatohaskell/hrobots

/*	$NetBSD: extern.c,v 1.8 2003/08/07 09:37:36 agc Exp $	*/

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

# include	"robots.h"

bool	Dead;			/* Player is now dead */
bool	Running = FALSE;	/* Currently in the middle of a run */
bool	Waiting;		/* Player is waiting for end */

char	Cnt_move;		/* Command which has preceded the count */
char	Field[Y_FIELDSIZE][X_FIELDSIZE];	/* the playing field itslef */
char	Run_ch;			/* Character for the direction we are running */

int	Count = 0;		/* Command count */
int	Level;			/* Current level */
int	Num_robots;		/* Number of robots left */
int	Num_scrap;		/* Number of scrap heaps */

COORD	Max;			/* Max area robots take up */
COORD	Min;			/* Min area robots take up */
COORD	My_pos;			/* Player's current position */
COORD	Robots[MAXROBOTS];	/* Robots' current positions */
COORD	Scrap[MAXROBOTS];	/* ScrapHeap' current position */
