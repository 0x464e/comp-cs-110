#include <iostream>

using namespace std;

ulong factorial(int number)
{
    ulong result = 1;
    for(int i = number; i > 0; i--)
        result *= i;

    return result;
}

ulong chance(int balls, int drawn)
{
    return factorial(balls)/(factorial(balls-drawn)*factorial(drawn));
}

int main()
{
    int balls;
    int drawn;
    cout << "Enter the total number of lottery balls: ";
    cin >> balls;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn;
    if (balls <= 0)
        cout << "The number of balls must be a positive number." << endl;
    else if (drawn > balls)
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    else
        cout << "The probability of guessing all " << drawn << " balls correctly is 1/" << chance(balls, drawn) << endl;
    return EXIT_SUCCESS;
}

