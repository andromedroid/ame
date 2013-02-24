#include	<iostream>
#include	<fstream>
#include	<sstream>

#include	<string.h>

using namespace	std;

typedef	unsigned int	uint;


int		main(	int		argc,
				char*	argv[])
{
	char			line[448],
					word[32];
	char			search[32];
	uint			lnum		= 0;
	ifstream		ifs(argv[2]);

//	cout << "argc: " << argc << endl;

	if(argc < 3) {
		cout << "[USAGE] " << argv[0] << " [SEARCH WORD]" << " [FILE NAME]" << endl;
	}

#if	0
	strncpy(search, argv[1], sizeof(search));

	while(ifs.getline(line, sizeof(line))) {
		lnum++;

		while(line >> word) {
			if( ! strcmp(search, word)) {
				cout << "[" << argv[1] << ":" << lnum << "] " << line << endl;
			}
		}
	}
#else
	while(ifs.getline(line, sizeof(line))) {
		istringstream	lineiss(line);

		while(lineiss >> word) {
			cout << word << endl;
			cout << line << endl;
		}
	}
#endif

	return	0;
}
