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

#include	"srv_common.c"


static	inline	int		max(int a, int b)
{
	return	(a >= b) ? a : b;
}

int		main(void)
{
	int					sfd1,
						sfd2,
						cfd1	= 0,
						cfd2	= 0,
						maxfd	= 0;
	fd_set				rfds,
						wfds;
	int					fdnum;
	struct	sockaddr_un	sun;
	socklen_t			sunlen;
	char				str[STR_LENGTH];
	unsigned int		uii		= 0;

	unlink(SOCKET_PATH_CL1);
	unlink(SOCKET_PATH_CL2);

	UNIX_SOCK_BIND(sfd1, SOCKET_PATH_CL1);
	UNIX_SOCK_BIND(sfd2, SOCKET_PATH_CL2);

	setSignalHandler();			/* if SIGINT then unlink(SOCKET_PATH) */

	if(	listen(	sfd1,
				LISTEN_BACKLOG) < 0) {
		errexit(__func__, __LINE__);
	}

	if(	listen(	sfd2,
				LISTEN_BACKLOG) < 0) {
		errexit(__func__, __LINE__);
	}

	printf("select() then waiting...\n");

	while('u') {
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		maxfd	= 0;

		if(cfd1 == 0) {
			if(sfd1 != 0) {
				FD_SET(sfd1, &rfds);			/* register fd to fd_set */
				maxfd	= max(maxfd, sfd1);
			}
		}
		else {
			FD_SET(cfd1, &rfds);
			if(uii > 0) {
				FD_SET(cfd1, &wfds);
				uii	= 0;
			}
			maxfd	= max(maxfd, cfd1);
		}

		if(cfd2 == 0) {
			if(sfd2 != 0) {
				FD_SET(sfd2, &rfds);
				maxfd	= max(maxfd, sfd2);
			}
		}
		else {
			FD_SET(cfd2, &rfds);
			if(uii > 0) {
				FD_SET(cfd2, &wfds);
				uii	= 0;
			}
			maxfd	= max(maxfd, cfd2);
		}

//		printf("r:%d, w:%d\n", rfds, wfds);
		if((FD_ISSET(sfd1, &rfds)) ||
		   (FD_ISSET(sfd2, &rfds)) ||
		   (FD_ISSET(cfd1, &rfds)) ||
		   (FD_ISSET(cfd2, &rfds)) ||
		   (FD_ISSET(cfd1, &wfds)) ||
		   (FD_ISSET(cfd2, &wfds))) {
		}
		else {
			break;
		}

		fdnum	= select(	maxfd + 1,
							&rfds,
							&wfds,
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

		printf("\nevent occured !\n");

		if(FD_ISSET(sfd1, &rfds)) {
			printf("sfd1 !\n");

			UNIX_SOCK_ACCEPT(sfd1, cfd1);
			close(sfd1);
			sfd1	= 0;
		}

		if(FD_ISSET(sfd2, &rfds)) {
			printf("sfd2 !\n");

			UNIX_SOCK_ACCEPT(sfd2, cfd2);
			close(sfd2);
			sfd2	= 0;
		}

		if(FD_ISSET(cfd1, &rfds)) {
			printf("cfd1 R !\n");

			if(uii == 0) {
				read(	cfd1,
						str,
						sizeof(str));
				printf("[s] %s\n", str);

				uii++;
			}
		}

		if(FD_ISSET(cfd1, &wfds)) {
			printf("cfd1 W !\n");

			strncpy(	str,
						"HELLO",
						sizeof(str) - 1);

			write(	cfd1,
					str,
					sizeof(str));

			close(cfd1);
			cfd1	= 0;
		}

		if(FD_ISSET(cfd2, &rfds)) {
			printf("cfd2 R !\n");

			if(uii == 0) {
				read(	cfd2,
						str,
						sizeof(str));
				printf("[s] %s\n", str);

				uii++;
			}
		}

		if(FD_ISSET(cfd2, &wfds)) {
			printf("cfd2 W !\n");

			strncpy(	str,
						"WORLD",
						sizeof(str) - 1);

			write(	cfd2,
					str,
					sizeof(str));

			close(cfd2);
			cfd2	= 0;
		}
	}

	unlink(SOCKET_PATH_CL1);
	unlink(SOCKET_PATH_CL2);

	printf("[s] bye\n");

	return	0;
}
