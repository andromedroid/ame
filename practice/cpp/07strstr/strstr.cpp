#include	<iostream>
//#include	<strstream>				/* obsolete */
#include	<sstream>

using namespace	std;


int		main(void)
{
	char	str[]	= "This is a string.";
	char	buf[32];

//	istrstream	iss(str);			/* obsolete */
	istringstream	iss(str);		/* not char but string type. */

	while(iss >> buf) {
		cout << buf << endl;
	}

	return	0;
}
