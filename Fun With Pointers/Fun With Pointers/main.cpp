#include <iostream>
using namespace std;

int main() 
{

	//Each int is 32-bits is size, taking up 4 8-bit memory slots
	int SomeArray[10] = { 3,6,9,12,15,18,21,24,27,30 };

	
	
	int *pLocation6 = &SomeArray[6];
	int* pLocation0 = &SomeArray[0];

	//When we subtract them from each other, we see a memory location difference
	//of 24, but a subtraction difference of 6, because they are contiguous in memory
	cout << "pLocation6 = " << (int)pLocation6 << endl;
	cout << "pLocation0 = " << (int)pLocation0 << endl;
	cout << "Difference = " << pLocation6 - pLocation0 << endl;



	for (int i = 0; i < 10; i++)
	{
		cout << SomeArray + i << " = " << *(SomeArray + i) << endl;
		
	}
	cout << endl;


	for (int i = 0; i < 10; i++)
	{
		cout << pLocation0 << " = " << *pLocation0 << endl;
		pLocation0++;
	}



	cout << endl;  system("pause");
	return 0;
}