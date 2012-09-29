/**
 *	@file
 *	@brief		unix server side (common)
 */


#define	UNIX_SOCK_BIND(sfd, path)						\
{														\
	sfd	= socket(	AF_UNIX,							\
					SOCK_STREAM,						\
					0);				/* protocol */		\
	if(	sfd < 0) {										\
		errexit(__func__, __LINE__);					\
	}													\
														\
	memset(	&sun,										\
			0,											\
			sizeof(sun));								\
	sun.sun_family	= AF_UNIX;							\
	strncpy(	sun.sun_path,							\
				path,									\
				sizeof(sun.sun_path) - 1);				\
														\
	if(	bind(	sfd,									\
				(struct sockaddr*)&sun,					\
				sizeof(sun)) < 0) {						\
		errexit(__func__, __LINE__);					\
	}													\
}

#define	UNIX_SOCK_ACCEPT(sfd, cfd)						\
{														\
	sunlen	= sizeof(sun);								\
	cfd	= accept(	sfd,								\
					(struct sockaddr*)&sun,				\
					&sunlen);							\
	if(	cfd < 0) {										\
		errexit(__func__, __LINE__);					\
	}													\
	printf("[s] accept() ok.\n");						\
}

void	sigIntHandler(int i_Arg)
{
	printf("\nuser canceled. -> exit();\n");
	unlink(SOCKET_PATH_CL1);
	unlink(SOCKET_PATH_CL2);
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
