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

#define	MAX_EVENT_NUM	10

#include	"srv_common.c"

#define	MY_EPOLL_CTL(sfd, op, evt)		\
{										\
	ctlevt.events	= evt;				\
	ctlevt.data.fd	= sfd;				\
										\
	if(	epoll_ctl(	epfd,				\
					op,					\
					sfd,				\
					&ctlevt) < 0) {		\
		errexit(__func__, __LINE__);	\
	}									\
}

int		main(void)
{
	int					sfd1,
						sfd2,
						cfd1,
						cfd2,
						epfd,
						nfds;
	struct	epoll_event	ctlevt,
						events[MAX_EVENT_NUM],
						*p_evts;
	struct	sockaddr_un	sun;
	socklen_t			sunlen;
	char				str[STR_LENGTH];
	int					ii;

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

	epfd	= epoll_create1(0);
	if(epfd < 0) {
		errexit(__func__, __LINE__);
	}

	MY_EPOLL_CTL(sfd1, EPOLL_CTL_ADD, EPOLLIN);
	MY_EPOLL_CTL(sfd2, EPOLL_CTL_ADD, EPOLLIN);

	printf("epoll_wait() then waiting...\n");
	while('u') {
		nfds	= epoll_wait(	epfd,
								events,
								MAX_EVENT_NUM,
								-1);			/* timeout: unlimited*/

		printf(	"\n%d event occured !\n",
				nfds);

		for(ii = 0;
			ii < nfds;
			ii++) {
			p_evts	= &events[ii];

			if(p_evts->data.fd == sfd1) {
				printf("sfd1 !\n");

				UNIX_SOCK_ACCEPT(sfd1, cfd1);

				MY_EPOLL_CTL(sfd1, EPOLL_CTL_DEL, EPOLLIN);
				close(sfd1);

				MY_EPOLL_CTL(cfd1, EPOLL_CTL_ADD, EPOLLIN);
			}

			if(p_evts->data.fd == sfd2) {
				printf("sfd2 !\n");

				UNIX_SOCK_ACCEPT(sfd2, cfd2);

				MY_EPOLL_CTL(sfd2, EPOLL_CTL_DEL, EPOLLIN);
				close(sfd2);

				MY_EPOLL_CTL(cfd2, EPOLL_CTL_ADD, EPOLLIN);
			}

			if(p_evts->data.fd == cfd1) {
				if(p_evts->events & EPOLLIN) {
					printf("cfd1 R !\n");

					read(	cfd1,
							str,
							sizeof(str));
					printf("[s] %s\n", str);

					MY_EPOLL_CTL(cfd1, EPOLL_CTL_MOD, EPOLLOUT);
				}

				if(p_evts->events & EPOLLOUT) {
					printf("cfd1 W !\n");

					strncpy(	str,
								"HELLO",
								sizeof(str) - 1);

					write(	cfd1,
							str,
							sizeof(str));

					close(cfd1);
				}
			}

			if(p_evts->data.fd == cfd2) {
				if(p_evts->events & EPOLLIN) {
					printf("cfd2 R !\n");

					read(	cfd2,
							str,
							sizeof(str));
					printf("[s] %s\n", str);

					MY_EPOLL_CTL(cfd2, EPOLL_CTL_MOD, EPOLLOUT);
				}

				if(p_evts->events & EPOLLOUT) {
					printf("cfd2 W !\n");

					strncpy(	str,
								"WORLD",
								sizeof(str) - 1);

					write(	cfd2,
							str,
							sizeof(str));

					close(cfd2);
				}
			}
		}
	}

	unlink(SOCKET_PATH_CL1);
	unlink(SOCKET_PATH_CL2);

	printf("[s] bye\n");

	return	0;
}
