/**
 *	@file
 *	@brief		unix server side
 */

#include	<unistd.h>
#include	<signal.h>
#include	<sys/socket.h>
#include	<sys/un.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"local_rules.h"

#include	"unix_srv_common.c"


int		main(void)
{
	int					sfd,
						cfd;
	struct	sockaddr_un	sun;
	socklen_t			sunlen;
	char				str[STR_LENGTH];

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

	if(	bind(	sfd,
				(struct sockaddr*)&sun,
				sizeof(sun)) < 0) {
		errexit(__func__, __LINE__);
	}

	setSignalHandler();			/* if SIGINT then unlink(SOCKET_PATH) */

	if(	listen(	sfd,
				LISTEN_BACKLOG) < 0) {
		errexit(__func__, __LINE__);
	}

	printf("accept() then waiting...\n");
	sunlen	= sizeof(sun);
	cfd	= accept(	sfd,
					(struct sockaddr*)&sun,
					&sunlen);
	if(	cfd < 0) {
		errexit(__func__, __LINE__);
	}
	printf("accept() ok.\n");

	read(	cfd,
			str,
			sizeof(str));
	printf("[s] %s\n", str);

	strncpy(	str,
				"HELLO",
				sizeof(str) - 1);

	write(	cfd,
			str,
			sizeof(str));

	close(sfd);
	close(cfd);

	unlink(SOCKET_PATH);

	printf("[s] bye\n");

	return	0;
}
