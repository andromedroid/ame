/**
 *	@file
 *	@brief		unix server side with select()
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


static	inline	int		max(int a, int b)
{
	return	(a >= b) ? a : b;
}

int		main(void)
{
	int					sfd,
						cfd,
						maxfd	= 0;
	fd_set				rfds;
	int					fdnum;
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

	FD_ZERO(&rfds);
	FD_SET(sfd, &rfds);			/* register fd to fd_set */
	maxfd	= max(maxfd, sfd);

	printf("select() then waiting...\n");
	fdnum	= select(	maxfd + 1,
						&rfds,
						NULL,
						NULL,
						NULL);	/* timeout: unlimited */

	if(fdnum < 0) {
		errexit(__func__, __LINE__);
	}
	else if(fdnum == 0) {
		printf("select() timeout.\n");
		errexit(__func__, __LINE__);
	}
	else {
		;	/* succeed */
	}

	if(FD_ISSET(sfd, &rfds)) {
		sunlen	= sizeof(sun);
		cfd	= accept(	sfd,
						(struct sockaddr*)&sun,
						&sunlen);
		if(	cfd < 0) {
			errexit(__func__, __LINE__);
		}
		printf("accept() ok.\n");
	}

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
