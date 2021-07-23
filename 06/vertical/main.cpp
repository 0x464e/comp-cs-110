#include <iostream>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

void print_vertical(unsigned int num)
{
	RECURSIVE_FUNC


	// 2317
	auto exp = 0;
	if (1000000000 > num)
	{
		if (100000000 > num)
		{
			if (10000000 > num)
			{
				if (1000000 > num)
				{
					if (100000 > num)
					{
						if (10000 > num)
						{
							if (1000 > num)
							{
								if (100 > num)
								{
									if (10 > num)
									{
										exp = 1;
									}
									else
										exp = 10;
								}
								else
									exp = 100;
							}
							else
								exp = 1000;
						}
						else
							exp = 10000;
					}
					else
						exp = 100000;
				}
				else
					exp = 1000000;
			}
			else
				exp = 10000000;
		}
		else
			exp = 100000000;
	}
	else
		exp = 1000000000;

	const auto d = num / exp;
	cout << d << endl;
	if (10 > num)
		return;
	print_vertical(num - d * exp);
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
	unsigned int number = 0;
	cout << "Enter a number: ";
	cin >> number;
	cout << "The given number (" << number << ") written vertically:" << endl;
	print_vertical(number);
	
	return 0;
}
#endif
