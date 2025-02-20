#include <iostream>

using namespace std;

int main()
{
	cout << "Enter the width of the room: ";
	int room_width {0};
	cin >> room_width;
	cout << "Enter the length of the room: ";
	int room_length {0};
	cin >> room_length;
	int area = room_width * room_length;
	cout << "The are of the room is " << area << " square feet" << endl;

	return 0;
}
