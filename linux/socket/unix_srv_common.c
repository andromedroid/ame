/**
 *	@file
 *	@brief		unix server side (common)
 */


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
