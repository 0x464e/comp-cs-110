#include "array_operations.hh"
#include <algorithm>

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */
int greatest_v1(int* itemptr, int size)
{
	auto greatest = *itemptr;
	for (auto i = 0; i < size; i++)
	{
		const auto& value = *(itemptr + i);
		if (greatest < value)
			greatest = value;
	}
	return greatest;
}

int greatest_v2(int* itemptr, int* endptr)
{
	return greatest_v1(itemptr, endptr - itemptr);
}

void copy(int* itemptr, int* endptr, int* targetptr)
{
	for (auto i = 0; i < endptr - itemptr; i++)
		*(targetptr + i) = *(itemptr + i);
}

void reverse(int* leftptr, int* rightptr)
{
	std::reverse(leftptr, rightptr);
}
