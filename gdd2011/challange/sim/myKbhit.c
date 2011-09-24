/**
 *	@brief	my Kbhit module
 *	@note
 *		-	refer : http://d.hatena.ne.jp/peroon/20110730/1311996770
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


int		myKbhit(void)
{
	struct termios	oldt,
					newt;
	int				ch,
					oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt			= oldt;
	newt.c_lflag	&= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf			= fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF) {
		ungetc(ch, stdin);
		return	1;
	}

	return	0;
}
