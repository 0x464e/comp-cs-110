#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int number;
    cout << "Enter a number: ";
    cin >> number;
    int cube = number*number*number;

    if (cbrt(cube) == number)
        cout << "The cube of " << number << " is " << cube << ".";
    else
        cout << "Error! The cube of " << number << " is not " << cube << ".";

    return 0;
}
