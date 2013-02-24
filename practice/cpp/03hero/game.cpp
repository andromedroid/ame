#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


class Hero {
	int power;

public:
	Hero() : power(100) {}
	void attack(int n);
	void attacked(int n);
};

void Hero::attack(int n)
{
	if(power <= 0) {
		cout << "power is empty.";

		return;
	}

	power -= n;

	cout << "attack !! -> " << n << " damage." << endl;
	cout << "remaining power -> " << power << "." << endl;
}

int		main(void)
{
	Hero	hoge;

	hoge.attack(5);

	return	0;
}
