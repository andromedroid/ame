#include	<unistd.h>
#include	<sys/socket.h>
#include	<sys/un.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"local_rules.h"

#define	SOCKET_PATH		"/tmp/sockis"


int		main(void)
{
	int					sfd;
	struct	sockaddr_un	sun;
	char				str[10]	= {'A', 'B', 'C', 'D', 'E', '\0'};

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
				SOCKET_PATH,
				sizeof(sun.sun_path) - 1);

	if(	connect(	sfd,
					(struct sockaddr*)&sun,
					(socklen_t)sizeof(sun)) < 0) {
		errexit(__func__, __LINE__);
	}
	printf("connect() ok.\n");

	write(	sfd,
			str,
			6);

	close(sfd);

	return	0;
}
