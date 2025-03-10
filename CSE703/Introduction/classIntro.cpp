#include <iostream>

using namespace std;

class Franchise
{
	public:
		void KFC()
		{
			cout << "They have the best chicken" << endl;
		}

		void BurgerKing()
		{
			cout << "They have the best burgers" << endl;
		}
};

int main()
{
	Franchise fran;
	fran.KFC();
	fran.BurgerKing();

	return 0;
}
