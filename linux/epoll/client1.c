/**
 *	@file
 *	@brief		unix client side
 */

#include	<unistd.h>
#include	<sys/socket.h>
#include	<sys/un.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"local_rules.h"


int		main(void)
{
	int					sfd;
	struct	sockaddr_un	sun;
	char				str[STR_LENGTH]	= {'a', 'b', 'c', 'd', 'e', '\0'};

	sfd	= socket(	AF_UNIX,
					SOCK_STREAM,
					0);				/* protocol */
	if(	sfd < 0) {
		errexit(__func__, __LINE__);
	}

	memset(	&sun,
			0,
			sizeof(sun));
	sun.sun_family	= AF_UNIX;
	strncpy(	sun.sun_path,
				SOCKET_PATH_CL1,
				sizeof(sun.sun_path) - 1);

	if(	connect(	sfd,
					(struct sockaddr*)&sun,
					(socklen_t)sizeof(sun)) < 0) {
		errexit(__func__, __LINE__);
	}
	printf("[c] connect() ok.\n");

	printf("[c] write\n");
	write(	sfd,
			str,
			sizeof(str));

	printf("[c] read\n");
	read(	sfd,
			str,
			sizeof(str));
	printf("[c] %s\n", str);

	printf("[c] closing...\n");

	close(sfd);

	printf("[c] bye\n");

	return	0;
}
