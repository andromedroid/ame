/**
 *	@file
 *	@brief	pipe practice (parent -> child)
 */

//	-----+---------+---------+---------+---------+---------+--------->>	include headers

#include	<unistd.h>
#include	<error.h>
#include	<sys/wait.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

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
	pid_t	Pid;

	/* for pipe */
	int		afd_Pipe[2];
	int		i_Stat;
	char	ac_Str[5];
	int		i_Ret;

	if(	pipe(afd_Pipe) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	Pid	= fork();

	if(Pid < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	else if(Pid == 0) {							/* child */
		i_Ret	= dup2(afd_Pipe[0], STDIN_FILENO);
		if(i_Ret < 0) {
			perror("[c] dup2");
			exit(EXIT_FAILURE);
		}

		read(	STDIN_FILENO,
				ac_Str,
				sizeof(ac_Str));

		printf(	"[c] %s\n",
				ac_Str);
	}
	else {										/* parent */
		strncpy(	ac_Str,
					"ABCD",
					sizeof(ac_Str) - 1);

		printf(	"[p] %s\n",
				ac_Str);		/* if printf() after dup2(), it dones't show.  */

		i_Ret	= dup2(afd_Pipe[1], STDOUT_FILENO);
		if(i_Ret < 0) {
			perror("[p] dup2");
			exit(EXIT_FAILURE);
		}

		write(	STDOUT_FILENO,
				ac_Str,
				sizeof(ac_Str));

		waitpid(	Pid,
					&i_Stat,
					0);
	}

	return	0;
}
