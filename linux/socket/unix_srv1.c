#include	<unistd.h>
#include	<signal.h>
#include	<sys/socket.h>
#include	<sys/un.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#define	SOCKET_PATH		"/tmp/sockis"
#define	LISTEN_BACKLOG	1


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
		perror("sigaction");
		exit(1);
	}
}

int		main(void)
{
	int					sfd,
						cfd;
	struct	sockaddr_un	sun;
	socklen_t			sunlen;
	char				str[10];

	sfd	= socket(	AF_UNIX,
					SOCK_STREAM,
					0);				/* protocol */
	if(	sfd < 0) {
		perror("socket");
		exit(1);
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
		perror("bind");
		exit(1);
	}

	setSignalHandler();			/* if SIGINT then unlink(SOCKET_PATH) */

	if(	listen(	sfd,
				LISTEN_BACKLOG) < 0) {
		perror("listen");
		exit(1);
	}

	printf("accept() then waiting...\n");
	sunlen	= sizeof(sun);
	cfd	= accept(	sfd,
					(struct sockaddr*)&sun,
					&sunlen);
	if(	cfd < 0) {
		perror("accept");
		exit(1);
	}
	printf("accept() ok.\n");

	read(	cfd,
			str,
			sizeof(str));
	printf("%s\n", str);

	close(sfd);
	close(cfd);

	unlink(SOCKET_PATH);

	return	0;
}
