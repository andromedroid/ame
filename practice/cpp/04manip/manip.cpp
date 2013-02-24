#include	<iostream>
#include	<iomanip>

using namespace	std;


int		main(void)
{
	cout << setw(5) << "dec"
		 << setw(5) << "hex"
		 << setw(5) << "oct" << endl;

	for(int ii = 0;
		ii < 20;
		ii++) {
		cout << dec << setw(5) << ii
			 << hex << uppercase << setw(5) << ii
			 << oct << setw(5) << ii << endl;
	}

	return	0;
}
