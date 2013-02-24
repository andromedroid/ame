#include	<iostream>
#include	<fstream>

using namespace	std;


int		main(	int		argc,
				char*	argv[])
{
//	cout << "argc: " << argc << endl;

	if(argc < 2) {
		cout << "[USAGE] " << argv[0] << " [FILE NAME]" << endl;
	}

	ifstream	ifs(argv[1]);
	char		buf[512];

//	while(ifs >> buf) {
	while(ifs.getline(buf, sizeof(buf))) {
		cout << buf << endl;
	}

	return	0;
}
