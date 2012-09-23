/**
 *	@file
 *	@brief		local rules
 */

#include	<stdio.h>
#include	<stdlib.h>


static	inline	void	errexit(const char* func, int line)
{
	perror(func);
	printf(	"%s:%d\n",
			func,
			line);
	exit(EXIT_FAILURE);
}
