#include	<iostream>
#include	<fstream>

using namespace	std;


int		main(void)
{
	char	buf[512];

//	ifstream	ifs;
//	ofstream	ofs;

//	ifs.open("input.txt");
//	ofs.open("output.txt");

	ifstream	ifs("input.txt");
	ofstream	ofs("output.txt");

	while(ifs.getline(buf, sizeof(buf))) {
		ofs << buf << endl;
	}

	return	0;
}
