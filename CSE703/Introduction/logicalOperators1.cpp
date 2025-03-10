#include <iostream>

using namespace std;

int main()
{
	cout << "Enter an integer between 0 and 24: ";
	int time;
	cin >> time;

	if (time < 0 || time > 24)
	{
		cout << "You have entered invalid timw\n";
	}
	else
	{
		if (time < 10)
		{
			cout << "Good morning.\n";
		}
		else if (time < 20)
		{
			cout << "Good day.\n";
		}
		else
		{
			cout << "Good evening.\n";
		}
	}

	return 0;
}


