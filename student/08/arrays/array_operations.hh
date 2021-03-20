#ifndef ARRAY_OPERATIONS_HH
#define ARRAY_OPERATIONS_HH

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */
int greatest_v1(const int* itemptr, int size);

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int* endptr: pointer to the memory address after the last element of the array
 * return value: the greatest element of the array
 */
int greatest_v2(const int* itemptr, const int* endptr);

/* Copies the content of the array to another array
 * int* itemptr: pointer to the first array element to be copied
 * int* endptr: pointer to the memory address after the last element of the array to be copied
 * int* targetptr: pointer to the head of the array, to which to copy
 */
void copy(const int* itemptr, const int* endptr, const int* targetptr);

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int* leftptr, int* rightptr);
#endif