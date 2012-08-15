/**
 *	@file
 *	@brief	master of ipc
 */

//	-----+---------+---------+---------+---------+---------+--------->>	include headers

#include	<unistd.h>
#include	<error.h>

#include	<stdio.h>
#include	<stdlib.h>

#include	"common.h"

//	-----+---------+---------+---------+---------+---------+--------->>	macro

//	-----+---------+---------+---------+---------+---------+--------->>	struct

//	-----+---------+---------+---------+---------+---------+--------->>	enum

//	-----+---------+---------+---------+---------+---------+--------->>	external function

//	-----+---------+---------+---------+---------+---------+--------->>	external variable

//	-----+---------+---------+---------+---------+---------+--------->>	grobal variable


/**
 *	@brief	main
 */
int		main(void)
{
	/* for process */
	pid_t	pid;

	/* for pipe */
	int		pipfd[2];

	/* for signal */
	struct	sigaction	act,
						old_act;

	/*
	 *	initialize
	 */
	if(	pipe(pipfd) < 0) {
		perror("pipe");
		exit(1);
	}

	pid	= fork();

	if(pid < 0) {
		perror("pipe");
		exit(1);
	}
	else if(pid == 0) {
							/* close pipe which doesn't use. */
	}
	else {
		;
	}
	

	return	0;
}
