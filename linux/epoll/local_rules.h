/**
 *	@file
 *	@brief		local rules
 */

#include	<stdio.h>
#include	<stdlib.h>

#define	SOCKET_PATH_CL1	"./sock_cl1"
#define	SOCKET_PATH_CL2	"./sock_cl2"
#define	LISTEN_BACKLOG	1

#define	STR_LENGTH		10


static	inline	void	errexit(const char* func, int line)
{
	perror(func);
	printf(	"%s:%d\n",
			func,
			line);
	exit(EXIT_FAILURE);
}
