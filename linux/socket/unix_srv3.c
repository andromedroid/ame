/**
 *	@file
 *	@brief		unix server side with epoll
 */

#include	<unistd.h>
#include	<signal.h>
#include	<sys/socket.h>
#include	<sys/un.h>
#include	<sys/epoll.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"local_rules.h"

#define	SOCKET_PATH		"/tmp/sockis"
#define	LISTEN_BACKLOG	1
#define	MAX_EVENT_NUM	1


static	inline	int		max(int a, int b)
{
	return	(a >= b) ? a : b;
}

void	sigIntHandler(int i_Arg)
{
	printf("\nuser canceled. -> exit();\n");
	unlink(SOCKET_PATH);
	exit(0);
}

void	setSignalHandler(void)
{
	struct	sigaction	act;

	memset(	&act,
			0,
			sizeof(act));
	act.sa_handler	= sigIntHandler;

	if(	sigaction(	SIGINT,
					&act,
					NULL) < 0) {		/* oldact */
		errexit(__func__, __LINE__);
	}
}

int		main(void)
{
	int					sfd,
						cfd,
						epfd,
						nfds;
	struct	epoll_event	ctlevt,
						events[MAX_EVENT_NUM],
						*p_evts;
	struct	sockaddr_un	sun;
	socklen_t			sunlen;
	char				str[10];
	int					ii;

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

	epfd	= epoll_create1(0);
	if(epfd < 0) {
		errexit(__func__, __LINE__);
	}

	ctlevt.events	= EPOLLIN;
	ctlevt.data.fd	= sfd;

	if(	epoll_ctl(	epfd,
					EPOLL_CTL_ADD,
					sfd,
					&ctlevt) < 0) {
		errexit(__func__, __LINE__);
	}

	printf("epoll_wait() then waiting...\n");
	nfds	= epoll_wait(	epfd,
							events,
							MAX_EVENT_NUM,
							-1);			/* timeout: unlimited*/

	for(ii = 0;
		ii < nfds;
		ii++) {
		p_evts	= &events[ii];

		if(p_evts->data.fd == sfd) {
			sunlen	= sizeof(sun);
			cfd	= accept(	sfd,
							(struct sockaddr*)&sun,
							&sunlen);
			if(	cfd < 0) {
				errexit(__func__, __LINE__);
			}
			printf("accept() ok.\n");
		}
	}

	read(	cfd,
			str,
			sizeof(str));
	printf("%s\n", str);

	close(sfd);
	close(cfd);

	unlink(SOCKET_PATH);

	return	0;
}
